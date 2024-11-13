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

#include "R/UnmanagedMemory.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/ArmsIntegration.h"

R_BooleanValue
R_allocateUnmanaged_nojump
  (
    void** p,
    R_SizeValue n
  )
{ return R_Arms_allocateUnmanaged_nojump(p, n); }

R_BooleanValue
R_deallocateUnmanaged_nojump
  (
    void* p
  )
{ return R_Arms_deallocateUnmanaged_nojump(p); }

R_BooleanValue
R_reallocateUnmanaged_nojump
  (
    void** p,
    R_SizeValue n
  )
{ return R_Arms_reallocateUnmanaged_nojump(p, n); }

void
R_DynamicArrayUtilities_ensureFreeCapacity1
  (
    void** elements,
    R_SizeValue elementSize,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  )
{
  if (!elements || !capacity || !elementSize || size > (*capacity)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_SizeValue availableFreeCapacity = (*capacity) - size;
  if (availableFreeCapacity > requiredFreeCapacity) {
    // Nothing to do.
    return;
  }
  R_SizeValue additionalCapacity = requiredFreeCapacity - availableFreeCapacity;
  const R_SizeValue maximalCapacity = R_SizeValue_Maximum / elementSize;
  if (maximalCapacity - additionalCapacity < (*capacity)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  R_SizeValue newCapacity = additionalCapacity + (*capacity);
  if (!R_reallocateUnmanaged_nojump(elements, newCapacity * elementSize)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  *capacity = newCapacity;
}

// Compute the new capacity
// - <new capacity> = 2^<n> * 1 if <capacit> > 0
// - <new capacity> = 2^<n> * <capacity> otherwise
// such that
// - <n> is minimal and
// - <new capacity> - <size> >= <required free capacity>
//
// If such a <new capacity> does not exist, return false and do not modify *capacity.
// Otherwise, assign <new capacity> to *capacity and return true.
static bool
computeNewCapacity21
  (
    R_SizeValue elementSize,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  )
{
  R_SizeValue const maximalCapacity = R_SizeValue_Maximum / elementSize;
  R_SizeValue currentNewCapacity = *capacity ? *capacity : 1;
  R_SizeValue availableFreeCapacity = currentNewCapacity - size;
  while (availableFreeCapacity < requiredFreeCapacity && currentNewCapacity <= maximalCapacity / 2) {
    currentNewCapacity *= 2;
    availableFreeCapacity = currentNewCapacity - size;
  }
  if (availableFreeCapacity < requiredFreeCapacity) {
    return false;
  }
  *capacity = currentNewCapacity;
  return true;
}

// Compute the new capacity
// <new capacity> = <maximal capacity>
// such that
// <new capacity> - <size> >= <required free capacity>.
// 
// If such a <new capacity> does not exist, return false and do not modify *capacity.
// Otherwise, assign <new capacity> to *capacity and return true.
static bool
computeNewCapacity22
  (
    R_SizeValue elementSize,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  )
{
  R_SizeValue const maximalCapacity = R_SizeValue_Maximum / elementSize;
  R_SizeValue currentNewCapacity = maximalCapacity;
  R_SizeValue availableFreeCapacity = currentNewCapacity - size;
  if (requiredFreeCapacity > availableFreeCapacity) {
    return false;
  }
  *capacity = currentNewCapacity;
  return true;
}

static bool
computeNewCapacity2
  (
    R_SizeValue elementSize,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  )
{
  if (computeNewCapacity21(elementSize, size, capacity, requiredFreeCapacity)) {
    return true;
  }
  if (computeNewCapacity22(elementSize, size, capacity, requiredFreeCapacity)) {
    return true;
  }
  return false;
}

void
R_DynamicArrayUtilities_ensureFreeCapacity2
  (
    void** elements,
    R_SizeValue elementSize,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  )
{
  R_SizeValue newCapacity = *capacity;
  if (!computeNewCapacity2(elementSize, size, &newCapacity, requiredFreeCapacity)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  if (newCapacity != *capacity) {
    if (!R_reallocateUnmanaged_nojump(elements, newCapacity * elementSize)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    *capacity = newCapacity;
  }
}
