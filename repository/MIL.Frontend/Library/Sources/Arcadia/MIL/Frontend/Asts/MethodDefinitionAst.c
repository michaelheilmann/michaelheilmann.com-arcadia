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

#include "Arcadia/MIL/Frontend/Asts/MethodDefinitionAst.h"

#include "Arcadia/MIL/Frontend/Include.h"

/// @code
/// construct(methodName:Arcadia.String, methodParameters:Arcadia.List, methodBody:Arcadia.List)
/// @endcode
static void
Arcadia_MIL_MethodDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_MethodDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_MethodDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_MethodDefinitionAst_objectTypeOperations = {
  .construct = &Arcadia_MIL_MethodDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_MethodDefinitionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_MethodDefinitionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_MethodDefinitionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.MethodDefinitionAst", Arcadia_MIL_MethodDefinitionAst,
                         u8"Arcadia.MIL.Ast", Arcadia_MIL_Ast,
                         &_Arcadia_MIL_MethodDefinitionAst_typeOperations);

static void
Arcadia_MIL_MethodDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_MethodDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_MethodDefinitionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 4 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (Arcadia_ValueStack_isVoidValue(thread, 4)) {
    _self->nativeName = NULL;
  } else {
    _self->nativeName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 4, _Arcadia_String_getType(thread));
  }
  _self->methodName = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  _self->methodParameters = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_List_getType(thread));
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    _self->methodBody = NULL;
  } else {
    _self->methodBody = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 4 + 1);
}

static void
Arcadia_MIL_MethodDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_MethodDefinitionAst* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->nativeName);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->methodName);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->methodParameters);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->methodBody);
}

Arcadia_MIL_MethodDefinitionAst*
Arcadia_MIL_MethodDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* nativeName,
    Arcadia_String* methodName,
    Arcadia_List* methodParameters,
    Arcadia_List* methodBody
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (nativeName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, nativeName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (methodName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, methodName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (methodParameters) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, methodParameters);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (methodBody) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, methodBody);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_MethodDefinitionAst);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
