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
#include "R/Value.h"

#include "R/Interpreter/Include.h"
#include "R/cstdlib.h"
#include "R/Interpreter/Procedure.h"
#include "R/String.h"

static R_Value*
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

static R_Value const*
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
  R_Value const* value = indexKind == R_Machine_Code_IndexKind_Constant ?
                         R_Interpreter_Code_Constants_getAt(process, constants, indexValue) : R_Interpreter_ThreadState_getRegisterAt(thread, indexValue);
  return value;
}

static R_String*
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
  if (!Arcadia_Type_isSubType(R_Value_getType(process, R_Interpreter_Code_Constants_getAt(process, constants, indexValue)), _R_String_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  return (R_String*)R_Value_getObjectReferenceValue(R_Interpreter_Code_Constants_getAt(process, constants, indexValue));
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

void
R_Instructions_add
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Add == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->add) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->add(process, targetValue, firstOperandValue, secondOperandValue);
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
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_And == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->and) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->and(process, targetValue, firstOperandValue, secondOperandValue);
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
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Concatenate == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->concatenate) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->concatenate(process, targetValue, firstOperandValue, secondOperandValue);
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
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Divide == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->divide) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->divide(process, targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_equalTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_EqualTo == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->equalTo) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->equalTo(process, targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_greaterThan
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_GreaterThan == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->greaterThan) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->greaterThan(process, targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_GreaterThanOrEqualTo == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->greaterThanOrEqualTo) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->greaterThanOrEqualTo(process, targetValue, firstOperandValue, secondOperandValue);
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
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Idle == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;
}

void
R_Instructions_lowerThan
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_LowerThan == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->lowerThan) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->lowerThan(process, targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_LowerThanOrEqualTo == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->lowerThanOrEqualTo) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->lowerThanOrEqualTo(process, targetValue, firstOperandValue, secondOperandValue);
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
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Multiply == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->multiply) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->multiply(process, targetValue, firstOperandValue, secondOperandValue);
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

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* operandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue operandType = R_Value_getType(process, operandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(operandType);
  if (!operations->negate) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->negate(process, targetValue, operandValue);
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

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* operandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue operandType = R_Value_getType(process, operandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(operandType);
  if (!operations->not) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->not(process, targetValue, operandValue);
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
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_NotEqualTo == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->notEqualTo) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->notEqualTo(process, targetValue, firstOperandValue, secondOperandValue);
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
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Or == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations-> or ) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->or(process, targetValue, firstOperandValue, secondOperandValue);
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
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Subtract == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process, interpreterProcess);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process, interpreterProcess);

  Arcadia_TypeValue firstOperandType = R_Value_getType(process, firstOperandValue);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(firstOperandType);
  if (!operations->subtract) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  operations->subtract(process, targetValue, firstOperandValue, secondOperandValue);
}
