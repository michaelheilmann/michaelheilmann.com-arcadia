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

#include "R/Machine/Code/Instruction.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/UnmanagedMemory.h"
#include <string.h>

void
R_Instructions_add
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{/*Intentionally empty.*/}

void
R_Instructions_lowerThan
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  R_Value const* operandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  R_Value const* operandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
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
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations-> or ) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations-> or (targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_subtract
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  )
{
  R_Value* targetValue = &(registers[targetIndex]);
  uint8_t i = Instruction_Index_decode(firstOperandIndex);
  uint8_t j = Instruction_Index_decode(secondOperandIndex);
  R_Value const* firstOperandValue = Instruction_Index_isConstant(firstOperandIndex) ? &(constants[i]) : &(registers[i]);
  R_Value const* secondOperandValue = Instruction_Index_isConstant(secondOperandIndex) ? &(constants[j]) : &(registers[j]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->subtract) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->subtract(targetValue, firstOperandValue, secondOperandValue);
}

static void
R_Machine_Code_destruct
  (
    R_Machine_Code* self
  );

static void
R_Machine_Code_destruct
  (
    R_Machine_Code* self
  )
{
  if (self->p) {
    R_deallocateUnmanaged_nojump(self->p);
    self->p = NULL;
  }
}

Rex_defineObjectType("R.Machine.Code", R_Machine_Code, "R.Object", R_Object, NULL, &R_Machine_Code_destruct);

void
R_Machine_Code_construct
  (
    R_Machine_Code* self
  )
{
  R_Type* _type = _R_Machine_Code_getType();
  R_Object_construct((R_Object*)self);
  self->p = NULL;
  self->sz = 0;
  self->cp = 0;
  if (!R_allocateUnmanaged_nojump(&self->p, 0)) {
    R_jump();
  }
  R_Object_setType((R_Object*)self, _type);
}

R_Machine_Code*
R_Machine_Code_create
  (
  )
{
  R_Machine_Code* self = R_allocateObject(_R_Machine_Code_getType());
  R_Machine_Code_construct(self);
  return self;
}

// Compute the new capacity
// - <new capacity> = 2 * <n> * <capacity> if <capacit> > 0
// - <new capacity> = 2 * <n> * 1 otherwise
// such that <n> is minimal and <new capacity> - <size> >= <required free capacity>
// If <new capacity> exists, return true and assign it to *new_cp.
// Otherwise return false.
static bool growCapacity1(R_SizeValue size, R_SizeValue capacity, R_SizeValue requiredFreeCapacity, R_SizeValue *newCapacity) {
  static const R_SizeValue maximalCapacity = SIZE_MAX / sizeof(uint8_t);
  R_SizeValue currentNewCapacity = capacity ? capacity : 1;
  R_SizeValue availableFreeCapacity = currentNewCapacity - size;
  while (availableFreeCapacity < requiredFreeCapacity && currentNewCapacity <= maximalCapacity / 2) {
    currentNewCapacity *= 2;
    availableFreeCapacity = currentNewCapacity - size;
  }
  if (availableFreeCapacity < requiredFreeCapacity) {
    return false;
  }
  *newCapacity = currentNewCapacity;
  return true;
}

// Compute the new capacity
// <new capacity> = <maximal capacity>
// such that <new capacity> - <size> >= <required free capacity>.
// If such a new capacity exists, return true and assign it to *new_cp.
// Otherwise return false.*
static bool growCapacity2(R_SizeValue size, R_SizeValue capacity, R_SizeValue requiredFreeCapacity, R_SizeValue *newCapacity) {
  static const R_SizeValue maximalCapacity = SIZE_MAX / sizeof(uint8_t);
  R_SizeValue currentNewCapacity = maximalCapacity;
  R_SizeValue availableFreeCapacity = currentNewCapacity - size;
  if (requiredFreeCapacity > availableFreeCapacity) {
    return false;
  }
  *newCapacity = currentNewCapacity;
  return true;
}

static bool growCapacity(R_SizeValue size, R_SizeValue capacity, R_SizeValue requiredFreeCapacity, R_SizeValue* newCapacity) {
  if (growCapacity1(size, capacity, requiredFreeCapacity, newCapacity)) {
    return true;
  }
  if (growCapacity2(size, capacity, requiredFreeCapacity, newCapacity)) {
    return true;
  }
  return false;
}

static void ensureFreeCapacity(R_Machine_Code* self, R_SizeValue requiredFreeCapacity) {
  R_SizeValue actualFreeCapacity = self->cp - self->sz;
  if (actualFreeCapacity < requiredFreeCapacity) {
    R_SizeValue newCapacity;
    if (!growCapacity(self->sz, self->cp, requiredFreeCapacity, &newCapacity)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    if (!R_reallocateUnmanaged_nojump(&self->p, newCapacity)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    self->cp = newCapacity;
  }
}

void
R_Machine_Code_append
  (
    R_Machine_Code* self,
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  )
{
  ensureFreeCapacity(self, numberOfBytes);
  memcpy(self->p + self->sz, bytes, numberOfBytes);
}
