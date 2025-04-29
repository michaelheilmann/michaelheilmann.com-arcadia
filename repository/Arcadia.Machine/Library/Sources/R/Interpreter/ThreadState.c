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

// Last modified: 2024-12-07

#include "R/Interpreter/ThreadState.private.h"

#include "Arcadia/Ring1/Include.h"

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
  if (!R_allocateUnmanaged_nojump(&self->elements, 0 * sizeof(Arcadia_Value))) {
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
    Arcadia_Process* process
  )
{
  R_Interpreter_ThreadState* thread = NULL;
  Arcadia_Process_allocateUnmanaged(process, &thread, sizeof(R_Interpreter_ThreadState));
  thread->numberOfRegisters = R_Configuration_DefaultNumberOfRegisters;

  Arcadia_JumpTarget jumpTarget;

  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Process_allocateUnmanaged(process, &thread->registers, sizeof(Arcadia_Value) * thread->numberOfRegisters);
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  } else {
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
    Arcadia_Process_deallocateUnmanaged(process, thread);
    thread = NULL;
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }

  for (Arcadia_SizeValue i = 0, n = thread->numberOfRegisters; i < n; ++i) {
    Arcadia_Value_setVoidValue(thread->registers + i, Arcadia_VoidValue_Void);
  }

  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Process_allocateUnmanaged(process, &thread->calls.elements, sizeof(R_CallState));
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  } else {
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
    Arcadia_Process_deallocateUnmanaged(process, thread->registers);
    thread->registers = NULL;
    Arcadia_Process_deallocateUnmanaged(process, thread);
    thread = NULL;
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }

  thread->calls.size = 0;
  thread->calls.capacity = 1;

  return thread;
}

void
R_Interpreter_ThreadState_destroy
  (
    Arcadia_Process* process,
    R_Interpreter_ThreadState* thread
  )
{
  Arcadia_Process_deallocateUnmanaged(process, thread->calls.elements);
  thread->calls.elements = NULL;
  Arcadia_Process_deallocateUnmanaged(process, thread->registers);
  thread->registers = NULL;
  Arcadia_Process_deallocateUnmanaged(process, thread);
  thread = NULL;
}

void
R_Interpreter_ThreadState_visit
  (
    Arcadia_Process* process,
    R_Interpreter_ThreadState* thread
  )
{
  for (Arcadia_SizeValue i = 0, n = thread->numberOfRegisters; i < n; ++i) {
    Arcadia_Value_visit(Arcadia_Process_getThread(process), thread->registers + i);
  }
  for (Arcadia_SizeValue i = 0, n = thread->calls.size; i < n; ++i) {
    R_CallState* callState = &(thread->calls.elements[i]);
    if (callState->flags == R_CallState_Flags_Procedure) {
      Arcadia_Object_visit(Arcadia_Process_getThread(process), callState->procedure);
    }
  }
}

Arcadia_SizeValue
R_Interpreter_ThreadState_getNumberOfRegisters
  (
    R_Interpreter_ThreadState* thread
  )
{ return thread->numberOfRegisters; }

Arcadia_Value*
R_Interpreter_ThreadState_getRegisterAt
  (
    R_Interpreter_ThreadState* thread,
    Arcadia_SizeValue registerIndex
  )
{ return &(thread->registers[registerIndex]); }

R_CallState*
R_Interpreter_ThreadState_beginForeignProcedureCall
  (
    Arcadia_Process* process,
    R_Interpreter_ThreadState* thread,
    Arcadia_Natural32Value instructionIndex,
    Arcadia_ForeignProcedureValue foreignProcedure
  )
{
  Arcadia_Arrays_resizeByFreeCapacity(Arcadia_Process_getThread(process), Arms_getDefaultMemoryManager(), &thread->calls.elements, sizeof(R_CallState), thread->calls.size, &thread->calls.capacity, 1, Arcadia_Arrays_ResizeStrategy_Type1);
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
    Arcadia_Process* process,
    R_Interpreter_ThreadState* thread,
    Arcadia_Natural32Value instructionIndex,
    R_Interpreter_Procedure* procedure
  )
{
  Arcadia_Arrays_resizeByFreeCapacity(Arcadia_Process_getThread(process), Arms_getDefaultMemoryManager(), &thread->calls.elements, sizeof(R_CallState), thread->calls.size, &thread->calls.capacity, 1, Arcadia_Arrays_ResizeStrategy_Type1);
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
