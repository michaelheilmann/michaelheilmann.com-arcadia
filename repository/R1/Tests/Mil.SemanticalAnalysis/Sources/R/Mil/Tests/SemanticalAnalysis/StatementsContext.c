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

// Last modified: 2024-10-18

#include "R/Mil/Tests/SemanticalAnalysis/StatementsContext.h"

#include "R/Include.h"
#include "R/Mil/Include.h"

static void
Arcadia_Mil_CallableContext_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_CallableContext_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_CallableContext_objectTypeOperations = {
  .construct = &Arcadia_Mil_CallableContext_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_CallableContext_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_CallableContext_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_CallableContext_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.CallableContext", Arcadia_Mil_CallableContext, u8"Arcadia.Object", Arcadia_Object, &_Arcadia_Mil_CallableContext_typeOperations);

static void
Arcadia_Mil_CallableContext_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_CallableContext* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_CallableContext_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->labels = Arcadia_Map_create(process);
  _self->variables = Arcadia_List_create(process);
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_CallableContext_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self
  )
{
  if (self->labels) {
    Arcadia_Object_visit(process, self->labels);
  }
  if (self->variables) {
    Arcadia_Object_visit(process, self->variables);
  }
}

Arcadia_Mil_CallableContext*
Arcadia_Mil_CallableContext_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
  Arcadia_Mil_CallableContext* self = R_allocateObject(process, _Arcadia_Mil_CallableContext_getType(process), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_Mil_CallableContext_onReset
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self
  )
{
  Arcadia_Map_clear(process, self->labels);
  Arcadia_List_clear(process, self->variables);
  self->statementIndex = 0;
}

void
Arcadia_Mil_CallableContext_onDefineLabel
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self,
    Arcadia_String* name,
    Arcadia_Mil_LabelStatementAst* ast,
    Arcadia_Natural32Value instructionIndex
  )
{
  Arcadia_Value k;
  Arcadia_Value_setObjectReferenceValue(&k, name);
  Arcadia_Value v = Arcadia_Map_get(process, self->labels, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value_setObjectReferenceValue(&v, ast);
  Arcadia_Map_set(process, self->labels, k, v);
}

void
Arcadia_Mil_CallableContext_onParameterVariableDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* self,
    Arcadia_String* name,
    Arcadia_Mil_Ast* ast
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, self->variables); i < n; ++i) {
    Arcadia_Value args[2] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name },
                              Arcadia_List_getAt(process, self->variables, i) };
    if (Arcadia_Value_isEqualTo(process, &args[0], &args[1])) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
  }
}

void
Arcadia_Mil_CallableContext_onLocalVariableDefinition
  (
    Arcadia_Process* process,
    Arcadia_Mil_CallableContext* context,
    Arcadia_String* name,
    Arcadia_Mil_VariableDefinitionStatementAst* ast
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, context->variables); i < n; ++i) {
    Arcadia_Value args[2] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name },
                              Arcadia_List_getAt(process, context->variables, i) };
    if (Arcadia_Value_isEqualTo(process, &args[0], &args[1])) {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
  }
}
