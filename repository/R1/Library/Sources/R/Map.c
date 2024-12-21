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

// Last modified: 2024-10-07

#include "R/Map.h"

#include "R/ArmsIntegration.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/DynamicArrayUtilities.h"
#include "R/cstdlib.h"

static R_BooleanValue g_initialized = R_BooleanValue_False;

static R_SizeValue g_minimumCapacity = -1;
static R_SizeValue g_maximumCapacity = -1;

typedef struct Node Node;

struct Node {
  Node* next;
  R_SizeValue hash;
  R_Value key;
  R_Value value;
};

struct R_Map {
  R_Object _parent;
  Node** buckets;
  R_SizeValue size;
  R_SizeValue capacity;
};

static void
R_Map_ensureFreeCapacity
  (
    R_Map* self,
    R_SizeValue requiredFreeCapacity
  );

static void
R_Map_ensureInitialized
  (
  );

static void
R_Map_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Map_destruct
  (
    R_Map* self
  );

static void
R_Map_visit
  (
    R_Map* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Map_constructImpl,
  .destruct = &R_Map_destruct,
  .visit = &R_Map_visit,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("R.Map", R_Map, "R.Object", R_Object, &_typeOperations);

static void
R_Map_ensureFreeCapacity
  (
    R_Map* self,
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
  Node** oldBuckets = self->buckets;
  Node** newBuckets = NULL;
  if (!R_allocateUnmanaged_nojump((void**)&newBuckets, sizeof(Node*) * newCapacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = newCapacity; i < n; ++i) {
    newBuckets[i] = NULL;
  }
  for (R_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
    while (oldBuckets[i]) {
      Node* node = oldBuckets[i];
      oldBuckets[i] = oldBuckets[i]->next;
      R_SizeValue j = node->hash % newCapacity;
      node->next = newBuckets[j];
      newBuckets[j] = node;
    }
  }
  R_deallocateUnmanaged_nojump(oldBuckets);
  self->buckets = newBuckets;
  self->capacity = newCapacity;
}

static void
R_Map_ensureInitialized
  (
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(Node*);
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
R_Map_destruct
  (
    R_Map* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      R_deallocateUnmanaged_nojump(node);
      node = NULL;
    }
  }
  if (self->buckets) {
    R_deallocateUnmanaged_nojump(self->buckets);
    self->buckets = NULL;
  }
}

static void
R_Map_visit
  (
    R_Map* self
  )
{
  if (self->buckets) {
    for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      Node* node = self->buckets[i];
      while (node) {
        R_Value_visit(&node->key);
        R_Value_visit(&node->value);
        node = node->next;
      }
    }
  }
}

static void
R_Map_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Map* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Map_getType();
  R_Map_ensureInitialized();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->buckets = NULL;
  _self->capacity = 0;
  _self->size = 0;
  _self->capacity = g_minimumCapacity;
  if (!R_allocateUnmanaged_nojump((void**)&_self->buckets, sizeof(Node*) * _self->capacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  R_Object_setType((R_Object*)_self, _type);
}

R_Map*
R_Map_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_Map* self = R_allocateObject(_R_Map_getType(), 0, &argumentValues[0]);
  R_Value selfValue = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)self };
  R_Map_constructImpl(&selfValue, 0, &argumentValues[0]);
  return self;
}

R_Map*
R_Map_clone
  (
    R_Map* self
  )
{
  R_Map* clone = R_Map_create();
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    for (Node* node = self->buckets[i]; NULL != node; node = node->next) {
      R_Map_set(clone, node->key, node->value);
    }
  }
  return clone;
}

void
R_Map_clear
  (
    R_Map* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      R_deallocateUnmanaged_nojump(node);
      node = NULL;
    }
  }
  self->size = 0;
}


R_SizeValue
R_Map_getSize
  (
    R_Map const* self
  )
{ return self->size; }

void
R_Map_set
  (
    R_Map* self,
    R_Value key,
    R_Value value
  )
{ 
  if (R_Value_isVoidValue(&key)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_SizeValue hash = R_Value_hash(&key);
  R_SizeValue index = hash % self->capacity;
  for (Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash) {
      if (R_Value_isEqualTo(&key, &node->key)) {
        node->key = key;
        node->value = value;
        return;
      }
    }
  }
  Node* node = NULL;
  if (!R_allocateUnmanaged_nojump(&node, sizeof(Node))) {
    R_jump();
  }
  node->value = value;
  node->key = key;
  node->hash = hash;
  node->next = self->buckets[index];
  self->buckets[index] = node;
  self->size++;
}

R_Value
R_Map_get
  (
    R_Map const* self,
    R_Value key
  )
{ 
  if (R_Value_isVoidValue(&key)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_SizeValue hash = R_Value_hash(&key);
  R_SizeValue index = hash % self->capacity;

  for (Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash) {
      if (R_Value_isEqualTo(&key, &node->key)) {
        return node->value;
      }
    }
  }
  R_Value temporary;
  R_Value_setVoidValue(&temporary, R_VoidValue_Void);
  return temporary;
}

R_List*
R_Map_getValues
  (
    R_Map const* self
  )
{
  R_List* list = R_List_create();
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      R_List_append(list, node->value);
      node = node->next;
    }
  }
  return list;
}

R_List*
R_Map_getKeys
  (
    R_Map const* self
  )
{
  R_List* list = R_List_create();
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      R_List_append(list, node->key);
      node = node->next;
    }
  }
  return list;
}
