// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_ARMS_MEMORYMANAGER_PRIVATE_H_INCLUDED)
#define ARCADIA_ARMS_MEMORYMANAGER_PRIVATE_H_INCLUDED

#include "Arcadia/ARMS/MemoryManager.h"
#include "Arcadia/ARMS/Configure.h"

typedef enum Arcadia_ARMS_MemoryManagerStartupShutdown_Status {
  Arcadia_ARMS_MemoryManagerStartupShutdown_Status_Success = 0,
  Arcadia_ARMS_MemoryManagerStartupShutdown_Status_ArgumentValueInvalid = 1,
  Arcadia_ARMS_MemoryManagerStartupShutdown_Status_AllocationFailed = 2,
} Arcadia_ARMS_MemoryManagerStartupShutdown_Status;

struct Arcadia_ARMS_MemoryManager {
  Arcadia_ARMS_MemoryManager_Status (*allocate)(Arcadia_ARMS_MemoryManager* self, void** p, size_t n);
  Arcadia_ARMS_MemoryManager_Status (*reallocate)(Arcadia_ARMS_MemoryManager* self, void** p, size_t n);
  Arcadia_ARMS_MemoryManager_Status (*deallocate)(Arcadia_ARMS_MemoryManager* self, void* p);
  Arcadia_ARMS_MemoryManagerStartupShutdown_Status(*destroy)(Arcadia_ARMS_MemoryManager* self);
};

Arcadia_ARMS_MemoryManagerStartupShutdown_Status
Arcadia_ARMS_MemoryManager_destroy
  (
    Arcadia_ARMS_MemoryManager* memoryManager
  );

#endif // ARCADIA_ARMS_MEMORYMANAGER_PRIVATE_H_INCLUDED
