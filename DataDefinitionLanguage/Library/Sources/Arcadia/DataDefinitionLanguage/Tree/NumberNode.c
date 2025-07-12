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
#include "Arcadia/DataDefinitionLanguage/Tree/NumberNode.h"

static void
Arcadia_DataDefinitionLanguage_Tree_NumberNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Tree_NumberNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Tree_NumberNode_objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Tree_NumberNode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Tree_NumberNode_visit,
};

static const Arcadia_Type_Operations _Arcadia_DataDefinitionLanguage_Tree_NumberNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DataDefinitionLanguage_Tree_NumberNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.NumberNode", Arcadia_DataDefinitionLanguage_Tree_NumberNode,
                         u8"Arcadia.DataDefinitionLanguage.Tree.Node", Arcadia_DataDefinitionLanguage_Tree_Node,
                         &_Arcadia_DataDefinitionLanguage_Tree_NumberNode_typeOperations);

static inline bool isDigit(Arcadia_Natural8Value byte) {
  return ('0' <= byte && byte <= '9');
}

static void
Arcadia_DataDefinitionLanguage_Tree_NumberNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeInteger32Value(Arcadia_DataDefinitionLanguage_Tree_NodeType_Number),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  switch (Arcadia_Value_getTag(&argumentValues[0])) {
    case Arcadia_ValueTag_Integer16: {
      _self->value = Arcadia_String_createFromInteger16(thread, Arcadia_Value_getInteger16Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Integer32: {
      _self->value = Arcadia_String_createFromInteger32(thread, Arcadia_Value_getInteger32Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Integer64: {
      _self->value = Arcadia_String_createFromInteger64(thread, Arcadia_Value_getInteger64Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Integer8: {
      _self->value = Arcadia_String_createFromInteger8(thread, Arcadia_Value_getInteger8Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Natural16: {
      _self->value = Arcadia_String_createFromNatural16(thread, Arcadia_Value_getNatural16Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Natural32: {
      _self->value = Arcadia_String_createFromNatural32(thread, Arcadia_Value_getNatural32Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Natural64: {
      _self->value = Arcadia_String_createFromNatural64(thread, Arcadia_Value_getNatural64Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Natural8: {
      _self->value = Arcadia_String_createFromNatural8(thread, Arcadia_Value_getNatural8Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Real32: {
      _self->value = Arcadia_String_createFromReal32(thread, Arcadia_Value_getReal32Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_Real64: {
      _self->value = Arcadia_String_createFromReal64(thread, Arcadia_Value_getReal64Value(&argumentValues[0]));
    } break;
    case Arcadia_ValueTag_ObjectReference: {
      _self->value = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
      Arcadia_Natural8Value const* start = Arcadia_String_getBytes(thread, _self->value);
      Arcadia_Natural8Value const* end = start + Arcadia_String_getNumberOfBytes(thread, _self->value);
      Arcadia_Natural8Value const* current = start; 
      if (current != end && *current == '+' || *current == '-') {
        current++;
      }
      if (current == end) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      if (isDigit(*current)) {
        do {
          current++;
        } while (current != end && isDigit(*current));
        if (current != end && *current == '.') {
          current++;
          while (current != end && isDigit(*current)) {
            current++;
          }
        }
      } else if ('.' == *current) {
          current++;
          if (current == end || !isDigit(*current)) {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
            Arcadia_Thread_jump(thread);
          }
          do {
            current++;
          } while (current != end && isDigit(*current));
      } else {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      if (current != end && ('e' == *current || 'E' == *current)) {
        current++;
        if (current != end && *current == '+' || *current == '-') {
          current++;
        }
        if (current == end || !isDigit(*current)) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        }
        do {
          current++;
        } while (current != end && isDigit(*current));
      }
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
}

static void
Arcadia_DataDefinitionLanguage_Tree_NumberNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* self
  )
{
  if (self->value) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->value);
  }
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeInteger16Value(integer16Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeInteger32Value(integer32Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeInteger64Value(integer64Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeInteger8Value(integer8Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural16Value(natural16Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural32Value(natural32Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural64Value(natural64Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeNatural8Value(natural8Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createReal32
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value real32Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeReal32Value(real32Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value real64Value
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeReal64Value(real64Value),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createString
  (
    Arcadia_Thread* thread,
    Arcadia_String* stringValue
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(stringValue),
  };
  Arcadia_DataDefinitionLanguage_Tree_NumberNode* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread), 1, &argumentValues[0]);
  return self;
}
