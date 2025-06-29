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

#if !defined(ARCADIA_ARMS_INTERNAL_STATISTICS_H_INCLUDED)
#define ARCADIA_ARMS_INTERNAL_STATISTICS_H_INCLUDED

#include "Arcadia/Arms/SizeType.h"
#include "Arcadia/Arms/StatusType.h"

/// @brief
/// Statistics of the GC.
/// @remarks
/// The statistics keep track of the total number of objects and the total number of Bytes allocated.
typedef struct Arcadia_Arms_AllocatorStatistics {

  Arcadia_Arms_Size numberOfBlocks;    ///< The number of blocks currently allocated.
                                       ///< @a numberOfBytes is the sum of the sizes, in Bytes, of all these blocks.

  Arcadia_Arms_Size numberOfBytes;     ///< The number of Bytes currently allocated.

} Arcadia_Arms_AllocatorStatistics;

/// @brief Initialize a @a Arcadia_Arms_AllocatorStatistics object.
/// @param self a pointer to an uninitialized a @a Arcadia_Arms_AllocatorStatistics object.
/// @return #Arcadia_Arms_Status_Success on success. A non-zero Arcadia_Arms_Status value on failure.
Arcadia_Arms_Status
Arcadia_Arms_AllocatorStatistics_initialize
  (
    Arcadia_Arms_AllocatorStatistics* statistics
  );

/// @brief Uninitialize a @a Arcadia_Arms_AllocatorStatistics object.
/// @param statistics a pointer to an uninitialized @a Arcadia_Arms_AllocatorStatistics object
/// @return #Arcadia_Arms_Status_Success on success. A non-zero Arcadia_Arms_Status value on failure.
Arcadia_Arms_Status
Arcadia_Arms_AllocatorStatistics_uninitialize
  (
    Arcadia_Arms_AllocatorStatistics* statistics
  );

/// @brief Update memory statistics for an allocation.
/// @param statistics a pointer to an initialized @a Arcadia_Arms_AllocatorStatistics object
/// @param numberOfBytes The number of Bytes that has been allocated.
/// @return #Arcadia_Arms_Status_Success on success. A non-zero Arcadia_Arms_Status value on failure.
Arcadia_Arms_Status
Arcadia_Arms_AllocatorStatistics_onBlockAllocated
  (
    Arcadia_Arms_AllocatorStatistics* statistics,
    Arcadia_Arms_Size numberOfBytes
  );

/// @brief Update memory statistics for a deallocation.
/// @param statistics a pointer to an initialized @a Arcadia_Arms_AllocatorStatistics object
/// @param numberOfBytes The number of Bytes that has been deallocated.
/// @return #Arcadia_Arms_Status_Success on success. A non-zero Arcadia_Arms_Status value on failure.
Arcadia_Arms_Status
Arcadia_Arms_AllocatorStatistics_onBlockDeallocated
  (
    Arcadia_Arms_AllocatorStatistics* statistics,
    Arcadia_Arms_Size numberOfBytes
  );

#endif // ARCADIA_ARMS_INTERNAL_STATISTICS_H_INCLUDED
