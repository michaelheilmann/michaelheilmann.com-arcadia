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

// Last modified: 2025-01-01

#include "R/Mil/Asts/MethodDefinitionAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(methodName:Arcadia.String, methodParameters:R.List, methodBody:R.List)
/// @endcode
static void
Arcadia_Mil_MethodDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_MethodDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_MethodDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_MethodDefinitionAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_MethodDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_MethodDefinitionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_MethodDefinitionAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_MethodDefinitionAst_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcadia.Mil.MethodDefinitionAst", Arcadia_Mil_MethodDefinitionAst, u8"Arcadia.Mil.ClassMemberDefinitionAst", Arcadia_Mil_ClassMemberDefinitionAst, &_Arcadia_Mil_MethodDefinitionAst_typeOperations);

static void
Arcadia_Mil_MethodDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_MethodDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_MethodDefinitionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (4 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->nativeName = R_Argument_getObjectReferenceValueOrNull(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  _self->methodName = (Arcadia_String*)R_Argument_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_String_getType(thread));
  _self->methodParameters = (Arcadia_List*)R_Argument_getObjectReferenceValue(thread, &argumentValues[2], _Arcadia_List_getType(thread));
  _self->methodBody = (Arcadia_List*)R_Argument_getObjectReferenceValueOrNull(thread, &argumentValues[3], _Arcadia_List_getType(thread));
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_Mil_MethodDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_MethodDefinitionAst* self
  )
{
  Arcadia_Object_visit(thread, self->nativeName);
  Arcadia_Object_visit(thread, self->methodName);
  Arcadia_Object_visit(thread, self->methodParameters);
  Arcadia_Object_visit(thread, self->methodBody);
}

Arcadia_Mil_MethodDefinitionAst*
Arcadia_Mil_MethodDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* nativeName,
    Arcadia_String* methodName,
    Arcadia_List* methodParameters,
    Arcadia_List* methodBody
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
                               {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = methodName },
                               {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = methodParameters },
                               {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
  if (nativeName) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[0], nativeName);
  }
  if (methodBody) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[3], methodBody);
  }
  Arcadia_Mil_MethodDefinitionAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_MethodDefinitionAst_getType(thread), 4, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
