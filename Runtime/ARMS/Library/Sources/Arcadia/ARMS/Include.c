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

#include "Arcadia/ARMS/Include.h"

#include "Arcadia/ARMS/Internal/MemoryManager.private.h"
#include "Arcadia/ARMS/Internal/DefaultMemoryManager.h"
#include "Arcadia/ARMS/Internal/SlabMemoryManager.h"
#include "Arcadia/ARMS/Internal/Statistics.h"
#include "Arcadia/ARMS/NotifyDestroy.h"
#include "Arcadia/ARMS/Internal/Tag.h"

#include "Arcadia/ARMS/Internal/Common.h"

// malloc, free, realloc
#include <malloc.h>
// memcmp, memcpy
#include <string.h>
// uint8_t
#include <stdint.h>
// bool, true, false
#include <stdbool.h>
// assert()
#include <assert.h>

#if defined(Arcadia_ARMS_Configuration_WithLocks) && 1 == Arcadia_ARMS_Configuration_WithLocks

// INT_MAX
#include <limits.h>

#endif

typedef struct Arms_Type Arms_Type;


#if defined(Arcadia_ARMS_Configuration_WithLocks) && 1 == Arcadia_ARMS_Configuration_WithLocks

typedef struct Arms_Lock Arms_Lock;

#endif

struct Arms_Type {
  Arms_Type* next;
  uint8_t* name;
  size_t nameLength;
  void* context;
  Arcadia_ARMS_TypeRemovedCallbackFunction* typeRemoved;
  Arcadia_ARMS_VisitCallbackFunction* visit;
  Arcadia_ARMS_FinalizeCallbackFunction* finalize;
};

#if defined(Arcadia_ARMS_Configuration_WithLocks) && 1 == Arcadia_ARMS_Configuration_WithLocks

struct Arms_Lock {
  Arms_Lock* next;
  int count;
  void* object;
};

#endif

typedef Arcadia_ARMS_Size Arcadia_ARMS_ReferenceCount;
#define Arcadia_ARMS_ReferenceCount_Minimum (Arcadia_ARMS_Size_Minimum)
#define Arcadia_ARMS_ReferenceCount_Maximum (Arcadia_ARMS_Size_Maximum)
static Arcadia_ARMS_ReferenceCount g_referenceCount = 0;

static Arms_Type* g_types = NULL;
static Arcadia_ARMS_Tag* g_universe = NULL;
static Arcadia_ARMS_Tag* g_grayObjects = NULL;

#if defined(Arcadia_ARMS_Configuration_WithLocks) && 1 == Arcadia_ARMS_Configuration_WithLocks

static Arms_Lock* g_locks = NULL;

#endif

static Arcadia_ARMS_DefaultMemoryManager* g_defaultMemoryManager = NULL;
static Arcadia_ARMS_SlabMemoryManager* g_slabMemoryManager = NULL;

Arcadia_ARMS_Status
Arcadia_ARMS_startup
  (
  )
{
  if (g_referenceCount == Arcadia_ARMS_ReferenceCount_Maximum) {
    // Cannot increment further.
    return Arcadia_ARMS_Status_OperationInvalid;
  }
  if (!g_referenceCount) {
    switch (Arcadia_ARMS_DefaultMemoryManager_create(&g_defaultMemoryManager)) {
      case Arcadia_ARMS_MemoryManagerStartupShutdown_Status_AllocationFailed: {
        return Arcadia_ARMS_Status_AllocationFailed;
      } break;
      case Arcadia_ARMS_MemoryManagerStartupShutdown_Status_ArgumentValueInvalid: {
        return Arcadia_ARMS_Status_ArgumentValueInvalid;
      } break;
      case Arcadia_ARMS_MemoryManagerStartupShutdown_Status_Success: {
        /* Intentionally empty.*/
      } break;
      default: {
        return Arcadia_ARMS_Status_EnvironmentFailed;
      } break;
    };
    switch (Arcadia_ARMS_SlabMemoryManager_create(&g_slabMemoryManager)) {
      case Arcadia_ARMS_MemoryManagerStartupShutdown_Status_AllocationFailed: {
        Arcadia_ARMS_MemoryManager_destroy((Arcadia_ARMS_MemoryManager*)g_defaultMemoryManager);
        g_defaultMemoryManager = NULL;
        return Arcadia_ARMS_Status_AllocationFailed;
      } break;
      case Arcadia_ARMS_MemoryManagerStartupShutdown_Status_ArgumentValueInvalid: {
        Arcadia_ARMS_MemoryManager_destroy((Arcadia_ARMS_MemoryManager*)g_defaultMemoryManager);
        g_defaultMemoryManager = NULL;
        return Arcadia_ARMS_Status_ArgumentValueInvalid;
      } break;
      case Arcadia_ARMS_MemoryManagerStartupShutdown_Status_Success: {
        /* Intentionally empty.*/
      } break;
      default: {
        Arcadia_ARMS_MemoryManager_destroy((Arcadia_ARMS_MemoryManager*)g_defaultMemoryManager);
        g_defaultMemoryManager = NULL;
        return Arcadia_ARMS_Status_EnvironmentFailed;
      } break;
    };

    g_types = NULL;

    g_universe = NULL;
    g_grayObjects = NULL;

  #if defined(Arcadia_ARMS_Configuration_WithLocks) && 1 == Arcadia_ARMS_Configuration_WithLocks
    g_locks = NULL;
  #endif

  #if defined(Arcadia_ARMS_Configuration_WithNotifyDestroy) && 1 == Arcadia_ARMS_Configuration_WithNotifyDestroy
    if (Arcadia_ARMS_NotifyDestroyModule_startup()) {
      Arcadia_ARMS_MemoryManager_destroy((Arcadia_ARMS_MemoryManager*)g_slabMemoryManager);
      g_slabMemoryManager = NULL;
      Arcadia_ARMS_MemoryManager_destroy((Arcadia_ARMS_MemoryManager*)g_defaultMemoryManager);
      g_defaultMemoryManager = NULL;
      return Arcadia_ARMS_Status_EnvironmentFailed;
    }
  #endif

  }
  g_referenceCount++;
  return Arcadia_ARMS_Status_Success;
}

Arcadia_ARMS_Status
Arcadia_ARMS_shutdown
  (
  )
{
  if (Arcadia_ARMS_ReferenceCount_Minimum == g_referenceCount) {
    // Cannot decrement further.
    return Arcadia_ARMS_Status_OperationInvalid;
  }
  int32_t referenceCount = g_referenceCount - 1;
  if (!referenceCount) {
    if (g_grayObjects || g_universe) {
      Cxx_fatalError();
    }
  #if defined(Arcadia_ARMS_Configuration_WithLocks) && 1 == Arcadia_ARMS_Configuration_WithLocks
    if (g_locks) {
      Cxx_fatalError();
    }
  #endif
  #if defined(Arcadia_ARMS_Configuration_WithNotifyDestroy) && 1 == Arcadia_ARMS_Configuration_WithNotifyDestroy
    Arcadia_ARMS_NotifyDestroyModule_shutdown();
  #endif
    while (g_types) {
      Arms_Type* type = g_types;
      g_types = type->next;
      if (type->typeRemoved) {
        type->typeRemoved(type->context, type->name, type->nameLength);
      }
      free(type->name);
      type->name = NULL;
      free(type);
      type = NULL;
    }
    Arcadia_ARMS_MemoryManager_destroy((Arcadia_ARMS_MemoryManager*)g_slabMemoryManager);
    g_slabMemoryManager = NULL;
    Arcadia_ARMS_MemoryManager_destroy((Arcadia_ARMS_MemoryManager*)g_defaultMemoryManager);
    g_defaultMemoryManager = NULL;
  }
  g_referenceCount = referenceCount;
  return Arcadia_ARMS_Status_Success;
}

Arcadia_ARMS_Status
Arcadia_ARMS_addType
  (
    Arms_Natural8 const* name,
    Arcadia_ARMS_Size nameLength,
    void* context,
    Arcadia_ARMS_TypeRemovedCallbackFunction* typeRemoved,
    Arcadia_ARMS_VisitCallbackFunction* visit,
    Arcadia_ARMS_FinalizeCallbackFunction* finalize
  )
{
  if (!name) {
    return Arcadia_ARMS_Status_ArgumentValueInvalid;
  }

  for (Arms_Type* type = g_types; NULL != type; type = type->next) {
    if (type->nameLength == nameLength){
      if (!memcmp(type->name, name, nameLength)) {
        return Arcadia_ARMS_Status_TypeExists;
      }
    }
  }

  Arms_Type* type = malloc(sizeof(Arms_Type));
  if (!type) {
    return Arcadia_ARMS_Status_AllocationFailed;
  }

  type->nameLength = nameLength;
  type->name = malloc(nameLength > 0 ? nameLength : 1);
  if (!type->name) {
    free(type);
    type = NULL;
    return Arcadia_ARMS_Status_AllocationFailed;
  }
  memcpy(type->name, name, nameLength);

  type->context = context;
  type->typeRemoved = typeRemoved;
  type->visit = visit;
  type->finalize = finalize;

  type->next = g_types;
  g_types = type;

  return Arcadia_ARMS_Status_Success;
}

Arcadia_ARMS_Status
Arcadia_ARMS_allocate
  (
    void** pObject,
    Arms_Natural8 const* name,
    Arcadia_ARMS_Size nameLength,
    Arcadia_ARMS_Size size
  )
{
  if (!pObject || !name) {
    return Arcadia_ARMS_Status_ArgumentValueInvalid;
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
    return Arcadia_ARMS_Status_TypeNotExists;
  }
  if (SIZE_MAX - sizeof(Arcadia_ARMS_Tag) < size) {
    return Arcadia_ARMS_Status_ArgumentValueInvalid;
  }
  Arcadia_ARMS_Tag* object = malloc(sizeof(Arcadia_ARMS_Tag) + size);
  if (!object) {
    return Arcadia_ARMS_Status_AllocationFailed;
  }
  object->flags = Arcadia_ARMS_TagFlags_White;
  object->type = type;
  object->universeNext = g_universe;
  g_universe = object;
  *pObject = object + 1;
  return Arcadia_ARMS_Status_Success;
}

Arcadia_ARMS_Status
Arcadia_ARMS_run
  (
    Arcadia_ARMS_RunStatistics* statistics
  )
{
  Arcadia_ARMS_RunStatistics statistics0 = Arcadia_ARMS_RunStatistics_StaticInitializer();
  // Premark phase:
  // Add all locked objects to the gray list.
  // Also remove locks with a lock count of 0.
  Arms_Lock** previousLock = &g_locks;
  Arms_Lock* currentLock = g_locks;
  while (currentLock) {
    assert(NULL != currentLock->object);
    if (currentLock->count) {
      Arcadia_ARMS_visit(currentLock->object);
      statistics0.locked++;
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
    Arcadia_ARMS_Tag* object = g_grayObjects;
    g_grayObjects = object->grayNext;
    Arcadia_ARMS_Tag_setBlack(object);
    if (object->type->visit) {
      object->type->visit(object->type->context, object + 1);
    }
  }
  // Sweep phase:
  // Iterate over all objects in the universe.
  // If an object is black: color it white.
  // If an object is white: Remove, finalize, and deallocate the object.
  Arcadia_ARMS_Tag** previousObject = &g_universe;
  Arcadia_ARMS_Tag* currentObject = g_universe;
  while (currentObject) {
    if (Arcadia_ARMS_Tag_isWhite(currentObject)) {
      Arcadia_ARMS_Tag* deadObject = currentObject;
      *previousObject = currentObject->universeNext;
      currentObject = currentObject->universeNext;
    #if defined(Arcadia_ARMS_Configuration_WithNotifyDestroy) && 1 == Arcadia_ARMS_Configuration_WithNotifyDestroy
      Arcadia_ARMS_NotifyDestroyModule_notifyDestroy(deadObject + 1);
    #endif
      if (deadObject->type->finalize) {
        deadObject->type->finalize(deadObject->type->context, deadObject + 1);
        statistics0.finalized++;
      }
      statistics0.dead++;
      free(deadObject);
    } else {
      Arcadia_ARMS_Tag_setWhite(currentObject);
      statistics0.live++;
      previousObject = &currentObject->universeNext;
      currentObject = currentObject->universeNext;
    }
  }
  *statistics = statistics0;
  return Arcadia_ARMS_Status_Success;
}

void
Arcadia_ARMS_visit
  (
    void* object
  )
{
  Arcadia_ARMS_Tag* tag = ((Arcadia_ARMS_Tag*)object) - 1;
  if (Arcadia_ARMS_Tag_isWhite(tag)) {
    if (tag->type->visit) {
      Arcadia_ARMS_Tag_setGray(tag);
      tag->grayNext = g_grayObjects;
      g_grayObjects = tag;
    } else {
      Arcadia_ARMS_Tag_setBlack(tag);
    }
  }
}

#if defined(Arcadia_ARMS_Configuration_WithLocks) && 1 == Arcadia_ARMS_Configuration_WithLocks

Arcadia_ARMS_Status
Arcadia_ARMS_lock
  (
    void* object
  )
{
  for (Arms_Lock* lock = g_locks; NULL != lock; lock = lock->next) {
    if (lock->object == object) {
      if (lock->count == INT_MAX) {
         return Arcadia_ARMS_Status_OperationInvalid;
      } else {
         lock->count++;
         return Arcadia_ARMS_Status_Success;
      }
    }
  }
  Arms_Lock *lock = malloc(sizeof(Arms_Lock));
  if (!lock) {
    return Arcadia_ARMS_Status_AllocationFailed;
  }
  lock->next = g_locks;
  g_locks = lock;
  lock->object = object;
  lock->count = 1;
  return Arcadia_ARMS_Status_Success;
}

Arcadia_ARMS_Status
Arcadia_ARMS_unlock
  (
    void* object
  )
{
  for (Arms_Lock* lock = g_locks; NULL != lock; lock = lock->next) {
    if (lock->object == object) {
      if (lock->count == 0) {
         return Arcadia_ARMS_Status_OperationInvalid;
      } else {
         lock->count--;
         return Arcadia_ARMS_Status_Success;
      }
    }
  }
  return Arcadia_ARMS_Status_OperationInvalid;
}

#endif

#if defined(Arcadia_ARMS_Configuration_WithBarriers) && 1 == Arcadia_ARMS_Configuration_WithBarriers

void
Arcadia_ARMS_forwardBarrier
  (
    void* source,
    void* target
  )
{ }

void
Arcadia_ARMS_backwardBarrier
  (
    void* source,
    void* target
  )
{ }

#endif // Arcadia_ARMS_Configuration_WithBarriers

Arcadia_ARMS_MemoryManager*
Arcadia_ARMS_getDefaultMemoryManager
  (
  )
{ return (Arcadia_ARMS_MemoryManager*)g_defaultMemoryManager; }

Arcadia_ARMS_MemoryManager*
Arcadia_ARMS_getSlabMemoryManager
  (
  )
{ return (Arcadia_ARMS_MemoryManager*)g_slabMemoryManager; }
