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
#include "Arcadia/DataDefinitionLanguage/Tree/NameNode.h"

static void
Arcadia_DataDefinitionLanguage_Tree_NameNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Tree_NameNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_NameNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Tree_NameNode_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Tree_NameNode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Tree_NameNode_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Tree_NameNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Tree_NameNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.NameNode", Arcadia_DataDefinitionLanguage_Tree_NameNode,
                         u8"Arcadia.DataDefinitionLanguage.Tree.Node", Arcadia_DataDefinitionLanguage_Tree_Node,
                         &_Arcadia_DataDefinitionLanguage_Tree_NameNode_typeOperations);

static inline Arcadia_BooleanValue
isFirst
  (
    Arcadia_Natural8Value byte
  )
{
  return '_' == byte
      || ('a' <= byte && byte <= 'z')
      || ('A' <= byte && byte <= 'Z');
}

static inline Arcadia_BooleanValue
isRest
  (
    Arcadia_Natural8Value byte
  )
{
  return '_' == byte
    || ('a' <= byte && byte <= 'z')
    || ('A' <= byte && byte <= 'Z')
    || ('0' <= byte && byte <= '9');
}

static void
Arcadia_DataDefinitionLanguage_Tree_NameNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Tree_NameNode* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Tree_NameNode_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeInteger32Value(Arcadia_DataDefinitionLanguage_Tree_NodeType_Name),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 1);
  switch (Arcadia_Value_getTag(&x)) {
    case Arcadia_ValueTag_ObjectReference: {
      _self->value = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &x, _Arcadia_String_getType(thread));
      Arcadia_Natural8Value const* start = Arcadia_String_getBytes(thread, _self->value);
      Arcadia_Natural8Value const* end = start + Arcadia_String_getNumberOfBytes(thread, _self->value);
      Arcadia_Natural8Value const* current = start;
      if (current == end || !isFirst(*current)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      do {
        current++;
      } while (current != end && isRest(*current));
      if (current != end) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

static void
Arcadia_DataDefinitionLanguage_Tree_NameNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_NameNode* self
  )
{
  if (self->value) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->value);
  }
}

Arcadia_DataDefinitionLanguage_Tree_NameNode*
Arcadia_DataDefinitionLanguage_Tree_NameNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (string) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, string);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NameNode);
}