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

#if !defined(R_ARMSINTEGRATION_H_INCLUDED)
#define R_ARMSINTEGRATION_H_INCLUDED

#include "R/Boolean.h"
#include "R/Size.h"
#include "R/Status.h"

R_Status
R_Arms_startup
  (
  );

R_Status
R_Arms_shutdown
  (
  );

R_Status
R_Arms_step
  (
  );

R_Status
R_Arms_run
  (
  );

/// @brief Allocate managed memory.
/// @param p A pointer to a <code>void*</code> variable.
/// @param name A pointer to an array of Bytes.
/// @param nameLength The number of Bytes in the array pointed to by @a name.
/// @param size The size, in Bytes, of the memory to allocate. @a 0 is a valid size.
/// @return
/// R_Status_Success on success.
/// - R_Status_AllocationFailed if an allocation failed.
/// - R_Status_TypeNotExists if the type does not exist.
/// - R_Status_ArgumentInvalid if @a p or @a name is a null pointer.
R_BooleanValue
R_Arms_allocate_nojump
  (
    void** p,
    char const* name,
    size_t nameLength,
    size_t size
  );

/// @return #R_BooleanValue_True on success. #R_BooleanValue_False on failure.
/// @remarks This function sets the status variable on failure. However, it does not invoke R_jump(),
/// If <code>p</code> is a null pointer, then #R_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #R_Status_AllocationFailed is assigned.
R_BooleanValue
R_Arms_allocateUnmanaged_nojump
  (
    void** p,
    R_SizeValue n
  );

/// @return #R_BooleanValue_True on success. #R_BooleanValue_False on failure.
/// @remarks This function sets the status variable on failure. However, it does not invoke R_jump(),
/// If <code>p</code> is a null pointer, then #R_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #R_Status_AllocationFailed is assigned.
R_BooleanValue
R_Arms_deallocateUnmanaged_nojump
  (
    void* p
  );

/// @return #R_BooleanValue_True on success. #R_BooleanValue_False on failure.
/// @remarks This function sets the status variable on failure. However, it does not invoke R_jump(),
/// If <code>p</code> is a null pointer, then #R_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #R_Status_AllocationFailed is assigned.
R_BooleanValue
R_Arms_reallocateUnmanaged_nojump
  (
    void** p,
    R_SizeValue n
  );

#endif // R_ARMSINTEGRATION_H_INCLUDED
