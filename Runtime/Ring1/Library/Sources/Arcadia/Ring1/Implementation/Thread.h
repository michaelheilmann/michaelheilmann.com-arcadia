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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_THREAD_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_THREAD_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Annotations/NoReturn.h"

#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC
#include <stddef.h>
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Status.h"
#include "Arcadia/Ring1/Implementation/Value.h"

#include <setjmp.h>
typedef struct Arcadia_Process Arcadia_Process; // Forward declaration.



typedef struct Arcadia_JumpTarget Arcadia_JumpTarget;

/// Representation of an interpreter thread.
typedef struct Arcadia_Thread Arcadia_Thread;



struct Arcadia_JumpTarget {
  Arcadia_JumpTarget* previous;
  jmp_buf environment;
};

#define Arcadia_JumpTarget_save(jumpTarget) (!setjmp((jumpTarget)->environment))

Arcadia_SizeValue
Arcadia_ValueStack_getSize
  (
    Arcadia_Thread* thread
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a index is greater than or equal to the stack size
Arcadia_Value
Arcadia_ValueStack_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a value is a null pointer
/// @error Arcadia_Status_AllocationFailed an allocation failed
void
Arcadia_ValueStack_pushValue
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a count is greater than the size of the stack
void
Arcadia_ValueStack_popValues
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue count
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a{start + count} overflows
/// @error Arcadia_Status_ArgumentValueInvalid @a{start + count} is greater than the size of the stack
void
Arcadia_ValueStack_reverse
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue start,
    Arcadia_SizeValue count
  );

/// @brief Push a jump target on the top of the jump target stack of this thread
/// @param thread A pointer to this Arcadia_Thread object
/// @undefined @a process does not refer to a Arcadia_Thread object
/// @undefined @a jumpTarget does not point to an Arcadia_JumpTarget object
/// @undefined Invoked without having the exclusive lock to the thread
void
Arcadia_Thread_pushJumpTarget
  (
    Arcadia_Thread* thread,
    Arcadia_JumpTarget* jumpTarget
  );

/// @brief Pop a jump target from the top of the jump target stack of this thread
/// @param thread A pointer to this Arcadia_Thread object
/// @undefined @a thread does not refer to a Arcadia_Thread object
/// @undefined the jump target stack of the Arcadia_Thread object is empty
/// @undefined Invoked without having the exclusive lock to the thread
void
Arcadia_Thread_popJumpTarget
  (
    Arcadia_Thread* thread
  );

/// @brief Jump to the jump target on the top of the jump target stack of this thread
/// @param thread A pointer to this Arcadia_Thread object
/// @undefined @a thread does not refer to a Arcadia_Thread object
/// @undefined the jump target stack of the Arcadia_Process object is empty
/// @undefined Invoked without having the exclusive lock to the thread
Arcadia_NoReturn() void
Arcadia_Thread_jump
  (
    Arcadia_Thread* thread
  );

/// @brief Get the status variable value of this thread.
/// @param thread A pointer to this Arcadia_Thread object.
/// @return the status value.
/// @undefined @a thread does not refer to a Arcadia_Thread object.
/// @undefined Invoked without having the exclusive lock to the thread.
Arcadia_Status
Arcadia_Thread_getStatus
  (
    Arcadia_Thread* thread
  );

/// @brief Set the status variable value of this thread.
/// @param thread A pointer to this Arcadia_Thread object.
/// @param status the status value.
/// @undefined @a thread does not refer to a Arcadia_Thread object.
/// @undefined Invoked without having the exclusive lock to the thread.
void
Arcadia_Thread_setStatus
  (
    Arcadia_Thread* thread,
    Arcadia_Status status
  );

/// @brief Get the process of this thread.
/// @param thread A pointer to this Arcadia_Thread object.
/// @retur A pointer to the process of this thread.
/// @undefined @a thread does not refer to a Arcadia_Thread object.
/// @undefined Invoked without having the exclusive lock to the thread.
Arcadia_Process*
Arcadia_Thread_getProcess
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_THREAD_H_INCLUDED
