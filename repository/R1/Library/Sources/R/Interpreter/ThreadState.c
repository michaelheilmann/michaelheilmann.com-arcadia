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

// Last modified: 2024-12-07

#include "R/Interpreter/ThreadState.private.h"

#include "R/ArmsIntegration.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/DynamicArrayUtilities.h"
#include "R/Value.h"

#define R_Configuration_DefaultNumberOfArgumentRegisters 32
#define R_Configuration_DefaultNumberOfRegisters 256
#define R_Configuration_DefaultRegisterStackCapacity 256

#if defined(R_ThreadState_withRegisterStack) && 1 == R_ThreadState_withRegisterStack

void
_RegisterStack_initialize
  (
    _RegisterStack* self
  )
{
  if (!R_allocateUnmanaged_nojump(&self->elements, 0 * sizeof(R_Value))) {
    R_jump();
  }
  self->size = 0;
  self->capacity = 0;
}

void
_RegisterStack_uninitialize
  (
    _RegisterStack* self
  )
{
  self->size = 0;
  R_deallocateUnmanaged_nojump(self->elements);
  self->capacity = 0;
}

#endif

R_Interpreter_ThreadState*
R_Interpreter_ThreadState_create
  (
  )
{
  R_Interpreter_ThreadState* thread = NULL;
  if (!R_allocateUnmanaged_nojump(&thread, sizeof(R_Interpreter_ThreadState))) {
    R_jump();
  }
  thread->numberOfRegisters = R_Configuration_DefaultNumberOfRegisters;
  if (!R_allocateUnmanaged_nojump(&thread->registers, sizeof(R_Value) * thread->numberOfRegisters)) {
    R_deallocateUnmanaged_nojump(thread);
    thread = NULL;
    R_jump();
  }
  for (R_SizeValue i = 0, n = thread->numberOfRegisters; i < n; ++i) {
    R_Value_setVoidValue(thread->registers + i, R_VoidValue_Void);
  }

  if (!R_allocateUnmanaged_nojump(&thread->calls.elements, sizeof(R_CallState))) {
    R_deallocateUnmanaged_nojump(thread->registers);
    thread->registers = NULL;
    R_deallocateUnmanaged_nojump(thread);
    thread = NULL;
    R_jump();
  }
  thread->calls.size = 0;
  thread->calls.capacity = 1;

  return thread;
}

void
R_Interpreter_ThreadState_destroy
  (
    R_Interpreter_ThreadState* thread
  )
{
  R_deallocateUnmanaged_nojump(thread->calls.elements);
  thread->calls.elements = NULL;
  R_deallocateUnmanaged_nojump(thread->registers);
  thread->registers = NULL;
  R_deallocateUnmanaged_nojump(thread);
  thread = NULL;
}

void
R_Interpreter_ThreadState_visit
  (
    R_Interpreter_ThreadState* thread
  )
{
  for (R_SizeValue i = 0, n = thread->numberOfRegisters; i < n; ++i) {
    R_Value_visit(thread->registers + i);
  }
  for (R_SizeValue i = 0, n = thread->calls.size; i < n; ++i) {
    R_CallState* callState = &(thread->calls.elements[i]);
    if (callState->flags == R_CallState_Flags_Procedure) {
      R_Object_visit(callState->procedure);
    }
  }
}

R_SizeValue
R_Interpreter_ThreadState_getNumberOfRegisters
  (
    R_Interpreter_ThreadState* thread
  )
{ return thread->numberOfRegisters; }

R_Value*
R_Interpreter_ThreadState_getRegisters
  (
    R_Interpreter_ThreadState* thread
  )
{ return thread->registers; }

R_Value*
R_Interpreter_ThreadState_getRegisterAt
  (
    R_Interpreter_ThreadState* thread,
    R_SizeValue registerIndex
  )
{ return &(thread->registers[registerIndex]); }

R_CallState*
R_Interpreter_ThreadState_beginForeignProcedureCall
  (
    R_Interpreter_ThreadState* thread,
    R_Natural32Value instructionIndex,
    R_ForeignProcedureValue foreignProcedure
  )
{
  R_DynamicArrayUtilities_ensureFreeCapacity(&thread->calls.elements, sizeof(R_CallState), thread->calls.size, &thread->calls.capacity, 1, R_DynamicArrayUtilities_GrowthStrategy1);
  R_CallState* callState = &(thread->calls.elements[thread->calls.size]);
  if (thread->calls.size) {
    callState->previous = &(thread->calls.elements[thread->calls.size - 1]);
  } else {
    callState->previous = NULL;
  }
  callState->instructionIndex = instructionIndex;
  callState->flags = R_CallState_Flags_ForeignProcedure;
  callState->foreignProcedure = foreignProcedure;
  thread->calls.size++;
  return callState;
}

R_CallState*
R_Interpreter_ThreadState_beginProcedureCall
  (
    R_Interpreter_ThreadState* thread,
    R_Natural32Value instructionIndex,
    R_Interpreter_Procedure* procedure
  )
{
  R_DynamicArrayUtilities_ensureFreeCapacity(&thread->calls.elements, sizeof(R_CallState), thread->calls.size, &thread->calls.capacity, 1, R_DynamicArrayUtilities_GrowthStrategy1);
  R_CallState* callState = &(thread->calls.elements[thread->calls.size]);
  if (thread->calls.size) {
    callState->previous = &(thread->calls.elements[thread->calls.size - 1]);
  } else {
    callState->previous = NULL;
  }
  callState->instructionIndex = instructionIndex;
  callState->flags = R_CallState_Flags_Procedure;
  callState->procedure = procedure;
  thread->calls.size++;
  return callState;
}

void
R_Interpreter_ThreadState_endCall
  (
    R_Interpreter_ThreadState* thread
  )
{ 
  thread->calls.size--;
}

R_CallState*
R_Interpreter_ThreadState_getCurrentCall
  (
    R_Interpreter_ThreadState* thread
  )
{
  if (!thread->calls.size) {
    return NULL;
  }
  return &(thread->calls.elements[thread->calls.size - 1]);
}
