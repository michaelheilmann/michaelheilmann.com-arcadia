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
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* self
  );

static void
Arcadia_DataDefinitionLanguage_Tree_NumberNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DataDefinitionLanguage_Tree_NumberNode_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DataDefinitionLanguage_Tree_NumberNode_constructImpl,
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
    Arcadia_DataDefinitionLanguage_Tree_NumberNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Tree_NumberNode_getType(thread);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DataDefinitionLanguage_Tree_NodeType_Number);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 1);
  switch (Arcadia_Value_getTag(&x)) {
    case Arcadia_ValueTag_Integer16: {
      self->value = Arcadia_String_createFromInteger16(thread, Arcadia_Value_getInteger16Value(&x));
    } break;
    case Arcadia_ValueTag_Integer32: {
      self->value = Arcadia_String_createFromInteger32(thread, Arcadia_Value_getInteger32Value(&x));
    } break;
    case Arcadia_ValueTag_Integer64: {
      self->value = Arcadia_String_createFromInteger64(thread, Arcadia_Value_getInteger64Value(&x));
    } break;
    case Arcadia_ValueTag_Integer8: {
      self->value = Arcadia_String_createFromInteger8(thread, Arcadia_Value_getInteger8Value(&x));
    } break;
    case Arcadia_ValueTag_Natural16: {
      self->value = Arcadia_String_createFromNatural16(thread, Arcadia_Value_getNatural16Value(&x));
    } break;
    case Arcadia_ValueTag_Natural32: {
      self->value = Arcadia_String_createFromNatural32(thread, Arcadia_Value_getNatural32Value(&x));
    } break;
    case Arcadia_ValueTag_Natural64: {
      self->value = Arcadia_String_createFromNatural64(thread, Arcadia_Value_getNatural64Value(&x));
    } break;
    case Arcadia_ValueTag_Natural8: {
      self->value = Arcadia_String_createFromNatural8(thread, Arcadia_Value_getNatural8Value(&x));
    } break;
    case Arcadia_ValueTag_Real32: {
      self->value = Arcadia_String_createFromReal32(thread, Arcadia_Value_getReal32Value(&x));
    } break;
    case Arcadia_ValueTag_Real64: {
      self->value = Arcadia_String_createFromReal64(thread, Arcadia_Value_getReal64Value(&x));
    } break;
    case Arcadia_ValueTag_ObjectReference: {
      self->value = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &x, _Arcadia_String_getType(thread));
      Arcadia_Natural8Value const* start = Arcadia_String_getBytes(thread, self->value);
      Arcadia_Natural8Value const* end = start + Arcadia_String_getNumberOfBytes(thread, self->value);
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
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
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
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger16Value(thread, integer16Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, integer32Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger64Value(thread, integer64Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger8Value(thread, integer8Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural16Value(thread, natural16Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural32Value(thread, natural32Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural64Value(thread, natural64Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, natural8Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createReal32
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value real32Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushReal32Value(thread, real32Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value real64Value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushReal64Value(thread, real64Value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createString
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
  ARCADIA_CREATEOBJECT(Arcadia_DataDefinitionLanguage_Tree_NumberNode);
}
