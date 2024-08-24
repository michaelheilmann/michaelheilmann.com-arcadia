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

// Last modified: 2024-08-22

#if !defined(ARCADIA_ARMS_H_INCLUDED)
#define ARCADIA_ARMS_H_INCLUDED

#define Arms_Compiler_Msvc (1)
#define Arms_Compiler_Gcc (2)
#define Arms_Compiler_Clang (3)

// Define this to one of the Arms_Compiler_* constants.
#define Arms_Compiler Arms_Compiler_Msvc

// Define to 0 or undefine to disable locks.
// Note that without locks, ARMS1 will consider any object as dead when invoking Arms_run() which restricts the usage scenarios.
#define Arms_WithLocks (1)

// size_t
#include <stddef.h>

typedef enum Arms_Status {
  Arms_Status_Success = 0,
  Arms_Status_ArgumentValueInvalid = 1,
  Arms_Status_AllocationFailed = 2,
  Arms_Status_TypeExists = 3,
  Arms_Status_TypeNotExists = 4,
  Arms_Status_OperationInvalid = 5,
} Arms_Status;

typedef void (Arms_VisitCallbackFunction)(void*);

typedef void (Arms_FinalizeCallbackFunction)(void*);

Arms_Status
Arms_startup
  (
  );

Arms_Status
Arms_shutdown
  (
  );

Arms_Status
Arms_registerType
  (
    char const* name,
    size_t nameLength,
    Arms_VisitCallbackFunction* visit,
    Arms_FinalizeCallbackFunction* finalize
  );

Arms_Status
Arms_allocate
  (
    void** pObject,
    char const* name,
    size_t nameLength,
    size_t size
  );

Arms_Status
Arms_run
  (
  );

void
Arms_visit
  (
    void* object
  );
  
#if defined(Arms_WithLocks) && 1 == Arms_WithLocks

Arms_Status
Arms_lock
  (
    void* object
  );

Arms_Status
Arms_unlock
  (
    void* object
  );

#endif

Arms_Status
Arms_allocateUnmanaged
  (
    void** p,
    size_t n
  );

Arms_Status
Arms_reallocateUnmanaged
  (
    void** p,
    size_t n
  );

Arms_Status
Arms_deallocateUnmanaged
  (
    void* p
  );

#endif // ARCADIA_ARMS_H_INCLUDED
