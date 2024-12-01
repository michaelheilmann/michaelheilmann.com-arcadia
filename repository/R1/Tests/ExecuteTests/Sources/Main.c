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

// Last modified: 2024-08-27

#include <stdlib.h>

#include "R.h"

static R_BooleanValue
safeExecute
  (
    R_ForeignProcedureValue f
  )
{
  bool result = true;
  R_Status status = R_startup();
  if (status) {
    result = false;
    return result;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_Value targetValue;
    R_Value argumentValues[1];
    (*f)(&targetValue, 0, &argumentValues[0]);
  } else {
    result = false;
  }
  R_popJumpTarget();
  status = R_shutdown();
  if (status) {
    result = false;
  }
  return result;
}

static void
execute1
  (
    R_Value* targetValue,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Interpreter_ProcessState* process = R_Interpreter_ProcessState_create();
  R_Interpreter_Code* code = R_Interpreter_Code_create();
  uint8_t codeBytes[] = {
    R_Machine_Code_Opcode_Idle,  
  };
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_append(code, codeBytes, 1);
    R_executeProcedure(process, R_Procedure_create(code));
    R_Interpreter_ProcessState_destroy(process);
    process = NULL;
    R_popJumpTarget();
  } else {
    R_Interpreter_ProcessState_destroy(process);
    process = NULL;
    R_popJumpTarget();
    R_jump();
  }
}

static void
execute2
  (
    R_Value* targetValue,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Interpreter_ProcessState* process = R_Interpreter_ProcessState_create();
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(process);
    R_Interpreter_Code* code = R_Interpreter_Code_create();
    if (0 != R_Interpreter_Code_Constants_getOrCreateInteger32(constants, R_Integer32Value_Literal(5))) {
      R_setStatus(R_Status_TestFailed);
      R_jump();
    }
    if (1 != R_Interpreter_Code_Constants_getOrCreateInteger32(constants, R_Integer32Value_Literal(7))) {
      R_setStatus(R_Status_TestFailed);
      R_jump();
    }
    uint8_t opcode = R_Machine_Code_Opcode_Add;
    R_Interpreter_Code_append(code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Register, 2);
    R_Interpreter_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Constant, 0);
    R_Interpreter_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Constant, 1);
    R_executeProcedure(process, R_Procedure_create(code));
    R_Interpreter_ProcessState_destroy(process);
    process = NULL;
    R_popJumpTarget();
  } else {
    R_Interpreter_ProcessState_destroy(process);
    process = NULL;
    R_popJumpTarget();
    R_jump();
  }
}

static void
print
  (
    R_Value* targetValue,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  fprintf(stdout, "Hello, World!\n");
}

static void
execute3
  (
    R_Value* targetValue,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Interpreter_ProcessState* process = R_Interpreter_ProcessState_create();
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(process);
    R_Interpreter_Code* code = R_Interpreter_Code_create();
    if (0 != R_Interpreter_Code_Constants_getOrCreateForeignProcedure(constants, &print)) {
      R_setStatus(R_Status_TestFailed);
      R_jump();
    }
    if (1 != R_Interpreter_Code_Constants_getOrCreateString(constants, R_String_create_pn(R_ImmutableByteArray_create("Hello, World!\n", sizeof("Hello, World!\n"))))) {
      R_setStatus(R_Status_TestFailed);
      R_jump();
    }
    uint8_t opcode = R_Machine_Code_Opcode_Invoke;
    R_Interpreter_Code_append(code, &opcode, 1);
    R_Interpreter_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Register, 0); // target
    R_Interpreter_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Constant, 0); // calleee
    R_Interpreter_Code_appendCountNatural8(code, 1); // number of arguments
    R_Interpreter_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Constant, 1); // argument #1
    R_executeProcedure(process, R_Procedure_create(code));
    R_Interpreter_ProcessState_destroy(process);
    process = NULL;
    R_popJumpTarget();
  } else {
    R_Interpreter_ProcessState_destroy(process);
    process = NULL;
    R_popJumpTarget();
    R_jump();
  }
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!safeExecute(&execute1)) {
    return EXIT_FAILURE;
  }
  if (!safeExecute(&execute2)) {
    return EXIT_FAILURE;
  }
  if (!safeExecute(&execute3)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
