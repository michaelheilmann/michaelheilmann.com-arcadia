#include "R/execute.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Machine/Code/Include.h"
#include "R/ThreadState.h"

static void
execute
  (
    R_Value const* constants,
    R_ThreadState* threadState,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_InterpreterStateArgument interpreterState;
  interpreterState.constants = constants;
  interpreterState.registers = R_ThreadState_getRegisters(threadState);
  interpreterState.ipStart = ((uint8_t const*)bytes) + 0;
  interpreterState.ipEnd = ((uint8_t const*)bytes) + numberOfBytes;
  interpreterState.ipCurrent = ((uint8_t const*)bytes) + 0;
  while (interpreterState.ipCurrent != interpreterState.ipEnd) {
    switch (*interpreterState.ipCurrent) {
      case R_Machine_Code_Opcode_Idle: {
        R_Instructions_idle(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Add: {
        R_Instructions_add(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_And: {
        R_Instructions_and(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Concatenate: {
        R_Instructions_concatenate(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Divide: {
        R_Instructions_divide(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Subtract: {
        R_Instructions_subtract(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Multiply: {
        R_Instructions_multiply(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Negate: {
        R_Instructions_negate(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Not: {
        R_Instructions_not(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Or: {
        R_Instructions_or(&interpreterState);
      } break;
      case R_Machine_Code_Opcode_Return: {
        // Not yet implemented.
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
      default: {
        // Borked code. This should never happen.
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
    };
  }
}

void
R_execute
  (
    R_Value const* constants,
    R_Value* registers,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_ThreadState* threadState = R_ThreadState_create();
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    execute(constants, threadState, bytes, numberOfBytes);
    R_popJumpTarget();
    R_ThreadState_destroy(threadState);
    threadState = NULL;
  } else {
    R_popJumpTarget();
    R_ThreadState_destroy(threadState);
    threadState = NULL;
    R_jump();
  }
}
