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

#include "Arms/MemoryManager.private.h"



Arms_MemoryManager_Status
Arms_MemoryManager_allocate
  (
    Arms_MemoryManager* memoryManager,
    void** p,
    Arms_Size n
  )
{
  if (!memoryManager) {
    return Arms_MemoryManager_Status_ArgumentValueInvalid;
  }
  return memoryManager->allocate(memoryManager, p, n);
}

Arms_MemoryManager_Status
Arms_MemoryManager_reallocate
  (
    Arms_MemoryManager* memoryManager,
    void** p,
    Arms_Size n
  )
{
  if (!memoryManager) {
    return Arms_MemoryManager_Status_ArgumentValueInvalid;
  }
  return memoryManager->reallocate(memoryManager, p, n);
}

Arms_MemoryManager_Status
Arms_MemoryManager_deallocate
  (
    Arms_MemoryManager* memoryManager,
    void* p
  )
{
  if (!memoryManager) {
    return Arms_MemoryManager_Status_ArgumentValueInvalid;
  }
  return memoryManager->deallocate(memoryManager, p);
}
