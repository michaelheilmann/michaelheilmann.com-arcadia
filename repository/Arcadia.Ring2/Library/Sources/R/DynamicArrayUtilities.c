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

#include "R/DynamicArrayUtilities.h"

#include "Arms.h"

R_DynamicArrayUtilities_Result
R_DynamicArrayUtilities_grow
  (
    void** elements,
    Arcadia_SizeValue elementSize,
    Arcadia_SizeValue size,
    Arcadia_SizeValue* capacity,
    Arcadia_SizeValue additionalCapacity,
    R_DynamicArrayUtilities_GrowthStrategy strategy
  )
{ 
  if (!elements || !elementSize || !capacity || size > (*capacity)) {
    return R_DynamicArrayUtilities_Result_InvalidArgument;
  }
  Arcadia_SizeValue oldCapacity = *capacity;
  Arcadia_SizeValue newCapacity;
  Arcadia_SizeValue const maximalCapacity = Arcadia_SizeValue_Maximum / elementSize;
  switch (strategy) {
    case R_DynamicArrayUtilities_GrowthStrategy1: {
      if (maximalCapacity - oldCapacity < additionalCapacity) {
        return R_DynamicArrayUtilities_Result_NotExists;
      }
      newCapacity = oldCapacity + additionalCapacity;
      if (Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), elements, newCapacity * elementSize)) {
        return R_DynamicArrayUtilities_Result_AllocationFailed;
      }
      *capacity = newCapacity;
    } break;
    case R_DynamicArrayUtilities_GrowthStrategy2: {
      Arcadia_SizeValue currentNewCapacity = oldCapacity ? oldCapacity : 1; // 1 = 2^n with n = 0
      Arcadia_SizeValue currentAdditionalCapacity = currentNewCapacity - oldCapacity;
      while (currentAdditionalCapacity < additionalCapacity && currentNewCapacity <= maximalCapacity / 2) {
        currentNewCapacity *= 2;
        currentAdditionalCapacity = currentNewCapacity - oldCapacity;
      }
      if (currentAdditionalCapacity < additionalCapacity) {
        return R_DynamicArrayUtilities_Result_NotExists;
      }
      newCapacity = currentAdditionalCapacity + oldCapacity;
      if (Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), elements, newCapacity * elementSize)) {
        return R_DynamicArrayUtilities_Result_AllocationFailed;
      }
      *capacity = newCapacity;
    } break;
    case R_DynamicArrayUtilities_GrowthStrategy3: {
      Arcadia_SizeValue newCapacity = maximalCapacity;
      if (additionalCapacity > newCapacity - oldCapacity) {
        return R_DynamicArrayUtilities_Result_NotExists;
      }
      if (Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), elements, newCapacity * elementSize)) {
        return R_DynamicArrayUtilities_Result_AllocationFailed;
      }
      *capacity = newCapacity;
    } break;
    case R_DynamicArrayUtilities_GrowthStrategy4: {
      int result;
      result = R_DynamicArrayUtilities_grow(elements, elementSize, size, capacity, additionalCapacity, R_DynamicArrayUtilities_GrowthStrategy2);
      if (result) {
        return result;
      }
      result = R_DynamicArrayUtilities_grow(elements, elementSize, size, capacity, additionalCapacity, R_DynamicArrayUtilities_GrowthStrategy3);
      if (result) {
        return result;
      }
    } break;
    default: {
      return R_DynamicArrayUtilities_Result_InvalidArgument;
    } break;
  };
  return R_DynamicArrayUtilities_Result_Success;
}

R_DynamicArrayUtilities_Result
R_DynamicArrayUtilities_ensureFreeCapacity
  (
    void** elements,
    Arcadia_SizeValue elementSize,
    Arcadia_SizeValue size,
    Arcadia_SizeValue* capacity,
    Arcadia_SizeValue requiredFreeCapacity,
    R_DynamicArrayUtilities_GrowthStrategy strategy
  )
{
  if (!elements || !elementSize || !capacity || size > (*capacity)) {
    return R_DynamicArrayUtilities_Result_InvalidArgument;
  }
  Arcadia_SizeValue availableFreeCapacity = (*capacity) - size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    return R_DynamicArrayUtilities_grow(elements, elementSize, size, capacity, requiredFreeCapacity - availableFreeCapacity, strategy);
  }
  return R_DynamicArrayUtilities_Result_Success;
}
