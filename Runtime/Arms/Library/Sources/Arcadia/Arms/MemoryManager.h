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

typedef enum Arcadia_Arms_MemoryManager_Status {
  Arcadia_Arms_MemoryManager_Status_Success = 0,
  Arcadia_Arms_MemoryManager_Status_ArgumentValueInvalid = 1,
  Arcadia_Arms_MemoryManager_Status_AllocationFailed = 2,
} Arcadia_Arms_MemoryManager_Status;

/// A memory manager.
/// Allows for allocation, reallocation, and deallocation of memory blocks.
typedef struct Arcadia_Arms_MemoryManager Arcadia_Arms_MemoryManager;

Arcadia_Arms_MemoryManager_Status
Arcadia_Arms_MemoryManager_allocate
  (
    Arcadia_Arms_MemoryManager* memoryManager,
    void** p,
    Arcadia_Arms_Size n
  );

Arcadia_Arms_MemoryManager_Status
Arcadia_Arms_MemoryManager_reallocate
  (
    Arcadia_Arms_MemoryManager* memoryManager,
    void** p,
    Arcadia_Arms_Size n
  );

Arcadia_Arms_MemoryManager_Status
Arcadia_Arms_MemoryManager_deallocate
  (
    Arcadia_Arms_MemoryManager* memoryManager,
    void* p
  );

#endif // ARCADIA_ARMS_MEMORYMANAGER_H_INCLUDED
