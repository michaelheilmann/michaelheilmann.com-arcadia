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
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(process, code, &call->instructionIndex, &indexKind, &indexValue);
  if (R_Machine_Code_IndexKind_Register != indexKind) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  return R_Interpreter_ThreadState_getRegisterAt(thread, indexValue);
}

static Arcadia_Value const*
R_InterpreterState_decodeOperand
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(process, code, &call->instructionIndex, &indexKind, &indexValue);
  Arcadia_Value const* value = indexKind == R_Machine_Code_IndexKind_Constant ?
                         R_Interpreter_Code_Constants_getAt(process, constants, indexValue) : R_Interpreter_ThreadState_getRegisterAt(thread, indexValue);
  return value;
}

static Arcadia_String*
R_InterpreterState_decodeStringConstant
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(process, code, &call->instructionIndex, &indexKind, &indexValue);
  if (R_Machine_Code_IndexKind_Constant != indexKind) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, R_Interpreter_Code_Constants_getAt(process, constants, indexValue)), _Arcadia_String_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  return (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(R_Interpreter_Code_Constants_getAt(process, constants, indexValue));
}

static Arcadia_Natural32Value
R_InterpreterState_decodeCount
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  Arcadia_Natural32Value countValue;
  R_Interpreter_Code_decodeCount(process, code, &call->instructionIndex, &countValue);
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
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(Add);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->add) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->add(process, targetValue, 2, &args[0]);
}

void
R_Instructions_and
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(And);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->and) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->and(process, targetValue, 2, &args[0]);
}

void
R_Instructions_concatenate
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(Concatenate);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->concatenate) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->concatenate(process, targetValue, 2, &args[0]);
}

void
R_Instructions_divide
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(Divide);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->divide) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->divide(process, targetValue, 2, &args[0]);
}

void
R_Instructions_isEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(IsEqualTo);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->equalTo) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->equalTo(process, targetValue, 2, &args[0]);
}

void
R_Instructions_isGreaterThan
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(IsGreaterThan);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->greaterThan) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->greaterThan(process, targetValue, 2, &args[0]);
}

void
R_Instructions_isGreaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(IsGreaterThanOrEqualTo);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->greaterThanOrEqualTo) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->greaterThanOrEqualTo(process, targetValue, 2, &args[0]);
}

void
R_Instructions_idle
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(Idle);

  call->instructionIndex++;
}

void
R_Instructions_islowerThan
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(IsLowerThan);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->lowerThan) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->lowerThan(process, targetValue, 2, &args[0]);
}

void
R_Instructions_isLowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(IsLowerThanOrEqualTo);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->lowerThanOrEqualTo) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->lowerThanOrEqualTo(process, targetValue, 2, &args[0]);
}

void
R_Instructions_multiply
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(Multiply);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->multiply) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] ={ *firstOperandValue, *secondOperandValue };
  operations->multiply(process, targetValue, 2, &args[0]);
}

void
R_Instructions_negate
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Negate == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* operandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue operandType = Arcadia_Value_getType(process, operandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(operandType);
  if (!operations->negate) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[1] = { *operandValue };
  operations->negate(process, targetValue, 1, &args[0]);
}

void
R_Instructions_not
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Not == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* operandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue operandType = Arcadia_Value_getType(process, operandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(operandType);
  if (!operations->not) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[1] = { *operandValue };
  operations->not(process, targetValue, 1, &args[0]);
}

void
R_Instructions_notEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(IsNotEqualTo);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->notEqualTo) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->notEqualTo(process, targetValue, 2, &args[0]);
}

void
R_Instructions_or
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(Or);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations-> or ) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->or(process, targetValue, 2, &args[0]);
}

void
R_Instructions_subtract
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  OnAssertOpcode(Subtract);

  call->instructionIndex++;

  Arcadia_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  Arcadia_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  Arcadia_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = Arcadia_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->subtract) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value args[2] = { *firstOperandValue, *secondOperandValue };
  operations->subtract(process, targetValue, 2, &args[0]);
}
