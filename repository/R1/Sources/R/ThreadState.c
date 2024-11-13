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

// Last modified: 2024-11-04

#include "R/ThreadState.private.h"

#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/UnmanagedMemory.h"
#include "R/Value.h"

#define R_Configuration_DefaultNumberOfArgumentRegisters 32
#define R_Configuration_DefaultNumberOfRegisters 256
#define R_Configuration_DefaultRegisterStackCapacity 256

R_ThreadState*
R_ThreadState_create
  (
    R_Procedure* procedure
  )
{
  R_ThreadState* threadState = NULL;
  if (!R_allocateUnmanaged_nojump(&threadState, sizeof(R_ThreadState))) {
    R_jump();
  }
  threadState->numberOfRegisters = R_Configuration_DefaultNumberOfRegisters;
  if (!R_allocateUnmanaged_nojump(&threadState->registers, sizeof(R_Value) * threadState->numberOfRegisters)) {
    R_deallocateUnmanaged_nojump(threadState);
    threadState = NULL;
    R_jump();
  }
  for (R_SizeValue i = 0, n = threadState->numberOfRegisters; i < n; ++i) {
    R_Value_setVoidValue(threadState->registers + i, R_VoidValue_Void);
  }

  if (!R_allocateUnmanaged_nojump(&threadState->calls.elements, sizeof(R_CallState))) {
    R_deallocateUnmanaged_nojump(threadState->registers);
    threadState->registers = NULL;
    R_deallocateUnmanaged_nojump(threadState);
    threadState = NULL;
    R_jump();
  }
  threadState->calls.size = 1;
  threadState->calls.capacity = 1;
  R_CallState* callState = &(threadState->calls.elements[threadState->calls.size - 1]);
  callState->flags = R_CallState_Flags_Procedure;
  callState->procedure = procedure;
  callState->instructionIndex = 0;
  callState->previous = NULL;

  return threadState;
}

void
R_ThreadState_destroy
  (
    R_ThreadState* threadState
  )
{
  R_deallocateUnmanaged_nojump(threadState->calls.elements);
  threadState->calls.elements = NULL;
  R_deallocateUnmanaged_nojump(threadState->registers);
  threadState->registers = NULL;
  R_deallocateUnmanaged_nojump(threadState);
  threadState = NULL;
}

void
R_ThreadState_visit
  (
    R_ThreadState* threadState
  )
{
  for (R_SizeValue i = 0, n = threadState->numberOfRegisters; i < n; ++i) {
    R_Value_visit(threadState->registers + i);
  }
  for (R_SizeValue i = 0, n = threadState->calls.size; i < n; ++i) {
    R_CallState* callState = &(threadState->calls.elements[i]);
    if (callState->flags == R_CallState_Flags_Procedure) {
      R_Object_visit(callState->procedure);
    }
  }
}

R_SizeValue
R_ThreadState_getNumberOfRegisters
  (
    R_ThreadState* threadState
  )
{ return threadState->numberOfRegisters; }

R_Value*
R_ThreadState_getRegisters
  (
    R_ThreadState* threadState
  )
{ return threadState->registers; }

R_Value*
R_ThreadState_getRegisterAt
  (
    R_ThreadState* threadState,
    R_SizeValue registerIndex
  )
{ return &(threadState->registers[registerIndex]); }

R_CallState*
R_ThreadState_beginForeignProcedureCall
  (
    R_ThreadState* threadState,
    R_Natural32Value instructionIndex,
    R_ForeignProcedureValue foreignProcedure
  )
{
  R_DynamicArrayUtilities_ensureFreeCapacity1(&threadState->calls.elements, sizeof(R_CallState), threadState->calls.size, &threadState->calls.capacity, 1);
  R_CallState* callState = &(threadState->calls.elements[threadState->calls.size]);
  callState->previous = &(threadState->calls.elements[threadState->calls.size - 1]);
  callState->instructionIndex = instructionIndex;
  callState->flags = R_CallState_Flags_ForeignProcedure;
  callState->foreignProcedure = foreignProcedure;
  threadState->calls.size++;
  return callState;
}

R_CallState*
R_ThreadState_beginProcedureCall
  (
    R_ThreadState* threadState,
    R_Natural32Value instructionIndex,
    R_Procedure* procedure
  )
{
  R_DynamicArrayUtilities_ensureFreeCapacity1(&threadState->calls.elements, sizeof(R_CallState), threadState->calls.size, &threadState->calls.capacity, 1);
  R_CallState* callState = &(threadState->calls.elements[threadState->calls.size]);
  callState->previous = &(threadState->calls.elements[threadState->calls.size - 1]);
  callState->instructionIndex = instructionIndex;
  callState->flags = R_CallState_Flags_Procedure;
  callState->procedure = procedure;
  threadState->calls.size++;
  return callState;
}

void
R_ThreadState_endCall
  (
    R_ThreadState* threadState
  )
{ 
  threadState->calls.size--;
}
