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

// Last modified: 2024-08-27

#if !defined(ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/NoReturn.h"

#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC
#include <stddef.h>
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Value.h"

#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <setjmp.h>

typedef struct Arcadia_JumpTarget Arcadia_JumpTarget;

/// the thread object provides access to a thread.
typedef struct Arcadia_Thread Arcadia_Thread;

/// the process object provides access to the current thread.
/// the current thread provides access to the thread's jump target stack and the thread's status variable.
typedef struct Arcadia_Process Arcadia_Process;

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
#define Arcadia_Status_NotImplemented (22)

typedef uint32_t Arcadia_Status;

typedef uint32_t Arcadia_ProcessStatus;
#define Arcadia_ProcessStatus_Success (0)
#define Arcadia_ProcessStatus_ArgumentValueInvalid (1)
#define Arcadia_ProcessStatus_AllocationFailed (2)
#define Arcadia_ProcessStatus_OperationInvalid (3)
#define Arcadia_ProcessStatus_EnvironmentFailed (4)

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
Arcadia_SizeValue
Arcadia_Thread_getValueStackSize
  (
    Arcadia_Thread* thread
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
/// @error Arcadia_Status_ArgumentValueInvalid @a value is a null pointer
/// @error Arcadia_Status_AllocationFailed an allocation failed
void
Arcadia_Thread_pushValue
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
/// @error Arcadia_Status_ArgumentValueInvalid @a coutn is greater than the size of the stack
void
Arcadia_Thread_popValues
  (
    Arcadia_Thread* thread,
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

/// @brief Get the status variable value of this thread
/// @param thread A pointer to this Arcadia_Thread object
/// @return the status value
/// @undefined @a thread does not refer to a Arcadia_Thread object
/// @undefined Invoked without having the exclusive lock to the thread
Arcadia_Status
Arcadia_Thread_getStatus
  (
    Arcadia_Thread* thread
  );

/// @brief Set the status variable value of this thread
/// @param thread A pointer to this Arcadia_Thread object
/// @param status the status value
/// @undefined @a thread does not refer to a Arcadia_Thread object
/// @undefined Invoked without having the exclusive lock to the thread
void
Arcadia_Thread_setStatus
  (
    Arcadia_Thread* thread,
    Arcadia_Status status
  );

/// @brief Get the process of this thread
/// @param thread A pointer to this Arcadia_Thread object
/// @retur A pointer to the process of this thread
/// @undefined @a thread does not refer to a Arcadia_Thread object
/// @undefined Invoked without having the exclusive lock to the thread
Arcadia_Process*
Arcadia_Thread_getProcess
  (
    Arcadia_Thread* thread
  );

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

/// @brief Fill a memory region with a specified value.
/// @param process A pointer to the Arcadia_Process object
/// @param p The starting address of the memory region
/// @param n The size, in Bytes, of the memory region
/// @param v The value to assign to the Bytes of the memory region
/// @remarks @a p can be a null pointer
/// @error Arcadia_Status_ArgumentValueInvalid p + n overflows
void
Arcadia_Process_fillMemory
  (
    Arcadia_Process* process,
    void* p,
    size_t n,
    uint8_t v
  );

/// @brief Copy the contents of a memory region to another memory region.
/// @param process A pointer to the Arcadia_Process object
/// @param p The starting address of the target memory region
/// @param q The starting address of the source memory region
/// @param n The size, in Bytes, of the memory regions
/// @remarks The memory regions may overlap.
/// @remarks @a p and/or q can be a null pointers
/// @error Arcadia_Status_ArgumentValueInvalid p + n overflows
/// @error Arcadia_Status_ArgumentValueInvalid q + n overflows
void
Arcadia_Process_copyMemory
  (
    Arcadia_Process* process,
    void* p,
    const void* q,
    size_t n
  );

int
Arcadia_Process_compareMemory
  (
    Arcadia_Process* process,
    const void *p,
    const void* q, 
    size_t n
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

typedef void (Arcadia_Process_PreMarkCallback)(Arcadia_Thread* thread, bool purgeCaches);
typedef void (Arcadia_Process_VisitCallback)(Arcadia_Thread* thread);
typedef void (Arcadia_Process_FinalizeCallback)(Arcadia_Thread* thread, size_t* destroyed);

void
Arcadia_Process_addArmsPreMarkCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_PreMarkCallback* callback
  );

void
Arcadia_Process_removeArmsPreMarkCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_PreMarkCallback* callback
  );

void
Arcadia_Process_addArmsVisitCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_VisitCallback* callback
  );

void
Arcadia_Process_removeArmsVisitCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_VisitCallback* callback
  );

void
Arcadia_Process_addArmsFinalizeCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_FinalizeCallback* callback
  );

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

/// @brief Get the time, in milliseconds, since some undef

typedef struct ModuleInfo {
  /// @brief Pointer to the name of the module. The name is a static constant C string.
  const char* name;
  /// @brief Visit the module.
  /// @warning Internal function.
  Arcadia_Process_VisitCallback* onVisit;
  /// @brief Startup the module.
  /// @warning Internal function.
  void (*onStartUp)(Arcadia_Thread* thread);
  /// @brief Shutdown the module.
  /// @warning Internal function.
  void (*onShutDown)(Arcadia_Thread* thread);
  /// @brief Must be invoked in the pre mark phase.
  /// @warning Internal function.
  Arcadia_Process_PreMarkCallback* onPreMark;
  /// @brief Must be invoked in the finalize phase.
  /// @warning Internal function.
  Arcadia_Process_FinalizeCallback* onFinalize;
} ModuleInfo;

#define Arcadia_DeclareModule(Name, cName) \
  const ModuleInfo* \
  cName##_getModule \
    ( \
    );

#define Arcadia_DefineModule(Name, cName) \
  static void \
  _##cName##_onStartUp \
    ( \
      Arcadia_Thread* thread \
    ); \
\
  static void \
  _##cName##_onShutDown \
    ( \
      Arcadia_Thread* thread \
    ); \
\
  static void \
  _##cName##_onPreMark \
    ( \
      Arcadia_Thread* thread, \
      bool purgeCache \
    ); \
\
  static void \
  _##cName##_onFinalize \
    ( \
      Arcadia_Thread* thread, \
      size_t* destroyed \
    ); \
\
  static void \
  _##cName##_onVisit \
    ( \
      Arcadia_Thread* thread \
    ); \
\
  static const ModuleInfo _##cName##_moduleInfo = { \
    .name = Name, \
    .onVisit = &_##cName##_onVisit, \
    .onStartUp = &_##cName##_onStartUp, \
    .onShutDown = &_##cName##_onShutDown, \
    .onPreMark = &_##cName##_onPreMark, \
    .onFinalize = &_##cName##_onFinalize, \
  }; \
\
  const ModuleInfo* \
  cName##_getModule \
    ( \
    ) \
  { return &_##cName##_moduleInfo; }

#endif // ARCADIA_RING1_IMPLEMENTATION_PROCESS1_H_INCLUDED
