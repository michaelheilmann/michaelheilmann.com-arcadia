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

// Last modified: 2024-10-28

#include "R/Interpreter/Instruction.h"

#include "R/Interpreter/Include.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/cstdlib.h"
#include "R/Interpreter/Procedure.h"
#include "R/String.h"

static R_Value*
R_InterpreterState_decodeTarget
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  R_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(code, &call->instructionIndex, &indexKind, &indexValue);
  if (R_Machine_Code_IndexKind_Register != indexKind) {
    R_setStatus(R_Status_SemanticalError);
    R_jump();
  }
  return R_Interpreter_ThreadState_getRegisterAt(thread, indexValue);
}

static R_Value const*
R_InterpreterState_decodeOperand
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(process);
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  R_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(code, &call->instructionIndex, &indexKind, &indexValue);
  R_Value const* value = indexKind == R_Machine_Code_IndexKind_Constant ?
                         R_Interpreter_Code_Constants_getAt(constants, indexValue) : R_Interpreter_ThreadState_getRegisterAt(thread, indexValue);
  return value;
}

static R_String*
R_InterpreterState_decodeStringConstant
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(process);
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  R_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(code, &call->instructionIndex, &indexKind, &indexValue);
  if (R_Machine_Code_IndexKind_Constant != indexKind) {
    R_setStatus(R_Status_SemanticalError);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(R_Interpreter_Code_Constants_getAt(constants, indexValue)), _R_String_getType())) {
    R_setStatus(R_Status_SemanticalError);
    R_jump();
  }
  return (R_String*)R_Value_getObjectReferenceValue(R_Interpreter_Code_Constants_getAt(constants, indexValue));
}

static R_Natural32Value
R_InterpreterState_decodeCount
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Natural32Value countValue;
  R_Interpreter_Code_decodeCount(code, &call->instructionIndex, &countValue);
  return countValue;
}

void
R_Instructions_add
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Add == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->add) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->add(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_and
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_And == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->and) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->and(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_concatenate
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Concatenate == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->concatenate) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->concatenate(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_divide
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Divide == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->divide) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->divide(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_equalTo
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_EqualTo == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->equalTo) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->equalTo(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_greaterThan
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_GreaterThan == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->greaterThan) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->greaterThan(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_greaterThanOrEqualTo
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_GreaterThanOrEqualTo == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->greaterThanOrEqualTo) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->greaterThanOrEqualTo(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_idle
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
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
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_LowerThan == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->lowerThan) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->lowerThan(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_lowerThanOrEqualTo
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_LowerThanOrEqualTo == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->lowerThanOrEqualTo) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->lowerThanOrEqualTo(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_multiply
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Multiply == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->multiply) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->multiply(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_negate
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Negate == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* operandValue = R_InterpreterState_decodeOperand(process);

  R_Type* operandType = R_Value_getType(operandValue);
  R_Type_Operations const* operations = R_Type_getOperations(operandType);
  if (!operations->negate) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->negate(targetValue, operandValue);
}

void
R_Instructions_not
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Not == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* operandValue = R_InterpreterState_decodeOperand(process);

  R_Type* operandType = R_Value_getType(operandValue);
  R_Type_Operations const* operations = R_Type_getOperations(operandType);
  if (!operations->not) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->not(targetValue, operandValue);
}

void
R_Instructions_notEqualTo
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_NotEqualTo == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->notEqualTo) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->notEqualTo(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_or
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Or == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations-> or ) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->or(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_subtract
  (
    R_Interpreter_ProcessState* process
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(process);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
#if defined(_DEBUG)
  R_Interpreter_Code* code = call->procedure->code;
  assert(R_Machine_Code_Opcode_Subtract == (*code->p + call->instructionIndex));
#endif

  call->instructionIndex++;

  R_Value* targetValue = R_InterpreterState_decodeTarget(process);
  R_Value const* firstOperandValue = R_InterpreterState_decodeOperand(process);
  R_Value const* secondOperandValue = R_InterpreterState_decodeOperand(process);

  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->subtract) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->subtract(targetValue, firstOperandValue, secondOperandValue);
}
