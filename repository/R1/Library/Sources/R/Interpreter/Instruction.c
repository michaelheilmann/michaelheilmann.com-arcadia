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

// Last modified: 2024-10-28

#include "R/Interpreter/Instruction.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Include.h"
#include "R/Interpreter/Include.h"
#include <assert.h>

static Arcadia_Value*
R_InterpreterState_decodeTarget
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(thread, code, &call->instructionIndex, &indexKind, &indexValue);
  if (R_Machine_Code_IndexKind_Register != indexKind) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  return R_Interpreter_ThreadState_getRegisterAt(interpreterThread, indexValue);
}

static Arcadia_Value const*
R_InterpreterState_decodeOperand
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(thread, code, &call->instructionIndex, &indexKind, &indexValue);
  Arcadia_Value const* value = indexKind == R_Machine_Code_IndexKind_Constant ?
                               R_Interpreter_Code_Constants_getAt(Arcadia_Process_getThread(process), constants, indexValue) : R_Interpreter_ThreadState_getRegisterAt(interpreterThread, indexValue);
  return value;
}

static Arcadia_String*
R_InterpreterState_decodeStringConstant
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(thread, code, &call->instructionIndex, &indexKind, &indexValue);
  if (R_Machine_Code_IndexKind_Constant != indexKind) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Type_isSubType(thread, Arcadia_Value_getType(thread, R_Interpreter_Code_Constants_getAt(thread, constants, indexValue)), _Arcadia_String_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(R_Interpreter_Code_Constants_getAt(thread, constants, indexValue));
}

static Arcadia_Natural32Value
R_InterpreterState_decodeCount
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  R_Interpreter_Code* code = call->procedure->code;

  Arcadia_Natural32Value countValue;
  R_Interpreter_Code_decodeCount(thread, code, &call->instructionIndex, &countValue);
  return countValue;
}

#if defined(_DEBUG) 
  #define OnAssertOpcode(Name) \
    R_Interpreter_Code* code = call->procedure->code; \
    assert(R_Machine_Code_Opcode_##Name == (*code->p + call->instructionIndex));
#else
  #define OnAssertOpcode(Name)
#endif

void
R_Instructions_add
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(Add);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->add) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->add(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_and
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(And);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->and) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->and(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_concatenate
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(Concatenate);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->concatenate) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->concatenate(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_divide
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(Divide);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->divide) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->divide(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_isEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(IsEqualTo);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->equalTo) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->equalTo(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_isGreaterThan
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(IsGreaterThan);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->greaterThan) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->greaterThan(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_isGreaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(IsGreaterThanOrEqualTo);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->greaterThanOrEqualTo) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->greaterThanOrEqualTo(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_idle
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(Idle);

  call->instructionIndex++;
}

void
R_Instructions_isLowerThan
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(IsLowerThan);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->lowerThan) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->lowerThan(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_isLowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(IsLowerThanOrEqualTo);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->lowerThanOrEqualTo) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->lowerThanOrEqualTo(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_multiply
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(Multiply);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->multiply) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] ={ *firstOperandValue, *secondOperandValue };
  operations->multiply(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_negate
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Negate == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* operandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue operandType = Arcadia_Value_getType(thread, operandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(operandType);
  if (!operations->negate) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  Arcadia_Value args[1] = { *operandValue };
  operations->negate(thread, targetValue, 1, &args[0]);
}

void
R_Instructions_not
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Not == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* operandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue operandType = Arcadia_Value_getType(thread, operandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(operandType);
  if (!operations->not) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[1] = { *operandValue };
  operations->not(thread, targetValue, 1, &args[0]);
}

void
R_Instructions_isNotEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(IsNotEqualTo);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->notEqualTo) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->notEqualTo(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_or
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(Or);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations-> or ) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->or(thread, targetValue, 2, &args[0]);
}

void
R_Instructions_subtract
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  R_Interpreter_ThreadState* interpreterThread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(interpreterThread);
  OnAssertOpcode(Subtract);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(thread, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->subtract) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->subtract(thread, targetValue, 2, &args[0]);
}
