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

#include "R/Interpreter/ProcessState.private.h"

#include "R/ArmsIntegration.h"
#include "R/Interpreter/Code/Constants.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Interpreter/ThreadState.h"
#include "R/UnmanagedMemory.h"
#include "R/Interpreter/Procedure.h"

R_Interpreter_ProcessState*
R_Interpreter_ProcessState_create
  (
  )
{
  R_Interpreter_ProcessState* process = NULL;
  if (!R_allocateUnmanaged_nojump(&process, sizeof(R_Interpreter_ProcessState))) {
    R_jump();
  }
  R_JumpTarget jumpTarget;

  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    process->constants = R_Interpreter_Code_Constants_create();
    process->globals = R_Map_create();
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_deallocateUnmanaged_nojump(process);
    process = NULL;
    R_jump();
  }

  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    process->mainThread = R_Interpreter_ThreadState_create();
    process->currentThread = process->mainThread;
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_deallocateUnmanaged_nojump(process);
    process = NULL;
    R_jump();
  }

  return process;
}

void
R_Interpreter_ProcessState_destroy
  (
    R_Interpreter_ProcessState* process
  )
{
  process->currentThread = NULL;

  R_Interpreter_ThreadState_destroy(process->mainThread);
  process->mainThread = NULL;

  process->globals = NULL;
  process->constants = NULL;
  
  R_deallocateUnmanaged_nojump(process);
  process = NULL;
}

void
R_Interpreter_ProcessState_visit
  (
    R_Interpreter_ProcessState* processState
  )
{
  R_Object_visit(processState->globals);
  R_Object_visit(processState->constants);

  R_Interpreter_ThreadState_visit(processState->currentThread);
  R_Interpreter_ThreadState_visit(processState->mainThread);
}

void
R_Interpreter_ProcessState_defineGlobalProcedure
  (
    R_Interpreter_ProcessState* self,
    R_Interpreter_Procedure* procedure
  )
{ 
  if (!procedure) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = procedure->procedureName };
  R_Value value = R_Map_get(self->globals, key);
  if (!R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_Exists);
    R_jump();
  }
  value = (R_Value){ .tag = R_ValueTag_ObjectReference, .objectReferenceValue = procedure };
  R_Map_set(self->globals, key, value);
}

void
R_Interpreter_ProcessState_defineGlobalClass
  (
    R_Interpreter_ProcessState* self,
    R_Interpreter_Class* class
  )
{
  if (!class) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = class->className };
  R_Value value = R_Map_get(self->globals, key);
  if (!R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_Exists);
    R_jump();
  }
  value = (R_Value){ .tag = R_ValueTag_ObjectReference, .objectReferenceValue = class };
  R_Map_set(self->globals, key, value);
}

R_Value
R_Interpreter_ProcessState_getGlobal
  (
    R_Interpreter_ProcessState* self,
    R_String* name
  )
{ 
  if (!name) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = name };
  R_Value value = R_Map_get(self->globals, key);
  if (R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_NotExists);
    R_jump();
  }
  return value;
}

R_Interpreter_ThreadState*
R_Interpreter_ProcessState_getMainThread
  (
    R_Interpreter_ProcessState* self
  )
{ return self->mainThread; }

R_Interpreter_ThreadState*
R_Interpreter_ProcessState_getCurrentThread
  (
    R_Interpreter_ProcessState* self
  )
{ return self->currentThread; }

R_Interpreter_Code_Constants*
R_Interpreter_ProcessState_getConstants
  (
    R_Interpreter_ProcessState* self
  )
{ return self->constants; }
