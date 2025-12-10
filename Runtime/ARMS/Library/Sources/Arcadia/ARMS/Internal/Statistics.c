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

#include "Arcadia/ARMS/Internal/Statistics.h"

Arcadia_ARMS_Status
Arcadia_ARMS_AllocatorStatistics_initialize
  (
    Arcadia_ARMS_AllocatorStatistics* statistics
  )
{
  statistics->numberOfBlocks = 0;
  statistics->numberOfBytes = 0;
  return Arcadia_ARMS_Status_Success;
}

Arcadia_ARMS_Status
Arcadia_ARMS_AllocatorStatistics_uninitialize
  (
    Arcadia_ARMS_AllocatorStatistics* statistics
  )
{
  statistics->numberOfBlocks = 0;
  statistics->numberOfBytes = 0;
  return Arcadia_ARMS_Status_Success;
}

Arcadia_ARMS_Status
Arcadia_ARMS_AllocatorStatistics_onBlockAllocated
  (
    Arcadia_ARMS_AllocatorStatistics* statistics,
    Arcadia_ARMS_Size numberOfBytes
  )
{
  if (!statistics) {
    return Arcadia_ARMS_Status_ArgumentValueInvalid;
  }
  // It is possible to have n > 0 blocks with m = 0 Bytes as zero-sized allocations are allowed.
  if (Arcadia_ARMS_Size_Maximum - statistics->numberOfBytes < numberOfBytes || Arcadia_ARMS_Size_Maximum - statistics->numberOfBlocks < 1) {
    return Arcadia_ARMS_Status_ArgumentValueInvalid;
  }
  statistics->numberOfBytes += numberOfBytes;
  statistics->numberOfBlocks += 1;
  return Arcadia_ARMS_Status_Success;
}

Arcadia_ARMS_Status
Arcadia_ARMS_AllocatorStatistics_onBlockDeallocated
  (
    Arcadia_ARMS_AllocatorStatistics* statistics,
    Arcadia_ARMS_Size numberOfBytes
  )
{
  if (!statistics) {
    return Arcadia_ARMS_Status_ArgumentValueInvalid;
  }
  if (statistics->numberOfBytes < numberOfBytes || statistics->numberOfBlocks < 1) {
    return Arcadia_ARMS_Status_ArgumentValueInvalid;
  }
  statistics->numberOfBytes -= numberOfBytes;
  statistics->numberOfBlocks -= 1;
  return Arcadia_ARMS_Status_Success;
}
