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
#include "Arcadia/Ring2/Implementation/Deque.h"

#include "Arcadia/Ring2/Implementation/ArgumentsValidation.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

// Macro-like function to compute index % capacity.
static inline Arcadia_SizeValue MAX(Arcadia_SizeValue self, Arcadia_SizeValue other);

static inline Arcadia_SizeValue MIN(Arcadia_SizeValue self, Arcadia_SizeValue other);

static inline MOD(Arcadia_SizeValue index, Arcadia_SizeValue capacity);

static inline Arcadia_SizeValue MAX(Arcadia_SizeValue self, Arcadia_SizeValue other) {
  return self > other ? self : other;
}

static inline Arcadia_SizeValue MIN(Arcadia_SizeValue self, Arcadia_SizeValue other) {
  return self < other ? self : other;
}

static inline MOD(Arcadia_SizeValue index, Arcadia_SizeValue capacity) {
  return index % capacity;
}

struct Arcadia_Deque {
  Arcadia_Object _parent;
  /// @brief A pointer to an array of @a capacity @a Arcadia_Value elements.
  Arcadia_Value* elements;
  /// @brief The capacity, in elements, of the array pointed to by @a array.
  Arcadia_SizeValue capacity;
  /// @brief The number of elements in this array.
  Arcadia_SizeValue size;
  /// @brief The position to read the next element from.
  Arcadia_SizeValue read;

};

static void
Arcadia_Deque_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_Deque_ensureInitialized
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_Deque_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Deque_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

static void
Arcadia_Deque_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Deque_constructImpl,
  .destruct = &Arcadia_Deque_destruct,
  .visit = &Arcadia_Deque_visit,
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

Arcadia_defineObjectType(u8"Arcadia.Deque", Arcadia_Deque, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Deque_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
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
  Arcadia_Value* oldElements = self->elements;
  Arcadia_Value* newElements = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_Value) * newCapacity);
  for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
    newElements[i] = oldElements[MOD(self->read + i, self->capacity)];
  }
  Arcadia_Memory_deallocateUnmanaged(thread, oldElements);
  self->elements = newElements;
  self->capacity = newCapacity;
}

static void
Arcadia_Deque_ensureInitialized
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
Arcadia_Deque_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  if (self->elements) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->elements);
    self->elements = NULL;
  }
}

static void
Arcadia_Deque_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
    Arcadia_Value_visit(thread, &self->elements[MOD(self->read + i, self->capacity)]);
  }
}

static void
Arcadia_Deque_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Deque* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Deque_getType(thread);
  Arcadia_Deque_ensureInitialized(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (numberOfArgumentValues) {
    Arcadia_Deque* other = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_Deque_getType(thread));
    _self->elements = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_Value) * other->capacity);
    Arcadia_Memory_copy(thread, _self->elements, other->elements, sizeof(Arcadia_Value) * other->capacity);
    _self->read = other->read;
    _self->size = other->size;
    _self->capacity = other->capacity;
  } else {
    _self->elements = NULL;
    _self->read = 0;
    _self->size = 0;
    _self->capacity = g_minimumCapacity;
    _self->elements = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_Value) * _self->capacity);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

Arcadia_Deque*
Arcadia_Deque_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Deque* self = Arcadia_allocateObject(thread, _Arcadia_Deque_getType(thread), 0, &argumentValues[0]);
  return self;
}

Arcadia_Deque*
Arcadia_Deque_clone
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(self),
  };
  Arcadia_Deque* clone = Arcadia_allocateObject(thread, _Arcadia_Deque_getType(thread), 1, &argumentValues[0]);
  return clone;
}

void
Arcadia_Deque_clear
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  self->size = 0;
  self->read = 0;
}

Arcadia_SizeValue
Arcadia_Deque_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Deque const* self
  )
{ return self->size; }

void
Arcadia_Deque_insertFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_Value value
  )
{ Arcadia_Deque_insertAt(thread, self, 0, value); }

void
Arcadia_Deque_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_Value value
  )
{ Arcadia_Deque_insertAt(thread, self, self->size, value);}

void
Arcadia_Deque_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  )
{
  Arcadia_Deque_ensureFreeCapacity(thread, self, 1);

  Arcadia_SizeValue const capacity = self->capacity; // The capacity does not change anymore for the rest of this
                                                     // function but is frequently referenced, hence it is cached
                                                     // here.

  // The goal of the following algorithm is to minimize the number of shift operations when inserting into an index
  // smaller than size.

  // Assume the deque is not empty.
  // Treating the deque as an infinite array,
  // ..., a[0],...,a[read],...,a[read+index], ..., a[read+size-1]
  // then
  // a) the index of the first element is "read" and
  // b) the index of the last element is "read + size - 1" and
  // c) "read <= index <= read + size".
  //
  // So to insert at index "index", one can either shift up the elements
  // "a[read + index],... a[read+size-1]" or
  // shift down the elements
  // "a[read] ... a[read + index-1]"
  // to make room for the new element.
  //
  // The choice made here is to minimize the number of shifts:
  // if "index < size / 2" then "a[read] ... a[read + index - 1]" is shifted down
  // and otherwise "a[read + index],... a[read+size-1]" is shifted up.
  if (index < self->size / 2) {
    // If a' ist the new queue and a is the old queue, then the operation
    // can be described as follows:
    // - a'[read-1] = a[read], ..., a'[read - 1 + index] = a[read + index]
    // - a'[read+index] = newElement
    // - read' = read - 1
    // - size' = size + 1
    // As read' = read - 1, one can also write
    // - a'[read'] = a[read' + 1], ..., a'[read + index] = a[read' + index + 1]
    // which is the form used here.
    Arcadia_SizeValue offset = MOD(self->read - 1, capacity);
    for (Arcadia_SizeValue j = 0; j < index; ++j) {
      self->elements[MOD(offset + j, capacity)] = self->elements[MOD(offset + j + 1, capacity)];
    }
    self->read = MOD(self->read - 1, capacity);
  } else {
    // If a' ist the new queue and a is the old queue, then the operation
    // can be described as follows:
    // - a'[read + size] = a[read + size - 1], ..., a'[read + index + 1] = a[read + index]
    // - a'[read + index] = newElement
    // - read' = read
    // - size' = size+1
    Arcadia_SizeValue offset = self->read;
    for (Arcadia_SizeValue j = self->size; j > index; --j) {
      self->elements[MOD(offset + j, capacity)] = self->elements[MOD(offset + j - 1, capacity)];
    }
  }
  self->elements[MOD(self->read + index, capacity)] = value;
  self->size++;
}

Arcadia_Value
Arcadia_Deque_getFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  return Arcadia_Deque_getAt(thread, self, 0);
}

Arcadia_Value
Arcadia_Deque_getBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  if (!self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid),
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Deque_getAt(thread, self, self->size - 1);
}

Arcadia_Value
Arcadia_Deque_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index
  )
{
  if (index >= self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid),
    Arcadia_Thread_jump(thread);
  }
  return self->elements[MOD(self->read + index, self->capacity)];
}

void
Arcadia_Deque_removeFront
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  Arcadia_Deque_removeAt(thread, self, 0);
}

void
Arcadia_Deque_removeBack
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self
  )
{
  if (!self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid),
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Deque_removeAt(thread, self, self->size - 1);
}

void
Arcadia_Deque_removeAt
  (
    Arcadia_Thread* thread,
    Arcadia_Deque* self,
    Arcadia_SizeValue index
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (index >= self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue const capacity = self->capacity;
  if (index < self->size / 2) {
    // - a'[read] = a[read-1], ..., a'[read + index] = a[read + index - 1]
    // - read' = read + 1
    // - size' = size - 1
    Arcadia_SizeValue offset = self->read;
    for (Arcadia_SizeValue j = index; j > 0; --j) {
      self->elements[MOD(offset + j, capacity)] = self->elements[MOD(offset + j - 1, capacity)];
    }
    self->read = MOD(self->read + 1, capacity);
  } else {
    // - a'[read+index] = a[read+index+1], ..., a'[read+size-2] = a[read+size-1]
    // - read' = read
    // - size' = size - 1
    // shift a[i+1],..,a[n-1] left one position
    for (Arcadia_SizeValue j = index; j < self->size - 1; ++j) {
      self->elements[MOD(self->read + j, capacity)] = self->elements[MOD(self->read + j + 1, capacity)];
    }
  }
  self->size--;
}
