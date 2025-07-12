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
#include "Arcadia/Ring2/Implementation/List.h"

#include "Arcadia/Ring2/Include.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

static void
Arcadia_List_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_List_ensureInitialized
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_List_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_List_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  );

static void
Arcadia_List_visit
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  );

static void
Arcadia_List_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  );

static Arcadia_SizeValue
Arcadia_List_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_List_constructImpl,
  .destruct = &Arcadia_List_destruct,
  .visit = &Arcadia_List_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.List", Arcadia_List, u8"Arcadia.Collection", Arcadia_Collection, &_typeOperations);

static void
Arcadia_List_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
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
Arcadia_List_ensureInitialized
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
Arcadia_List_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_List* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_List_getType(thread);
  Arcadia_List_ensureInitialized(thread);
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
  _self->elements = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_Value) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    Arcadia_Value_setVoidValue(_self->elements + i, Arcadia_VoidValue_Void);
  }
  ((Arcadia_Collection*)_self)->clear = (void (*)(Arcadia_Thread*,Arcadia_Collection*))&Arcadia_List_clearImpl;
  ((Arcadia_Collection*)_self)->getSize = (Arcadia_SizeValue (*)(Arcadia_Thread*,Arcadia_Collection*))&Arcadia_List_getSizeImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_List_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  )
{
  if (self->elements) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->elements);
    self->elements = NULL;
  }
}

static void
Arcadia_List_visit
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  )
{
  if (self->elements) {
    for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
      Arcadia_Value_visit(thread, self->elements + i);
    }
  }
}

static void
Arcadia_List_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  )
{ self->size = 0; }

static Arcadia_SizeValue
Arcadia_List_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  )
{ return self->size; }

Arcadia_List*
Arcadia_List_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_List* self = Arcadia_allocateObject(thread, _Arcadia_List_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_List_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_Value value
  )
{
  Arcadia_List_insertAt(thread, self, self->size, value);
}

void
Arcadia_List_insertFront
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_Value value
  )
{
  Arcadia_List_insertAt(thread, self, Arcadia_SizeValue_Literal(0), value);
}

void
Arcadia_List_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
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
    Arcadia_List_ensureFreeCapacity(thread, self, Arcadia_SizeValue_Literal(1));
  }
  if (index < self->size) {
    Arcadia_Memory_copy(thread, self->elements + index + 1,
                        self->elements + index + 0, sizeof(Arcadia_Value) * (self->size - index));
  }
  self->elements[index] = value;
  self->size++;
}

Arcadia_Value
Arcadia_List_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_SizeValue index
  )
{
  if (index >= self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->elements[index];
}

void
Arcadia_List_removeAt
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
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

#define Define(Type, Suffix, Variable) \
  void \
  Arcadia_List_insertBack##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    Arcadia_List_insertBack(thread, self, value); \
  } \
\
  void \
  Arcadia_List_insertFront##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    Arcadia_List_insertFront(thread, self, value); \
  } \
\
  Arcadia_BooleanValue \
  Arcadia_List_is##Suffix##ValueAt \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Thread_jump(thread); \
    } \
    return Arcadia_Value_is##Suffix##Value(self->elements + index); \
  } \
\
  Type##Value \
  Arcadia_List_get##Suffix##ValueAt \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Thread_jump(thread); \
    } \
    Arcadia_Value* element = self->elements + index; \
    if (!Arcadia_Value_is##Suffix##Value(element)) { \
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Thread_jump(thread); \
    } \
    return Arcadia_Value_get##Suffix##Value(element); \
  }

Define(Arcadia_Boolean, Boolean, boolean)
Define(Arcadia_BigInteger, BigInteger, bigInteger)
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

Arcadia_List*
Arcadia_List_filter
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_Value context,
    Arcadia_BooleanValue(*predicate)(Arcadia_Thread* thread, Arcadia_Value context, Arcadia_Value value)
  )
{
  Arcadia_List* result = Arcadia_List_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self); i < n; ++i) {
    Arcadia_Value v = Arcadia_List_getAt(thread, self, i);
    if ((*predicate)(thread, context, v)) {
      Arcadia_List_insertBack(thread, result, v);
    }
  }
  return result;
}
