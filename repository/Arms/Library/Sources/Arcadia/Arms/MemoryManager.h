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

#if !defined(ARCADIA_ARMS_MEMORYMANAGER_H_INCLUDED)
#define ARCADIA_ARMS_MEMORYMANAGER_H_INCLUDED

#include "Arcadia/Arms/Configure.h"
#include "Arcadia/Arms/SizeType.h"

#include <stdlib.h>

typedef enum Arms_MemoryManager_Status {
  Arms_MemoryManager_Status_Success = 0,
  Arms_MemoryManager_Status_ArgumentValueInvalid = 1,
  Arms_MemoryManager_Status_AllocationFailed = 2,
} Arms_MemoryManager_Status;

/// A memory manager.
/// Allows for allocation, reallocation, and deallocation of memory blocks.
typedef struct Arms_MemoryManager Arms_MemoryManager;

Arms_MemoryManager_Status
Arms_MemoryManager_allocate
  (
    Arms_MemoryManager* memoryManager,
    void** p,
    Arcadia_Arms_Size n
  );

Arms_MemoryManager_Status
Arms_MemoryManager_reallocate
  (
    Arms_MemoryManager* memoryManager,
    void** p,
    Arcadia_Arms_Size n
  );

Arms_MemoryManager_Status
Arms_MemoryManager_deallocate
  (
    Arms_MemoryManager* memoryManager,
    void* p
  );

#endif // ARCADIA_ARMS_MEMORYMANAGER_H_INCLUDED
