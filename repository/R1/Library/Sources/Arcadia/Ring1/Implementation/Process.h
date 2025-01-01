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

// Last modified: 2024-08-27

#if !defined(ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED

#include "Arcadia/Ring1/Implementation/NoReturn.h"
#include <stdint.h>
#include <setjmp.h>

typedef struct R_JumpTarget R_JumpTarget;

struct R_JumpTarget {
  R_JumpTarget* previous;
  jmp_buf environment;
};

#define R_JumpTarget_save(jumpTarget) (!setjmp((jumpTarget)->environment))

#define Arcadia_Status_Success (0)

#define Arcadia_Status_AllocationFailed (1)
#define Arcadia_Status_ArgumentTypeInvalid (2)
#define Arcadia_Status_ArgumentValueInvalid (3)
#define Arcadia_Status_ConversionFailed (4)
#define Arcadia_Status_DivisionByZero (5)
#define Arcadia_Status_EncodingInvalid (6)
#define Arcadia_Status_Exists (7)
#define Arcadia_Status_FileSystemOperationFailed (8)
#define Arcadia_Status_Initialized (9)
#define Arcadia_Status_LexicalError (10)
#define Arcadia_Status_NotExists (11)
#define Arcadia_Status_NumberOfArgumentsInvalid (12)
#define Arcadia_Status_OperationInvalid (13)
#define Arcadia_Status_SemanticalError (14)
#define Arcadia_Status_SyntacticalError (15)
#define Arcadia_Status_TestFailed (16)
#define Arcadia_Status_TypeExists (17)
#define Arcadia_Status_TypeNotExists (18)
#define Arcadia_Status_Uninitialized (19)
#define Arcadia_Status_EnvironmentFailed (20)
#define Arcadia_Status_NotInitialized (21)

typedef uint32_t Arcadia_Status;

typedef uint32_t Arcadia_ProcessStatus;
#define Arcadia_ProcessStatus_Success (0)
#define Arcadia_ProcessStatus_ArgumentValueInvalid (1)
#define Arcadia_ProcessStatus_AllocationFailed (2)
#define Arcadia_ProcessStatus_OperationInvalid (3)
#define Arcadia_ProcessStatus_EnvironmentFailed (4)

/// the process object provides access to the current thread.
/// the current thread provides access to the thread's jump target stack and the thread's status variable.
typedef struct Arcadia_Process Arcadia_Process;

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
Arcadia_ProcessStatus
Arcadia_Process_acquire
  (
    Arcadia_Process* process
  );

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
Arcadia_ProcessStatus
Arcadia_Process_relinquish
  (
    Arcadia_Process* process
  );

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
/// - #Arcadia_ProcessStatus_EnvironmentFailed initialization of Arcadia ARMS failed
/// - #Arcadia_ProcessStatus_AllocationFailed an allocation failed
Arcadia_ProcessStatus
Arcadia_Process_get
  (
    Arcadia_Process** process
  );

/// @undefined @a process does not refer to a Arcadia_Process object.
/// @undefined @a jumpTarget does not point to an Arcadia_JumpTarget object.
void
Arcadia_Process_pushJumpTarget
  (
    Arcadia_Process* process,
    R_JumpTarget* jumpTarget
  );

/// @undefined @a process does not refer to a Arcadia_Process object.
/// @undefined the jump target stack of the Arcadia_Process object is empty.
void
Arcadia_Process_popJumpTarget
  (
    Arcadia_Process* process
  );

/// @undefined @a process does not refer to a Arcadia_Process object.
/// @undefined the jump target stack of the Arcadia_Process object is empty.
Arcadia_NoReturn() void
Arcadia_Process_jump
  (
    Arcadia_Process* process
  );

Arcadia_Status
Arcadia_Process_getStatus
  (
    Arcadia_Process* process
  );

void
Arcadia_Process_setStatus
  (
    Arcadia_Process* process,
    Arcadia_Status status
  );

#endif // R_JUMPTARGET_H_INCLUDED
