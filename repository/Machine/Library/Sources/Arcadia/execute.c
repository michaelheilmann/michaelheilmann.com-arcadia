#include "Arcadia/execute.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Interpreter/Procedure.h"
#include "Arcadia/Interpreter/Include.h"
#include "Arcadia/Interpreter/ThreadState.private.h" // TODO: Remove this.
#include "Arcadia/Interpreter/Code.h"
#include <assert.h>

static void
execute1
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcessState
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcessState);
  R_CallState* currentCallState = NULL;
  while (true) {
    R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcessState);
    currentCallState = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);

    if (currentCallState->instructionIndex == currentCallState->procedure->code->sz) {
      interpreterThread->calls.size--;
      if (currentCallState->previous) {
        currentCallState = currentCallState->previous;
      } else {
        return;
      }
    }
    switch (*(currentCallState->procedure->code->p + currentCallState->instructionIndex)) {
      case R_Machine_Code_Opcode_Idle: {
        R_Instructions_idle(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Add: {
        R_Instructions_add(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_And: {
        R_Instructions_and(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Concatenate: {
        R_Instructions_concatenate(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Divide: {
        R_Instructions_divide(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Subtract: {
        R_Instructions_subtract(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Multiply: {
        R_Instructions_multiply(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Negate: {
        R_Instructions_negate(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Not: {
        R_Instructions_not(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Or: {
        R_Instructions_or(process, interpreterProcessState);
      } break;
      case R_Machine_Code_Opcode_Return: {
        // Not yet implemented.
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
      case R_Machine_Code_Opcode_Invoke: {
        assert(R_Machine_Code_Opcode_Invoke == *(currentCallState->procedure->code->p + currentCallState->instructionIndex));
        currentCallState->instructionIndex++;
        // target index
        R_Machine_Code_IndexKind targetIndexKind;
        Arcadia_Natural32Value targetIndex;
        Arcadia_Value* targetValue = NULL;
        R_Interpreter_Code_decodeIndex(thread, currentCallState->procedure->code, &currentCallState->instructionIndex, &targetIndexKind, &targetIndex);
        if (targetIndexKind == R_Machine_Code_IndexKind_Constant) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
          Arcadia_Thread_jump(thread);
        } else {
          targetValue = R_Interpreter_ThreadState_getRegisterAt(interpreterThread, targetIndex);
        }
        // callee
        R_Machine_Code_IndexKind calleeIndexKind;
        Arcadia_Natural32Value calleeIndex;
        Arcadia_Value calleeValue;
        R_Interpreter_Code_decodeIndex(thread, currentCallState->procedure->code, &currentCallState->instructionIndex, &calleeIndexKind, &calleeIndex);
        if (calleeIndexKind == R_Machine_Code_IndexKind_Constant) {
          calleeValue = *R_Interpreter_Code_Constants_getAt(Arcadia_Process_getThread(process), constants, calleeIndex);
        } else {
          calleeValue = *R_Interpreter_ThreadState_getRegisterAt(interpreterThread, calleeIndex);
        }
        Arcadia_SizeValue oldStackSize = Arcadia_ValueStack_getSize(thread);
        // number of arguments
        Arcadia_Natural32Value count;
        R_Interpreter_Code_decodeCount(thread, currentCallState->procedure->code, &currentCallState->instructionIndex, &count);
        if (count > R_Machine_Code_NumberOfArguments_Maximum) {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
          Arcadia_Thread_jump(thread);
        }
        for (Arcadia_Natural32Value i = 0, n = count; i < n; ++i) {
          R_Machine_Code_IndexKind argumentIndexKind;
          Arcadia_Natural32Value argumentIndex;
          R_Interpreter_Code_decodeIndex(thread, currentCallState->procedure->code, &currentCallState->instructionIndex, &argumentIndexKind, &argumentIndex);
          if (argumentIndexKind == R_Machine_Code_IndexKind_Constant) {
            Arcadia_ValueStack_pushValue(thread, R_Interpreter_Code_Constants_getAt(Arcadia_Process_getThread(process), constants, argumentIndex));
          } else {
            Arcadia_ValueStack_pushValue(thread, R_Interpreter_ThreadState_getRegisterAt(interpreterThread, argumentIndex));
          }
        }
        Arcadia_ValueStack_pushNatural8Value(thread, count);
        if (Arcadia_Value_isForeignProcedureValue(&calleeValue)) {
          Arcadia_ForeignProcedureValue foreignProcedureValue = Arcadia_Value_getForeignProcedureValue(&calleeValue);
          R_Interpreter_ThreadState_beginForeignProcedureCall(process, interpreterThread, 0, foreignProcedureValue);
          Arcadia_JumpTarget jumpTarget;
          Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
          if (Arcadia_JumpTarget_save(&jumpTarget)) {
            (*foreignProcedureValue)(thread);
            if (oldStackSize > Arcadia_ValueStack_getSize(thread)) {
              Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
              Arcadia_Thread_jump(thread);
            }
            Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
            R_Interpreter_ThreadState_endCall(interpreterThread); // Must not fail.
          } else {
            Arcadia_Thread_popJumpTarget(thread);
            R_Interpreter_ThreadState_endCall(interpreterThread); // Must not fail.
            Arcadia_Thread_jump(thread);
          }
        } else if (Arcadia_Value_isObjectReferenceValue(&calleeValue)) {
          Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&calleeValue);
          if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, object), _R_Interpreter_Procedure_getType(thread))) {
            R_Interpreter_ThreadState_beginProcedureCall(process, interpreterThread, 0, (R_Interpreter_Procedure*)object);
          } else {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
            Arcadia_Thread_jump(thread);
          }
        } else {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
          Arcadia_Thread_jump(thread);
        }
      } break;
      default: {
        // Borked code. This should never happen.
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
  }
}

static void
execute
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{ execute1(process, interpreterProcess); }

void
R_executeProcedure
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess,
    R_Interpreter_Procedure* procedure
  )
{
  R_Interpreter_ThreadState_beginProcedureCall(process, R_Interpreter_ProcessState_getMainThread(interpreterProcess), 0, procedure);
  execute(process, interpreterProcess);
}
