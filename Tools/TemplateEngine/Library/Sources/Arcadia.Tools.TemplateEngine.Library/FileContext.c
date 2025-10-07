// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia.Tools.TemplateEngine.Library/FileContext.h"

#include "Arcadia.Tools.TemplateEngine.Library/Ast.h"
#include "Arcadia.Tools.TemplateEngine.Library/Context.h"
#include "Arcadia.Tools.TemplateEngine.Library/Environment.h"

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

static Arcadia_String*
getLiteral
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, context->context->temporaryBuffer->p, context->context->temporaryBuffer->sz));
}

static void
evalInvoke
  (
    Arcadia_Thread* thread,
    FileContext* context,
    Ast* ast
  )
{
  Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)ast->name);
  Arcadia_Value v = Environment_get(thread, context->environment, k, Arcadia_BooleanValue_True);
  if (Arcadia_Value_isVoidValue(&v)) {
    // Error.
    Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
    Arcadia_StringBuffer_insertBack(thread, sb, k);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` not defined\n");
    fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Value_isForeignProcedureValue(&v)) {
    // Error.
    Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
    Arcadia_StringBuffer_insertBack(thread, sb, k);
    Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` is not of procedure string\n");
    fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ForeignProcedure* p = Arcadia_Value_getForeignProcedureValue(&v);
  Arcadia_Value targetValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
  Arcadia_SizeValue numberOfValues = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)ast->arguments);
  Arcadia_Value* argumentValues = malloc(sizeof(Arcadia_Value) * numberOfValues);
  if (!argumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    for (Arcadia_SizeValue i = 0, n = numberOfValues; i < n; ++i) {
      argumentValues[i] = Arcadia_List_getAt(thread, ast->arguments, i);
    }
    (*p)(thread, &targetValue, numberOfValues, argumentValues);
    Arcadia_Thread_popJumpTarget(thread);
    free(argumentValues);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(argumentValues);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_String* string = NULL;
  if (Arcadia_Value_isInteger16Value(&targetValue)) {
    string = Arcadia_String_createFromInteger16(thread, Arcadia_Value_getInteger16Value(&targetValue));
  } else if (Arcadia_Value_isInteger32Value(&targetValue)) {
    string = Arcadia_String_createFromInteger32(thread, Arcadia_Value_getInteger32Value(&targetValue));
  } else if (Arcadia_Value_isInteger64Value(&targetValue)) {
    string = Arcadia_String_createFromInteger64(thread, Arcadia_Value_getInteger64Value(&targetValue));
  } else if (Arcadia_Value_isInteger8Value(&targetValue)) {
    string = Arcadia_String_createFromInteger8(thread, Arcadia_Value_getInteger8Value(&targetValue));
  } else  if (Arcadia_Value_isObjectReferenceValue(&targetValue)) {
    Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&targetValue);
    if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, object), _Arcadia_String_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    string = (Arcadia_String*)object;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ByteBuffer_append_pn(thread, context->context->targetBuffer, Arcadia_String_getBytes(thread, string), Arcadia_String_getNumberOfBytes(thread, string));

}

static void
evalAst
  (
    Arcadia_Thread* thread,
    FileContext* context,
    Ast* ast
  )
{
  switch (ast->type) {
    case Arcadia_TemplateEngine_AstKind_GetVariable: {
      Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)ast->name);
      Arcadia_Value v = Environment_get(thread, context->environment, k, Arcadia_BooleanValue_True);
      if (Arcadia_Value_isVoidValue(&v)) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` not defined\n");
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      } else  if (!Arcadia_Value_isObjectReferenceValue(&v)) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` is not of type string\n");
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&v);
      if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, object), _Arcadia_String_getType(thread))) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"variable `");
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_insertBackCxxString(thread, sb, u8"` is not of type string\n");
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_ByteBuffer_append_pn(thread, context->context->targetBuffer, Arcadia_String_getBytes(thread, (Arcadia_String*)object), Arcadia_String_getNumberOfBytes(thread, (Arcadia_String*)object));
    } break;
    case Arcadia_TemplateEngine_AstKind_Invoke: {
      if (Arcadia_String_isEqualTo_pn(thread, ast->name, u8"include", sizeof(u8"include") - 1)) {
        if (1 != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)ast->arguments)) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        }
        Arcadia_Object* object = Arcadia_List_getObjectReferenceValueAt(thread, ast->arguments, 0);
        if (!Arcadia_Object_isInstanceOf(thread, object, _Arcadia_String_getType(thread))) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
          Arcadia_Thread_jump(thread);
        }
        Arcadia_String* string = (Arcadia_String*)object;
        Arcadia_FilePath* filePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_getBytes(thread, string), Arcadia_String_getNumberOfBytes(thread, string));
        Arcadia_Value value;
        Arcadia_Value_setObjectReferenceValue(&value, filePath);
        Arcadia_Stack_push(thread, context->context->stack, value);
        Context_onRun(thread, context->context);
      } else {
        evalInvoke(thread, context, ast);
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

static Ast*
onExpression
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  Ast* ast = NULL;
  Arcadia_ByteBuffer_clear(thread, context->context->temporaryBuffer);
  onIdentifier(thread, context);
  Arcadia_String* name = getLiteral(thread, context);
  Arcadia_String* argument = NULL;
  if (isLeftParenthesis(thread, context)) {
    ast = Ast_create(thread, Arcadia_TemplateEngine_AstKind_Invoke, name);
    Arcadia_Utf8Reader_next(thread, context->source);
    if (is(thread, context, '"')) {
      Arcadia_ByteBuffer_clear(thread, context->context->temporaryBuffer);
      onString(thread, context);
      argument = getLiteral(thread, context);
      Arcadia_List_insertBackObjectReferenceValue(thread, ast->arguments, (Arcadia_ObjectReferenceValue)argument);
    }
    if (!isRightParenthesis(thread, context)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Utf8Reader_next(thread, context->source);
  } else {
    ast = Ast_create(thread, Arcadia_TemplateEngine_AstKind_GetVariable, name);
  }
  return ast;
}

static Ast*
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
  Ast* ast = Ast_create(thread, Arcadia_TemplateEngine_AstKind_Invoke, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"include", sizeof(u8"include") - 1)));
  Arcadia_List_insertBackObjectReferenceValue(thread, ast->arguments, getLiteral(thread, context));
  if (!isRightParenthesis(thread, context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Utf8Reader_next(thread, context->source);
  return ast;
}

static void
onStatement
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  Ast* ast = onExpression(thread, context);
  evalAst(thread, context, ast);
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
    FileContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & FileContext_constructImpl,
  .destruct = &FileContext_destruct,
  .visit = &FileContext_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.FileContext", FileContext,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

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
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->context);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->sourceFilePath);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->environment);
}

static void
FileContext_constructImpl
  (
    Arcadia_Thread* thread,
    FileContext* self
  )
{
  Arcadia_TypeValue _type = _FileContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->context = (Context*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Context_getType(thread));
  self->environment = (Environment*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Environment_getType(thread));
  self->sourceFilePath = (Arcadia_FilePath*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_FilePath_getType(thread));
  self->source = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

FileContext*
FileContext_create
  (
    Arcadia_Thread* thread,
    Context* context,
    Environment* environment,
    Arcadia_FilePath* sourceFilePath
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)context);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)environment);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)sourceFilePath);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(FileContext);

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
