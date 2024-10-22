// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R/Stack.h"

#include "R/ArmsIntegration.h"
#include "R.h"

static R_BooleanValue g_initialized = R_BooleanValue_False;

static R_SizeValue g_minimumCapacity = -1;
static R_SizeValue g_maximumCapacity = -1;

static void
R_Stack_ensureFreeCapacity
  (
    R_Stack* self,
    R_SizeValue requiredFreeCapacity
  );

static void
R_Stack_ensureInitialized
  (
  );

static void
R_Stack_destruct
  (
    R_Stack* self
  );

static void
R_Stack_visit
  (
    R_Stack* self
  );

static void
R_Stack_ensureFreeCapacity
  (
    R_Stack* self,
    R_SizeValue requiredFreeCapacity
  )
{
  R_SizeValue newAvailableFreeCapacity = self->capacity - self->size;
  R_SizeValue oldCapacity = self->capacity;
  R_SizeValue newCapacity = oldCapacity;
  while (requiredFreeCapacity > newAvailableFreeCapacity) {
    oldCapacity = self->capacity;
    newCapacity = oldCapacity;
    if (oldCapacity > g_maximumCapacity / 2) {
      // If oldCapacity > maximumCapacity / 2 holds then oldCapacity * 2 > maximumCapacity holds.
      // Consequently, we cannot double the capacity. Try to saturate the capacity.
      if (oldCapacity == g_maximumCapacity) {
        R_setStatus(R_Status_AllocationFailed);
        R_jump();
      } else {
        newCapacity = g_maximumCapacity;
      }
    } else {
      newCapacity = oldCapacity * 2;
    }
    newAvailableFreeCapacity = newCapacity - self->size;
  }
  if (!R_reallocateUnmanaged_nojump(&self->elements, sizeof(R_Value) * newCapacity)) {
    R_jump();
  }
  self->capacity = newCapacity;
}

static void
R_Stack_ensureInitialized
  (
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(R_Value);
    if (g_maximumCapacity > R_Integer32Value_Maximum) {
      g_maximumCapacity = R_Integer32Value_Maximum;
    }
    if (g_minimumCapacity > g_maximumCapacity) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    g_initialized = R_BooleanValue_True;
  }
}

static void
R_Stack_destruct
  (
    R_Stack* self
  )
{
  if (self->elements) {
    R_deallocateUnmanaged_nojump(self->elements);
    self->elements = NULL;
  }
}

static void
R_Stack_visit
  (
    R_Stack* self
  )
{
  if (self->elements) {
    for (R_SizeValue i = 0, n = self->size; i < n; ++i) {
      R_Value_visit(self->elements + i);
    }
  }
}

Rex_defineObjectType("R.Stack", R_Stack, "R.Object", R_Object, &R_Stack_visit, &R_Stack_destruct);

void
R_Stack_construct
  (
    R_Stack* self
  )
{
  R_Stack_ensureInitialized();
  R_Type* _type = _R_Stack_getType();
  R_Object_construct((R_Object*)self);
  self->elements = NULL;
  self->capacity = 0;
  self->size = 0;
  self->capacity = g_minimumCapacity;
  if (!R_allocateUnmanaged_nojump(&self->elements, sizeof(R_Value) * self->capacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    R_Value_setVoidValue(self->elements + i, R_VoidValue_Void);
  }
  R_Object_setType((R_Object*)self, _type);
}

R_Stack*
R_Stack_create
  (
  )
{
  R_Stack* self = R_allocateObject(_R_Stack_getType());
  R_Stack_construct(self);
  return self;
}

void
R_Stack_clear
  (
    R_Stack* self
  )
{ self->size = 0; }

R_SizeValue
R_Stack_getSize
  (
    R_Stack* self
  )
{ return self->size; }

void
R_Stack_push
  (
    R_Stack* self,
    R_Value value
  )
{
  if (self->capacity == self->size) {
    R_Stack_ensureFreeCapacity(self, R_SizeValue_Literal(1));
  }
  self->elements[self->size++] = value;
}

void
R_Stack_pop
  ( 
    R_Stack* self
  )
{
  if (0 == self->size) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  --self->size;
}

R_Value
R_Stack_peek
  (
    R_Stack* self
  )
{
  if (0 == self->size) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  return self->elements[self->size - 1];
}

#define Define(Suffix, Prefix) \
  void \
  R_Stack_push##Suffix##Value \
    ( \
      R_Stack* self, \
      R_##Suffix##Value prefix##Value \
    ) \
  { \
    R_Value value; \
    R_Value_set##Suffix##Value(&value, prefix##Value); \
    R_Stack_push(self, value); \
  } \
\
  R_BooleanValue \
  R_Stack_is##Suffix##Value \
    ( \
      R_Stack* self, \
      R_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      R_setStatus(R_Status_ArgumentValueInvalid); \
      R_jump(); \
    } \
    return R_Value_is##Suffix##Value(self->elements + self->size - index - 1); \
  } \
\
  R_##Suffix##Value \
  R_Stack_get##Suffix##Value \
    ( \
      R_Stack* self, \
      R_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      R_setStatus(R_Status_ArgumentValueInvalid); \
      R_jump(); \
    } \
    R_Value* element = self->elements + self->size - index - 1; \
    if (!R_Value_is##Suffix##Value(element)) { \
      R_setStatus(R_Status_ArgumentValueInvalid); \
      R_jump(); \
    } \
    return R_Value_get##Suffix##Value(element); \
  }

Define(Boolean, boolean)
Define(ForeignProcedure, foreignProcedure)
Define(Integer8, integer8)
Define(Integer16, integer16)
Define(Integer32, integer32)
Define(Integer64, integer64)
Define(Natural8, natural8)
Define(Natural16, natural16)
Define(Natural32, natural32)
Define(Natural64, natural64)
Define(ObjectReference, objectReference)
Define(Size, size)
Define(Void, void)

#undef Define