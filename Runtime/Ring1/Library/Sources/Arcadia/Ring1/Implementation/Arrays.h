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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_ARRAYS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_ARRAYS_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Arms/Include.h"

/// @brief The strategy for a call to <code>Arcadia_Arrays_resizeBy*</code> functions.
typedef enum Arcadia_Arrays_ResizeStrategy {

  /// Symbolic constant indicating a growth strategy.
  ///
  /// Let capacity denote the capacity of the array, size denote the size of the array.
  /// Let maximalCapacity denote the maximal capacity.
  /// Let additionalCapacity be the amount to increase the capacity by.
  ///
  /// The growth strategy computes:
  /// - capacity@new = capacity@old + additionalCapacity if maximalCapacity - capacity@old >= additionalCapacity
  /// - fail otherwise
  Arcadia_Arrays_ResizeStrategy_Type1 = 1,

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
  Arcadia_Arrays_ResizeStrategy_Type2 = 2,

  /// Symbolic constant indicating a growth strategy.
  ///
  /// Let capacity denote the capacity of the array, size denote the size of the array.
  /// Let maximalCapacity denote the maximal capacity.
  /// Let additionalCapacity be the amount to increase the capacity by.
  ///
  /// This growth strategy computes:
  /// - capacity@new = maximalCapacity if maximalCapacity - size >= additionalCapacity
  /// - fail otherwise
  Arcadia_Arrays_ResizeStrategy_Type3 = 3,

  /// Attempt Arcadia_Arrays_ResizeStrategy_Type2 first.
  /// If that growth strategy fails:
  /// Attempt Arcadia_Arrays_ResizeStrategy_Type3 second.
  /// If that growth strategy fails:
  /// Fail.
  Arcadia_Arrays_ResizeStrategy_Type4 = 4,

} Arcadia_Arrays_ResizeStrategy;

/// @brief Resize an array taking into account a required additional capacity.
/// @param elements A pointer to the element array of the array.
/// @param elementSize The size of an element.
/// @param size The size of the array.
/// @param capacity A pointer to the capacity of the array.
/// @param requiredAdditionalCapacity The required additional capacity.
/// @param strategy The resize strategy.
/// @error #Arcadia_Status_ArgumentValueInvalid @a memoryManager, @a elements, or @a capacity are null
/// @error #Arcadia_Status_ArgumentValueInvalid @a elementSize is @a 0
/// @error #Arcadia_Status_ArgumentValueInvalid @a size is greater than @a *capacity
/// @error #Arcadia_Status_NotExists the new capacity cannot be represented by the Arcadia_SizeValue type
/// @error #Arcadia_Status_AllocationFailed an allocation failed
void
Arcadia_Arrays_resizeByAdditionalCapacity
  (
    Arcadia_Thread* thread,
    Arms_MemoryManager* memoryManager,
    void** elements,
    Arcadia_SizeValue elementSize,
    Arcadia_SizeValue size,
    Arcadia_SizeValue* capacity,
    Arcadia_SizeValue requiredAdditionalCapacity,
    Arcadia_Arrays_ResizeStrategy strategy
  );

/// @brief Resize an array taking into account a required free capacity.
/// @param elements A pointer to the element array of the array.
/// @param elementSize The size of an element.
/// @param size The size of the array.
/// @param capacity A pointer to the capacity of the array.
/// @param requiredFreeCapacity The required free capacity.
/// @param strategy The resize strategy.
/// @error #Arcadia_Status_ArgumentValueInvalid @a memoryManager, @a elements, or @a capacity are null
/// @error #Arcadia_Status_ArgumentValueInvalid @a elementSize is @a 0
/// @error #Arcadia_Status_ArgumentValueInvalid @a size is greater than @a *capacity
/// @error #Arcadia_Status_NotExists the new capacity cannot be represented by the Arcadia_SizeValue type
/// @error #Arcadia_Status_AllocationFailed an allocation failed
void
Arcadia_Arrays_resizeByFreeCapacity
  (
    Arcadia_Thread* thread,
    Arms_MemoryManager* memoryManager,
    void** elements,
    Arcadia_SizeValue elementSize,
    Arcadia_SizeValue size,
    Arcadia_SizeValue* capacity,
    Arcadia_SizeValue requiredFreeCapacity,
    Arcadia_Arrays_ResizeStrategy strategy
  );

#endif // ARCADIA_RING1_ARRAYS_H_INCLUDED
