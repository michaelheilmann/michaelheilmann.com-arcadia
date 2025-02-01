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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Ring1/Implementation/Process1.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include "Arcadia/Ring1/Implementation/Atoms.private.h"
#include "Arcadia/Ring1/Implementation/Types.private.h"
#include "Arcadia/Ring1/Implementation/Diagnostics.h"
#include <malloc.h> /*TODO: Use ARMS*/

typedef uint32_t ReferenceCount;

#define ReferenceCount_Minimum (UINT32_C(0))
#define ReferenceCount_Maximum (UINT32_MAX)

Arcadia_StaticAssert(ReferenceCount_Minimum < ReferenceCount_Maximum, "environment not (yet) supported");

struct Arcadia_Process {
  ReferenceCount referenceCount;
  Arcadia_Process1* process1;
};

static void
startup
  (
    Arcadia_Process1* process
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process1_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Atoms_startup(process);
    Arcadia_Process1_popJumpTarget(process);
  } else {
    Arcadia_Process1_popJumpTarget(process);

    Arcadia_Process1_runArms(process);
    Arcadia_Process1_jump(process);
  }

  Arcadia_Process1_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Types_startup(process);
    Arcadia_Process1_popJumpTarget(process);
  } else {
    Arcadia_Process1_popJumpTarget(process);

    Arcadia_Atoms_onPreMark(process, Arcadia_BooleanValue_True);
    Arcadia_Process1_runArms(process);
    Arcadia_Atoms_onFinalize(process);
    Arcadia_Atoms_shutdown(process);

    Arcadia_Process1_runArms(process);
    Arcadia_Process1_jump(process);
  }
}

static void
shutdown
  (
    Arcadia_Process1* process
  )
{
  Arcadia_Types_onPreMark(process, Arcadia_BooleanValue_True);
  Arcadia_Atoms_onPreMark(process, Arcadia_BooleanValue_True);
  Arcadia_Process1_runArms(process);
  Arcadia_Types_onFinalize(process);
  Arcadia_Atoms_onFinalize(process);

  Arcadia_Types_shutdown(process);

  Arcadia_Atoms_onPreMark(process, Arcadia_BooleanValue_True);
  Arcadia_Process1_runArms(process);
  Arcadia_Atoms_onFinalize(process);

  Arcadia_Atoms_shutdown(process);

  Arcadia_Process1_runArms(process);
}

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
    shutdown(g_process->process1);
    Arcadia_Process1_relinquish(g_process->process1);
    g_process->process1 = NULL;
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
    g_process = malloc(sizeof(Arcadia_Process));
    if (!g_process) {
      return Arcadia_ProcessStatus_AllocationFailed;
    }
    g_process->referenceCount = ReferenceCount_Minimum + 1;
    if (Arcadia_Process1_get(&g_process->process1)) {
      free(g_process);
      g_process = NULL;
      return Arcadia_ProcessStatus_AllocationFailed;
    }
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Process1_pushJumpTarget(g_process->process1, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      startup(g_process->process1);
      Arcadia_Process1_popJumpTarget(g_process->process1);
    } else {
      Arcadia_Process1_popJumpTarget(g_process->process1);
      Arcadia_Process1_relinquish(g_process->process1);
      g_process->process1 = NULL;
      free(g_process);
      g_process = NULL;
      return Arcadia_ProcessStatus_AllocationFailed;
    }
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
    Arcadia_JumpTarget* jumpTarget
  )
{
  Arcadia_Process1_pushJumpTarget(process->process1, jumpTarget);
}

void
Arcadia_Process_popJumpTarget
  (
    Arcadia_Process* process
  )
{
  Arcadia_Process1_popJumpTarget(process->process1);
}

Arcadia_NoReturn() void
Arcadia_Process_jump
  (
    Arcadia_Process* process
  )
{
  Arcadia_Process1_jump(process->process1);
}

Arcadia_Status
Arcadia_Process_getStatus
  (
    Arcadia_Process* process
  )
{ return Arcadia_Process1_getStatus(process->process1); }

void
Arcadia_Process_setStatus
  (
    Arcadia_Process* process,
    Arcadia_Status status
  )
{ Arcadia_Process1_setStatus(process->process1, status); }

void
Arcadia_Process_allocateUnmanaged
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  )
{ Arcadia_Process1_allocateUnmanaged(process->process1, p, n); }

void
Arcadia_Process_deallocateUnmanaged
  (
    Arcadia_Process* process,
    void* p
  )
{ Arcadia_Process1_deallocateUnmanaged(process->process1, p); }

void
Arcadia_Process_reallocateUnmanaged
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  )
{ Arcadia_Process1_reallocateUnmanaged(process->process1, p, n); }

void
Arcadia_Process_visitObject
  (
    Arcadia_Process* process,
    void* object
  )
{ Arcadia_Process1_visitObject(process->process1, object); }

Arcadia_Status
Arcadia_Process_lockObject
  (
    Arcadia_Process* process,
    void* object
  )
{ return Arcadia_Process1_lockObject(process->process1, object); }

Arcadia_Status
Arcadia_Process_unlockObject
  (
    Arcadia_Process* process,
    void* object
  )
{ return Arcadia_Process1_unlockObject(process->process1, object); }

Arcadia_Status
Arcadia_Process_stepArms
  ( 
    Arcadia_Process* process
  )
{ return Arcadia_Process1_stepArms(process->process1); }

Arcadia_Status
Arcadia_Process_runArms
  (
    Arcadia_Process* process
  )
{ return Arcadia_Process1_runArms(process->process1); }

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
  )
{ Arcadia_Process1_registerType(process->process1, name, nameLength, context, typeRemoved, visit, finalize); }

void
Arcadia_Process_allocate
  (
    Arcadia_Process* process,
    void** p,
    const char* name,
    size_t nameLength,
    size_t size
  )
{ Arcadia_Process1_allocate(process->process1, p, name, nameLength, size); }

Arcadia_Process1*
Arcadia_Process_getBackendNoLock
  (
    Arcadia_Process* process
  )
{ return process->process1; }
