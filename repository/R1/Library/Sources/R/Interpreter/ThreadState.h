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

// Last modified: 2024-12-07

#if !defined(R_INTERPRETER_THREADSTATE_H_INCLUDED)
#define R_INTERPRETER_THREADSTATE_H_INCLUDED

#include "R/Value.h"
typedef struct R_Interpreter_Code R_Interpreter_Code;
typedef struct R_Interpreter_Procedure R_Interpreter_Procedure;

/// The thread state consists
/// - registers (at least 256)
/// - parameter passing registers (at least 32)
/// - stack of register frames which allow for pushing and restoring ranges of registers
typedef struct R_Interpreter_ThreadState R_Interpreter_ThreadState;

// @private
// @brief Create a thread state.
// @return A pointer to the thread state.
// @error #Arcadia_Status_AllocationFailed an allocation failed
R_Interpreter_ThreadState*
R_Interpreter_ThreadState_create
  (
    Arcadia_Process* process
  );

// @private
// @brief Destroy a thread state.
// @param A pointer to the thread state.
void
R_Interpreter_ThreadState_destroy
  (
    Arcadia_Process* process,
    R_Interpreter_ThreadState* thread
  );

// @private
// @brief Visit this thread state during a "visit" phase.
// @param A pointer to the thread state.
void
R_Interpreter_ThreadState_visit
  (
    R_Interpreter_ThreadState* thread
  );

// @private
// @brief Get the number of registers.
// @param A pointer to the thread state.
// @return The number of registers.
Arcadia_SizeValue
R_Interpreter_ThreadState_getNumberOfRegisters
  (
    R_Interpreter_ThreadState* thread
  );

/// @private
/// @brief Get the register at the specified index.
/// @param A pointer to the thread state.
/// @return A pointer to the register.
/// @error #Arcadia_Status_RegisterIndexOutOfBounds the index is not within the bounds of [0, R_Interpreter_ThreadState_getNumberOfRegisters(threadState)].
R_Value*
R_Interpreter_ThreadState_getRegisterAt
  (
    R_Interpreter_ThreadState* thread,
    Arcadia_SizeValue registerIndex
  );

typedef struct R_CallState R_CallState;

/**
 * @brief Indicates that a call state is the call state of a procedure.
 */
#define R_CallState_Flags_Procedure (1)

/**
 * @brief Indicates that a call state is the call state of a foreign procedure.
 */
#define R_CallState_Flags_ForeignProcedure (2)

struct R_CallState {
  R_CallState* previous;
  /**
   * @brief Must be one of R_CallState_Flags_Procedure or R_CallState_Flags_ForeignProcedure.
   */
  Arcadia_Natural8Value flags;
  /** 
   * The instruction index of this call.
   */
  Arcadia_Natural32Value instructionIndex;
  union {
    /// Pointer to the procedure to be called.
    R_Interpreter_Procedure* procedure;
    /// Pointer to the foreign procedure to be called.
    Arcadia_ForeignProcedureValue foreignProcedure;
  };
};

///
R_CallState*
R_Interpreter_ThreadState_beginForeignProcedureCall
  (
    R_Interpreter_ThreadState* thread,
    Arcadia_Natural32Value instructionIndex,
    Arcadia_ForeignProcedureValue foreignProcedure
  );

R_CallState*
R_Interpreter_ThreadState_beginProcedureCall
  (
    R_Interpreter_ThreadState* thread,
    Arcadia_Natural32Value instructionIndex,
    R_Interpreter_Procedure* procedure
  );

/// calls@new = [...] and calls@old = [x,...]
void
R_Interpreter_ThreadState_endCall
  (
    R_Interpreter_ThreadState* thread
  );

/**
 * @brief Get the current call of this thread.
 * @param thread A pointer to this thread.
 * @return A pointer to the current call. The null pointer if there is no current call.
 */
R_CallState*
R_Interpreter_ThreadState_getCurrentCall
  (
    R_Interpreter_ThreadState* thread
  );

#endif // R_INTERPRETER_THREADSTATE_H_INCLUDED
