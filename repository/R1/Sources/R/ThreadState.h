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
typedef struct R_Machine_Code R_Machine_Code;
typedef struct R_Procedure R_Procedure;

/// The thread state consists
/// - registers (at least 256)
/// - parameter passing registers (at least 32)
/// - stack of register frames which allow for pushing and restoring ranges of registers
typedef struct R_ThreadState R_ThreadState;

// @private
// @brief Create a thread state.
// @param procedure A pointer to the procedure to execute.
// @return A pointer to the thread state.
// @error #R_Status_AllocationFailed an allocation failed
R_ThreadState*
R_ThreadState_create
  (
    R_Procedure* procedure
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

typedef struct R_CallState R_CallState;

/*#define R_CallState_Flags_Interpreter (1)*/
#define R_CallState_Flags_Procedure (1)
#define R_CallState_Flags_ForeignProcedure (2)

struct R_CallState {
  R_CallState* previous;
  R_Natural8Value flags;
  /// The current instruction index of this call.
  R_Natural32Value instructionIndex;
  union {
    /// Pointer to the procedure to be called.
    R_Procedure* procedure;
    /// Pointer to the foreign procedure to be called.
    R_ForeignProcedureValue foreignProcedure;
  };
};

///
R_CallState*
R_ThreadState_beginForeignProcedureCall
  (
    R_ThreadState* threadState,
    R_Natural32Value instructionIndex,
    R_ForeignProcedureValue foreignProcedure
  );

R_CallState*
R_ThreadState_beginProcedureCall
  (
    R_ThreadState* threadState,
    R_Natural32Value instructionIndex,
    R_Procedure* procedure
  );

/// calls@new = [...] and calls@old = [x,...]
void
R_ThreadState_endCall
  (
    R_ThreadState* threadState
  );

#endif // R_THREADSTATE_H_INCLUDED
