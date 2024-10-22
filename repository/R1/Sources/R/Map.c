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

#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/UnmanagedMemory.h"
// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

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
R_Map_destruct
  (
    R_Map* self
  );

static void
R_Map_visit
  (
    R_Map* self
  );

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

Rex_defineObjectType("R.Map", R_Map, "R.Object", R_Object, &R_Map_visit, &R_Map_destruct);

void
R_Map_construct
  (
    R_Map* self
  )
{
  R_Type* _type = _R_Map_getType();
  R_Map_ensureInitialized();
  R_Object_construct((R_Object*)self);
  self->buckets = NULL;
  self->capacity = 0;
  self->size = 0;
  self->capacity = g_minimumCapacity;
  if (!R_allocateUnmanaged_nojump((void**)&self->buckets, sizeof(Node*) * self->capacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    self->buckets[i] = NULL;
  }
  R_Object_setType((R_Object*)self, _type);
}

R_Map*
R_Map_create
  (
  )
{
  R_Map* self = R_allocateObject(_R_Map_getType());
  R_Map_construct(self);
  return self;
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
