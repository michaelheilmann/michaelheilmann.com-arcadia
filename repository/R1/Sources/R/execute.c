#include "R/execute.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Procedure.h"
#include "R/Interpreter/Include.h"
#include "R/Interpreter/ThreadState.private.h" // TODO: Remove this.
#include "R/Interpreter/Code.h"
#include "R/cstdlib.h"

static void
execute1
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(process);
  R_CallState* currentCallState = NULL;
  while (true) {
    R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
    currentCallState = R_Interpreter_ThreadState_getCurrentCall(thread);
  
    if (currentCallState->instructionIndex == currentCallState->procedure->code->sz) {
      thread->calls.size--;
      if (currentCallState->previous) {
        currentCallState = currentCallState->previous;
      } else {
        return;
      }
    }
    switch (*(currentCallState->procedure->code->p + currentCallState->instructionIndex)) {
      case R_Machine_Code_Opcode_Idle: {
        R_Instructions_idle(process);
      } break;
      case R_Machine_Code_Opcode_Add: {
        R_Instructions_add(process);
      } break;
      case R_Machine_Code_Opcode_And: {
        R_Instructions_and(process);
      } break;
      case R_Machine_Code_Opcode_Concatenate: {
        R_Instructions_concatenate(process);
      } break;
      case R_Machine_Code_Opcode_Divide: {
        R_Instructions_divide(process);
      } break;
      case R_Machine_Code_Opcode_Subtract: {
        R_Instructions_subtract(process);
      } break;
      case R_Machine_Code_Opcode_Multiply: {
        R_Instructions_multiply(process);
      } break;
      case R_Machine_Code_Opcode_Negate: {
        R_Instructions_negate(process);
      } break;
      case R_Machine_Code_Opcode_Not: {
        R_Instructions_not(process);
      } break;
      case R_Machine_Code_Opcode_Or: {
        R_Instructions_or(process);
      } break;
      case R_Machine_Code_Opcode_Return: {
        // Not yet implemented.
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
      case R_Machine_Code_Opcode_Invoke: {
        assert(R_Machine_Code_Opcode_Invoke == *(currentCallState->procedure->code->p + currentCallState->instructionIndex));
        currentCallState->instructionIndex++;
        // target index
        R_Machine_Code_IndexKind targetIndexKind;
        R_Natural32Value targetIndex;
        R_Value* targetValue = NULL;
        R_Interpreter_Code_decodeIndex(currentCallState->procedure->code, &currentCallState->instructionIndex, &targetIndexKind, &targetIndex);
        if (targetIndexKind == R_Machine_Code_IndexKind_Constant) {
          R_setStatus(R_Status_NumberOfArgumentsInvalid);
          R_jump();
        } else {
          targetValue = R_Interpreter_ThreadState_getRegisterAt(thread, targetIndex);
        }
        // callee
        R_Machine_Code_IndexKind calleeIndexKind;
        R_Natural32Value calleeIndex;
        R_Value calleeValue;
        R_Interpreter_Code_decodeIndex(currentCallState->procedure->code, &currentCallState->instructionIndex, &calleeIndexKind, &calleeIndex);
        if (calleeIndexKind == R_Machine_Code_IndexKind_Constant) {
          calleeValue = *R_Interpreter_Code_Constants_getAt(constants, calleeIndex);
        } else {
          calleeValue = *R_Interpreter_ThreadState_getRegisterAt(thread, calleeIndex);
        }
        // number of arguments
        R_Natural32Value count;
        R_Interpreter_Code_decodeCount(currentCallState->procedure->code, &currentCallState->instructionIndex, &count);
        if (count > R_Machine_Code_NumberOfArguments_Maximum) {
          R_setStatus(R_Status_NumberOfArgumentsInvalid);
          R_jump();
        }
        R_Value argumentValues[R_Machine_Code_NumberOfArguments_Maximum];
        for (R_Natural32Value i = 0, n = count; i < n; ++i) {
          R_Machine_Code_IndexKind argumentIndexKind;
          R_Natural32Value argumentIndex;
          R_Interpreter_Code_decodeIndex(currentCallState->procedure->code, &currentCallState->instructionIndex, &argumentIndexKind, &argumentIndex);
          if (argumentIndexKind == R_Machine_Code_IndexKind_Constant) {
            argumentValues[i] = *R_Interpreter_Code_Constants_getAt(constants, argumentIndex);
          } else {
            argumentValues[i] = *R_Interpreter_ThreadState_getRegisterAt(thread, argumentIndex);
          }
        }
        if (R_Value_isForeignProcedureValue(&calleeValue)) {
          R_ForeignProcedureValue foreignProcedureValue = R_Value_getForeignProcedureValue(&calleeValue);
          R_Interpreter_ThreadState_beginForeignProcedureCall(thread, 0, foreignProcedureValue);
          R_JumpTarget jumpTarget;
          R_pushJumpTarget(&jumpTarget);
          if (R_JumpTarget_save(&jumpTarget)) {
            (*foreignProcedureValue)(targetValue, count, &(argumentValues[0]));
            R_popJumpTarget();
            R_Interpreter_ThreadState_endCall(thread); // Must not fail.
          } else {
            R_popJumpTarget();
            R_Interpreter_ThreadState_endCall(thread); // Must not fail.
            R_jump();
          }
        } else if (R_Value_isObjectReferenceValue(&calleeValue)) {
          R_Object* object = R_Value_getObjectReferenceValue(&calleeValue);
          if (R_Type_isSubType(R_Object_getType(object), _R_Procedure_getType())) {
            R_Interpreter_ThreadState_beginProcedureCall(thread, 0, (R_Procedure*)object);
          } else {
            R_setStatus(R_Status_ArgumentTypeInvalid);
            R_jump();
          }
        } else {
          R_setStatus(R_Status_ArgumentTypeInvalid);
          R_jump();
        }
      } break;
      default: {
        // Borked code. This should never happen.
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
    };
  }
}

static void
execute
  (
    R_Interpreter_ProcessState* process
  )
{ execute1(process); }

void
R_executeProcedure
  (
    R_Interpreter_ProcessState* process,
    R_Procedure* procedure
  )
{
  R_Interpreter_ThreadState_beginProcedureCall(R_Interpreter_ProcessState_getMainThread(process), 0, procedure);
  execute(process);
}
