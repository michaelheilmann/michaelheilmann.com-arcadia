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

#include "Arcadia/ARMS/Internal/SlabMemoryManager.h"

#include "Arcadia/ARMS/Include.h"

struct Arcadia_ARMS_SlabMemoryManager {
  Arcadia_ARMS_MemoryManager parent;
};

static Arcadia_ARMS_MemoryManager_Status
allocate
  (
    Arcadia_ARMS_SlabMemoryManager* self,
    void** p,
    Arcadia_ARMS_Size n
  )
{
  if (!p) {
    return Arcadia_ARMS_MemoryManager_Status_ArgumentValueInvalid;
  }
  void* q = malloc(n > 0 ? n : 1);
  if (!q) {
    return Arcadia_ARMS_MemoryManager_Status_AllocationFailed;
  }
  *p = q;
  return Arcadia_ARMS_MemoryManager_Status_Success;
}

static Arcadia_ARMS_MemoryManager_Status
reallocate
  (
    Arcadia_ARMS_SlabMemoryManager* self,
    void** p,
    Arcadia_ARMS_Size n
  )
{
  if (!p) {
    return Arcadia_ARMS_MemoryManager_Status_ArgumentValueInvalid;
  }
  void* q = realloc(*p, n > 0 ? n : 1);
  if (!q) {
    return Arcadia_ARMS_MemoryManager_Status_AllocationFailed;
  }
  *p = q;
  return Arcadia_ARMS_MemoryManager_Status_Success;
}

static Arcadia_ARMS_MemoryManager_Status
deallocate
  (
    Arcadia_ARMS_SlabMemoryManager* self,
    void* p
  )
{
  if (!p) {
    return Arcadia_ARMS_MemoryManager_Status_ArgumentValueInvalid;
  }
  free(p);
  return Arcadia_ARMS_MemoryManager_Status_Success;
}

static Arcadia_ARMS_MemoryManagerStartupShutdown_Status
destroy
  (
    Arcadia_ARMS_SlabMemoryManager* self
  )
{
  free(self);
  return Arcadia_ARMS_MemoryManagerStartupShutdown_Status_Success;
}

Arcadia_ARMS_MemoryManagerStartupShutdown_Status
Arcadia_ARMS_SlabMemoryManager_create
  (
    Arcadia_ARMS_SlabMemoryManager** result
  )
{
  if (!result) {
    return Arcadia_ARMS_MemoryManagerStartupShutdown_Status_ArgumentValueInvalid;
  }
  Arcadia_ARMS_SlabMemoryManager* self = malloc(sizeof(Arcadia_ARMS_SlabMemoryManager));
  if (!self) {
    return Arcadia_ARMS_MemoryManagerStartupShutdown_Status_AllocationFailed;
  }
  ((Arcadia_ARMS_MemoryManager*)self)->allocate = (Arcadia_ARMS_MemoryManager_Status (*)(Arcadia_ARMS_MemoryManager*, void**, Arcadia_ARMS_Size)) & allocate;
  ((Arcadia_ARMS_MemoryManager*)self)->reallocate = (Arcadia_ARMS_MemoryManager_Status(*)(Arcadia_ARMS_MemoryManager*, void**, Arcadia_ARMS_Size)) &reallocate;
  ((Arcadia_ARMS_MemoryManager*)self)->deallocate = (Arcadia_ARMS_MemoryManager_Status(*)(Arcadia_ARMS_MemoryManager*, void*)) &deallocate;
  ((Arcadia_ARMS_MemoryManager*)self)->destroy = (Arcadia_ARMS_MemoryManagerStartupShutdown_Status(*)(Arcadia_ARMS_MemoryManager*)) &destroy;
  *result = self;
  return Arcadia_ARMS_MemoryManagerStartupShutdown_Status_Success;
}
