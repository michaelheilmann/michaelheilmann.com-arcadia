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
#include "Arcadia/Ring2/Implementation/Set.h"

#include "Arcadia/Ring1/Include.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

struct _Arcadia_Set_Node {
  _Arcadia_Set_Node* next;
  Arcadia_SizeValue hash;
  Arcadia_Value value;
};

static void
Arcadia_Set_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_Set_ensureInitialized
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_Set_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Set_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  );

static void
Arcadia_Set_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  );

static void
Arcadia_Set_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  );

static Arcadia_SizeValue
Arcadia_Set_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Set_constructImpl,
  .destruct = &Arcadia_Set_destruct,
  .visit = &Arcadia_Set_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Set", Arcadia_Set, u8"Arcadia.Collection", Arcadia_Collection, &_typeOperations);

static void
Arcadia_Set_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
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
  _Arcadia_Set_Node** oldBuckets = self->buckets;
  _Arcadia_Set_Node** newBuckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_Set_Node*) * newCapacity);
  for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
    newBuckets[i] = NULL;
  }
  for (Arcadia_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
    while (oldBuckets[i]) {
      _Arcadia_Set_Node* node = oldBuckets[i];
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
Arcadia_Set_ensureInitialized
  (
    Arcadia_Thread* thread
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(_Arcadia_Set_Node*);
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
Arcadia_Set_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      _Arcadia_Set_Node* node = self->buckets[i];
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
Arcadia_Set_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  )
{
  if (self->buckets) {
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      _Arcadia_Set_Node* node = self->buckets[i];
      while (node) {
        Arcadia_Value_visit(thread, &node->value);
        node = node->next;
      }
    }
  }
}

static void
Arcadia_Set_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Set* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Set_getType(thread);
  Arcadia_Set_ensureInitialized(thread);
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
  _self->buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_Set_Node*) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  ((Arcadia_Collection*)_self)->clear = (void (*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_Set_clearImpl;
  ((Arcadia_Collection*)_self)->getSize = (Arcadia_SizeValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_Set_getSizeImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Set_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      _Arcadia_Set_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Memory_deallocateUnmanaged(thread, node);
      node = NULL;
    }
  }
  self->size = 0;
}

static Arcadia_SizeValue
Arcadia_Set_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  )
{
  return self->size;
}

void
Arcadia_Set_add
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
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
  _Arcadia_Set_Node* node = self->buckets[index];
  while (node) {
    if (Arcadia_Value_isEqualTo(thread, &value, &node->value)) {
      Arcadia_Value oldValueBackup = node->value;
      if (oldValue) *oldValue = oldValueBackup;
      node->value = value;
      return;
    }
  }
  node = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_Set_Node));
  node->value = value;
  node->hash = hash;
  node->next = self->buckets[index];
  self->buckets[index] = node;
  self->size++;
  if (oldValue) *oldValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
  return;
}

Arcadia_BooleanValue
Arcadia_Set_contains
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value
  )
{
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &value);
  Arcadia_SizeValue index = hash % self->capacity;
  for (_Arcadia_Set_Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash && Arcadia_Value_isEqualTo(thread, &value, &node->value)) {
      return Arcadia_BooleanValue_True;
    }
  }
  return Arcadia_BooleanValue_False;
}

Arcadia_Set*
Arcadia_Set_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Set* self = Arcadia_allocateObject(thread, _Arcadia_Set_getType(thread), 0, &argumentValues[0]);
  return self;
}


Arcadia_Value
Arcadia_Set_get
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value
  )
{
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &value);
  Arcadia_SizeValue index = hash % self->capacity;
  _Arcadia_Set_Node** previous = &self->buckets[index];
  _Arcadia_Set_Node* current = self->buckets[index];
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

void
Arcadia_Set_remove
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
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
  _Arcadia_Set_Node** previous = &self->buckets[index];
  _Arcadia_Set_Node* current = self->buckets[index];
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
