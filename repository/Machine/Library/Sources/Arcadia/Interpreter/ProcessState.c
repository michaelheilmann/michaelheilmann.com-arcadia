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

#include "Arcadia/Interpreter/ProcessState.private.h"

#include "Arcadia/Include.h"
#include "Arcadia/Interpreter/Include.h"

static R_Interpreter_ProcessState* g_singleton = NULL;

R_Interpreter_ProcessState*
R_Interpreter_ProcessState_get
  (
  )
{ return g_singleton; }

void
R_Interpreter_ProcessState_startup
  (
    Arcadia_Process* process
  )
{
  if (g_singleton) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_Initialized);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  R_Interpreter_ProcessState* singleton = NULL;
  Arcadia_Process_allocateUnmanaged(process, &singleton, sizeof(R_Interpreter_ProcessState));
  Arcadia_JumpTarget jumpTarget;

  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    singleton->constants = R_Interpreter_Code_Constants_create(Arcadia_Process_getThread(process));
    singleton->globals = Arcadia_Map_create(Arcadia_Process_getThread(process));
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  } else {
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
    Arcadia_Process_deallocateUnmanaged(process, singleton);
    singleton = NULL;
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }

  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    singleton->mainThread = R_Interpreter_ThreadState_create(process);
    singleton->currentThread = singleton->mainThread;
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  } else {
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
    Arcadia_Process_deallocateUnmanaged(process, singleton);
    singleton = NULL;
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }

  g_singleton = singleton;
}

void
R_Interpreter_ProcessState_shutdown
  (
    Arcadia_Process* process
  )
{
  if (!g_singleton) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_NotInitialized);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  R_Interpreter_ProcessState* singleton = g_singleton;
  g_singleton = NULL;
  singleton->currentThread = NULL;

  R_Interpreter_ThreadState_destroy(process, singleton->mainThread);
  singleton->mainThread = NULL;

  singleton->globals = NULL;
  singleton->constants = NULL;

  Arcadia_Process_deallocateUnmanaged(process, singleton);
  singleton = NULL;
}

void
R_Interpreter_ProcessState_visit
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* processState
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_Object_visit(thread, (Arcadia_Object*)processState->globals);
  Arcadia_Object_visit(thread, (Arcadia_Object*)processState->constants);

  R_Interpreter_ThreadState_visit(process, processState->currentThread);
  R_Interpreter_ThreadState_visit(process, processState->mainThread);
}

void
R_Interpreter_ProcessState_defineGlobalProcedure
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* self,
    R_Interpreter_Procedure* procedure
  )
{
  if (!procedure) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  Arcadia_Value key = Arcadia_Value_makeObjectReferenceValue(procedure->unqualifiedName);
  Arcadia_Value value = Arcadia_Map_get(Arcadia_Process_getThread(process), self->globals, key);
  if (!Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_Exists);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  value = Arcadia_Value_makeObjectReferenceValue(procedure);
  Arcadia_Map_set(Arcadia_Process_getThread(process), self->globals, key, value);
}

void
R_Interpreter_ProcessState_defineGlobalClass
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* self,
    R_Interpreter_Class* class
  )
{
  if (!class) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  Arcadia_Value key = Arcadia_Value_makeObjectReferenceValue(class->className);
  Arcadia_Value value = Arcadia_Map_get(Arcadia_Process_getThread(process), self->globals, key);
  if (!Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_Exists);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  value = Arcadia_Value_makeObjectReferenceValue(class);
  Arcadia_Map_set(Arcadia_Process_getThread(process), self->globals, key, value);
}

Arcadia_Value
R_Interpreter_ProcessState_getGlobal
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* self,
    Arcadia_String* name
  )
{
  if (!name) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  Arcadia_Value key = Arcadia_Value_makeObjectReferenceValue(name);
  Arcadia_Value value = Arcadia_Map_get(Arcadia_Process_getThread(process), self->globals, key);
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_NotExists);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
