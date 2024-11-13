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
    (*f)();
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
  )
{
  R_Machine_Code* code = R_Machine_Code_create();
  R_Value* constants = NULL,
         * registers = NULL;

  if (!R_allocateUnmanaged_nojump(&constants, 0)) {
    R_jump();
  }
  if (!R_allocateUnmanaged_nojump(&registers, 0)) {
    R_deallocateUnmanaged_nojump(constants);
    constants = NULL;
    R_jump();
  }
  uint8_t codeBytes[] = {
    R_Machine_Code_Opcode_Idle,  
  };
  R_Machine_Code_append(code, codeBytes, 1);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_execute(constants, registers, code->p, code->sz);
    R_deallocateUnmanaged_nojump(registers);
    registers = NULL;
    R_deallocateUnmanaged_nojump(constants);
    constants = NULL;
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_deallocateUnmanaged_nojump(registers);
    registers = NULL;
    R_deallocateUnmanaged_nojump(constants);
    constants = NULL;
    R_jump();
  }
}

static void
execute2
  (
  )
{
  R_Machine_Code* code = R_Machine_Code_create();
  R_Value* constants = NULL,
         * registers = NULL;

  if (!R_allocateUnmanaged_nojump(&constants, sizeof(R_Value) * 2)) {
    R_jump();
  }
  R_Value_setInteger32Value(constants + 0, R_Integer32Value_Literal(5));
  R_Value_setInteger32Value(constants + 1, R_Integer32Value_Literal(7));
  if (!R_allocateUnmanaged_nojump(&registers, sizeof(R_Value) * 3)) {
    R_deallocateUnmanaged_nojump(constants);
    constants = NULL;
    R_jump();
  }
  uint8_t opcode = R_Machine_Code_Opcode_Add;
  R_Machine_Code_append(code, &opcode, 1);
  R_Machine_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Register, 2);
  R_Machine_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Constant, 0);
  R_Machine_Code_appendIndexNatural8(code, R_Machine_Code_IndexKind_Constant, 1);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_execute(constants, registers, code->p, code->sz);
    R_deallocateUnmanaged_nojump(registers);
    registers = NULL;
    R_deallocateUnmanaged_nojump(constants);
    constants = NULL;
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_deallocateUnmanaged_nojump(registers);
    registers = NULL;
    R_deallocateUnmanaged_nojump(constants);
    constants = NULL;
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
  return EXIT_SUCCESS;
}
