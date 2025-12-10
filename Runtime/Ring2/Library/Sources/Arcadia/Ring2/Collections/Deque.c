// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Collections/Deque.h"

static void
Arcadia_Deque_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

static void
Arcadia_Deque_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DequeDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Deque_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Deque", Arcadia_Deque,
                         u8"Arcadia.Collection", Arcadia_Collection,
                         &_typeOperations);

static void
Arcadia_Deque_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Deque_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_Deque_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DequeDispatch* self
  )
{ }

void
Arcadia_Deque_insertFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_Value value
  )
{ Arcadia_VirtualCall(Arcadia_Deque, insertFront, self, value); }

void
Arcadia_Deque_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_Value value
  )
{ Arcadia_VirtualCall(Arcadia_Deque, insertBack, self, value); }

void
Arcadia_Deque_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  )
{ Arcadia_VirtualCall(Arcadia_Deque, insertAt, self, index, value); }

Arcadia_Value
Arcadia_Deque_getFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Deque, getFront, self); }

Arcadia_Value
Arcadia_Deque_getBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Deque, getBack, self); }

Arcadia_Value
Arcadia_Deque_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Deque, getAt, self, index); }

void
Arcadia_Deque_removeFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{ Arcadia_VirtualCall(Arcadia_Deque, removeFront, self); }

void
Arcadia_Deque_removeBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{ Arcadia_VirtualCall(Arcadia_Deque, removeBack, self); }

void
Arcadia_Deque_removeAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index
  )
{ Arcadia_VirtualCall(Arcadia_Deque, removeAt, self, index); }
