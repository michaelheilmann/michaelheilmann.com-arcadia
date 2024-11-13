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

// Last modified: 2024-11-04

#if !defined(R_THREADSTATE_H_INCLUDED)
#define R_THREADSTATE_H_INCLUDED

#include "R/Value.h"

/// The thread state consists
/// - registers (at least 256)
/// - parameter passing registers (at least 32)
/// - stack of register frames which allow for pushing and restoring ranges of registers
typedef struct R_ThreadState R_ThreadState;

// @private
// @brief Create a thread state.
// @return A pointer to the thread state.
// @error #R_Status_AllocationFailed an allocation failed
R_ThreadState*
R_ThreadState_create
  (
  );

// @private
// @brief Destroy a thread state.
// @param A pointer to the thread state.
void
R_ThreadState_destroy
  (
    R_ThreadState* threadState
  );

// @private
// @brief Visit this thread state during a "visit" phase.
// @param A pointer to the thread state.
void
R_ThreadState_visit
  (
    R_ThreadState* threadState
  );

// @private
// @brief Get the number of registers.
// @param A pointer to the thread state.
// @return The number of registers.
R_SizeValue
R_ThreadState_getNumberOfRegisters
  (
    R_ThreadState* threadState
  );

// @todo Remove this.
R_Value*
R_ThreadState_getRegisters
  (
    R_ThreadState* threadState
  );

/// @private
/// @brief Get the register at the specified index.
/// @param A pointer to the thread state.
/// @return A pointer to the register.
/// @error #R_Status_RegisterIndexOutOfBounds the index is not within the bounds of [0, R_ThreadState_getNumberOfRegisters(threadState)].
R_Value*
R_ThreadState_getRegisterAt
  (
    R_ThreadState* threadState,
    R_SizeValue registerIndex
  );

/// @private
/// @brief Push a register frame.
/// @param start The register index of the first register to push.
/// @param length The number of registers to push.
/// @error #R_Status_ArgumentValueInvalid if <code>start + length > n</code> where <code>n</code> is the number of registers. 
void
R_ThreadState_pushRegisterFrame
  (
    R_ThreadState* threadState,
    R_SizeValue start,
    R_SizeValue length
  );

/// @private
/// @brief Pop the top most register frame.
/// @error #R_Status_StackIsEmpty The register frame stack is empty.
void
R_ThreadState_popRegisterFrame
  (
    R_ThreadState* threadState
  ); 

#endif // R_THREADSTATE_H_INCLUDED
