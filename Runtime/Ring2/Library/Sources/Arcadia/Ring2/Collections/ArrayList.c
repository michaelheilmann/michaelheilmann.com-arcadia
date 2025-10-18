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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Collections/ArrayList.h"

#include "Arcadia/Ring2/Include.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

static void
Arcadia_ArrayList_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_ArrayList_ensureInitialized
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_ArrayList_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  );

static void
Arcadia_ArrayList_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  );

static void
Arcadia_ArrayList_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  );

static void
Arcadia_ArrayList_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  );

static Arcadia_Value
Arcadia_ArrayList_getAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_SizeValue index
  );

static Arcadia_SizeValue
Arcadia_ArrayList_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  );

static Arcadia_BooleanValue
Arcadia_ArrayList_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  );

static void
Arcadia_ArrayList_insertAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  );

static void
Arcadia_ArrayList_insertBackImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_Value value
  );

static void
Arcadia_ArrayList_insertFrontImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_Value value
  );

static void
Arcadia_ArrayList_removeAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue count
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_ArrayList_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_ArrayList_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_ArrayList_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ArrayList", Arcadia_ArrayList,
                         u8"Arcadia.List", Arcadia_List,
                         &_typeOperations);

static void
Arcadia_ArrayList_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_SizeValue requiredFreeCapacity
  )
{
  Arcadia_SizeValue newAvailableFreeCapacity = self->capacity - self->size;
  Arcadia_SizeValue oldCapacity = self->capacity;
  Arcadia_SizeValue newCapacity = oldCapacity;
  while (requiredFreeCapacity > newAvailableFreeCapacity) {
    oldCapacity = self->capacity;
    newCapacity = oldCapacity;
    if (oldCapacity > g_maximumCapacity / 2) {
      // If oldCapacity > maximumCapacity / 2 holds then oldCapacity * 2 > maximumCapacity holds.
      // Consequently, we cannot double the capacity. Try to saturate the capacity.
      if (oldCapacity == g_maximumCapacity) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
        Arcadia_Thread_jump(thread);
      } else {
        newCapacity = g_maximumCapacity;
      }
    } else {
      newCapacity = oldCapacity * 2;
    }
    newAvailableFreeCapacity = newCapacity - self->size;
  }
  Arcadia_Memory_reallocateUnmanaged(thread, &self->elements, sizeof(Arcadia_Value) * newCapacity);
  self->capacity = newCapacity;
}

static void
Arcadia_ArrayList_ensureInitialized
  (
    Arcadia_Thread* thread
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(Arcadia_Value);
    if (g_maximumCapacity > Arcadia_Integer32Value_Maximum) {
      g_maximumCapacity = Arcadia_Integer32Value_Maximum;
    }
    if (g_minimumCapacity > g_maximumCapacity) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    g_initialized = Arcadia_BooleanValue_True;
  }
}

static void
Arcadia_ArrayList_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ArrayList_getType(thread);
  Arcadia_ArrayList_ensureInitialized(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->elements = NULL;
  self->capacity = 0;
  self->size = 0;
  self->capacity = g_minimumCapacity;
  self->elements = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_Value) * self->capacity);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Arcadia_Value_setVoidValue(self->elements + i, Arcadia_VoidValue_Void);
  }
  ((Arcadia_Collection*)self)->clear = (void (*)(Arcadia_Thread*,Arcadia_Collection*))&Arcadia_ArrayList_clearImpl;
  ((Arcadia_Collection*)self)->getSize = (Arcadia_SizeValue (*)(Arcadia_Thread*,Arcadia_Collection*))&Arcadia_ArrayList_getSizeImpl;
  ((Arcadia_Collection*)self)->isImmutable = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_ArrayList_isImmutableImpl;
  ((Arcadia_List*)self)->getAt = (Arcadia_Value (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_SizeValue))&Arcadia_ArrayList_getAtImpl;
  ((Arcadia_List*)self)->insertAt = (void (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_SizeValue, Arcadia_Value)) & Arcadia_ArrayList_insertAtImpl;
  ((Arcadia_List*)self)->insertBack = (void (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_Value))  &Arcadia_ArrayList_insertBackImpl;
  ((Arcadia_List*)self)->insertFront = (void (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_Value))  &Arcadia_ArrayList_insertFrontImpl;
  ((Arcadia_List*)self)->removeAt = (void (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_SizeValue, Arcadia_SizeValue)) & Arcadia_ArrayList_removeAtImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_ArrayList_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  )
{
  if (self->elements) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->elements);
    self->elements = NULL;
  }
}

static void
Arcadia_ArrayList_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  )
{
  if (self->elements) {
    for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
      Arcadia_Value_visit(thread, self->elements + i);
    }
  }
}

static void
Arcadia_ArrayList_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  )
{ self->size = 0; }

static Arcadia_Value
Arcadia_ArrayList_getAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_SizeValue index
  )
{
  if (index >= self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->elements[index];
}

static Arcadia_SizeValue
Arcadia_ArrayList_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  )
{ return self->size; }

static Arcadia_BooleanValue
Arcadia_ArrayList_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self
  )
{ return Arcadia_BooleanValue_False; }

static void
Arcadia_ArrayList_insertBackImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_Value value
  )
{
  Arcadia_List_insertAt(thread, (Arcadia_List*)self, self->size, value);
}

static void
Arcadia_ArrayList_insertAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  )
{
  if (index > self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (Arcadia_Value_isVoidValue(&value)) {
    return;
  }
  if (self->capacity == self->size) {
    Arcadia_ArrayList_ensureFreeCapacity(thread, self, Arcadia_SizeValue_Literal(1));
  }
  if (index < self->size) {
    Arcadia_Memory_copy(thread, self->elements + index + 1,
                        self->elements + index + 0, sizeof(Arcadia_Value) * (self->size - index));
  }
  self->elements[index] = value;
  self->size++;
}

static void
Arcadia_ArrayList_insertFrontImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_Value value
  )
{
  Arcadia_List_insertAt(thread, (Arcadia_List*)self, Arcadia_SizeValue_Literal(0), value);
}

static void
Arcadia_ArrayList_removeAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ArrayList* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue count
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if ((Arcadia_SizeValue_Maximum - count) < index) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if ((index + count) > self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue tailLength = (self->size - index) - count;
  if (tailLength) {
    Arcadia_SizeValue tailStart = index + count;
    Arcadia_Memory_copy(thread, self->elements + index,
                        self->elements + tailStart, tailLength * sizeof(Arcadia_Value));
  }
  self->size -= count;
}

Arcadia_ArrayList*
Arcadia_ArrayList_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_ArrayList);
}
