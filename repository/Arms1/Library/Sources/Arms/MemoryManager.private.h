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

// Last modified: 2024-08-31

#if !defined(ARMS_MEMORYMANAGER_PRIVATE_H_INCLUDED)
#define ARMS_MEMORYMANAGER_PRIVATE_H_INCLUDED

#include "Arms/MemoryManager.h"
#include "Arms/Configure.h"

typedef enum Arms_MemoryManagerStartupShutdown_Status {
  Arms_MemoryManagerStartupShutdown_Status_Success = 0,
  Arms_MemoryManagerStartupShutdown_Status_ArgumentValueInvalid = 1,
  Arms_MemoryManagerStartupShutdown_Status_AllocationFailed = 2,
} Arms_MemoryManagerStartupShutdown_Status;

struct Arms_MemoryManager {
  Arms_MemoryManager_Status (*allocate)(Arms_MemoryManager* self, void** p, size_t n);
  Arms_MemoryManager_Status (*reallocate)(Arms_MemoryManager* self, void** p, size_t n);
  Arms_MemoryManager_Status (*deallocate)(Arms_MemoryManager* self, void* p);
  Arms_MemoryManagerStartupShutdown_Status(*destroy)(Arms_MemoryManager* self);
};

Arms_MemoryManagerStartupShutdown_Status
Arms_MemoryManager_destroy
  (
    Arms_MemoryManager* memoryManager
  );

#endif // ARMS_MEMORYMANAGER_PRIVATE_H_INCLUDED
