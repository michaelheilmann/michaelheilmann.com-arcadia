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
#include "Arcadia/DataDefinitionLanguage/Tree/VoidNode.h"

static void
Arcadia_DataDefinitionLanguage_Tree_VoidNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Tree_VoidNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_VoidNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Tree_VoidNode_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Tree_VoidNode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Tree_VoidNode_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Tree_VoidNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Tree_VoidNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.VoidNode", Arcadia_DataDefinitionLanguage_Tree_VoidNode,
                         u8"Arcadia.DataDefinitionLanguage.Tree.Node", Arcadia_DataDefinitionLanguage_Tree_Node,
                         &_Arcadia_DataDefinitionLanguage_Tree_VoidNode_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Tree_VoidNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Tree_VoidNode* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Tree_VoidNode_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeInteger32Value(Arcadia_DataDefinitionLanguage_Tree_NodeType_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  switch (Arcadia_Value_getTag(&argumentValues[0])) {
    case Arcadia_ValueTag_Void: {
      _self->value = Arcadia_String_createFromVoid(thread, Arcadia_Value_getVoidValue(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_ObjectReference: {
      _self->value = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
      static const Arcadia_Natural8Value voidString[] = u8"void";
      if (sizeof(voidString) - 1 != Arcadia_String_getNumberOfBytes(thread, _self->value) ||
          0 != Arcadia_Memory_compare(thread, voidString, Arcadia_String_getBytes(thread, _self->value), sizeof(voidString) - 1)) {
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
}

static void
Arcadia_DataDefinitionLanguage_Tree_VoidNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_VoidNode* self
  )
{
  if (self->value) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->value);
  }
}

Arcadia_DataDefinitionLanguage_Tree_VoidNode*
Arcadia_DataDefinitionLanguage_Tree_VoidNode_createVoid
  (
    Arcadia_Thread* thread,
    Arcadia_VoidValue voidValue
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(voidValue),
  };
  Arcadia_DataDefinitionLanguage_Tree_VoidNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_VoidNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_VoidNode*
Arcadia_DataDefinitionLanguage_Tree_VoidNode_createString
  (
    Arcadia_Thread* thread,
    Arcadia_String* stringValue
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(stringValue),
  };
  Arcadia_DataDefinitionLanguage_Tree_VoidNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_VoidNode_getType(thread), 1, &argumentValues[0]);
  return self;
}
