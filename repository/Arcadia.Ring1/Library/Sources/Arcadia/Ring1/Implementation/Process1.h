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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_PROCESS1_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_PROCESS1_H_INCLUDED

#include "Arcadia/Ring1/Implementation/NoReturn.h"
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>

typedef struct Arcadia_JumpTarget Arcadia_JumpTarget;

struct Arcadia_JumpTarget {
  Arcadia_JumpTarget* previous;
  jmp_buf environment;
};

#define Arcadia_JumpTarget_save(jumpTarget) (!setjmp((jumpTarget)->environment))

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
typedef struct Arcadia_Process1 Arcadia_Process1;

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
Arcadia_ProcessStatus
Arcadia_Process1_acquire
  (
    Arcadia_Process1* process
  );

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
Arcadia_ProcessStatus
Arcadia_Process1_relinquish
  (
    Arcadia_Process1* process
  );

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
/// - #Arcadia_ProcessStatus_EnvironmentFailed initialization of Arcadia ARMS failed
/// - #Arcadia_ProcessStatus_AllocationFailed an allocation failed
Arcadia_ProcessStatus
Arcadia_Process1_get
  (
    Arcadia_Process1** process
  );

/// @param process A pointer to the Arcadia_Process1 object
/// @undefined @a process does not refer to a Arcadia_Process object
/// @undefined @a jumpTarget does not point to an Arcadia_JumpTarget object
void
Arcadia_Process1_pushJumpTarget
  (
    Arcadia_Process1* process,
    Arcadia_JumpTarget* jumpTarget
  );

/// @param process A pointer to the Arcadia_Process1 object
/// @undefined @a process does not refer to a Arcadia_Process object
/// @undefined the jump target stack of the Arcadia_Process object is empty
void
Arcadia_Process1_popJumpTarget
  (
    Arcadia_Process1* process
  );

/// @undefined @a process does not refer to a Arcadia_Process object
/// @param process A pointer to the Arcadia_Process1 object
/// @undefined the jump target stack of the Arcadia_Process object is empty
Arcadia_NoReturn() void
Arcadia_Process1_jump
  (
    Arcadia_Process1* process
  );

/// @brief Get the status variable value
/// @param process A pointer to the Arcadia_Process1 object
/// @return the status value
/// @undefined @a process does not refer to a Arcadia_Process object
Arcadia_Status
Arcadia_Process1_getStatus
  (
    Arcadia_Process1* process
  );

/// @brief Set the status variable value
/// @param process A pointer to the Arcadia_Process1 object
/// @param status the status value
/// @undefined @a process does not refer to a Arcadia_Process object
void
Arcadia_Process1_setStatus
  (
    Arcadia_Process1* process,
    Arcadia_Status status
  );

/// @brief Fill a memory region with a specified value.
/// @param process A pointer to the Arcadia_Process1 object
/// @param p The starting address of the memory region
/// @param n The size, in Bytes, of the memory region
/// @param v The value to assign to the Bytes of the memory region
/// @remarks @a p can be a null pointer
/// @error Arcadia_Status_ArgumentValueInvalid p + n overflows
void
Arcadia_Process1_fillMemory
  (
    Arcadia_Process1* process,
    void* p,
    size_t n,
    uint8_t v
  );

/// @brief Copy the contents of a memory region to another memory region.
/// @param process A pointer to the Arcadia_Process1 object
/// @param p The starting address of the target memory region
/// @param q The starting address of the source memory region
/// @param n The size, in Bytes, of the memory regions
/// @remarks The memory regions may overlap.
/// @remarks @a p and/or q can be a null pointers
/// @error Arcadia_Status_ArgumentValueInvalid p + n overflows
/// @error Arcadia_Status_ArgumentValueInvalid q + n overflows
void
Arcadia_Process1_copyMemory
  (
    Arcadia_Process1* process,
    void* p,
    const void* q,
    size_t n
  );

/// @brief
/// Allocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process1 object
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
Arcadia_Process1_allocateUnmanaged
  (
    Arcadia_Process1* process,
    void** p,
    size_t n
  );

/// @brief
/// Deallocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process1 object
/// @param p
/// A pointer to a memory region of @a n Bytes.
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a p is a null pointer
void
Arcadia_Process1_deallocateUnmanaged
  (
    Arcadia_Process1* process,
    void* p
  );

/// @brief
/// Reallocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process1 object
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
Arcadia_Process1_reallocateUnmanaged
  (
    Arcadia_Process1* process,
    void** p,
    size_t n
  );

/// @param process A pointer to the Arcadia_Process1 object
void
Arcadia_Process1_visitObject
  (
    Arcadia_Process1* process,
    void* object
  );

/// @param process A pointer to the Arcadia_Process1 object
Arcadia_Status
Arcadia_Process1_lockObject
  (
    Arcadia_Process1* process,
    void* object
  );

/// @param process A pointer to the Arcadia_Process1 object
Arcadia_Status
Arcadia_Process1_unlockObject
  (
    Arcadia_Process1* process,
    void* object
  );

Arcadia_Status
Arcadia_Process1_stepArms
  (
    Arcadia_Process1* process
  );

Arcadia_Status
Arcadia_Process1_runArms
  (
    Arcadia_Process1* process
  );

void
Arcadia_Process1_registerType
  (
    Arcadia_Process1* process,
    const char* name,
    size_t nameLength,
    void* context,
    void (*typeRemoved)(void*, uint8_t const*, size_t),
    void (*visit)(void*, void*),
    void (*finalize)(void*, void*)
  );

/// @brief Allocate managed memory.
/// @param process A pointer to the process.
/// @param p A pointer to a <code>void*</code> variable.
/// @param name A pointer to an array of Bytes.
/// @param nameLength The number of Bytes in the array pointed to by @a name.
/// @param size The size, in Bytes, of the memory to allocate. @a 0 is a valid size.
/// @return @a true on success. @a false on failure.
/// On failure, this function sets the status variable of the process.
/// - Arcadia_Status_AllocationFailed if an allocation failed.
/// - Arcadia_Status_TypeNotExists if the type does not exist.
/// - Arcadia_Status_ArgumentInvalid if @a p or @a name is a null pointer.
bool
Arcadia_Process1_allocate_nojump
  (
    Arcadia_Process1* process,
    void** p,
    const char* name,
    size_t nameLength,
    size_t size
  );

void
Arcadia_Process1_allocate
  (
    Arcadia_Process1* process,
    void** p,
    const char* name,
    size_t nameLength,
    size_t size
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_PROCESS1_H_INCLUDED
