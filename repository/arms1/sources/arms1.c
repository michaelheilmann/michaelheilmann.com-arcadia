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

// Last modified: 2024-08-29

#include "arms1.h"

// malloc, free, realloc
#include <malloc.h>
// memcmp, memcpy
#include <string.h>
// uint8_t
#include <stdint.h>
// bool
#include <stdbool.h>

#if defined(Arms_WithLocks) && 1 == Arms_WithLocks

// INT_MAX
#include <limits.h>

#endif

typedef struct Arms_Type Arms_Type;

typedef struct Arms_Tag Arms_Tag;

#if defined(Arms_WithLocks) && 1 == Arms_WithLocks

typedef struct Arms_Lock Arms_Lock;

#endif

struct Arms_Type {
  Arms_Type* next;
  char* name;
  size_t nameLength;
  void (*visit)(void*);
  void (*finalize)(void*);
};

#define Arms_TagFlags_White (1)
#define Arms_TagFlags_Black (2)
#define Arms_TagFlags_Gray (Arms_TagFlags_White|Arms_TagFlags_Black)

// We must make sure that this thing is 64 bit aligned.
#if Arms_Compiler == Arms_Compiler_Msvc
#pragma pack(push, 8)
#endif
struct Arms_Tag{
  uint8_t flags;
  Arms_Type* type;
  Arms_Tag* universeNext;
  Arms_Tag* grayNext;
}
#if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Gcc
__attribute__((aligned(16)))
#endif
;
#if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Msvc
#pragma pack(pop, 8)
#endif

static_assert(sizeof(Arms_Tag) % 8 == 0, "Arms_Tag size not 8 Byte aligned");

#if defined(Arms_WithLocks) && 1 == Arms_WithLocks

struct Arms_Lock {
  Arms_Lock* next;
  int count;
  void* object;
};

#endif

#define REFERENCECOUNT_MINIMUM (UINT32_C(0))
#define REFERENCECOUNT_MAXIMUM (INT32_MAX)
static int32_t g_referenceCount = 0;

static Arms_Type* g_types = NULL;
static Arms_Tag* g_universe = NULL;
static Arms_Tag* g_grayObjects = NULL;

#if defined(Arms_WithLocks) && 1 == Arms_WithLocks

static Arms_Lock* g_locks = NULL;

#endif

static inline bool
Arms_Tag_isWhite
  (
    Arms_Tag const* tag
  )
{ return Arms_TagFlags_White == (tag->flags & Arms_TagFlags_Gray); }

static inline void
Arms_Tag_setWhite
  (
    Arms_Tag* tag
  )
{ tag->flags = (tag->flags & ~Arms_TagFlags_Black) | Arms_TagFlags_White;  }

static inline bool
Arms_Tag_isGray
  (
    Arms_Tag const* tag
  )
{ return Arms_TagFlags_Gray == (tag->flags & Arms_TagFlags_Gray); }

static inline void
Arms_Tag_setGray
  (
    Arms_Tag* tag
  )
{ tag->flags |= Arms_TagFlags_Gray; }

static inline bool
Arms_Tag_isBlack
  (
    Arms_Tag const* tag
  )
{ return Arms_TagFlags_Black == (tag->flags & Arms_TagFlags_Gray); }

static inline void
Arms_Tag_setBlack
  (
    Arms_Tag* tag
  )
{ tag->flags = (tag->flags & ~Arms_TagFlags_White) | Arms_TagFlags_Black; }

Arms_Status
Arms_startup
  (
  )
{
  if (g_referenceCount == REFERENCECOUNT_MAXIMUM) {
    // Cannot increment further.
    return Arms_Status_OperationInvalid;
  }
  if (!g_referenceCount) {
    g_types = NULL;

    g_universe = NULL;
    g_grayObjects = NULL;

  #if defined(Arms_WithLocks) && 1 == Arms_WithLocks
    g_locks = NULL;
  #endif
  }
  g_referenceCount++;
  return Arms_Status_Success;
}

Arms_Status
Arms_shutdown
  (
  )
{
  if (REFERENCECOUNT_MINIMUM == g_referenceCount) {
    // Cannot decrement further.
    return Arms_Status_OperationInvalid;
  }
  int32_t referenceCount = g_referenceCount - 1;
  if (!referenceCount) {
    if (g_grayObjects || g_universe) {
      return Arms_Status_ArgumentValueInvalid;
    }
  #if defined(Arms_WithLocks) && 1 == Arms_WithLocks
    if (g_locks) {
      return Arms_Status_OperationInvalid;
    }  
  #endif
    while (g_types) {
      Arms_Type* type = g_types;
      g_types = type->next;
      free(type->name);
      type->name = NULL;
      free(type);
      type = NULL;
    }
  }
  g_referenceCount = referenceCount;
  return Arms_Status_Success;
}

Arms_Status
Arms_registerType
  (
    char const* name,
    size_t nameLength,
    Arms_VisitCallbackFunction* visit,
    Arms_FinalizeCallbackFunction* finalize
  )
{
  if (!name) {
    return Arms_Status_ArgumentValueInvalid;
  }
  for (Arms_Type* type = g_types; NULL != type; type = type->next) {
    if (type->nameLength == nameLength){
      if (!memcmp(type->name, name, nameLength)) {
        return Arms_Status_TypeExists;
      }
    }
  }
  Arms_Type* type = malloc(sizeof(Arms_Type));
  if (!type) {
    return Arms_Status_AllocationFailed;
  }
  type->nameLength = nameLength;
  type->name = malloc(nameLength > 0 ? nameLength : 1);
  if (!type->name) {
    free(type);
    type = NULL;
    return Arms_Status_AllocationFailed;
  }
  memcpy(type->name, name, nameLength);
  
  type->visit = visit;
  type->finalize = finalize;
  
  type->next = g_types;
  g_types = type;

  return Arms_Status_Success;
}

Arms_Status
Arms_allocate
  (
    void** pObject,
    char const* name,
    size_t nameLength,
    size_t size
  )
{
  if (!pObject || !name) {
    return Arms_Status_ArgumentValueInvalid;
  }
  Arms_Type* type;
  for (type = g_types; NULL != type; type = type->next) {
    if (type->nameLength == nameLength){
      if (!memcmp(type->name, name, nameLength)) {
        break;
      }
    }
  }
  if (!type) {
    return Arms_Status_TypeNotExists;
  }
  if (SIZE_MAX - sizeof(Arms_Tag) < size) {
    return Arms_Status_ArgumentValueInvalid;
  }
  Arms_Tag* object = malloc(sizeof(Arms_Tag) + size);
  if (!object) {
    return Arms_Status_AllocationFailed;
  }
  object->flags = Arms_TagFlags_White;
  object->type = type;
  object->universeNext = g_universe;
  g_universe = object;
  *pObject = object + 1;
  return Arms_Status_Success;
}

#include <assert.h>

Arms_Status
Arms_run
  (
  )
{
  // Premark phase:
  // Add all locked objects to the gray list.
  // Also remove locks with a lock count of 0.
  Arms_Lock** previousLock = &g_locks;
  Arms_Lock* currentLock = g_locks;
  while (currentLock) {
    assert(NULL != currentLock->object);
    if (currentLock->count) {
      Arms_visit(currentLock->object);
      previousLock = &currentLock->next;
      currentLock = currentLock->next;
    } else {
      Arms_Lock* lock = currentLock;
      *previousLock = currentLock->next;
      currentLock = currentLock->next;
      free(lock);
    }
  }
  // Mark phase:
  // As long as the gray list is not empty: Remove an object from the gray list, color it black, visit it.
  while (g_grayObjects) {
    Arms_Tag* object = g_grayObjects;
    g_grayObjects = object->grayNext;
    Arms_Tag_setBlack(object);
    if (object->type->visit) {
      object->type->visit(object + 1);
    }
  }
  // Sweep phase:
  // Iterate over all objects in the universe.
  // If an object is black: color it white.
  // If an object is white: Remove, finalize, and deallocate the object.
  Arms_Tag** previousObject = &g_universe;
  Arms_Tag* currentObject = g_universe;
  while (currentObject) {
    if (Arms_Tag_isWhite(currentObject)) {
      Arms_Tag* deadObject = currentObject;
      *previousObject = currentObject->universeNext;
      currentObject = currentObject->universeNext;
      if (deadObject->type->finalize) {
        deadObject->type->finalize(deadObject + 1);
      }
      free(deadObject);
    } else {
      Arms_Tag_setWhite(currentObject);
      previousObject = &currentObject->universeNext;
      currentObject = currentObject->universeNext;
    }
  }
  return Arms_Status_Success;
}

void
Arms_visit
  (
    void* object
  )
{
  Arms_Tag* tag = ((Arms_Tag*)object) - 1;
  if (Arms_Tag_isWhite(tag)) {
    if (tag->type->visit) {
      Arms_Tag_setGray(tag);
      tag->grayNext = g_grayObjects;
      g_grayObjects = tag;
    } else {
      Arms_Tag_setBlack(tag);
    }
  }
}

#if defined(Arms_WithLocks) && 1 == Arms_WithLocks

Arms_Status
Arms_lock
  (
    void* object
  )
{
  for (Arms_Lock* lock = g_locks; NULL != lock; lock = lock->next) {
    if (lock->object == object) {
      if (lock->count == INT_MAX) {
         return Arms_Status_OperationInvalid;
      } else {
         lock->count++;
         return Arms_Status_Success;
      }
    }
  }
  Arms_Lock *lock = malloc(sizeof(Arms_Lock));
  if (!lock) {
    return Arms_Status_AllocationFailed;
  }
  lock->next = g_locks;
  g_locks = lock;
  lock->object = object;
  lock->count = 1;
  return Arms_Status_Success;
}

Arms_Status
Arms_unlock
  (
    void* object
  )
{
  for (Arms_Lock* lock = g_locks; NULL != lock; lock = lock->next) {
    if (lock->object == object) {
      if (lock->count == 0) {
         return Arms_Status_OperationInvalid;
      } else {
         lock->count--;
         return Arms_Status_Success;
      }
    }
  }
  return Arms_Status_OperationInvalid;  
}

#endif

Arms_Status
Arms_allocateUnmanaged
  (
    void** p,
    size_t n
  )
{
  if (!p) {
    return Arms_Status_ArgumentValueInvalid;
  }
  void *q = malloc(n > 0 ? n : 1);
  if (!q) {
    return Arms_Status_AllocationFailed;
  }
  *p = q;
  return Arms_Status_Success;
}

Arms_Status
Arms_reallocateUnmanaged
  (
    void** p,
    size_t n
  )
{
  if (!p) {
    return Arms_Status_ArgumentValueInvalid;
  }
  void* q = realloc(*p, n > 0 ? n : 1);
  if (!q) {
    return Arms_Status_AllocationFailed;
  }
  *p = q;
  return Arms_Status_Success;
}

Arms_Status
Arms_deallocateUnmanaged
  (
    void* p
  )
{
  if (!p) {
    return Arms_Status_ArgumentValueInvalid;
  }
  free(p);
  return Arms_Status_Success;
}
