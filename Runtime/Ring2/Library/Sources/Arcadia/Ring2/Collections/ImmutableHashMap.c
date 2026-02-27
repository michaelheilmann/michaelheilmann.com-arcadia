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
#include "Arcadia/Ring2/Collections/ImmutableHashMap.h"

#include "Arcadia/Ring2/Include.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

struct _Arcadia_ImmutableHashMap_Node {
  _Arcadia_ImmutableHashMap_Node* next;
  Arcadia_SizeValue hash;
  Arcadia_Value key;
  Arcadia_Value value;
};

static void
Arcadia_ImmutableHashMap_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_ImmutableHashMap_ensureInitialized
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_ImmutableHashMap_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  );

static void
Arcadia_ImmutableHashMap_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMapDispatch* self
  );

static void
Arcadia_ImmutableHashMap_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  );

static void
Arcadia_ImmutableHashMap_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  );

static void
Arcadia_ImmutableHashMap_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  );

static Arcadia_SizeValue
Arcadia_ImmutableHashMap_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  );

static Arcadia_BooleanValue
Arcadia_ImmutableHashMap_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  );

static Arcadia_Value
Arcadia_ImmutableHashMap_getImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self,
    Arcadia_Value key
  );

static void
Arcadia_ImmutableHashMap_removeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self,
    Arcadia_Value key,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  );

static void
Arcadia_ImmutableHashMap_setImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self,
    Arcadia_Value key,
    Arcadia_Value value,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  );

static Arcadia_List*
Arcadia_ImmutableHashMap_getValuesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  );

static Arcadia_List*
Arcadia_ImmutableHashMap_getKeysImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_ImmutableHashMap_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_ImmutableHashMap_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_ImmutableHashMap_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ImmutableHashMap", Arcadia_ImmutableHashMap,
                         u8"Arcadia.Map", Arcadia_Map,
                         &_typeOperations);

static void
Arcadia_ImmutableHashMap_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self,
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
  _Arcadia_ImmutableHashMap_Node** oldBuckets = self->buckets;
  _Arcadia_ImmutableHashMap_Node** newBuckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_ImmutableHashMap_Node*) * newCapacity);
  for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
    newBuckets[i] = NULL;
  }
  for (Arcadia_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
    while (oldBuckets[i]) {
      _Arcadia_ImmutableHashMap_Node* node = oldBuckets[i];
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
Arcadia_ImmutableHashMap_ensureInitialized
  (
    Arcadia_Thread* thread
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(_Arcadia_ImmutableHashMap_Node*);
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
Arcadia_ImmutableHashMap_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      _Arcadia_ImmutableHashMap_Node* node = self->buckets[i];
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
Arcadia_ImmutableHashMap_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  )
{
  if (self->buckets) {
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      _Arcadia_ImmutableHashMap_Node* node = self->buckets[i];
      while (node) {
        Arcadia_Value_visit(thread, &node->key);
        Arcadia_Value_visit(thread, &node->value);
        node = node->next;
      }
    }
  }
}

static void
Arcadia_ImmutableHashMap_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ImmutableHashMap_getType(thread);
  Arcadia_ImmutableHashMap_ensureInitialized(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value nargs = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 == nargs) {
    self->buckets = NULL;
    self->capacity = 0;
    self->size = 0;
    self->capacity = g_minimumCapacity;
    self->buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_ImmutableHashMap_Node*) * self->capacity);
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      self->buckets[i] = NULL;
    }
  } else if (1 == nargs) {
    Arcadia_ImmutableHashMap* other = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_HashMap_getType(thread));
    self->buckets = NULL;
    self->size = 0;
    self->capacity = other->capacity;
    self->buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_ImmutableHashMap_Node*) * self->capacity);
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      self->buckets[i] = NULL;
    }
    for (Arcadia_SizeValue i = 0, n = other->capacity; i < n; ++i) {
      for (_Arcadia_ImmutableHashMap_Node* otherNode = other->buckets[i]; NULL != otherNode; otherNode = otherNode->next) {
        _Arcadia_ImmutableHashMap_Node* selfNode = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_ImmutableHashMap_Node));
        selfNode->hash = otherNode->hash;
        selfNode->key = otherNode->key;
        selfNode->value = otherNode->value;
        selfNode->next = self->buckets[i];
        self->buckets[i] = selfNode;
      }
    }
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, nargs + 1);
}

static void
Arcadia_ImmutableHashMap_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMapDispatch* self
  )
{
  ((Arcadia_CollectionDispatch*)self)->clear = (void (*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_ImmutableHashMap_clearImpl;
  ((Arcadia_CollectionDispatch*)self)->getSize = (Arcadia_SizeValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_ImmutableHashMap_getSizeImpl;
  ((Arcadia_CollectionDispatch*)self)->isImmutable = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_ImmutableHashMap_isImmutableImpl;
  ((Arcadia_MapDispatch*)self)->get = (Arcadia_Value(*)(Arcadia_Thread*, Arcadia_Map*, Arcadia_Value)) & Arcadia_ImmutableHashMap_getImpl;
  ((Arcadia_MapDispatch*)self)->remove = (void (*)(Arcadia_Thread*, Arcadia_Map*, Arcadia_Value, Arcadia_Value*, Arcadia_Value*)) & Arcadia_ImmutableHashMap_removeImpl;
  ((Arcadia_MapDispatch*)self)->set = (void (*)(Arcadia_Thread*, Arcadia_Map*, Arcadia_Value, Arcadia_Value, Arcadia_Value*, Arcadia_Value*)) & Arcadia_ImmutableHashMap_setImpl;
  ((Arcadia_MapDispatch*)self)->getKeys = (Arcadia_List * (*)(Arcadia_Thread*, Arcadia_Map*)) & Arcadia_ImmutableHashMap_getKeysImpl;
  ((Arcadia_MapDispatch*)self)->getValues = (Arcadia_List * (*)(Arcadia_Thread*, Arcadia_Map*)) & Arcadia_ImmutableHashMap_getValuesImpl;
}

static void
Arcadia_ImmutableHashMap_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  )
{
  Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
  Arcadia_Thread_jump(thread);
}

static Arcadia_SizeValue
Arcadia_ImmutableHashMap_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  )
{
  return self->size;
}

static Arcadia_BooleanValue
Arcadia_ImmutableHashMap_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  )
{
  return Arcadia_BooleanValue_True;
}

static Arcadia_Value
Arcadia_ImmutableHashMap_getImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self,
    Arcadia_Value key
  )
{
  if (Arcadia_Value_isVoidValue(&key)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &key);
  Arcadia_SizeValue index = hash % self->capacity;

  for (_Arcadia_ImmutableHashMap_Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash) {
      if (Arcadia_Value_isEqualTo(thread, &key, &node->key)) {
        return node->value;
      }
    }
  }
  return Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
}

static void
Arcadia_ImmutableHashMap_removeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self,
    Arcadia_Value key,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  )
{
  Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
  Arcadia_Thread_jump(thread);
}

static void
Arcadia_ImmutableHashMap_setImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self,
    Arcadia_Value key,
    Arcadia_Value value,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  )
{
  Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
  Arcadia_Thread_jump(thread);
}

Arcadia_ImmutableHashMap*
Arcadia_ImmutableHashMap_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
  } else {
    Arcadia_ValueStack_pushValue(thread, &value);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
  }
  ARCADIA_CREATEOBJECT(Arcadia_HashMap);
}

static Arcadia_List*
Arcadia_ImmutableHashMap_getValuesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  )
{
  Arcadia_List* list = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    _Arcadia_ImmutableHashMap_Node* node = self->buckets[i];
    while (node) {
      Arcadia_List_insertBack(thread, list, node->value);
      node = node->next;
    }
  }
  return list;
}

static Arcadia_List*
Arcadia_ImmutableHashMap_getKeysImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableHashMap* self
  )
{
  Arcadia_List* list = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    _Arcadia_ImmutableHashMap_Node* node = self->buckets[i];
    while (node) {
      Arcadia_List_insertBack(thread, list, node->key);
      node = node->next;
    }
  }
  return list;
}
