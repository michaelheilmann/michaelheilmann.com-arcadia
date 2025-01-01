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

// Last modified: 2025-01-01

#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdio.h>
#include <malloc.h>
#include "Arms.h"

static Arcadia_Status
startupArms
  (
  );

static Arcadia_Status
shutdownArms
  (
  );

static Arcadia_Status
startupArms
  (
  )
{
  Arms_Status status = Arms_startup();
  switch (status) {
    case Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is Arcadia_Status_EnvironmentInvalid.
      return Arcadia_Status_OperationInvalid;
    } break;
  };
}

static Arcadia_Status
shutdownArms
  (
  )
{
  Arms_Status status = Arms_shutdown();
  switch (status) {
    case Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is Arcadia_Status_EnvironmentInvalid.
      return Arcadia_Status_OperationInvalid;
    } break;
  };
}


typedef uint32_t ReferenceCount;

#define ReferenceCount_Minimum (UINT32_C(0))
#define ReferenceCount_Maximum (UINT32_MAX)

Arcadia_StaticAssert(ReferenceCount_Minimum < ReferenceCount_Maximum, "environment not (yet) supported");

struct Arcadia_Process {
  ReferenceCount referenceCount;
  Arcadia_Status status;
  R_JumpTarget* jumpTarget;
};

static Arcadia_Process* g_process = NULL;

Arcadia_ProcessStatus
Arcadia_Process_acquire
  (
    Arcadia_Process* process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (ReferenceCount_Minimum == process->referenceCount || ReferenceCount_Maximum == process->referenceCount) {
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  process->referenceCount++;
  return Arcadia_ProcessStatus_Success;
}

Arcadia_ProcessStatus
Arcadia_Process_relinquish
  (
    Arcadia_Process* process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (ReferenceCount_Minimum == process->referenceCount || !g_process) {
    /* This is, actually, undefined behavior. */
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  if (ReferenceCount_Minimum == --process->referenceCount) {
    if (Arms_shutdown()) {
      fprintf(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
    }
    free(g_process);
    g_process = NULL;
  }
  return Arcadia_ProcessStatus_Success;
}

Arcadia_ProcessStatus
Arcadia_Process_get
  (
    Arcadia_Process** process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (!g_process) {
    if (Arms_startup()) {
      return Arcadia_ProcessStatus_EnvironmentFailed;
    }
    g_process = malloc(sizeof(Arcadia_Process));
    if (!g_process) {
      if (Arms_shutdown()) {
        fprintf(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
      }
      return Arcadia_ProcessStatus_AllocationFailed;
    }
    g_process->referenceCount = ReferenceCount_Minimum + 1;
    g_process->status = Arcadia_Status_Success;
    g_process->jumpTarget = NULL;
    *process = g_process;
    return Arcadia_ProcessStatus_Success;
  }
  if (ReferenceCount_Maximum == g_process->referenceCount) {
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  g_process->referenceCount++;
  *process = g_process;
  return Arcadia_ProcessStatus_Success;
}

void
Arcadia_Process_pushJumpTarget
  (
    Arcadia_Process* process,
    R_JumpTarget* jumpTarget
  )
{
  jumpTarget->previous = process->jumpTarget;
  process->jumpTarget = jumpTarget;
}

void
Arcadia_Process_popJumpTarget
  (
    Arcadia_Process* process
  )
{
  process->jumpTarget = process->jumpTarget->previous;
}

Arcadia_NoReturn() void
Arcadia_Process_jump
  (
    Arcadia_Process* process
  )
{ 
  longjmp(process->jumpTarget->environment, -1);
}

Arcadia_Status
Arcadia_Process_getStatus
  (
    Arcadia_Process* process
  )
{ return process->status; }

void
Arcadia_Process_setStatus
  (
    Arcadia_Process* process,
    Arcadia_Status status
  )
{
  process->status = status;
}
