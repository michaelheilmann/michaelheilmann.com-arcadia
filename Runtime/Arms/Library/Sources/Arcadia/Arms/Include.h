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

/// Alias for
#define Arms_SizeOf(x) sizeof(x)
#define Arms_AlignOf(x) _Alignof(x)
#define Arms_OffsetOf(x) offsetof(x)

typedef void (Arms_TypeRemovedCallbackFunction)(void* context, Arms_Natural8 const* name, Arcadia_Arms_Size nameLength);

typedef void (Arms_VisitCallbackFunction)(void* context, void* object);

typedef void (Arms_FinalizeCallbackFunction)(void* context, void* object);

Arcadia_Arms_Status
Arms_startup
  (
  );

Arcadia_Arms_Status
Arms_shutdown
  (
  );

Arcadia_Arms_Status
Arms_addType
  (
    Arms_Natural8 const* name,
    Arcadia_Arms_Size nameLength,
    void* context,
    Arms_TypeRemovedCallbackFunction* typeRemoved,
    Arms_VisitCallbackFunction* visit,
    Arms_FinalizeCallbackFunction* finalize
  );

Arcadia_Arms_Status
Arms_allocate
  (
    void** pObject,
    Arms_Natural8 const* name,
    Arcadia_Arms_Size nameLength,
    Arcadia_Arms_Size size
  );

typedef struct Arms_RunStatistics {
  /// The number of objects destroyed in this run.
  Arcadia_Arms_Size destroyed;
} Arms_RunStatistics;

Arcadia_Arms_Status
Arms_run
  (
    Arms_RunStatistics* statistics
  );

void
Arms_visit
  (
    void* object
  );

#if defined(Arcadia_Arms_Configuration_WithNotifyDestroy) && 1 ==  Arcadia_Arms_Configuration_WithNotifyDestroy

typedef void (Arms_NotifyDestroyCallback)(void* argument1, void *argument2);

Arcadia_Arms_Status
Arms_removeNotifyDestroyAll
  (
    void* observed
  );

Arcadia_Arms_Status
Arms_addNotifyDestroy
  (
    void* observed,
    void* argument1,
    void* argument2,
    Arms_NotifyDestroyCallback* callback
  );

Arcadia_Arms_Status
Arms_removeNotifyDestroy
  (
    void* observed,
    void* argument1,
    void* argument2,
    Arms_NotifyDestroyCallback* callback
  );

Arcadia_Arms_Status
Arms_removeNotifyDestroyAll
  (
    void* observed
  );

#endif // Arcadia_Arms_Configuration_WithNotifyDestroy

#if defined(Arcadia_Arms_Configuration_WithLocks) && 1 == Arcadia_Arms_Configuration_WithLocks

Arcadia_Arms_Status
Arms_lock
  (
    void* object
  );

Arcadia_Arms_Status
Arms_unlock
  (
    void* object
  );

#endif // Arcadia_Arms_Configuration_WithLocks

Arms_MemoryManager*
Arms_getDefaultMemoryManager
  (
  );

Arms_MemoryManager*
Arms_getSlabMemoryManager
  (
  );

#endif // ARCADIA_ARMS_INCLUDE_H_INCLUDED
