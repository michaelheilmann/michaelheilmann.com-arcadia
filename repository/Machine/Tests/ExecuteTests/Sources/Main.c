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

#include <stdlib.h>
#include <stdio.h> // @todo Remove references to `stdio.h`.

#include "Arcadia/Include.h"

static void
execute1
  (
    Arcadia_Thread* thread
  )
{
  R_Interpreter_ProcessState_startup(Arcadia_Thread_getProcess(thread));
  R_Interpreter_ProcessState* interpreterProcess = R_Interpreter_ProcessState_get();
  R_Interpreter_Code* code = R_Interpreter_Code_create(thread);
  uint8_t codeBytes[] = {
    R_Machine_Code_Opcode_Idle,
  };
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_append(thread, code, codeBytes, 1);
    R_executeProcedure(Arcadia_Thread_getProcess(thread), interpreterProcess, R_Interpreter_Procedure_create(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"main", sizeof(u8"main") - 1)), code));
    R_Interpreter_ProcessState_shutdown(Arcadia_Thread_getProcess(thread));
    interpreterProcess = NULL;
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    R_Interpreter_ProcessState_shutdown(Arcadia_Thread_getProcess(thread));
    interpreterProcess = NULL;
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

static void
execute2
  (
    Arcadia_Thread* thread
  )
{
  R_Interpreter_ProcessState_startup(Arcadia_Thread_getProcess(thread));
  R_Interpreter_ProcessState* interpreterProcess = R_Interpreter_ProcessState_get();
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
    R_Interpreter_Code* code = R_Interpreter_Code_create(thread);
    if (0 != R_Interpreter_Code_Constants_getOrCreateInteger32(thread, constants, Arcadia_Integer32Value_Literal(5))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    }
    if (1 != R_Interpreter_Code_Constants_getOrCreateInteger32(thread, constants, Arcadia_Integer32Value_Literal(7))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    }
    uint8_t opcode = R_Machine_Code_Opcode_Add;
    R_Interpreter_Code_append(thread, code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural8(thread, code, R_Machine_Code_IndexKind_Register, 2);
    R_Interpreter_Code_appendIndexNatural8(thread, code, R_Machine_Code_IndexKind_Constant, 0);
    R_Interpreter_Code_appendIndexNatural8(thread, code, R_Machine_Code_IndexKind_Constant, 1);
    R_executeProcedure(Arcadia_Thread_getProcess(thread), interpreterProcess, R_Interpreter_Procedure_create(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"main", sizeof(u8"main") - 1)), code));
    R_Interpreter_ProcessState_shutdown(Arcadia_Thread_getProcess(thread));
    interpreterProcess = NULL;
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    R_Interpreter_ProcessState_shutdown(Arcadia_Thread_getProcess(thread));
    interpreterProcess = NULL;
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

static void
print
  (
    Arcadia_Thread* thread
  )
{
  fprintf(stdout, "Hello, World!\n");
  Arcadia_Natural8Value numberOfArguments = Arcadia_ValueStack_getNatural8Value(thread, 0);
  Arcadia_ValueStack_popValues(thread, (Arcadia_SizeValue)numberOfArguments + 1);
}

static void
execute3
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  R_Interpreter_ProcessState_startup(process);
  R_Interpreter_ProcessState* interpreterProcess = R_Interpreter_ProcessState_get();
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
    R_Interpreter_Code* code = R_Interpreter_Code_create(thread);
    if (0 != R_Interpreter_Code_Constants_getOrCreateForeignProcedure(thread, constants, &print)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    }
    if (1 != R_Interpreter_Code_Constants_getOrCreateString(Arcadia_Process_getThread(process), constants, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"Hello, World!\n", sizeof(u8"Hello, World!\n"))))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    }
    uint8_t opcode = R_Machine_Code_Opcode_Invoke;
    R_Interpreter_Code_append(thread, code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural8(thread, code, R_Machine_Code_IndexKind_Register, 0); // target
    R_Interpreter_Code_appendIndexNatural8(thread, code, R_Machine_Code_IndexKind_Constant, 0); // calleee
    R_Interpreter_Code_appendCountNatural8(thread, code, 1); // number of arguments
    R_Interpreter_Code_appendIndexNatural8(thread, code, R_Machine_Code_IndexKind_Constant, 1); // argument #1
    R_executeProcedure(process, interpreterProcess, R_Interpreter_Procedure_create(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"main", sizeof(u8"main") - 1)), code));
    R_Interpreter_ProcessState_shutdown(process);
    interpreterProcess = NULL;
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    R_Interpreter_ProcessState_shutdown(process);
    interpreterProcess = NULL;
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&execute1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&execute2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&execute3)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
