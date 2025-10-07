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

#include "Arcadia/MIL/AST/Definitions/ConstructorDefinitionNode.h"

#include "Arcadia/MIL/AST/Include.h"

/// @code
/// constructor(constructorParameters:Arcadia.List, constructorBody:Arcadia.List)
/// @endcode
static void
Arcadia_MIL_AST_ConstructorDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ConstructorDefinitionNode* self
  );

static void
Arcadia_MIL_AST_ConstructorDefinitionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ConstructorDefinitionNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_AST_ConstructorDefinitionNode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_AST_ConstructorDefinitionNode_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.ConstructorDefinitionNode", Arcadia_MIL_AST_ConstructorDefinitionNode,
                         u8"Arcadia.MIL.AST.Node", Arcadia_MIL_AST_Node,
                         &_typeOperations);

static void
Arcadia_MIL_AST_ConstructorDefinitionNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ConstructorDefinitionNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_AST_ConstructorDefinitionNode_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 3 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  if (Arcadia_ValueStack_isVoidValue(thread, 3)) {
    self->nativeName = NULL;
  } else {
    self->nativeName = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  }

  self->constructorParameters = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_List_getType(thread));

  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->constructorBody = NULL;
  } else {
    self->constructorBody = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  }

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 3 + 1);
}

static void
Arcadia_MIL_AST_ConstructorDefinitionNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ConstructorDefinitionNode* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->nativeName);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->constructorParameters);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->constructorBody);
}

Arcadia_MIL_AST_ConstructorDefinitionNode*
Arcadia_MIL_AST_ConstructorDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* nativeName,
    Arcadia_List* constructorParameters,
    Arcadia_List* constructorBody
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (nativeName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, nativeName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (constructorParameters) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, constructorParameters);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (constructorBody) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, constructorBody);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_AST_ConstructorDefinitionNode);
}
