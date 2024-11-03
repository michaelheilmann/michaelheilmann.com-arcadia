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

#if !defined(R_INSTRUCTIONS_INSTRUCTION_H_INCLUDED)
#define R_INSTRUCTIONS_INSTRUCTION_H_INCLUDED

#include "R/Value.h"


typedef enum R_Machine_Opcode {
  
  // add <target> <firstOperand> <secondOperand>
  R_Opcode_Add,
  
  // and <target> <firstOperand> <secondOperand>
  R_Opcode_And,
  
  // concatenate <target> <firstOperand> <secondOperand>
  R_Opcode_Concatenate,
  
  // divide <target> <firstOperand> <secondOperand>
  R_Opcode_Divide,
  
  // equalTo <target> <firstOperand> <secondOperand>
  R_Opcode_EqualTo,
  
  // greaterThan <target> <firstOperand> <secondOperand>
  R_Opcode_GreaterThan,
  
  // greaterThanOrEqualTo <target> <firstOperand> <secondOperand>
  R_Opcode_GreaterThanOrEqualTo,
  
  // idle
  R_Opcode_Idle,
  
  // lowerThan <target> <firstOperand> <secondOperand>
  R_Opcode_LowerThan,
  
  // lowerThanOrEqualTo <target> <firstOperand> <secondOperand>
  R_Opcode_LowerThanOrEqualTo,
  
  // multiply <target> <firstOperand> <secondOperand>
  R_Opcode_Multiply,

  // add <target> <operand>
  R_Opcode_Negate,

  // not <target> <operand>
  R_Opcode_Not,

  // notEqualTo <target> <firstOperand> <secondOperand>
  R_Opcode_NotEqualTo,

  // or <target> <firstOperand> <secondOperand>
  R_Opcode_Or,
  
  // return
  R_Opcode_Return,

  // subtract <target> <firstOperand> <secondOperand>
  R_Opcode_Subtract,

} R_Machine_Opcode;


// 11xx 0000 denotes neither constant nor register.
// 00xx xxxx denotes 00xx xxxx is a register index.
// 01xx xxxx denotes 00xx xxxx is a constant index.
// 10xx xxxx is reserved for future use.
static inline R_BooleanValue
Instruction_Index_isInvalid
  (
    R_Natural8Value index
  )
{ return 0b11000000 == (0b11000000 & index); }

static inline R_BooleanValue
Instruction_Index_isRegister
  (
    R_Natural8Value index
  )
{ return 0b00000000 == (0b11000000 & index); }

static inline R_BooleanValue
Instruction_Index_isConstant
  (
    R_Natural8Value index
  )
{ return 0b01000000 == (0b11000000 & index); }

static inline R_Natural8Value
Instruction_Index_decode
  (
    R_Natural8Value index
  )
{ return 0b00111111 & index; }

void
R_Instructions_add
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_and
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_concatenate
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_divide
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_equalTo
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_greaterThan
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_greaterThanOrEqualTo
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_idle
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_lowerThan
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_lowerThanOrEqualTo
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_multiply
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_negate
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_not
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_notEqualTo
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_or
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

void
R_Instructions_subtract
  (
    R_Value const* constants,
    R_Value* registers,
    uint8_t targetIndex,
    uint8_t firstOperandIndex,
    uint8_t secondOperandIndex
  );

#include "R/Object.h"

Rex_declareObjectType("R.Machine.Code", R_Machine_Code, R_Object);

struct R_Machine_Code {
  R_Object _parent;
  R_Natural8Value* p;
  R_SizeValue sz, cp;
};

R_Machine_Code*
R_Machine_Code_create
  (
  );

void
R_Machine_Code_append
  (
    R_Machine_Code* self,
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  );

#endif // R_INSTRUCTIONS_INSTRUCTION_H_INCLUDED
