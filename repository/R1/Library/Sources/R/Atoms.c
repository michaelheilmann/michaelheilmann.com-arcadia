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

// Last modified: 2024-09-20

#include "R/Atoms.h"

#include "R/ArmsIntegration.h"
#include "R/getTickCount.h"
#include "R/Integer32.h"
#include "R/JumpTarget.h"
#include "R/Natural64.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/DynamicArrayUtilities.h"
#include "R/cstdlib.h"

typedef struct Singleton Singleton;

struct R_Atom {
  R_Atom* next;
  /// If the key was visited.
  R_BooleanValue visited;
  /// The last time this key was visited.
  R_Natural64Value lastVisited;
  /// The hash value of this keys.
  R_SizeValue hash;
  /// The number of Bytes of this key.
  R_SizeValue numberOfBytes;
  /// The Bytes of this key.
  char bytes[];
};

struct Singleton {
  R_Natural64Value referenceCount;
  R_SizeValue minimumCapacity;
  R_SizeValue maximumCapacity;
  R_Atom **buckets;
  R_SizeValue size;
  R_SizeValue capacity;
}; 

static Singleton* g_singleton = NULL;

static R_SizeValue
hashBytes
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

static void
resize
  (
  );

static R_SizeValue
hashBytes
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  uint8_t const* p = (uint8_t const*)bytes;
  R_SizeValue hashValue = numberOfBytes;
  for (R_SizeValue i = 0, n = numberOfBytes; i < n; ++i) {
    hashValue = hashValue * 37 + p[i];
  }
  return hashValue;
}

static void
resize
  (
  )
{
  if (g_singleton->size == g_singleton->capacity) {
    R_SizeValue oldCapacity = g_singleton->capacity;
    R_SizeValue newCapacity = oldCapacity;
    if (oldCapacity > g_singleton->maximumCapacity / 2) {
      // If oldCapacity > maximumCapacity / 2 holds then oldCapacity * 2 > maximumCapacity holds.
      // Consequently, we cannot double the capacity. Try to saturate the capacity.
      if (oldCapacity == g_singleton->maximumCapacity) {
        // Do nothing.
        return;
      } else {
        newCapacity = g_singleton->maximumCapacity;
      }
    } else {
      newCapacity = oldCapacity * 2;
    }
    R_Atom** oldBuckets = g_singleton->buckets;
    R_Atom** newBuckets = NULL;
    if (!R_allocateUnmanaged_nojump((void**)&newBuckets, newCapacity * sizeof(R_Atom*))) {
      R_jump();
    }
    for (R_SizeValue i = 0, n = newCapacity; i < n; ++i) {
      newBuckets[i] = NULL;
    }
    for (R_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
      while (oldBuckets[i]) {
        R_Atom *node = oldBuckets[i];
        oldBuckets[i] = oldBuckets[i]->next;
        R_SizeValue j = node->hash % newCapacity;
        node->next = newBuckets[j];
        newBuckets[j] = node;
      }
    }
    R_deallocateUnmanaged_nojump(oldBuckets);
    g_singleton->buckets = newBuckets;
    g_singleton->capacity = newCapacity;
  }
}

void
R_Atoms_startup
  (
  )
{
  if (!g_singleton) {
    if (!R_allocateUnmanaged_nojump((void**)&g_singleton, sizeof(Singleton))) {
      R_jump();
    }
    g_singleton->minimumCapacity = 8;
    g_singleton->maximumCapacity = SIZE_MAX / sizeof(R_Atom);
    if (g_singleton->maximumCapacity > R_Integer32Value_Maximum) {
      g_singleton->maximumCapacity = R_Integer32Value_Maximum;
    }
    if (g_singleton->minimumCapacity > g_singleton->maximumCapacity) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    if (!R_allocateUnmanaged_nojump((void**)&g_singleton->buckets, 8 * sizeof(R_Atom*))) {
      R_deallocateUnmanaged_nojump(g_singleton);
      g_singleton = NULL;
      R_jump();
    }
    for (R_SizeValue i = 0, n = 8; i < n; ++i) {
      g_singleton->buckets[i] = NULL;
    }
    g_singleton->size = 0;
    g_singleton->capacity = 8;
    g_singleton->referenceCount = 1;
  } else {
    if (g_singleton->referenceCount == R_Natural64Value_Maximum) {
      R_setStatus(R_Status_OperationInvalid);
      R_jump();
    }
    g_singleton->referenceCount++;
    
  }
}

void
R_Atoms_shutdown
  (
  )
{
  if (!g_singleton) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  if (g_singleton->referenceCount == R_Natural64Value_Minimum) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  if (0 == --g_singleton->referenceCount) {
    if (g_singleton->size > 0) {
      fprintf(stderr, "%s:%d warning: atoms not empty\n", __FILE__, __LINE__);
    }
    R_deallocateUnmanaged_nojump(g_singleton->buckets);
    g_singleton->buckets = NULL;
    R_deallocateUnmanaged_nojump(g_singleton);
    g_singleton = NULL;
  }
}

void
R_Atoms_onPreMark
  (
  )
{
  for (R_SizeValue i = 0, n = g_singleton->capacity; i < n; ++i) {
    R_Atom* current = g_singleton->buckets[i];
    while (current) {
      current->visited = R_BooleanValue_False;
      current = current->next;
    }
  }
}

void
R_Atoms_onPostFinalize
  (
    bool shutdown
  )
{
  R_Natural64Value now = R_getTickCount();
  // 60 seconds
  #define THRESHOLD 1000*60
  for (R_SizeValue i = 0, n = g_singleton->capacity; i < n; ++i) {
    R_Atom** previous = &g_singleton->buckets[i];
    R_Atom* current = g_singleton->buckets[i];
    while (current) {
      if (!current->visited && (now - current->visited > THRESHOLD || shutdown)) {
        R_Atom* node = current;
        *previous = current->next;
        current = current->next;
        R_deallocateUnmanaged_nojump(node); 
        g_singleton->size--;
      } else {
        previous = &current->next;
        current = current->next;
      }
    }
  }  
}

R_AtomValue
R_Atoms_getOrCreateAtom
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!bytes || (SIZE_MAX - sizeof(R_Atom)) < numberOfBytes) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_SizeValue hash = hashBytes(bytes, numberOfBytes);
  R_SizeValue index = hash % g_singleton->capacity;
  for (R_Atom* atom = g_singleton->buckets[index]; NULL != atom; atom = atom->next) {
    if (atom->numberOfBytes == numberOfBytes && atom->hash == hash) {
      if (!c_memcmp(atom->bytes, bytes, numberOfBytes)) {
        return atom;
      }
    }
  }
  R_Atom* atom = NULL;
  if (!R_allocateUnmanaged_nojump(&atom, sizeof(R_Atom) + numberOfBytes)) {
    R_jump();
  }
  c_memcpy(atom->bytes, bytes, numberOfBytes);
  atom->numberOfBytes = numberOfBytes;
  atom->hash = hash;
  atom->lastVisited = R_getTickCount();
  atom->visited = R_BooleanValue_True;
  atom->next = g_singleton->buckets[index];
  g_singleton->buckets[index] = atom;
  g_singleton->size++;
  resize();
  return atom;
}

void
R_Atom_visit
  (
    R_AtomValue self
  )
{ 
  self->lastVisited = R_getTickCount();
  self->visited = R_BooleanValue_True;
}

void const*
R_Atom_getBytes
  (
    R_AtomValue self
  )
{ return self->bytes; }

R_SizeValue
R_Atom_getNumberOfBytes
  (
    R_AtomValue self
  )
{ return self->numberOfBytes; }

R_SizeValue
R_Atom_getHash
  (
    R_AtomValue self
  )
{ return self->hash; }

R_BooleanValue
R_Atom_isEqualTo
  (
    R_AtomValue self,
    R_AtomValue other
  )
{ return self == other; }
