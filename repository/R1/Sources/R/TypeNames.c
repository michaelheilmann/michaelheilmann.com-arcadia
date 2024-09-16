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

#include "R/TypeNames.h"

#include "R.h"
#include "R/ArmsIntegration.h"
#include <string.h>

typedef struct Singleton {
  R_Natural64Value referenceCount;
  R_SizeValue minimumCapacity;
  R_SizeValue maximumCapacity;
  R_TypeName** buckets;
  R_SizeValue size;
  R_SizeValue capacity;
} Singleton;

static Singleton* g_singleton = NULL;

static void
resize
  (
  );

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
    R_TypeName** oldBuckets = g_singleton->buckets;
    R_TypeName** newBuckets = NULL;
    if (!R_Arms_allocateUnmanaged_nojump((void**)&newBuckets, newCapacity * sizeof(R_TypeName*))) {
      R_jump();
    }
    for (R_SizeValue i = 0, n = newCapacity; i < n; ++i) {
      newBuckets[i] = NULL;
    }
    for (R_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
      while (oldBuckets[i]) {
        R_TypeName* node = oldBuckets[i];
        oldBuckets[i] = oldBuckets[i]->next;
        R_SizeValue j = R_Atom_getHashValue(node->atomValue) % newCapacity;
        node->next = newBuckets[j];
        newBuckets[j] = node;
      }
    }
    R_Arms_deallocateUnmanaged_nojump(oldBuckets);
    g_singleton->buckets = newBuckets;
    g_singleton->capacity = newCapacity;
  }
}

static bool
isAlphabetic
  (
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    return false;
  }
  return ('a' <= *current && *current <= 'z')
      || ('A' <= *current && *current <= 'Z');
}

static bool
isAlphanumeric
  (
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    return false;
  }
  return '0' <= *current && *current <= '9';
}

static bool
isUnderscore
  (
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    return false;
  }
  return '_' == *current;
}

static bool
isPeriod
  (
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    return false;
  }
  return '.' == *current;
}

static bool
isEnd
  (
    char const* current,
    char const* start,
    char const* end
  )
{ return current == end; }

static void
parseName
  (
    char const** current,
    char const* start,
    char const* end
  )
{
  if (!isAlphabetic(*current, start, end) && !isUnderscore(*current, start, end)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  (*current)++;
  while (isAlphabetic(*current, start, end) || isUnderscore(*current, start, end) || isAlphanumeric(*current, start, end)) {
    (*current)++;
  }
}

R_TypeNameValue
R_TypeNames_getOrCreateTypeName
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    char const* current = bytes,
              * start = bytes,
              * end = ((uint8_t const*)bytes) + numberOfBytes;
    parseName(&current, start, end);
    while (isPeriod(current, start, end)) {
      current++;
      parseName(&current, start, end);
    }
    if (!isEnd(current, start, end)) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_jump();
  }
  R_AtomValue atomValue = R_Atoms_getOrCreateAtom(bytes, numberOfBytes);
  R_SizeValue hash = R_Atom_getHashValue(atomValue);
  R_SizeValue index = hash % g_singleton->capacity;
  for (R_TypeNameValue typeName = g_singleton->buckets[index]; NULL != typeName; typeName = typeName->next) {
    if (typeName->atomValue == atomValue) {
      return typeName;
    }
  }
  R_TypeNameValue typeNameValue = NULL;
  if (!R_Arms_allocateUnmanaged_nojump(&typeNameValue, sizeof(R_TypeName))) {
    R_jump();
  }
  typeNameValue->atomValue = atomValue;
  typeNameValue->lastVisited = R_getTickCount();
  typeNameValue->visited = R_BooleanValue_True;
  typeNameValue->next = g_singleton->buckets[index];
  g_singleton->buckets[index] = typeNameValue;
  g_singleton->size++;
  resize();
  return typeNameValue;
}

void
R_TypeNames_startup
  (
  )
{
  if (!g_singleton) {
    R_Atoms_startup();
    if (!R_Arms_allocateUnmanaged_nojump((void**)&g_singleton, sizeof(Singleton))) {
      R_Atoms_shutdown();
      R_jump();
    }
    g_singleton->minimumCapacity = 8;
    g_singleton->maximumCapacity = SIZE_MAX / sizeof(R_TypeName);
    if (g_singleton->maximumCapacity > R_Integer32Value_Maximum) {
      g_singleton->maximumCapacity = R_Integer32Value_Maximum;
    }
    if (g_singleton->minimumCapacity > g_singleton->maximumCapacity) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    if (!R_Arms_allocateUnmanaged_nojump((void**)&g_singleton->buckets, 8 * sizeof(R_Atom*))) {
      R_Arms_deallocateUnmanaged_nojump(g_singleton);
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
R_TypeNames_shutdown
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
      fprintf(stderr, "%s:%d warning: type names not empty\n", __FILE__, __LINE__);
    }
    R_Arms_deallocateUnmanaged_nojump(g_singleton->buckets);
    g_singleton->buckets = NULL;
    R_Arms_deallocateUnmanaged_nojump(g_singleton);
    g_singleton = NULL;
    R_Atoms_shutdown();
  }
}

void
R_TypeNames_onPreMark
  (
  )
{
  for (R_SizeValue i = 0, n = g_singleton->capacity; i < n; ++i) {
    R_TypeName* current = g_singleton->buckets[i];
    while (current) {
      current->visited = R_BooleanValue_False;
      current = current->next;
    }
  }
  /* @todo Let the atoms register themselves at startup and remove this here. */
  R_Atoms_onPreMark();
}

void
R_TypeNames_onPostFinalize
  (
    bool shutdown
  )
{
  R_Natural64Value now = R_getTickCount();
  // 60 seconds
#define THRESHOLD 1000*60
  for (R_SizeValue i = 0, n = g_singleton->capacity; i < n; ++i) {
    R_TypeName** previous = &g_singleton->buckets[i];
    R_TypeName* current = g_singleton->buckets[i];
    while (current) {
      if (!current->visited && (now - current->visited > THRESHOLD || shutdown)) {
        R_TypeName* node = current;
        *previous = current->next;
        current = current->next;
        R_Arms_deallocateUnmanaged_nojump(node);
        g_singleton->size--;
      } else {
        previous = &current->next;
        current = current->next;
      }
    }
  }
  /* @todo Let the atoms register themselves at startup and remove this here. */
  R_Atoms_onPostFinalize(shutdown);
}

void
R_TypeName_visit
  (
    R_TypeNameValue typeNameValue
  )
{
  typeNameValue->lastVisited = R_getTickCount();
  typeNameValue->visited = R_BooleanValue_True;
  R_Atom_visit(typeNameValue->atomValue);
}
