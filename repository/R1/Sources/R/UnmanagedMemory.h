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

#if !defined(R_UNMANAGEDMEMORY_H_INCLUDED)
#define R_UNMANAGEDMEMORY_H_INCLUDED

#include "R/Boolean.h"
#include "R/Size.h"

/// @return #R_BooleanValue_True on success. #R_BooleanValue_False on failure.
/// @remarks This function sets the status variable on failure. However, it does not invoke R_jump(),
/// If <code>p</code> is a null pointer, then #R_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #R_Status_AllocationFailed is assigned.
R_BooleanValue
R_allocateUnmanaged_nojump
  (
    void** p,
    R_SizeValue n
  );

/// @return #R_BooleanValue_True on success. #R_BooleanValue_False on failure.
/// @remarks This function sets the status variable on failure. However, it does not invoke R_jump(),
/// If <code>p</code> is a null pointer, then #R_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #R_Status_AllocationFailed is assigned.
R_BooleanValue
R_deallocateUnmanaged_nojump
  (
    void* p
  );

/// @return #R_BooleanValue_True on success. #R_BooleanValue_False on failure.
/// @remarks This function sets the status variable on failure. However, it does not invoke R_jump(),
/// If <code>p</code> is a null pointer, then #R_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #R_Status_AllocationFailed is assigned.
R_BooleanValue
R_reallocateUnmanaged_nojump
  (
    void** p,
    R_SizeValue n
  );

// Grow the array such that there is room for at least required free capacity elements.
// availableFreeCapacity = capacity@old - size
// capacity@new = capacity@old + (requiredFreeCapacity - availableFreeCapacity) if requiredFreeCapacity > availableFreeCapacity
// capacity@new = capacity@old otherwise
void
R_DynamicArrayUtilities_ensureFreeCapacity1
  (
    void** elements,
    R_SizeValue elementSize,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  );

// Grow the array such there is room for at least required free capacity elements.
// There are two attempts made.
// 
// The first attempt made is:
// Compute a new capacity
// - <new capacity> = 2^<n> * 1 if <capacit> > 0
// - <new capacity> = 2^<n> * <capacity> otherwise
// such that
// - <n> is minimal and
// - <new capacity> - <size> >= <required free capacity>
//
// If such a capacity does not exist, attempt two is made.
// The second attempt is:
// // <new capacity> = <maximal capacity>
// such that
// <new capacity> - <size> >= <required free capacity>.
// 
// If such a capacity does not exist, fail.
void
R_DynamicArrayUtilities_ensureFreeCapacity2
  (
    void** elements,
    R_SizeValue elementSize,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  );

#endif // R_UNMANAGEDMEMORY_H_INCLUDED
