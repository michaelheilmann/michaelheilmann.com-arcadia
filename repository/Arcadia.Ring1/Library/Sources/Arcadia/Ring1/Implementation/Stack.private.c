// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2025-02-02

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Stack.private.h"

#include "Arcadia/Ring1/Include.h"

// the desired amount grow by
#define desiredAdditionalCapacity 64

// the maximum capacity
#define maximumCapacity (Arcadia_SizeValue_Maximum / sizeof(Arcadia_Value))

// the minimum capacity
#define minimumCapacity ((Arcadia_SizeValue)8)

Arcadia_StaticAssert(minimumCapacity <= maximumCapacity, "environment not (yet) supported");

void
Arcadia_ValueStack_initialize
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack * self
  )
{
  if (!self) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  Arcadia_Process1_allocateUnmanaged(process, &self->elements, sizeof(Arcadia_Value) * minimumCapacity);
  for (Arcadia_SizeValue i = 0; i < minimumCapacity; ++i) {
    self->elements[i] = (Arcadia_Value){ .tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void };
  }
  self->size = 0;
  self->capacity = minimumCapacity;
}

void
Arcadia_ValueStack_uninitialize
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self
  )
{
  if (!self) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  Arcadia_Process1_deallocateUnmanaged(process, self->elements);
  self->elements = NULL;
}

void
Arcadia_ValueStack_increaseCapacity
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self,
    Arcadia_SizeValue additionalCapacity
  )
{
  if (!self) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }

  Arcadia_SizeValue oldCapacity = self->capacity;
  if (maximumCapacity - oldCapacity < additionalCapacity) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process1_jump(process);
  }
  Arcadia_SizeValue maxAdditionalCapacity = maximumCapacity - oldCapacity;
  // We want to grow in steps of desiredAdditionalCapacity.
  if (additionalCapacity < desiredAdditionalCapacity && maxAdditionalCapacity >= desiredAdditionalCapacity) {
    additionalCapacity = desiredAdditionalCapacity;
  }
  
  Arcadia_SizeValue newCapacity = oldCapacity + additionalCapacity;
  Arcadia_Process1_reallocateUnmanaged(process, &self->elements, newCapacity * sizeof(Arcadia_Value));
  for (Arcadia_SizeValue i = oldCapacity; i < newCapacity; ++i) {
    self->elements[i] = (Arcadia_Value){ .tag =  Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void };
  }
  self->capacity = newCapacity;
}

void
Arcadia_ValueStack_ensureFreeCapacity
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self,
    Arcadia_SizeValue requiredFreeCapacity
  )
{
  if (!self) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  Arcadia_SizeValue availableFreeCapacity = self->capacity - self->size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    Arcadia_ValueStack_increaseCapacity(process, self, requiredFreeCapacity - availableFreeCapacity);
  }
}

Arcadia_SizeValue
Arcadia_ValueStack_getSize
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self
  )
{
  if (!self) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  return self->size;
}

void
Arcadia_ValueStack_push
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self,
    Arcadia_Value* value
  )
{
  Arcadia_ValueStack_ensureFreeCapacity(process, self, 1);
  self->elements[self->size] = *value;
  self->size++;
}

void
Arcadia_ValueStack_pop
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self,
    Arcadia_SizeValue count
  )
{
  if (!self) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  if (count < self->size) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  self->size -= count;
}
