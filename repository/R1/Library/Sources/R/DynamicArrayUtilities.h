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

#if !defined(R_DYNAMICARRAYUTILITIES_H_INCLUDED)
#define R_DYNAMICARRAYUTILITIES_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Size.h"

typedef enum R_DynamicArrayUtilities_GrowthStrategy {

  /// Symbolic constant indicating a growth strategy.
  ///
  /// Let capacity denote the capacity of the array, size denote the size of the array.
  /// Let maximalCapacity denote the maximal capacity.
  /// Let additionalCapacity be the amount to increase the capacity by.
  /// 
  /// The growth strategy computes:
  /// - capacity@new = capacity@old + additionalCapacity if maximalCapacity - capacity@old >= additionalCapacity
  /// - fail otherwise
  R_DynamicArrayUtilities_GrowthStrategy1 = 1,

  /// Symbolic constant indicating a growth strategy.
  ///
  /// Let capacity denote the capacity of the array, size denote the size of the array.
  /// Let maximalCapacity denote the maximal capacity.
  /// Let additionalCapacity be the amount to increase the capacity by.
  /// 
  /// This growth strategy computes:
  /// - capacity@new = 2^n * 1 if capacity@old = 0
  /// - capacity@new = 2^n * capacity@old
  /// such that
  /// n is minimal whilst capacity@new >= capacity@old + additionalCapacity
  /// If no such n exists, fail.
  R_DynamicArrayUtilities_GrowthStrategy2 = 2,

  /// Symbolic constant indicating a growth strategy.
  ///
  /// Let capacity denote the capacity of the array, size denote the size of the array.
  /// Let maximalCapacity denote the maximal capacity.
  /// Let additionalCapacity be the amount to increase the capacity by.
  /// 
  /// This growth strategy computes:
  /// - capacity@new = maximalCapacity if maximalCapacity - size >= additionalCapacity
  /// - fail otherwise
  R_DynamicArrayUtilities_GrowthStrategy3 = 3,

  /// Attempt R_DynamicArrayUtilities_GrowthStrategy2 first.
  /// If that growth strategy fails:
  /// Attempt R_DynamicArrayUtilities_GrowthStrategy3 second.
  /// If that growth strategy fails:
  /// Fail.
  R_DynamicArrayUtilities_GrowthStrategy4 = 4,

} R_DynamicArrayUtilities_GrowthStrategy;

typedef enum R_DynamicArrayUtilities_Result {
  R_DynamicArrayUtilities_Result_Success = 0,
  R_DynamicArrayUtilities_Result_InvalidArgument = 1,
  R_DynamicArrayUtilities_Result_NotExists = 2,
  R_DynamicArrayUtilities_Result_AllocationFailed = 3,
} R_DynamicArrayUtilities_Result;

// @brief Grow an array as specified by a growth strategy.
// @param A pointer to the element array of the array.
// @param The size of the array.
// @param capacity A pointer to the capacity of the array.
// @param additionalCapacity The least amount to grow the array by.
// @param strategy The growth strategy.
// @return
// #R_DynamicArrayUtilities_Success on success.
// A non-zero R_DynamicArraySizing value on failure.
// @todo
// The array must have been (re)allocated using Arms_getDefaultMemoryManager.
// Allow for passing the memory manager.
R_DynamicArrayUtilities_Result
R_DynamicArrayUtilities_grow
  (
    void** elements,
    Arcadia_SizeValue elementSize,
    Arcadia_SizeValue size,
    Arcadia_SizeValue* capacity,
    Arcadia_SizeValue additionalCapacity,
    R_DynamicArrayUtilities_GrowthStrategy strategy
  );

// Grow the array such that there is room for at least required free capacity elements.
// availableFreeCapacity = capacity@old - size
// capacity@new = capacity@old + (requiredFreeCapacity - availableFreeCapacity) if requiredFreeCapacity > availableFreeCapacity
// capacity@new = capacity@old otherwise
R_DynamicArrayUtilities_Result
R_DynamicArrayUtilities_ensureFreeCapacity
  (
    void** elements,
    Arcadia_SizeValue elementSize,
    Arcadia_SizeValue size,
    Arcadia_SizeValue* capacity,
    Arcadia_SizeValue requiredFreeCapacity,
    R_DynamicArrayUtilities_GrowthStrategy strategy
  );

#endif // R_DYNAMICARRAYS_H_INCLUDED
