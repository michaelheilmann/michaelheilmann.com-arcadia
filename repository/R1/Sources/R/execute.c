#include "R/execute.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Machine/Code/Include.h"

void
R_execute
  (
    R_Value const* constants,
    R_Value* registers,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  uint8_t const* start = ((uint8_t const*)bytes) + 0;
  uint8_t const* end = ((uint8_t const*)bytes) + numberOfBytes;
  uint8_t const* current = start;
  while (current != end) {
    switch (*current) {
      case R_Opcode_Idle: {
        current++;
        R_Instructions_idle(constants, registers, 0b11000000, 0b11000000, 0b11000000);
      } break;
      case R_Opcode_Add: {
        uint8_t target = *(++current);
        uint8_t firstOperand = *(++current);
        uint8_t secondOperand = *(++current);
        current++;
        R_Instructions_add(constants, registers, target, firstOperand, secondOperand);
      } break;
      case R_Opcode_And: {
        uint8_t target = *(++current);
        uint8_t firstOperand = *(++current);
        uint8_t secondOperand = *(++current);
        current++;
        R_Instructions_and(constants, registers, target, firstOperand, secondOperand);
      } break;
      case R_Opcode_Concatenate: {
        uint8_t target = *(++current);
        uint8_t firstOperand = *(++current);
        uint8_t secondOperand = *(++current);
        current++;
        R_Instructions_concatenate(constants, registers, target, firstOperand, secondOperand);
      } break;
      case R_Opcode_Divide: {
        uint8_t target = *(++current);
        uint8_t firstOperand = *(++current);
        uint8_t secondOperand = *(++current);
        current++;
        R_Instructions_divide(constants, registers, target, firstOperand, secondOperand);
      } break;
      case R_Opcode_Subtract: {
        uint8_t target = *(++current);
        uint8_t firstOperand = *(++current);
        uint8_t secondOperand = *(++current);
        current++;
        R_Instructions_subtract(constants, registers, target, firstOperand, secondOperand);
      } break;
      case R_Opcode_Multiply: {
        uint8_t target = *(++current);
        uint8_t firstOperand = *(++current);
        uint8_t secondOperand = *(++current);
        current++;
        R_Instructions_multiply(constants, registers, target, firstOperand, secondOperand);
      } break;
      case R_Opcode_Negate: {
        uint8_t target = *(++current);
        uint8_t operand = *(++current);
        current++;
        R_Instructions_negate(constants, registers, target, operand, 0b11000000);
      } break;
      case R_Opcode_Not: {
        uint8_t target = *(++current);
        uint8_t operand = *(++current);
        current++;
        R_Instructions_not(constants, registers, target, operand, 0b11000000);
      } break;
      case R_Opcode_Or: {
        uint8_t target = *(++current);
        uint8_t firstOperand = *(++current);
        uint8_t secondOperand = *(++current);
        current++;
        R_Instructions_or(constants, registers, target, firstOperand, secondOperand);
      } break;
      case R_Opcode_Return: {
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
