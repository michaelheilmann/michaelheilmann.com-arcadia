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

// Last modified: 2025-01-06

#include "Arcadia/Ring1/Implementation/Atoms.private.h"

#include "Arcadia/Ring1/Implementation/TypeNameParser.h"
#include "R/cstdlib.h"

#include "R/ArmsIntegration.h"
#include "Arcadia/Ring1/Implementation/getTickCount.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"

// 60 seconds
#define THRESHOLD 1000*60

typedef struct Singleton Singleton;

struct Arcadia_Atom {
  Arcadia_Atom* next;
  /// If the key was visited.
  Arcadia_BooleanValue visited;
  /// The last time this key was visited.
  Arcadia_Natural64Value lastVisited;
  /// The hash value of this keys.
  Arcadia_SizeValue hash;
  /// The number of Bytes of this key.
  Arcadia_SizeValue numberOfBytes;
  /// The Bytes of this key.
  char bytes[];
};

struct Singleton {
  Arcadia_Natural64Value referenceCount;
  Arcadia_SizeValue minimumCapacity;
  Arcadia_SizeValue maximumCapacity;
  Arcadia_Atom **buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
}; 

static Singleton* g_singleton = NULL;

static Arcadia_SizeValue
hashBytes
  (
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
resize
  (
    Arcadia_Process* process
  );

static Arcadia_SizeValue
hashBytes
  (
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  uint8_t const* p = (uint8_t const*)bytes;
  Arcadia_SizeValue hashValue = numberOfBytes;
  for (Arcadia_SizeValue i = 0, n = numberOfBytes; i < n; ++i) {
    hashValue = hashValue * 37 + p[i];
  }
  return hashValue;
}

static void
resize
  (
    Arcadia_Process* process
  )
{
  if (g_singleton->size == g_singleton->capacity) {
    Arcadia_SizeValue oldCapacity = g_singleton->capacity;
    Arcadia_SizeValue newCapacity = oldCapacity;
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
    Arcadia_Atom** oldBuckets = g_singleton->buckets;
    Arcadia_Atom** newBuckets = NULL;
    if (!R_allocateUnmanaged_nojump(process, (void**)&newBuckets, newCapacity * sizeof(Arcadia_Atom*))) {
      Arcadia_Process_jump(process);
    }
    for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
      newBuckets[i] = NULL;
    }
    for (Arcadia_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
      while (oldBuckets[i]) {
        Arcadia_Atom*node = oldBuckets[i];
        oldBuckets[i] = oldBuckets[i]->next;
        Arcadia_SizeValue j = node->hash % newCapacity;
        node->next = newBuckets[j];
        newBuckets[j] = node;
      }
    }
    R_deallocateUnmanaged_nojump(process, oldBuckets);
    g_singleton->buckets = newBuckets;
    g_singleton->capacity = newCapacity;
  }
}

void
Arcadia_Atoms_startup
  (
    Arcadia_Process* process
  )
{
  if (!g_singleton) {
    if (!R_allocateUnmanaged_nojump(process, (void**)&g_singleton, sizeof(Singleton))) {
      Arcadia_Process_jump(process);
    }
    g_singleton->minimumCapacity = 8;
    g_singleton->maximumCapacity = SIZE_MAX / sizeof(Arcadia_Atom*);
    if (g_singleton->maximumCapacity > Arcadia_Integer32Value_Maximum) {
      g_singleton->maximumCapacity = Arcadia_Integer32Value_Maximum;
    }
    if (g_singleton->minimumCapacity > g_singleton->maximumCapacity) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    if (!R_allocateUnmanaged_nojump(process, (void**)&g_singleton->buckets, 8 * sizeof(Arcadia_Atom*))) {
      R_deallocateUnmanaged_nojump(process, g_singleton);
      g_singleton = NULL;
      Arcadia_Process_jump(process);
    }
    for (Arcadia_SizeValue i = 0, n = 8; i < n; ++i) {
      g_singleton->buckets[i] = NULL;
    }
    g_singleton->size = 0;
    g_singleton->capacity = 8;
    g_singleton->referenceCount = 1;
  } else {
    if (g_singleton->referenceCount == Arcadia_Natural64Value_Maximum) {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    }
    g_singleton->referenceCount++;
    
  }
}

void
Arcadia_Atoms_shutdown
  (
    Arcadia_Process* process
  )
{
  if (!g_singleton) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  if (g_singleton->referenceCount == Arcadia_Natural64Value_Minimum) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  if (0 == --g_singleton->referenceCount) {
    if (g_singleton->size > 0) {
      fprintf(stderr, "%s:%d warning: atoms not empty\n", __FILE__, __LINE__);
    }
    R_deallocateUnmanaged_nojump(process, g_singleton->buckets);
    g_singleton->buckets = NULL;
    R_deallocateUnmanaged_nojump(process, g_singleton);
    g_singleton = NULL;
  }
}

void
Arcadia_Atoms_onPreMark
  (
  )
{
  for (Arcadia_SizeValue i = 0, n = g_singleton->capacity; i < n; ++i) {
    Arcadia_Atom* current = g_singleton->buckets[i];
    while (current) {
      current->visited = Arcadia_BooleanValue_False;
      current = current->next;
    }
  }
}

void
Arcadia_Atoms_onFinalize
  (
    Arcadia_Process* process,
    Arcadia_BooleanValue purgeCache
  )
{
  Arcadia_Natural64Value now = Arcadia_getTickCount();

  for (Arcadia_SizeValue i = 0, n = g_singleton->capacity; i < n; ++i) {
    Arcadia_Atom** previous = &g_singleton->buckets[i];
    Arcadia_Atom* current = g_singleton->buckets[i];
    while (current) {
      if (!current->visited &&
         ((now - current->lastVisited) > THRESHOLD || purgeCache)) {
        Arcadia_Atom* node = current;
        *previous = current->next;
        current = current->next;
        R_deallocateUnmanaged_nojump(process, node); 
        g_singleton->size--;
      } else {
        previous = &current->next;
        current = current->next;
      }
    }
  }  
}

Arcadia_AtomValue
Arcadia_Atoms_getOrCreateAtom
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value flags,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!bytes || (SIZE_MAX - sizeof(Arcadia_Atom)) < numberOfBytes) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  
  if (Arcadia_AtomKind_Name == (flags & Arcadia_AtomKind_Name)) {
    R_Names_parseTypeName(process, bytes, numberOfBytes);
  }

  Arcadia_SizeValue hash = hashBytes(bytes, numberOfBytes);
  Arcadia_SizeValue index = hash % g_singleton->capacity;
  for (Arcadia_Atom* atom = g_singleton->buckets[index]; NULL != atom; atom = atom->next) {
    if (atom->numberOfBytes == numberOfBytes && atom->hash == hash) {
      if (!c_memcmp(atom->bytes, bytes, numberOfBytes)) {
        return atom;
      }
    }
  }
  Arcadia_Atom* atom = NULL;
  if (!R_allocateUnmanaged_nojump(process, &atom, sizeof(Arcadia_Atom) + numberOfBytes)) {
    Arcadia_Process_jump(process);
  }
  c_memcpy(atom->bytes, bytes, numberOfBytes);
  atom->numberOfBytes = numberOfBytes;
  atom->hash = hash;
  atom->lastVisited = Arcadia_getTickCount();
  atom->visited = Arcadia_BooleanValue_True;
  atom->next = g_singleton->buckets[index];
  g_singleton->buckets[index] = atom;
  g_singleton->size++;
  resize(process);
  return atom;
}

void
Arcadia_Atom_visit
  (
    Arcadia_AtomValue self
  )
{ 
  self->lastVisited = Arcadia_getTickCount();
  self->visited = Arcadia_BooleanValue_True;
}

void const*
Arcadia_Atom_getBytes
  (
    Arcadia_AtomValue self
  )
{ return self->bytes; }

Arcadia_SizeValue
Arcadia_Atom_getNumberOfBytes
  (
    Arcadia_AtomValue self
  )
{ return self->numberOfBytes; }

Arcadia_SizeValue
Arcadia_Atom_getHash
  (
    Arcadia_AtomValue self
  )
{ return self->hash; }

Arcadia_BooleanValue
Arcadia_Atom_isEqualTo
  (
    Arcadia_AtomValue self,
    Arcadia_AtomValue other
  )
{ return self == other; }
