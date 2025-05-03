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
#include "Arcadia/Ring2/Implementation/Stack.h"

#include "Arcadia/Ring2/Include.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

static void
Arcadia_Stack_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_Stack_ensureInitialized
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_Stack_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  );

static void
Arcadia_Stack_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  );

static void
Arcadia_Stack_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Stack_constructImpl,
  .destruct = &Arcadia_Stack_destruct,
  .visit = &Arcadia_Stack_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"Arcadia.Stack", Arcadia_Stack, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Stack_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self,
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
  Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->elements, sizeof(Arcadia_Value) * newCapacity);
  self->capacity = newCapacity;
}

static void
Arcadia_Stack_ensureInitialized
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
Arcadia_Stack_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Stack* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_Stack_ensureInitialized(thread);
  Arcadia_TypeValue _type = _Arcadia_Stack_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->elements = NULL;
  _self->capacity = 0;
  _self->size = 0;
  _self->capacity = g_minimumCapacity;
  Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &_self->elements, sizeof(Arcadia_Value) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    Arcadia_Value_setVoidValue(_self->elements + i, Arcadia_VoidValue_Void);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Stack_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{
  if (self->elements) {
    Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), self->elements);
    self->elements = NULL;
  }
}

static void
Arcadia_Stack_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{
  if (self->elements) {
    for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
      Arcadia_Value_visit(thread, self->elements + i);
    }
  }
}

Arcadia_Stack*
Arcadia_Stack_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Stack* self = Arcadia_allocateObject(thread, _Arcadia_Stack_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_Stack_clear
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{ self->size = 0; }

Arcadia_SizeValue
Arcadia_Stack_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{ return self->size; }

void
Arcadia_Stack_push
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self,
    Arcadia_Value value
  )
{
  if (self->capacity == self->size) {
    Arcadia_Stack_ensureFreeCapacity(thread, self, Arcadia_SizeValue_Literal(1));
  }
  self->elements[self->size++] = value;
}

void
Arcadia_Stack_pop
  ( 
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{
  if (0 == self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  --self->size;
}

Arcadia_Value
Arcadia_Stack_peek
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{
  if (0 == self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->elements[self->size - 1];
}

#define Define(Type, Suffix, Variable) \
  void \
  Arcadia_Stack_push##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_Stack* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    Arcadia_Stack_push(thread, self, value); \
  } \
\
  Arcadia_BooleanValue \
  Arcadia_Stack_is##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_Stack* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Thread_jump(thread); \
    } \
    return Arcadia_Value_is##Suffix##Value(self->elements + self->size - index - 1); \
  } \
\
  Type##Value \
  Arcadia_Stack_get##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_Stack* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Thread_jump(thread); \
    } \
    Arcadia_Value* element = self->elements + self->size - index - 1; \
    if (!Arcadia_Value_is##Suffix##Value(element)) { \
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Thread_jump(thread); \
    } \
    return Arcadia_Value_get##Suffix##Value(element); \
  }

Define(Arcadia_Boolean, Boolean, boolean)
Define(Arcadia_ForeignProcedure, ForeignProcedure, foreignProcedure)
Define(Arcadia_Integer8, Integer8, integer8)
Define(Arcadia_Integer16, Integer16, integer16)
Define(Arcadia_Integer32, Integer32, integer32)
Define(Arcadia_Integer64, Integer64, integer64)
Define(Arcadia_Natural8, Natural8, natural8)
Define(Arcadia_Natural16, Natural16, natural16)
Define(Arcadia_Natural32, Natural32, natural32)
Define(Arcadia_Natural64, Natural64, natural64)
Define(Arcadia_ObjectReference, ObjectReference, objectReference)
Define(Arcadia_Size, Size, size)
Define(Arcadia_Void, Void, void)

#undef Define