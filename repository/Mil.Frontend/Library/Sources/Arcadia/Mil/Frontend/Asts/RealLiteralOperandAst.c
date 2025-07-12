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

#include "Arcadia/Mil/Frontend/Asts/RealLiteralOperandAst.h"

#include "Arcadia/Mil/Frontend/Include.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Mil_RealLiteralOperandAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_RealLiteralOperandAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_RealLiteralOperandAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_RealLiteralOperandAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_RealLiteralOperandAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_RealLiteralOperandAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_RealLiteralOperandAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Mil_RealLiteralOperandAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Mil.RealLiteralOperandAst", Arcadia_Mil_RealLiteralOperandAst, u8"Arcadia.Mil.OperandAst", Arcadia_Mil_OperandAst, &_Arcadia_Mil_RealLiteralOperandAst_typeOperations);

static void
Arcadia_Mil_RealLiteralOperandAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_RealLiteralOperandAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_IntegerLiteralOperandAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->value = (Arcadia_String*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Mil_RealLiteralOperandAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_RealLiteralOperandAst* self
  )
{ Arcadia_Object_visit(thread, (Arcadia_Object*)self->value); }

Arcadia_Mil_RealLiteralOperandAst*
Arcadia_Mil_RealLiteralOperandAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(value),
  };
  Arcadia_Mil_RealLiteralOperandAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_RealLiteralOperandAst_getType(thread), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
