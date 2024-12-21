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
  R_FilePath* filePath = R_FilePath_parseWindows(context->context->temporaryBuffer->p, context->context->temporaryBuffer->sz);
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
    R_Value t;
    R_Value_setObjectReferenceValue(&t, (R_ObjectReferenceValue)context->context->temporaryBuffer);
    R_Value_setObjectReferenceValue(&t, (R_ObjectReferenceValue)R_String_create(t));
    t = R_Map_get(context->environment, t);
    if (!R_Value_isObjectReferenceValue(&t)) {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
    R_Object* object = R_Value_getObjectReferenceValue(&t);
    if (!R_Type_isSubType(R_Object_getType(object), _R_String_getType())) {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
    R_ByteBuffer_append_pn( context->context->targetBuffer, R_String_getBytes((R_String*)object), R_String_getNumberOfBytes((R_String*)object));
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
FileContext_destruct
  (
    FileContext* self
  );

static void
FileContext_visit
  (
    FileContext* self
  );

static void
FileContext_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &FileContext_constructImpl,
  .destruct = &FileContext_destruct,
  .visit = &FileContext_visit,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("Tools.TemplateEngine.FileContext", FileContext, "R.Object", R_Object, &_typeOperations);

static void
FileContext_destruct
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
  R_Object_visit(self->environment);
}

static void
FileContext_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  FileContext* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _FileContext_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _Context_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[1]), _R_FilePath_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  _self->context = R_Value_getObjectReferenceValue(&argumentValues[0]);
  _self->sourceFilePath = R_Value_getObjectReferenceValue(&argumentValues[1]);
  _self->source = NULL;
  _self->environment = R_Map_create();
  R_Value k, v;
  R_Value_setObjectReferenceValue(&k, (R_ObjectReferenceValue)R_String_create_pn(R_ImmutableByteArray_create("siteAddress", sizeof("siteAddress") - 1)));
  R_Value_setObjectReferenceValue(&v, (R_ObjectReferenceValue)R_String_create_pn(R_ImmutableByteArray_create("https://michaelheilmann.com", sizeof("https://michaelheilmann.com") - 1)));
  R_Map_set(_self->environment, k, v);
  R_Object_setType((R_Object*)_self, _type);
}

FileContext*
FileContext_create
  (
    Context* context,
    R_FilePath* sourceFilePath
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)context },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)sourceFilePath }, };
  FileContext* self = R_allocateObject(_FileContext_getType(), 2, &argumentValues[0]);
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
