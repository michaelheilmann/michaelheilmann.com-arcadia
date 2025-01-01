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

// Last modified: 2024-08-31

#if !defined(ARMS_H_INCLUDED)
#define ARMS_H_INCLUDED

#include "Arms/Configure.h"
#include "Arms/SizeType.h"
#include "Arms/MemoryManager.h"

// size_t
#include <stddef.h>
// uint8_t
#include <stdint.h>

/// Alias for
#define Arms_SizeOf(x) sizeof(x)
#define Arms_AlignOf(x) _Alignof(x)
#define Arms_OffsetOf(x) offsetof(x)

// An unsigned binary integer of a width of 8 Bits.
typedef uint8_t Arms_Natural8;

/// The minimum value of Arms_Natural8.
/// Guaranteed to be @a 0.
#define Arms_Natural8_Minimum (UINT8_C(0))

/// The maximum value of Arms_Natural8.
#define Arms_Natural8_Maximum (UINT8_MAX)

typedef enum Arms_Status {
  Arms_Status_Success = 0,
  Arms_Status_ArgumentValueInvalid = 1,
  Arms_Status_AllocationFailed = 2,
  Arms_Status_TypeExists = 3,
  Arms_Status_TypeNotExists = 4,
  Arms_Status_OperationInvalid = 5,
  Arms_Status_EnvironmentFailed = 6,
} Arms_Status;

typedef void (Arms_TypeRemovedCallbackFunction)(void* context, Arms_Natural8 const* name, Arms_Size nameLength);

typedef void (Arms_VisitCallbackFunction)(void* context, void* object);

typedef void (Arms_FinalizeCallbackFunction)(void* context, void* object);

Arms_Status
Arms_startup
  (
  );

Arms_Status
Arms_shutdown
  (
  );

Arms_Status
Arms_addType
  (
    Arms_Natural8 const* name,
    Arms_Size nameLength,
    void* contex,
    Arms_TypeRemovedCallbackFunction* typeRemoved,
    Arms_VisitCallbackFunction* visit,
    Arms_FinalizeCallbackFunction* finalize
  );

Arms_Status
Arms_allocate
  (
    void** pObject,
    Arms_Natural8 const* name,
    Arms_Size nameLength,
    Arms_Size size
  );

typedef struct Arms_RunStatistics {
  /// The number of objects destroyed in this run.
  Arms_Size destroyed;
} Arms_RunStatistics;

Arms_Status
Arms_run
  (
    Arms_RunStatistics* statistics
  );

void
Arms_visit
  (
    void* object
  );
  
#if defined(Arms_Configuration_WithLocks) && 1 == Arms_Configuration_WithLocks

Arms_Status
Arms_lock
  (
    void* object
  );

Arms_Status
Arms_unlock
  (
    void* object
  );

#endif // Arms_Configuration_WithLocks

Arms_MemoryManager*
Arms_getDefaultMemoryManager
  (
  );

Arms_MemoryManager*
Arms_getSlabMemoryManager
  (
  );

#endif // ARMS_H_INCLUDED
