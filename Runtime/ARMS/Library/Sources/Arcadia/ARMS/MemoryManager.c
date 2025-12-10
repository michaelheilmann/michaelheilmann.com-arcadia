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

#include "Arcadia/ARMS/Internal/MemoryManager.private.h"

Arcadia_ARMS_MemoryManager_Status
Arcadia_ARMS_MemoryManager_allocate
  (
    Arcadia_ARMS_MemoryManager* memoryManager,
    void** p,
    Arcadia_ARMS_Size n
  )
{
  if (!memoryManager) {
    return Arcadia_ARMS_MemoryManager_Status_ArgumentValueInvalid;
  }
  return memoryManager->allocate(memoryManager, p, n);
}

Arcadia_ARMS_MemoryManager_Status
Arcadia_ARMS_MemoryManager_reallocate
  (
    Arcadia_ARMS_MemoryManager* memoryManager,
    void** p,
    Arcadia_ARMS_Size n
  )
{
  if (!memoryManager) {
    return Arcadia_ARMS_MemoryManager_Status_ArgumentValueInvalid;
  }
  return memoryManager->reallocate(memoryManager, p, n);
}

Arcadia_ARMS_MemoryManager_Status
Arcadia_ARMS_MemoryManager_deallocate
  (
    Arcadia_ARMS_MemoryManager* memoryManager,
    void* p
  )
{
  if (!memoryManager) {
    return Arcadia_ARMS_MemoryManager_Status_ArgumentValueInvalid;
  }
  return memoryManager->deallocate(memoryManager, p);
}
