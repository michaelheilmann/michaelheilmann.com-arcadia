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

// Last modified: 2024-10-07

#include "R/Map.h"

#include "R/ArmsIntegration.h"
#include "R/Object.h"
#include "R/DynamicArrayUtilities.h"
#include "R/cstdlib.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

typedef struct Node Node;

struct Node {
  Node* next;
  Arcadia_SizeValue hash;
  R_Value key;
  R_Value value;
};

struct R_Map {
  R_Object _parent;
  Node** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

static void
R_Map_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_Map* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
R_Map_ensureInitialized
  (
    Arcadia_Process* process
  );

static void
R_Map_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Map_destruct
  (
    Arcadia_Process* process,
    R_Map* self
  );

static void
R_Map_visit
  (
    Arcadia_Process* process,
    R_Map* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Map_constructImpl,
  .destruct = &R_Map_destruct,
  .visit = &R_Map_visit,
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

Rex_defineObjectType(u8"R.Map", R_Map, u8"R.Object", R_Object, &_typeOperations);

static void
R_Map_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_Map* self,
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
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
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
  if (!R_allocateUnmanaged_nojump(process, (void**)&newBuckets, sizeof(Node*) * newCapacity)) {
    Arcadia_Process_jump(process);
  }
  for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
    newBuckets[i] = NULL;
  }
  for (Arcadia_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
    while (oldBuckets[i]) {
      Node* node = oldBuckets[i];
      oldBuckets[i] = oldBuckets[i]->next;
      Arcadia_SizeValue j = node->hash % newCapacity;
      node->next = newBuckets[j];
      newBuckets[j] = node;
    }
  }
  R_deallocateUnmanaged_nojump(process, oldBuckets);
  self->buckets = newBuckets;
  self->capacity = newCapacity;
}

static void
R_Map_ensureInitialized
  (
    Arcadia_Process* process
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(Node*);
    if (g_maximumCapacity > Arcadia_Integer32Value_Maximum) {
      g_maximumCapacity = Arcadia_Integer32Value_Maximum;
    }
    if (g_minimumCapacity > g_maximumCapacity) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    g_initialized = Arcadia_BooleanValue_True;
  }
}

static void
R_Map_destruct
  (
    Arcadia_Process* process,
    R_Map* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      R_deallocateUnmanaged_nojump(process, node);
      node = NULL;
    }
  }
  if (self->buckets) {
    R_deallocateUnmanaged_nojump(process, self->buckets);
    self->buckets = NULL;
  }
}

static void
R_Map_visit
  (
    Arcadia_Process* process,
    R_Map* self
  )
{
  if (self->buckets) {
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
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
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Map* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Map_getType(process);
  R_Map_ensureInitialized(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->buckets = NULL;
  _self->capacity = 0;
  _self->size = 0;
  _self->capacity = g_minimumCapacity;
  if (!R_allocateUnmanaged_nojump(process, (void**)&_self->buckets, sizeof(Node*) * _self->capacity)) {
    Arcadia_Process_jump(process);
  }
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  R_Object_setType((R_Object*)_self, _type);
}

R_Map*
R_Map_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Map* self = R_allocateObject(process, _R_Map_getType(process), 0, &argumentValues[0]);
  return self;
}

R_Map*
R_Map_clone
  (
    Arcadia_Process* process,
    R_Map* self
  )
{
  R_Map* clone = R_Map_create(process);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    for (Node* node = self->buckets[i]; NULL != node; node = node->next) {
      R_Map_set(process, clone, node->key, node->value);
    }
  }
  return clone;
}

void
R_Map_clear
  (
    Arcadia_Process* process,
    R_Map* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      R_deallocateUnmanaged_nojump(process, node);
      node = NULL;
    }
  }
  self->size = 0;
}


Arcadia_SizeValue
R_Map_getSize
  (
    R_Map const* self
  )
{ return self->size; }

void
R_Map_set
  (
    Arcadia_Process* process,
    R_Map* self,
    R_Value key,
    R_Value value
  )
{ 
  if (R_Value_isVoidValue(&key)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_SizeValue hash = R_Value_hash(process, &key);
  Arcadia_SizeValue index = hash % self->capacity;
  for (Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash) {
      if (R_Value_isEqualTo(process, &key, &node->key)) {
        node->key = key;
        node->value = value;
        return;
      }
    }
  }
  Node* node = NULL;
  if (!R_allocateUnmanaged_nojump(process, &node, sizeof(Node))) {
    Arcadia_Process_jump(process);
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
    Arcadia_Process* process,
    R_Map const* self,
    R_Value key
  )
{ 
  if (R_Value_isVoidValue(&key)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_SizeValue hash = R_Value_hash(process, &key);
  Arcadia_SizeValue index = hash % self->capacity;

  for (Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash) {
      if (R_Value_isEqualTo(process, &key, &node->key)) {
        return node->value;
      }
    }
  }
  R_Value temporary;
  R_Value_setVoidValue(&temporary, Arcadia_VoidValue_Void);
  return temporary;
}

R_List*
R_Map_getValues
  (
    Arcadia_Process* process,
    R_Map const* self
  )
{
  R_List* list = R_List_create(process);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      R_List_append(process, list, node->value);
      node = node->next;
    }
  }
  return list;
}

R_List*
R_Map_getKeys
  (
    Arcadia_Process* process,
    R_Map const* self
  )
{
  R_List* list = R_List_create(process);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      R_List_append(process, list, node->key);
      node = node->next;
    }
  }
  return list;
}
