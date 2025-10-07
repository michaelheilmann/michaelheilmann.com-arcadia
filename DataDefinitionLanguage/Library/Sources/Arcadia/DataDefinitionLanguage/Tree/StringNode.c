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

#define ARCADIA_DATADEFINITIONLANGUAGE_PRIVATE (1)
#include "Arcadia/DataDefinitionLanguage/Tree/StringNode.h"

static void
Arcadia_DataDefinitionLanguage_Tree_StringNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* self
  );

static void
Arcadia_DataDefinitionLanguage_Tree_StringNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Tree_StringNode_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DataDefinitionLanguage_Tree_StringNode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Tree_StringNode_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Tree_StringNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Tree_StringNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.StringNode", Arcadia_DataDefinitionLanguage_Tree_StringNode,
                         u8"Arcadia.DataDefinitionLanguage.Tree.Node", Arcadia_DataDefinitionLanguage_Tree_Node,
                         &_Arcadia_DataDefinitionLanguage_Tree_StringNode_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Tree_StringNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Tree_StringNode_getType(thread);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DataDefinitionLanguage_Tree_NodeType_String);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 1);
  switch (Arcadia_Value_getTag(&x)) {
    case Arcadia_ValueTag_ObjectReference: {
      self->value = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &x, _Arcadia_String_getType(thread));
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

static void
Arcadia_DataDefinitionLanguage_Tree_StringNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_StringNode* self
  )
{
  if (self->value) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->value);
  }
}

Arcadia_DataDefinitionLanguage_Tree_StringNode*
Arcadia_DataDefinitionLanguage_Tree_StringNode_createString
  (
    Arcadia_Thread* thread,
    Arcadia_String* stringValue
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (stringValue) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, stringValue);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_StringNode);
}
