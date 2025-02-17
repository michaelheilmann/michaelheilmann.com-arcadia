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

#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"
#include "Arcadia/Ring1/Implementation/Process1.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include <stdint.h>
typedef struct Arcadia_ValueStack Arcadia_ValueStack;
typedef struct Arcadia_Value Arcadia_Value;

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

/// @undefined @a process does not refer to a Arcadia_Process object
/// @undefined @a jumpTarget does not point to an Arcadia_JumpTarget object
void
Arcadia_Process_pushJumpTarget
  (
    Arcadia_Process* process,
    Arcadia_JumpTarget* jumpTarget
  );

/// @undefined @a process does not refer to a Arcadia_Process object
/// @undefined the jump target stack of the Arcadia_Process object is empty
void
Arcadia_Process_popJumpTarget
  (
    Arcadia_Process* process
  );

/// @undefined @a process does not refer to a Arcadia_Process object
/// @undefined the jump target stack of the Arcadia_Process object is empty
Arcadia_NoReturn() void
Arcadia_Process_jump
  (
    Arcadia_Process* process
  );

/// @return the status value
/// @undefined @a process does not refer to a Arcadia_Process object
Arcadia_Status
Arcadia_Process_getStatus
  (
    Arcadia_Process* process
  );

/// @param status the status value
/// @undefined @a process does not refer to a Arcadia_Process object
void
Arcadia_Process_setStatus
  (
    Arcadia_Process* process,
    Arcadia_Status status
  );

/// @brief
/// Allocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process object
/// @param p
/// A pointer to a <code>void*</code> variable.
/// @param n
/// The size, in Bytes, of the memory region to allocate.
/// @post
/// On success, <code>*p</code> was assigned a pointer to a memory region of @a n Bytes.
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a p is a null pointer
/// @error #Arcadia_Status_AllocationFailed
/// the allocation failed
void
Arcadia_Process_allocateUnmanaged
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  );

/// @brief
/// Deallocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process object
/// @param p
/// A pointer to a memory region of @a n Bytes.
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a p is a null pointer
void
Arcadia_Process_deallocateUnmanaged
  (
    Arcadia_Process* process,
    void* p
  );

/// @brief
/// Reallocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process object
/// @param p A pointer to a <code>void*</code> variable.
/// The variable points to the memory region to reallocate.
/// @param n
/// The size to reallocate the memory region to.
/// @post
/// On success, <code>*p</code> was assigned a pointer to a new memory region of @a n Bytes. The old memory region was deallocated.
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a p is a null pointer
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a *p is a null pointer
/// @error #Arcadia_Status_AllocationFailed
/// the allocation failed
/// @remarks O
void
Arcadia_Process_reallocateUnmanaged
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  );

/// @param process A pointer to the Arcadia_Process object
void
Arcadia_Process_visitObject
  (
    Arcadia_Process* process,
    void* object
  );

/// @param process A pointer to the Arcadia_Process object
Arcadia_Status
Arcadia_Process_lockObject
  (
    Arcadia_Process* process,
    void* object
  );

/// @param process A pointer to the Arcadia_Process object
Arcadia_Status
Arcadia_Process_unlockObject
  (
    Arcadia_Process* process,
    void* object
  );

Arcadia_Status
Arcadia_Process_stepArms
  (
    Arcadia_Process* process
  );

Arcadia_Status
Arcadia_Process_runArms
  (
    Arcadia_Process* process,
    bool purgeCaches
  );

void
Arcadia_Process_registerType
  (
    Arcadia_Process* process,
    const char* name,
    size_t nameLength,
    void* context,
    void (*typeRemoved)(void*, uint8_t const*, size_t),
    void (*visit)(void*, void*),
    void (*finalize)(void*, void*)
  );

void
Arcadia_Process_allocate
  (
    Arcadia_Process* process,
    void** p,
    const char* name,
    size_t nameLength,
    size_t size
  );

/// @return A pointer to the backing process object.
Arcadia_Process1*
Arcadia_Process_getProcess1
  (
    Arcadia_Process* process
  );

/// @return A pointer to the stack.
Arcadia_ValueStack*
Arcadia_Process_getStack
  (
    Arcadia_Process* process
  );

/// @brief Invoke a foreign procedure with the specified arguments.
/// Store the return value in result if the foreign procedure terminates with success.
/// Store void in return value if the foreign procedure terminates with failure.
/// The status variable indicates if the foreign procedure terminated with success or with failure.
void
Arcadia_Process_safeInvoke
  (
    Arcadia_Process* process,
    Arcadia_ForeignProcedure* procedure,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED
