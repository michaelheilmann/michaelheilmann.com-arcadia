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
#include "Arcadia/Ring2/Collections/HashSet.h"

#include "Arcadia/Ring1/Include.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

struct _Arcadia_HashSet_Node {
  _Arcadia_HashSet_Node* next;
  Arcadia_SizeValue hash;
  Arcadia_Value value;
};

static void
Arcadia_HashSet_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_HashSet_ensureInitialized
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_HashSet_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_HashSet_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  );

static void
Arcadia_HashSet_visit
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  );

static void
Arcadia_HashSet_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  );

static Arcadia_SizeValue
Arcadia_HashSet_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  );

static Arcadia_BooleanValue
Arcadia_HashSet_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  );

static void
Arcadia_HashSet_addImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_Value value,
    Arcadia_Value* oldValue
  );

static Arcadia_BooleanValue
Arcadia_HashSet_containsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_Value value
  );

static Arcadia_Value
Arcadia_HashSet_getImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_Value value
  );

static void
Arcadia_HashSet_removeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_Value value,
    Arcadia_Value* oldValue
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_HashSet_constructImpl,
  .destruct = &Arcadia_HashSet_destruct,
  .visit = &Arcadia_HashSet_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.HashSet", Arcadia_HashSet, u8"Arcadia.Set", Arcadia_Set, &_typeOperations);

static void
Arcadia_HashSet_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
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
  _Arcadia_HashSet_Node** oldBuckets = self->buckets;
  _Arcadia_HashSet_Node** newBuckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_HashSet_Node*) * newCapacity);
  for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
    newBuckets[i] = NULL;
  }
  for (Arcadia_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
    while (oldBuckets[i]) {
      _Arcadia_HashSet_Node* node = oldBuckets[i];
      oldBuckets[i] = oldBuckets[i]->next;
      Arcadia_SizeValue j = node->hash % newCapacity;
      node->next = newBuckets[j];
      newBuckets[j] = node;
    }
  }
  Arcadia_Memory_deallocateUnmanaged(thread, oldBuckets);
  self->buckets = newBuckets;
  self->capacity = newCapacity;
}

static void
Arcadia_HashSet_ensureInitialized
  (
    Arcadia_Thread* thread
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(_Arcadia_HashSet_Node*);
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
Arcadia_HashSet_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      _Arcadia_HashSet_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Memory_deallocateUnmanaged(thread, node);
      node = NULL;
    }
  }
  if (self->buckets) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->buckets);
    self->buckets = NULL;
  }
}

static void
Arcadia_HashSet_visit
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  )
{
  if (self->buckets) {
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      _Arcadia_HashSet_Node* node = self->buckets[i];
      while (node) {
        Arcadia_Value_visit(thread, &node->value);
        node = node->next;
      }
    }
  }
}

static void
Arcadia_HashSet_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_HashSet* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_HashSet_getType(thread);
  Arcadia_HashSet_ensureInitialized(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->buckets = NULL;
  _self->capacity = 0;
  _self->size = 0;
  _self->capacity = g_minimumCapacity;
  _self->buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_HashSet_Node*) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  ((Arcadia_Collection*)_self)->clear = (void (*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_HashSet_clearImpl;
  ((Arcadia_Collection*)_self)->getSize = (Arcadia_SizeValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_HashSet_getSizeImpl;
  ((Arcadia_Collection*)_self)->isImmutable = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_HashSet_isImmutableImpl;
  ((Arcadia_Set*)_self)->add = (void (*)(Arcadia_Thread*, Arcadia_Set*, Arcadia_Value, Arcadia_Value*)) &Arcadia_HashSet_addImpl;
  ((Arcadia_Set*)_self)->contains = (Arcadia_BooleanValue (*)(Arcadia_Thread*, Arcadia_Set*, Arcadia_Value)) &Arcadia_HashSet_containsImpl;
  ((Arcadia_Set*)_self)->get = (Arcadia_Value (*)(Arcadia_Thread*, Arcadia_Set*, Arcadia_Value)) &Arcadia_HashSet_getImpl;
  ((Arcadia_Set*)_self)->remove = (void (*)(Arcadia_Thread*, Arcadia_Set*, Arcadia_Value, Arcadia_Value*)) & Arcadia_HashSet_removeImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_HashSet_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      _Arcadia_HashSet_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Memory_deallocateUnmanaged(thread, node);
      node = NULL;
    }
  }
  self->size = 0;
}

static Arcadia_SizeValue
Arcadia_HashSet_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  )
{
  return self->size;
}

static Arcadia_BooleanValue
Arcadia_HashSet_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self
  )
{ return Arcadia_BooleanValue_False; }

static void
Arcadia_HashSet_addImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_Value value,
    Arcadia_Value* oldValue
  )
{
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &value);
  Arcadia_SizeValue index = hash % self->capacity;
  _Arcadia_HashSet_Node* node = self->buckets[index];
  while (node) {
    if (Arcadia_Value_isEqualTo(thread, &value, &node->value)) {
      Arcadia_Value oldValueBackup = node->value;
      if (oldValue) *oldValue = oldValueBackup;
      node->value = value;
      return;
    }
    node = node->next;
  }
  node = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_HashSet_Node));
  node->value = value;
  node->hash = hash;
  node->next = self->buckets[index];
  self->buckets[index] = node;
  self->size++;
  if (oldValue) *oldValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
  return;
}

static Arcadia_BooleanValue
Arcadia_HashSet_containsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_Value value
  )
{
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &value);
  Arcadia_SizeValue index = hash % self->capacity;
  for (_Arcadia_HashSet_Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash && Arcadia_Value_isEqualTo(thread, &value, &node->value)) {
      return Arcadia_BooleanValue_True;
    }
  }
  return Arcadia_BooleanValue_False;
}

static Arcadia_Value
Arcadia_HashSet_getImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_Value value
  )
{
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &value);
  Arcadia_SizeValue index = hash % self->capacity;
  _Arcadia_HashSet_Node** previous = &self->buckets[index];
  _Arcadia_HashSet_Node* current = self->buckets[index];
  while (current) {
    if (hash == current->hash && Arcadia_Value_isEqualTo(thread, &value, &current->value)) {
      return current->value;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
  return Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
}

static void
Arcadia_HashSet_removeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashSet* self,
    Arcadia_Value value,
    Arcadia_Value* oldValue
  )
{
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &value);
  Arcadia_SizeValue index = hash % self->capacity;
  _Arcadia_HashSet_Node** previous = &self->buckets[index];
  _Arcadia_HashSet_Node* current = self->buckets[index];
  while (current) {
    if (hash == current->hash && Arcadia_Value_isEqualTo(thread, &value, &current->value)) {
      Arcadia_Value oldValueBackup = current->value;
      *previous = current->next;
      self->size--;
      Arcadia_Memory_deallocateUnmanaged(thread, current);
      if (oldValue) *oldValue = oldValueBackup;
      return;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
  if (oldValue) *oldValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
  return;
}

Arcadia_HashSet*
Arcadia_HashSet_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_HashSet* self = Arcadia_allocateObject(thread, _Arcadia_HashSet_getType(thread), 0, &argumentValues[0]);
  return self;
}
