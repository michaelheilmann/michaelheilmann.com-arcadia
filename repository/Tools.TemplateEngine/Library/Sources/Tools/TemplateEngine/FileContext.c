// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R/ArgumentsValidation.h"

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    FileContext* context,
    uint32_t expectedCodePoint
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value currentCodePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
  return expectedCodePoint == currentCodePoint;
}

static Arcadia_BooleanValue
isSign
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return is(thread, context, '+') || is(thread, context, '-');
}

static Arcadia_BooleanValue
isLetter
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
  return ('A' <= current && current <= 'Z')
      || ('a' <= current && current <= 'z');
}

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
  return ('0' <= current && current <= '9');
}

static Arcadia_BooleanValue
isUnderscore
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return is(thread, context, '_');
}

static Arcadia_BooleanValue
isLeftParenthesis
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return is(thread, context, '(');
}

static Arcadia_BooleanValue
isRightParenthesis
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return is(thread, context, ')');
}

static void
onIdentifier
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!isUnderscore(thread, context) && !isLetter(thread, context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  do {
    Arcadia_Natural32Value targetCodePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
    Arcadia_Utf8Writer_writeCodePoints(thread, context->context->temporary, &targetCodePoint, 1);
    Arcadia_Utf8Reader_next(thread, context->source);
  } while (isUnderscore(thread, context) || isLetter(thread, context) || isDigit(thread, context));
}

static void
onString
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!is(thread, context, '"')) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Utf8Reader_next(thread, context->source);

  Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
  while (true) {
    if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Natural32Value current = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
    if (lastWasSlash) {
      switch (current) {
        case '\\': {
          Arcadia_Natural32Value targetCodePoint = '\\';
          Arcadia_Utf8Writer_writeCodePoints(thread, context->context->temporary, &targetCodePoint, 1);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        case '"': {
          Arcadia_Natural32Value targetCodePoint = '"';
          Arcadia_Utf8Writer_writeCodePoints(thread, context->context->temporary, &targetCodePoint, 1);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        default: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        } break;
      };
    } else {
      if (current == '"') {
        Arcadia_Utf8Reader_next(thread, context->source);
        return;
      } else if (current == '\\') {
        lastWasSlash = Arcadia_BooleanValue_True;
        Arcadia_Utf8Reader_next(thread, context->source);
      } else {
        Arcadia_Utf8Writer_writeCodePoints(thread, context->context->temporary, &current, 1);
        Arcadia_Utf8Reader_next(thread, context->source);
      }
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

static void
onIncludeDirective
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!isLeftParenthesis(thread, context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Utf8Reader_next(thread, context->source);
  Arcadia_ByteBuffer_clear(thread, context->context->temporaryBuffer);
  onString(thread, context);
  Arcadia_FilePath* filePath = Arcadia_FilePath_parseWindows(thread, context->context->temporaryBuffer->p, context->context->temporaryBuffer->sz);
  Arcadia_Value value;
  Arcadia_Value_setObjectReferenceValue(&value, filePath);
  Arcadia_Stack_push(thread, context->context->stack, value);
  if (!isRightParenthesis(thread, context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Utf8Reader_next(thread, context->source);
}

static void
onStatement
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  Arcadia_ByteBuffer_clear(thread, context->context->temporaryBuffer);
  onIdentifier(thread, context);
  if (Arcadia_ByteBuffer_isEqualTo_pn(thread, context->context->temporaryBuffer, "include", sizeof("include") - 1)) {
    onIncludeDirective(thread, context);
    Context_onRun(thread, context->context);
  } else {
    Arcadia_Value t;
    Arcadia_Value_setObjectReferenceValue(&t, (Arcadia_ObjectReferenceValue)context->context->temporaryBuffer);
    Arcadia_Value_setObjectReferenceValue(&t, (Arcadia_ObjectReferenceValue)Arcadia_String_create(thread, t));
    t = Arcadia_Map_get(thread, context->environment, t);
    if (!Arcadia_Value_isObjectReferenceValue(&t)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&t);
    if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(object), _Arcadia_String_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_ByteBuffer_append_pn(thread, context->context->targetBuffer, Arcadia_String_getBytes(thread, (Arcadia_String*)object), Arcadia_String_getNumberOfBytes(thread, (Arcadia_String*)object));
  }
}

static void
onDirective
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural32Value current = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
  switch (current) {
    case '@': {
      Arcadia_Natural32Value targetCodePoint = '@';
      Arcadia_Utf8Writer_writeCodePoints(thread, context->context->target, &targetCodePoint, 1);
      Arcadia_Utf8Reader_next(thread, context->source);
    } break;
    case '{': {
      Arcadia_Utf8Reader_next(thread, context->source);
      onStatement(thread, context);
      if (!is(thread, context, '}')) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Utf8Reader_next(thread, context->source);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static void
FileContext_destruct
  (
    Arcadia_Thread* thread,
    FileContext* self
  );

static void
FileContext_visit
  (
    Arcadia_Thread* thread,
    FileContext* self
  );

static void
FileContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &FileContext_constructImpl,
  .destruct = &FileContext_destruct,
  .visit = &FileContext_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"Tools.TemplateEngine.FileContext", FileContext, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
FileContext_destruct
  (
    Arcadia_Thread* thread,
    FileContext* self
  )
{/*Intentionally empty.*/}

static void
FileContext_visit
  (
    Arcadia_Thread* thread,
    FileContext* self
  )
{
  Arcadia_Object_visit(thread, self->context);
  Arcadia_Object_visit(thread, self->sourceFilePath);
  Arcadia_Object_visit(thread, self->source);
  Arcadia_Object_visit(thread, self->environment);
}

static void
FileContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  FileContext* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _FileContext_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->context = (Context*)R_Argument_getObjectReferenceValue(thread, &argumentValues[0], _Context_getType(thread));
  _self->sourceFilePath = (Arcadia_FilePath*)R_Argument_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_FilePath_getType(thread));
  _self->source = NULL;
  _self->environment = Arcadia_Map_create(thread);
  Arcadia_Value k, v;
  Arcadia_Value_setObjectReferenceValue(&k, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"siteAddress", sizeof(u8"siteAddress") - 1)));
  Arcadia_Value_setObjectReferenceValue(&v, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"https://michaelheilmann.com", sizeof(u8"https://michaelheilmann.com") - 1)));
  Arcadia_Map_set(thread, _self->environment, k, v);
  Arcadia_Object_setType(thread, _self, _type);
}

FileContext*
FileContext_create
  (
    Arcadia_Thread* thread,
    Context* context,
    Arcadia_FilePath* sourceFilePath
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)context },
                               {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)sourceFilePath }, };
  FileContext* self = Arcadia_allocateObject(thread, _FileContext_getType(thread), 2, &argumentValues[0]);
  return self;
}

void
FileContext_execute
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  while (Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    Arcadia_Natural32Value sourceCodePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
    if (sourceCodePoint == '@') {
      Arcadia_Utf8Reader_next(thread, context->source);
      onDirective(thread, context);
    } else {
      Arcadia_Natural32Value targetCodePoint = sourceCodePoint;
      Arcadia_Utf8Writer_writeCodePoints(thread, context->context->target, &targetCodePoint, 1);
      Arcadia_Utf8Reader_next(thread, context->source);
    }
  }
}
