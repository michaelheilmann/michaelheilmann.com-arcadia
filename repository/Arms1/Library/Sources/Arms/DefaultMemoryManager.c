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

#include "Arms/DefaultMemoryManager.h"

#include "Arms.h"

struct Arms_DefaultMemoryManager {
  Arms_MemoryManager parent;
};

static Arms_MemoryManager_Status
allocate
  (
    Arms_DefaultMemoryManager* self,
    void** p,
    Arms_Size n
  )
{
  if (!p) {
    return Arms_MemoryManager_Status_ArgumentValueInvalid;
  }
  void* q = malloc(n > 0 ? n : 1);
  if (!q) {
    return Arms_MemoryManager_Status_AllocationFailed;
  }
  *p = q;
  return Arms_MemoryManager_Status_Success;
}

static Arms_MemoryManager_Status
reallocate
  (
    Arms_DefaultMemoryManager* self,
    void** p,
    Arms_Size n
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

static Arms_MemoryManager_Status
deallocate
  (
    Arms_DefaultMemoryManager* self,
    void* p
  )
{
  if (!p) {
    return Arms_Status_ArgumentValueInvalid;
  }
  free(p);
  return Arms_Status_Success;
}

static Arms_MemoryManagerStartupShutdown_Status
destroy
  (
    Arms_DefaultMemoryManager* self
  )
{
  free(self);
  return Arms_MemoryManagerStartupShutdown_Status_Success;
}

Arms_MemoryManagerStartupShutdown_Status
Arms_DefaultMemoryManager_create
  (
    Arms_DefaultMemoryManager** result
  )
{ 
  if (!result) {
    return Arms_MemoryManagerStartupShutdown_Status_ArgumentValueInvalid;
  }
  Arms_DefaultMemoryManager* self = malloc(sizeof(Arms_DefaultMemoryManager));
  if (!self) {
    return Arms_MemoryManagerStartupShutdown_Status_AllocationFailed;
  }
  ((Arms_MemoryManager*)self)->allocate = (Arms_MemoryManager_Status (*)(Arms_MemoryManager*, void**, Arms_Size)) & allocate;
  ((Arms_MemoryManager*)self)->reallocate = (Arms_MemoryManager_Status(*)(Arms_MemoryManager*, void**, Arms_Size)) &reallocate;
  ((Arms_MemoryManager*)self)->deallocate = (Arms_MemoryManager_Status(*)(Arms_MemoryManager*, void*)) &deallocate;
  ((Arms_MemoryManager*)self)->destroy = (Arms_MemoryManagerStartupShutdown_Status(*)(Arms_MemoryManager*)) &destroy;
  *result = self;
  return Arms_MemoryManagerStartupShutdown_Status_Success;
}
