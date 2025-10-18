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

#if !defined(ARCADIA_ARMS_INCLUDE_H_INCLUDED)
#define ARCADIA_ARMS_INCLUDE_H_INCLUDED

#include "Arcadia/Arms/Configure.h"
#include "Arcadia/Arms/SizeType.h"
#include "Arcadia/Arms/Natural8Type.h"
#include "Arcadia/Arms/StatusType.h"
#include "Arcadia/Arms/MemoryManager.h"

/// Alias for sizeof(expression).
#define Arcadia_Arms_SizeOf(expression) sizeof(expression)

/// Alias for _Alignof(expression).
#define Arcadia_Arms_AlignOf(expression) _Alignof(expression)

/// Alias for offsetof(expression).
#define Arcadia_Arms_OffsetOf(expression) offsetof(expression)

typedef void (Arcadia_Arms_TypeRemovedCallbackFunction)(void* context, Arms_Natural8 const* name, Arcadia_Arms_Size nameLength);

typedef void (Arcadia_Arms_VisitCallbackFunction)(void* context, void* object);

typedef void (Arcadia_Arms_FinalizeCallbackFunction)(void* context, void* object);

Arcadia_Arms_Status
Arcadia_Arms_startup
  (
  );

Arcadia_Arms_Status
Arcadia_Arms_shutdown
  (
  );

Arcadia_Arms_Status
Arcadia_Arms_addType
  (
    Arms_Natural8 const* name,
    Arcadia_Arms_Size nameLength,
    void* context,
    Arcadia_Arms_TypeRemovedCallbackFunction* typeRemoved,
    Arcadia_Arms_VisitCallbackFunction* visit,
    Arcadia_Arms_FinalizeCallbackFunction* finalize
  );

Arcadia_Arms_Status
Arcadia_Arms_allocate
  (
    void** pObject,
    Arms_Natural8 const* name,
    Arcadia_Arms_Size nameLength,
    Arcadia_Arms_Size size
  );

typedef struct Arcadia_Arms_RunStatistics {
  /// The number of locked objects.
  Arcadia_Arms_Size locked;
  /// The number of dead objects.
  Arcadia_Arms_Size dead;
  /// The number of live objects.
  Arcadia_Arms_Size live;
  /// The number of finalized objects.
  Arcadia_Arms_Size finalized;
} Arcadia_Arms_RunStatistics;

#define Arcadia_Arms_RunStatistics_StaticInitializer() { .locked = 0, .live = 0, .dead = 0, .finalized = 0 };

Arcadia_Arms_Status
Arcadia_Arms_run
  (
    Arcadia_Arms_RunStatistics* statistics
  );

void
Arcadia_Arms_visit
  (
    void* object
  );

#if defined(Arcadia_Arms_Configuration_WithNotifyDestroy) && 1 ==  Arcadia_Arms_Configuration_WithNotifyDestroy

typedef void (Arcadia_Arms_NotifyDestroyCallback)(void* argument1, void *argument2);

Arcadia_Arms_Status
Arcadia_Arms_removeNotifyDestroyAll
  (
    void* observed
  );

Arcadia_Arms_Status
Arcadia_Arms_addNotifyDestroy
  (
    void* observed,
    void* argument1,
    void* argument2,
    Arcadia_Arms_NotifyDestroyCallback* callback
  );

Arcadia_Arms_Status
Arcadia_Arms_removeNotifyDestroy
  (
    void* observed,
    void* argument1,
    void* argument2,
    Arcadia_Arms_NotifyDestroyCallback* callback
  );

Arcadia_Arms_Status
Arcadia_Arms_removeNotifyDestroyAll
  (
    void* observed
  );

#endif // Arcadia_Arms_Configuration_WithNotifyDestroy

#if defined(Arcadia_Arms_Configuration_WithBarriers) && 1 == Arcadia_Arms_Configuration_WithBarriers

// Ensures the invariant no black object may refer to a white object is preserved.
// If source is black and target is white, then color target gray.
void
Arcadia_Arms_forwardBarrier
  (
    void* source,
    void* target
  );

// Ensures the invariant no black object may refer to a white object is preserved.
// If source is black and target is white, then color source gray.
void
Arcadia_Arms_backwardBarrier
  (
    void* source,
    void* target
  ); 

#endif // Arcadia_Arms_Configuration_WithBarriers

#if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks

Arcadia_Arms_Status
Arcadia_Arms_lock
  (
    void* object
  );

Arcadia_Arms_Status
Arcadia_Arms_unlock
  (
    void* object
  );

#endif // Arcadia_Arms_Configuration_WithLocks

Arcadia_Arms_MemoryManager*
Arcadia_Arms_getDefaultMemoryManager
  (
  );

Arcadia_Arms_MemoryManager*
Arcadia_Arms_getSlabMemoryManager
  (
  );

#endif // ARCADIA_ARMS_INCLUDE_H_INCLUDED
