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

#if !defined(ARCADIA_ARMS_INTERNAL_STATISTICS_H_INCLUDED)
#define ARCADIA_ARMS_INTERNAL_STATISTICS_H_INCLUDED

#include "Arcadia/ARMS/SizeType.h"
#include "Arcadia/ARMS/StatusType.h"

/// @brief
/// Statistics of the GC.
/// @remarks
/// The statistics keep track of the total number of objects and the total number of Bytes allocated.
typedef struct Arcadia_ARMS_AllocatorStatistics {

  Arcadia_ARMS_Size numberOfBlocks;    ///< The number of blocks currently allocated.
                                       ///< @a numberOfBytes is the sum of the sizes, in Bytes, of all these blocks.

  Arcadia_ARMS_Size numberOfBytes;     ///< The number of Bytes currently allocated.

} Arcadia_ARMS_AllocatorStatistics;

/// @brief Initialize a @a Arcadia_ARMS_AllocatorStatistics object.
/// @param self a pointer to an uninitialized a @a Arcadia_ARMS_AllocatorStatistics object.
/// @return #Arcadia_ARMS_Status_Success on success. A non-zero Arcadia_ARMS_Status value on failure.
Arcadia_ARMS_Status
Arcadia_ARMS_AllocatorStatistics_initialize
  (
    Arcadia_ARMS_AllocatorStatistics* statistics
  );

/// @brief Uninitialize a @a Arcadia_ARMS_AllocatorStatistics object.
/// @param statistics a pointer to an uninitialized @a Arcadia_ARMS_AllocatorStatistics object
/// @return #Arcadia_ARMS_Status_Success on success. A non-zero Arcadia_ARMS_Status value on failure.
Arcadia_ARMS_Status
Arcadia_ARMS_AllocatorStatistics_uninitialize
  (
    Arcadia_ARMS_AllocatorStatistics* statistics
  );

/// @brief Update memory statistics for an allocation.
/// @param statistics a pointer to an initialized @a Arcadia_ARMS_AllocatorStatistics object
/// @param numberOfBytes The number of Bytes that has been allocated.
/// @return #Arcadia_ARMS_Status_Success on success. A non-zero Arcadia_ARMS_Status value on failure.
Arcadia_ARMS_Status
Arcadia_ARMS_AllocatorStatistics_onBlockAllocated
  (
    Arcadia_ARMS_AllocatorStatistics* statistics,
    Arcadia_ARMS_Size numberOfBytes
  );

/// @brief Update memory statistics for a deallocation.
/// @param statistics a pointer to an initialized @a Arcadia_ARMS_AllocatorStatistics object
/// @param numberOfBytes The number of Bytes that has been deallocated.
/// @return #Arcadia_ARMS_Status_Success on success. A non-zero Arcadia_ARMS_Status value on failure.
Arcadia_ARMS_Status
Arcadia_ARMS_AllocatorStatistics_onBlockDeallocated
  (
    Arcadia_ARMS_AllocatorStatistics* statistics,
    Arcadia_ARMS_Size numberOfBytes
  );

#endif // ARCADIA_ARMS_INTERNAL_STATISTICS_H_INCLUDED
