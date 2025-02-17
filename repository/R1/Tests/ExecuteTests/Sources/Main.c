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

// Last modified: 2024-08-27

#include <stdlib.h>

#include "R/Include.h"

static void
execute1
  (
    Arcadia_Process* process
  )
{
  R_Interpreter_ProcessState_startup(process);
  R_Interpreter_ProcessState* interpreterProcess = R_Interpreter_ProcessState_get();
  R_Interpreter_Code* code = R_Interpreter_Code_create(process);
  uint8_t codeBytes[] = {
    R_Machine_Code_Opcode_Idle,  
  };
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_append(process, code, codeBytes, 1);
    R_executeProcedure(process, interpreterProcess, R_Interpreter_Procedure_create(process, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"main", sizeof(u8"main") - 1)), code));
    R_Interpreter_ProcessState_shutdown(process);
    interpreterProcess = NULL;
    Arcadia_Process_popJumpTarget(process);
  } else {
    R_Interpreter_ProcessState_shutdown(process);
    interpreterProcess = NULL;
    Arcadia_Process_popJumpTarget(process);
    Arcadia_Process_jump(process);
  }
}

static void
execute2
  (
    Arcadia_Process* process
  )
{
  R_Interpreter_ProcessState_startup(process);
  R_Interpreter_ProcessState* interpreterProcess = R_Interpreter_ProcessState_get();
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
    R_Interpreter_Code* code = R_Interpreter_Code_create(process);
    if (0 != R_Interpreter_Code_Constants_getOrCreateInteger32(process, constants, Arcadia_Integer32Value_Literal(5))) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
    if (1 != R_Interpreter_Code_Constants_getOrCreateInteger32(process, constants, Arcadia_Integer32Value_Literal(7))) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
    uint8_t opcode = R_Machine_Code_Opcode_Add;
    R_Interpreter_Code_append(process, code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural8(process, code, R_Machine_Code_IndexKind_Register, 2);
    R_Interpreter_Code_appendIndexNatural8(process, code, R_Machine_Code_IndexKind_Constant, 0);
    R_Interpreter_Code_appendIndexNatural8(process, code, R_Machine_Code_IndexKind_Constant, 1);
    R_executeProcedure(process, interpreterProcess, R_Interpreter_Procedure_create(process, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"main", sizeof(u8"main") - 1)), code));
    R_Interpreter_ProcessState_shutdown(process);
    interpreterProcess = NULL;
    Arcadia_Process_popJumpTarget(process);
  } else {
    R_Interpreter_ProcessState_shutdown(process);
    interpreterProcess = NULL;
    Arcadia_Process_popJumpTarget(process);
    Arcadia_Process_jump(process);
  }
}

static void
print
  (
    Arcadia_Process* process,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  fprintf(stdout, "Hello, World!\n");
}

static void
execute3
  (
    Arcadia_Process* process
  )
{
  R_Interpreter_ProcessState_startup(process);
  R_Interpreter_ProcessState* interpreterProcess = R_Interpreter_ProcessState_get();
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
    R_Interpreter_Code* code = R_Interpreter_Code_create(process);
    if (0 != R_Interpreter_Code_Constants_getOrCreateForeignProcedure(process, constants, &print)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
    if (1 != R_Interpreter_Code_Constants_getOrCreateString(process, constants, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"Hello, World!\n", sizeof(u8"Hello, World!\n"))))) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
    uint8_t opcode = R_Machine_Code_Opcode_Invoke;
    R_Interpreter_Code_append(process, code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural8(process, code, R_Machine_Code_IndexKind_Register, 0); // target
    R_Interpreter_Code_appendIndexNatural8(process, code, R_Machine_Code_IndexKind_Constant, 0); // calleee
    R_Interpreter_Code_appendCountNatural8(process, code, 1); // number of arguments
    R_Interpreter_Code_appendIndexNatural8(process, code, R_Machine_Code_IndexKind_Constant, 1); // argument #1
    R_executeProcedure(process, interpreterProcess, R_Interpreter_Procedure_create(process, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"main", sizeof(u8"main") - 1)), code));
    R_Interpreter_ProcessState_shutdown(process);
    interpreterProcess = NULL;
    Arcadia_Process_popJumpTarget(process);
  } else {
    R_Interpreter_ProcessState_shutdown(process);
    interpreterProcess = NULL;
    Arcadia_Process_popJumpTarget(process);
    Arcadia_Process_jump(process);
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
