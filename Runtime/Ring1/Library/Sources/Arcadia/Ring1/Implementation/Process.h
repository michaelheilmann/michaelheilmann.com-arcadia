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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Annotations/NoReturn.h"

#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC
#include <stddef.h>
#endif

#include "Arcadia/Ring1/Implementation/Status.h"

#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <setjmp.h>
typedef struct Arcadia_JumpTarget Arcadia_JumpTarget; // Forward declaration.
typedef struct Arcadia_Thread Arcadia_Thread; // Forward declaration.

/// the process object provides access to the current thread.
/// the current thread provides access to the thread's jump target stack and the thread's status variable.
typedef struct Arcadia_Process Arcadia_Process;

typedef uint32_t Arcadia_ProcessStatus;
#define Arcadia_ProcessStatus_Success (0)
#define Arcadia_ProcessStatus_ArgumentValueInvalid (1)
#define Arcadia_ProcessStatus_AllocationFailed (2)
#define Arcadia_ProcessStatus_OperationInvalid (3)
#define Arcadia_ProcessStatus_EnvironmentFailed (4)

/// @brief Get the thread of this process.
/// @param process A pointer to this Arcadia_Process object.
/// @return A pointer to the Arcadia_Thread object of this Arcadia_Process object.
Arcadia_Thread*
Arcadia_Process_getThread
  (
    Arcadia_Process* process
  );

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

/// @brief Acquire an initial handle to the process object singleton.
/// @param [out] process A pointer to a <code>Arcadia_Process*</code> variable.
/// @post
/// If the call to this function was is successful:
/// - <code>*process</code> was assigned a pointer to the process object singleton.
/// - the caller acquired a reference to that object which he must relinquish by a call to Arcadia_Process_relinquish when no longer required.
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

typedef void (Arcadia_Process_PreMarkCallback)(Arcadia_Thread* thread, bool purgeCaches);
typedef void (Arcadia_Process_VisitCallback)(Arcadia_Thread* thread);
typedef void (Arcadia_Process_FinalizeCallback)(Arcadia_Thread* thread, size_t* destroyed);

/// @brief Add a premark callback to the list of premark callbacks.
/// @param process A pointer to the process.
/// @param callback A pointer to the premark callback.
void
Arcadia_Process_addArmsPreMarkCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_PreMarkCallback* callback
  );

/// @brief Remove a premark callback from the list of premark callbacks.
/// @param process A pointer to the process.
/// @param callback A pointer to the premark callback.
/// @remark One occurrence of the callback in the list of premark callbacks was removed.
void
Arcadia_Process_removeArmsPreMarkCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_PreMarkCallback* callback
  );

/// @brief Add a visit callback to the list of visit callbacks.
/// @param process A pointer to the process.
/// @param callback A pointer to the visit callback.
void
Arcadia_Process_addArmsVisitCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_VisitCallback* callback
  );

/// @brief Remove a visit callback from the list of visit callbacks.
/// @param process A pointer to the process.
/// @param callback A pointer to the visit callback.
/// @remark One occurrence of the callback in the list of visit callbacks was removed.
void
Arcadia_Process_removeArmsVisitCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_VisitCallback* callback
  );

/// @brief Add a finalize callback to the list of finalize callbacks.
/// @param process A pointer to the process.
/// @param callback A pointer to the finalize callback.
void
Arcadia_Process_addArmsFinalizeCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_FinalizeCallback* callback
  );

/// @brief Remove a finalize callback from the list of finalize callbacks.
/// @param process A pointer to the process.
/// @param callback A pointer to the finalize callback.
/// @remark One occurrence of the callback in the list of finalize callbacks was removed.
void
Arcadia_Process_removeArmsFinalizeCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_FinalizeCallback* callback
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
void
Arcadia_Process_allocate
  (
    Arcadia_Process* process,
    void** p,
    const char* name,
    size_t nameLength,
    size_t size
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED
