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

#include "Arcadia/Arms/Include.h"

#include "Arcadia/Arms/Internal/MemoryManager.private.h"
#include "Arcadia/Arms/Internal/DefaultMemoryManager.h"
#include "Arcadia/Arms/Internal/SlabMemoryManager.h"
#include "Arcadia/Arms/Internal/Statistics.h"
#include "Arcadia/Arms/NotifyDestroy.h"

#include "Arcadia/Arms/Internal/Common.h"

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

#if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks

// INT_MAX
#include <limits.h>

#endif

typedef struct Arms_Type Arms_Type;

typedef struct Arms_Tag Arms_Tag;

#if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks

typedef struct Arms_Lock Arms_Lock;

#endif

struct Arms_Type {
  Arms_Type* next;
  uint8_t* name;
  size_t nameLength;
  void* context;
  Arms_TypeRemovedCallbackFunction* typeRemoved;
  Arms_VisitCallbackFunction* visit;
  Arms_FinalizeCallbackFunction* finalize;
};

#define Arms_TagFlags_White (1)
#define Arms_TagFlags_Black (2)
#define Arms_TagFlags_Gray (Arms_TagFlags_White|Arms_TagFlags_Black)

#if Arcadia_Arms_Configuration_InstructionSetArchitecture_X64 == Arcadia_Arms_Configuration_InstructionSetArchitecture

  // We must make sure that this thing is 64 bit aligned.
  #if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Msvc
    #pragma pack(push, 8)
  #endif

#elif Arcadia_Arms_Configuration_InstructionSetArchitecture_X32 == Arcadia_Arms_Configuration_InstructionSetArchitecture

  // We must make sure that this thing is 32 bit aligned.
  #if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Msvc
    #pragma pack(push, 4)
  #endif

#endif

struct Arms_Tag {
  uint8_t flags;
  Arms_Type* type;
  Arms_Tag* universeNext;
  Arms_Tag* grayNext;
}
#if Arcadia_Arms_Configuration_InstructionSetArchitecture_X64 == Arcadia_Arms_Configuration_InstructionSetArchitecture
  // We must make sure that this thing is 64 bit aligned.
  #if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Gcc
    __attribute__((aligned(16)))
  #endif
#elif Arcadia_Arms_Configuration_InstructionSetArchitecture_X32 == Arcadia_Arms_Configuration_InstructionSetArchitecture
  // We must make sure that this thing is 32 bit aligned.
  #if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Gcc
    __attribute__((aligned(16)))
  #endif
#endif
;

#if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Msvc
  #pragma pack(pop)
#endif

#if Arcadia_Arms_Configuration_InstructionSetArchitecture_X64 == Arcadia_Arms_Configuration_InstructionSetArchitecture
  Cxx_staticAssert(sizeof(Arms_Tag) % 8 == 0, "Arms_Tag size not 8 Byte aligned");
#elif Arcadia_Arms_Configuration_InstructionSetArchitecture_X32 == Arcadia_Arms_Configuration_InstructionSetArchitecture
  Cxx_staticAssert(sizeof(Arms_Tag) % 4 == 0, "Arms_Tag size not 4 Byte aligned");
#endif

#if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks

struct Arms_Lock {
  Arms_Lock* next;
  int count;
  void* object;
};

#endif

typedef Arcadia_Arms_Size Arcadia_Arms_ReferenceCount;
#define Arcadia_Arms_ReferenceCount_Minimum (Arcadia_Arms_Size_Minimum)
#define Arcadia_Arms_ReferenceCount_Maximum (Arcadia_Arms_Size_Maximum)
static Arcadia_Arms_ReferenceCount g_referenceCount = 0;

static Arms_Type* g_types = NULL;
static Arms_Tag* g_universe = NULL;
static Arms_Tag* g_grayObjects = NULL;

#if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks

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

static Arms_DefaultMemoryManager* g_defaultMemoryManager = NULL;
static Arms_SlabMemoryManager* g_slabMemoryManager = NULL;

Arcadia_Arms_Status
Arms_startup
  (
  )
{
  if (g_referenceCount == Arcadia_Arms_ReferenceCount_Maximum) {
    // Cannot increment further.
    return Arcadia_Arms_Status_OperationInvalid;
  }
  if (!g_referenceCount) {
    switch (Arms_DefaultMemoryManager_create(&g_defaultMemoryManager)) {
      case Arms_MemoryManagerStartupShutdown_Status_AllocationFailed: {
        return Arcadia_Arms_Status_AllocationFailed;
      } break;
      case Arms_MemoryManagerStartupShutdown_Status_ArgumentValueInvalid: {
        return Arcadia_Arms_Status_ArgumentValueInvalid;
      } break;
      case Arms_MemoryManagerStartupShutdown_Status_Success: {
        /* Intentionally empty.*/
      } break;
      default: {
        return Arcadia_Arms_Status_EnvironmentFailed;
      } break;
    };
    switch (Arms_SlabMemoryManager_create(&g_slabMemoryManager)) {
      case Arms_MemoryManagerStartupShutdown_Status_AllocationFailed: {
        Arms_MemoryManager_destroy((Arms_MemoryManager*)g_defaultMemoryManager);
        g_defaultMemoryManager = NULL;
        return Arcadia_Arms_Status_AllocationFailed;
      } break;
      case Arms_MemoryManagerStartupShutdown_Status_ArgumentValueInvalid: {
        Arms_MemoryManager_destroy((Arms_MemoryManager*)g_defaultMemoryManager);
        g_defaultMemoryManager = NULL;
        return Arcadia_Arms_Status_ArgumentValueInvalid;
      } break;
      case Arms_MemoryManagerStartupShutdown_Status_Success: {
        /* Intentionally empty.*/
      } break;
      default: {
        Arms_MemoryManager_destroy((Arms_MemoryManager*)g_defaultMemoryManager);
        g_defaultMemoryManager = NULL;
        return Arcadia_Arms_Status_EnvironmentFailed;
      } break;
    };

    g_types = NULL;

    g_universe = NULL;
    g_grayObjects = NULL;

  #if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks
    g_locks = NULL;
  #endif

  #if defined(Arcadia_Arms_Configuration_WithNotifyDestroy) && 1 == Arcadia_Arms_Configuration_WithNotifyDestroy
    if (Arms_NotifyDestroyModule_startup()) {
      Arms_MemoryManager_destroy((Arms_MemoryManager*)g_slabMemoryManager);
      g_slabMemoryManager = NULL;
      Arms_MemoryManager_destroy((Arms_MemoryManager*)g_defaultMemoryManager);
      g_defaultMemoryManager = NULL;
      return Arcadia_Arms_Status_EnvironmentFailed;
    }
  #endif

  }
  g_referenceCount++;
  return Arcadia_Arms_Status_Success;
}

Arcadia_Arms_Status
Arms_shutdown
  (
  )
{
  if (Arcadia_Arms_ReferenceCount_Minimum == g_referenceCount) {
    // Cannot decrement further.
    return Arcadia_Arms_Status_OperationInvalid;
  }
  int32_t referenceCount = g_referenceCount - 1;
  if (!referenceCount) {
    if (g_grayObjects || g_universe) {
      Cxx_fatalError();
    }
  #if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks
    if (g_locks) {
      Cxx_fatalError();
    }
  #endif
  #if defined(Arcadia_Arms_Configuration_WithNotifyDestroy) && 1 == Arcadia_Arms_Configuration_WithNotifyDestroy
    Arms_NotifyDestroyModule_shutdown();
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
    Arms_MemoryManager_destroy((Arms_MemoryManager*)g_slabMemoryManager);
    g_slabMemoryManager = NULL;
    Arms_MemoryManager_destroy((Arms_MemoryManager*)g_defaultMemoryManager);
    g_defaultMemoryManager = NULL;
  }
  g_referenceCount = referenceCount;
  return Arcadia_Arms_Status_Success;
}

Arcadia_Arms_Status
Arms_addType
  (
    Arms_Natural8 const* name,
    Arcadia_Arms_Size nameLength,
    void* context,
    Arms_TypeRemovedCallbackFunction* typeRemoved,
    Arms_VisitCallbackFunction* visit,
    Arms_FinalizeCallbackFunction* finalize
  )
{
  if (!name) {
    return Arcadia_Arms_Status_ArgumentValueInvalid;
  }

  for (Arms_Type* type = g_types; NULL != type; type = type->next) {
    if (type->nameLength == nameLength){
      if (!memcmp(type->name, name, nameLength)) {
        return Arcadia_Arms_Status_TypeExists;
      }
    }
  }

  Arms_Type* type = malloc(sizeof(Arms_Type));
  if (!type) {
    return Arcadia_Arms_Status_AllocationFailed;
  }

  type->nameLength = nameLength;
  type->name = malloc(nameLength > 0 ? nameLength : 1);
  if (!type->name) {
    free(type);
    type = NULL;
    return Arcadia_Arms_Status_AllocationFailed;
  }
  memcpy(type->name, name, nameLength);

  type->context = context;
  type->typeRemoved = typeRemoved;
  type->visit = visit;
  type->finalize = finalize;

  type->next = g_types;
  g_types = type;

  return Arcadia_Arms_Status_Success;
}

Arcadia_Arms_Status
Arms_allocate
  (
    void** pObject,
    Arms_Natural8 const* name,
    Arcadia_Arms_Size nameLength,
    Arcadia_Arms_Size size
  )
{
  if (!pObject || !name) {
    return Arcadia_Arms_Status_ArgumentValueInvalid;
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
    return Arcadia_Arms_Status_TypeNotExists;
  }
  if (SIZE_MAX - sizeof(Arms_Tag) < size) {
    return Arcadia_Arms_Status_ArgumentValueInvalid;
  }
  Arms_Tag* object = malloc(sizeof(Arms_Tag) + size);
  if (!object) {
    return Arcadia_Arms_Status_AllocationFailed;
  }
  object->flags = Arms_TagFlags_White;
  object->type = type;
  object->universeNext = g_universe;
  g_universe = object;
  *pObject = object + 1;
  return Arcadia_Arms_Status_Success;
}

Arcadia_Arms_Status
Arms_run
  (
    Arms_RunStatistics* statistics
  )
{
  size_t destroyed = 0;
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
      object->type->visit(object->type->context, object + 1);
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
    #if defined(Arcadia_Arms_Configuration_WithNotifyDestroy) && 1 == Arcadia_Arms_Configuration_WithNotifyDestroy
      Arms_NotifyDestroyModule_notifyDestroy(deadObject + 1);
    #endif
      if (deadObject->type->finalize) {
        deadObject->type->finalize(deadObject->type->context, deadObject + 1);
      }
      destroyed++;
      free(deadObject);
    } else {
      Arms_Tag_setWhite(currentObject);
      previousObject = &currentObject->universeNext;
      currentObject = currentObject->universeNext;
    }
  }
  statistics->destroyed = destroyed;
  return Arcadia_Arms_Status_Success;
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

#if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks

Arcadia_Arms_Status
Arms_lock
  (
    void* object
  )
{
  for (Arms_Lock* lock = g_locks; NULL != lock; lock = lock->next) {
    if (lock->object == object) {
      if (lock->count == INT_MAX) {
         return Arcadia_Arms_Status_OperationInvalid;
      } else {
         lock->count++;
         return Arcadia_Arms_Status_Success;
      }
    }
  }
  Arms_Lock *lock = malloc(sizeof(Arms_Lock));
  if (!lock) {
    return Arcadia_Arms_Status_AllocationFailed;
  }
  lock->next = g_locks;
  g_locks = lock;
  lock->object = object;
  lock->count = 1;
  return Arcadia_Arms_Status_Success;
}

Arcadia_Arms_Status
Arms_unlock
  (
    void* object
  )
{
  for (Arms_Lock* lock = g_locks; NULL != lock; lock = lock->next) {
    if (lock->object == object) {
      if (lock->count == 0) {
         return Arcadia_Arms_Status_OperationInvalid;
      } else {
         lock->count--;
         return Arcadia_Arms_Status_Success;
      }
    }
  }
  return Arcadia_Arms_Status_OperationInvalid;
}

#endif

Arms_MemoryManager*
Arms_getDefaultMemoryManager
  (
  )
{ return (Arms_MemoryManager*)g_defaultMemoryManager; }

Arms_MemoryManager*
Arms_getSlabMemoryManager
  (
  )
{ return (Arms_MemoryManager*)g_slabMemoryManager; }
