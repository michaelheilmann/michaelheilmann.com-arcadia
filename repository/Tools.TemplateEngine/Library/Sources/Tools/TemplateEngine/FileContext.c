// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

// Last modified: 2024-09-09

#include "Tools/TemplateEngine/FileContext.h"

static R_BooleanValue
is
  (
    FileContext* context,
    uint32_t expectedCodePoint
  )
{
  if (!R_Utf8Reader_hasCodePoint(context->source)) {
    return R_BooleanValue_False;
  }
  R_Natural32Value currentCodePoint = R_Utf8Reader_getCodePoint(context->source);
  return expectedCodePoint == currentCodePoint;
}

static R_BooleanValue
isSign
  (
    FileContext* context
  )
{
  return is(context, '+') || is(context, '-');
}

static R_BooleanValue
isLetter
  (
    FileContext* context
  )
{
  if (!R_Utf8Reader_hasCodePoint(context->source)) {
    return R_BooleanValue_False;
  }
  R_Natural32Value current = R_Utf8Reader_getCodePoint(context->source);
  return ('A' <= current && current <= 'Z')
      || ('a' <= current && current <= 'z');
}

static R_BooleanValue
isDigit
  (
    FileContext* context
  )
{
  if (!R_Utf8Reader_hasCodePoint(context->source)) {
    return R_BooleanValue_False;
  }
  R_Natural32Value current = R_Utf8Reader_getCodePoint(context->source);
  return ('0' <= current && current <= '9');
}

static R_BooleanValue
isUnderscore
  (
    FileContext* context
  )
{
  return is(context, '_');
}

static R_BooleanValue
isLeftParenthesis
  (
    FileContext* context
  )
{
  return is(context, '(');
}

static R_BooleanValue
isRightParenthesis
  (
    FileContext* context
  )
{
  return is(context, ')');
}


static void
onIdentifier
  (
    FileContext* context
  )
{
  if (!isUnderscore(context) && !isLetter(context)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  do {                                              
    R_Natural32Value targetCodePoint = R_Utf8Reader_getCodePoint(context->source);
    R_Utf8Writer_writeCodePoints(context->context->temporary, &targetCodePoint, 1);
    R_Utf8Reader_next(context->source);
  } while (isUnderscore(context) || isLetter(context) || isDigit(context));
}

static void
onString
  (
    FileContext* context
  )
{
  if (!is(context, '"')) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Utf8Reader_next(context->source);

  R_BooleanValue lastWasSlash = R_BooleanValue_False;
  while (true) {
    if (!R_Utf8Reader_hasCodePoint(context->source)) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    R_Natural32Value current = R_Utf8Reader_getCodePoint(context->source);
    if (lastWasSlash) {
      switch (current) {
        case '\\': {
          R_Natural32Value targetCodePoint = '\\';
          R_Utf8Writer_writeCodePoints(context->context->temporary, &targetCodePoint, 1);
          lastWasSlash = R_BooleanValue_False;
        } break;
        case '"': {
          R_Natural32Value targetCodePoint = '"';
          R_Utf8Writer_writeCodePoints(context->context->temporary, &targetCodePoint, 1);
          lastWasSlash = R_BooleanValue_False;
        } break;
        default: {
          R_setStatus(R_Status_ArgumentValueInvalid);
          R_jump();
        } break;
      };
    } else {
      if (current == '"') {
        R_Utf8Reader_next(context->source);
        return;
      } else if (current == '\\') {
        lastWasSlash = R_BooleanValue_True;
        R_Utf8Reader_next(context->source);
      } else {
        R_Utf8Writer_writeCodePoints(context->context->temporary, &current, 1);
        R_Utf8Reader_next(context->source);
      }
    }
  }
  R_setStatus(R_Status_ArgumentValueInvalid);
  R_jump();
}

static void
onIncludeDirective
  (
    FileContext* context
  )
{
  if (!isLeftParenthesis(context)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Utf8Reader_next(context->source);
  R_ByteBuffer_clear(context->context->temporaryBuffer);
  onString(context);
  R_FilePath* filePath = R_FilePath_parseWindowsFilePath(context->context->temporaryBuffer->p, context->context->temporaryBuffer->sz);
  R_Value value;
  R_Value_setObjectReferenceValue(&value, filePath);
  R_Stack_push(context->context->stack, value);
  if (!isRightParenthesis(context)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Utf8Reader_next(context->source);
}

static void
onStatement
  (
    FileContext* context
  )
{
  R_ByteBuffer_clear(context->context->temporaryBuffer);
  onIdentifier(context);
  if (R_ByteBuffer_isEqualTo_pn(context->context->temporaryBuffer, "include", sizeof("include") - 1)) {
    onIncludeDirective(context);
    Context_onRun(context->context);
  } else {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
}

static void
onDirective
  (
    FileContext* context
  )
{
  if (!R_Utf8Reader_hasCodePoint(context->source)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Natural32Value current = R_Utf8Reader_getCodePoint(context->source);
  switch (current) {
    case '@': {
      R_Natural32Value targetCodePoint = '@';
      R_Utf8Writer_writeCodePoints(context->context->target, &targetCodePoint, 1);
      R_Utf8Reader_next(context->source);
    } break;
    case '{': {
      R_Utf8Reader_next(context->source);
      onStatement(context);
      if (!is(context, '}')) {
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      }
      R_Utf8Reader_next(context->source);
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  };
}

static void
FileContext_finalize
  (
    FileContext* self
  )
{/*Intentionally empty.*/}

static void
FileContext_visit
  (
    FileContext* self
  )
{
  R_Object_visit(self->context);
  R_Object_visit(self->sourceFilePath);
  R_Object_visit(self->source);
}

void
FileContext_registerType
  (
  )
{
  R_registerObjectType("Tools.TemplateEngine.FileContext", sizeof("Tools.TemplateEngine.FileContext") - 1, sizeof(FileContext), NULL, &FileContext_visit, &FileContext_finalize);
}

FileContext*
FileContext_create
  (
    Context* context,
    R_FilePath* sourceFilePath
  )
{
  FileContext* self = R_allocateObject(R_getObjectType("Tools.TemplateEngine.FileContext", sizeof("Tools.TemplateEngine.FileContext") - 1));
  self->context = context;
  self->sourceFilePath = sourceFilePath;
  self->source = NULL;
  return self;
}

void
FileContext_execute
  (
    FileContext* context
  )
{
  while (R_Utf8Reader_hasCodePoint(context->source)) {
    R_Natural32Value sourceCodePoint = R_Utf8Reader_getCodePoint(context->source);
    if (sourceCodePoint == '@') {
      R_Utf8Reader_next(context->source);
      onDirective(context);
    } else {
      R_Natural32Value targetCodePoint = sourceCodePoint;
      R_Utf8Writer_writeCodePoints(context->context->target, &targetCodePoint, 1);
      R_Utf8Reader_next(context->source);
    }
  }
}
