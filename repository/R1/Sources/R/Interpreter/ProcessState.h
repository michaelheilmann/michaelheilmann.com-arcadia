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

// Last modified: 2024-12-07

#if !defined(R_INTERPRETER_PROCESSSTATE_H_INCLUDED)
#define R_INTERPRETER_PROCESSSTATE_H_INCLUDED

#include "R/Interpreter/Class.h"
#include "R/Interpreter/Procedure.h"
#include "R/String.h"
#include "R/Interpreter/Instruction.h"

/**
 * @brief The state of the interpreter process.
 * @details
 * The interpreter comprises a single interpreter process and multiple interpreter threads.
 * The threads are owned by the process.
 * The process has a single main thread when the process is created.
 * The process has a current thread which is the main thread when the process is created.
 * When the process executes, it will execute the current thread until the thread terminates.
 * When the current thread terminates, another thread becomes the main thread.
 */
typedef struct R_Interpreter_ProcessState R_Interpreter_ProcessState;

/// @error R_Status_AllocationFailed an allocation failed
R_Interpreter_ProcessState*
R_Interpreter_ProcessState_create
  (
  );

void
R_Interpreter_ProcessState_destroy
  (
    R_Interpreter_ProcessState* self
  );

void
R_Interpreter_ProcessState_visit
  (
    R_Interpreter_ProcessState* self
  );

/**
 * @brief Define a global procedure.
 * @param procedure The procedure.
 * @error R_Status_ArgumentValueInvalid @a procedure is a null pointer
 * @error R_Status_ArgumentValueInvalid a class or procedure of that name already exists
 * @error R_Status_AllocationFailed an allocation failed
 */
void
R_Interpreter_ProcessState_defineGlobalProcedure
  (
    R_Interpreter_ProcessState* self,
    R_Interpreter_Procedure* procedure
  );

/**
 * @brief Define a global class.
 * @param class The class.
 * @error R_Status_ArgumentValueInvalid @a class is a null pointer
 * @error R_Status_ArgumentValueInvalid a class or procedure of that name already exists
 * @error R_Status_AllocationFailed an allocation failed
 */
void
R_Interpreter_ProcessState_defineGlobalClass
  (
    R_Interpreter_ProcessState* self,
    R_Interpreter_Class* class
  );

/**
 * @brief Get a global.
 * @param name The name of the global.
 * @return The global.
 * @error R_Status_ArgumentValueInvalid @a name is a null pointer
 * @error R_Status_NotExists no global of name @a name was found 
 */
R_Value
R_Interpreter_ProcessState_getGlobal
  (
    R_Interpreter_ProcessState* self,
    R_String* name
  );

/**
 * @brief Get the main thread.
 * @param self A pointer to this process.
 * @return The main thread.
 */
R_Interpreter_ThreadState*
R_Interpreter_ProcessState_getMainThread
  (
    R_Interpreter_ProcessState* self
  );

/**
 * @brief Get the current thread.
 * @param self A pointer to this process.
 * @return The current thread.
 */
R_Interpreter_ThreadState*
R_Interpreter_ProcessState_getCurrentThread
  (
    R_Interpreter_ProcessState* self
  );

R_Interpreter_Code_Constants*
R_Interpreter_ProcessState_getConstants
  (
    R_Interpreter_ProcessState* self
  );

#endif // R_INTERPRETER_PROCESSSTATE_H_INCLUDED
