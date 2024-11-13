#include "R/execute.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Procedure.h"
#include "R/Machine/Code/Include.h"
#include "R/ThreadState.h"
#include "R/ThreadState.private.h"
#include <assert.h>

static void
execute1
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  R_CallState* currentCallState = NULL;
  while (true) {
    currentCallState = &(interpreterState->threadState->calls.elements[interpreterState->threadState->calls.size-1]);
    interpreterState->ipCurrent = interpreterState->code->p + currentCallState->instructionIndex;
  
    if (interpreterState->ipCurrent == interpreterState->code->p + interpreterState->code->sz) {
      interpreterState->threadState->calls.size--;
      if (currentCallState->previous) {
        currentCallState = currentCallState->previous;
        interpreterState->ipCurrent = currentCallState->procedure->code->p + currentCallState->instructionIndex; 
      } else {
        return;
      }
    }
    switch (*interpreterState->ipCurrent) {
      case R_Machine_Code_Opcode_Idle: {
        R_Instructions_idle(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Add: {
        R_Instructions_add(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_And: {
        R_Instructions_and(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Concatenate: {
        R_Instructions_concatenate(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Divide: {
        R_Instructions_divide(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Subtract: {
        R_Instructions_subtract(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Multiply: {
        R_Instructions_multiply(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Negate: {
        R_Instructions_negate(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Not: {
        R_Instructions_not(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Or: {
        R_Instructions_or(interpreterState);
        currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
      } break;
      case R_Machine_Code_Opcode_Return: {
        // Not yet implemented.
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
      case R_Machine_Code_Opcode_Invoke: {
        assert(R_Machine_Code_Opcode_Invoke == *interpreterState->ipCurrent);
        interpreterState->ipCurrent++;
        // target index
        R_Machine_Code_IndexKind targetIndexKind;
        R_Natural32Value targetIndex;
        R_Value* targetValue = NULL;
        R_Machine_Code_decodeIndex(interpreterState->code, &interpreterState->ipCurrent, &targetIndexKind, &targetIndex);
        if (targetIndexKind == R_Machine_Code_IndexKind_Constant) {
          R_setStatus(R_Status_NumberOfArgumentsInvalid);
          R_jump();
        } else {
          targetValue = R_ThreadState_getRegisterAt(interpreterState->threadState, targetIndex);
        }
        // callee
        R_Machine_Code_IndexKind calleeIndexKind;
        R_Natural32Value calleeIndex;
        R_Value calleeValue;
        R_Machine_Code_decodeIndex(interpreterState->code, &interpreterState->ipCurrent, &calleeIndexKind, &calleeIndex);
        if (calleeIndexKind == R_Machine_Code_IndexKind_Constant) {
          calleeValue = interpreterState->constants[calleeIndex];
        } else {
          calleeValue = *R_ThreadState_getRegisterAt(interpreterState->threadState, calleeIndex);
        }
        // number of arguments
        R_Natural32Value count;
        R_Machine_Code_decodeCount(interpreterState->code, &interpreterState->ipCurrent, &count);
        if (count > R_Machine_Code_NumberOfArguments_Maximum) {
          R_setStatus(R_Status_NumberOfArgumentsInvalid);
          R_jump();
        }
        R_Value argumentValues[R_Machine_Code_NumberOfArguments_Maximum];
        for (R_Natural32Value i = 0, n = count; i < n; ++i) {
          R_Machine_Code_IndexKind argumentIndexKind;
          R_Natural32Value argumentIndex;
          R_Machine_Code_decodeIndex(interpreterState->code, &interpreterState->ipCurrent, &argumentIndexKind, &argumentIndex);
          if (argumentIndexKind == R_Machine_Code_IndexKind_Constant) {
            argumentValues[i] = interpreterState->constants[argumentIndex];
          } else {
            argumentValues[i] = *R_ThreadState_getRegisterAt(interpreterState->threadState, argumentIndex);
          }
        }
        if (R_Value_isForeignProcedureValue(&calleeValue)) {
          currentCallState->instructionIndex = interpreterState->ipCurrent - currentCallState->procedure->code->p;
          R_ForeignProcedureValue foreignProcedureValue = R_Value_getForeignProcedureValue(&calleeValue);
          R_CallState* callState = R_ThreadState_beginForeignProcedureCall(interpreterState->threadState, interpreterState->ipCurrent - interpreterState->code->p, foreignProcedureValue);
          R_JumpTarget jumpTarget;
          R_pushJumpTarget(&jumpTarget);
          if (R_JumpTarget_save(&jumpTarget)) {
            (*foreignProcedureValue)(targetValue, count, &(argumentValues[0]));
            R_popJumpTarget();
            R_ThreadState_endCall(interpreterState->threadState); // Must not fail.
          } else {
            R_popJumpTarget();
            R_ThreadState_endCall(interpreterState->threadState); // Must not fail.
            R_jump();
          }
        } else if (R_Value_isObjectReferenceValue(&calleeValue)) {
          R_Object* object = R_Value_getObjectReferenceValue(&calleeValue);
          if (R_Type_isSubType(R_Object_getType(object), _R_Procedure_getType())) {
            R_ThreadState_beginProcedureCall(interpreterState->threadState, interpreterState->ipCurrent - interpreterState->code->p, (R_Procedure*)object);
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
    R_Value const* constants,
    R_ThreadState* threadState
  )
{
  R_InterpreterStateArgument interpreterState;
  interpreterState.constants = constants;
  interpreterState.threadState = threadState;
  interpreterState.code = threadState->calls.elements[0].procedure->code;
  interpreterState.ipCurrent = ((uint8_t const*)interpreterState.code->p) + 0;
  execute1(&interpreterState);
}

void
R_executeProcedure
  (
    R_Value const* constants,
    R_Procedure* procedure
  )
{
  R_ThreadState* threadState = R_ThreadState_create(procedure);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    execute(constants, threadState);
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
