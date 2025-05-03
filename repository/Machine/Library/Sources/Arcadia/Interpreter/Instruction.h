// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(R_INTERPRETER_INSTRUCTION_H_INCLUDED)
#define R_INTERPRETER_INSTRUCTION_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
typedef struct R_Interpreter_Code_Constants R_Interpreter_Code_Constants;
typedef struct R_Interpreter_ProcessState R_Interpreter_ProcessState;
typedef struct R_Interpreter_ThreadState R_Interpreter_ThreadState;
typedef struct R_Interpreter_Code R_Interpreter_Code;

#define R_Machine_Code_NumberOfArguments_Maximum (32)

typedef enum R_Machine_Code_IndexKind {
  R_Machine_Code_IndexKind_Register = 1,
  R_Machine_Code_IndexKind_Constant = 2,
  R_Machine_Code_IndexKind_Invalid = 3,
  R_Machine_Code_IndexKind_Reserved = 4,
} R_Machine_Code_IndexKind;

typedef enum R_Machine_Code_Opcode {

  // load <target> <operand>
  R_Machine_Code_Opcode_Load,
  
  // add <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_Add,
  
  // and <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_And,
  
  // concatenate <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_Concatenate,
  
  // divide <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_Divide,
  
  // isEqualTo <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_IsEqualTo,
  
  // isGreaterThan <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_IsGreaterThan,
  
  // isGreaterThanOrEqualTo <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_IsGreaterThanOrEqualTo,
  
  // idle
  R_Machine_Code_Opcode_Idle,
  
  // isLowerThan <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_IsLowerThan,
  
  // isLowerThanOrEqualTo <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_IsLowerThanOrEqualTo,
  
  // multiply <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_Multiply,

  // add <target> <operand>
  R_Machine_Code_Opcode_Negate,

  // not <target> <operand>
  R_Machine_Code_Opcode_Not,

  // IsNotEqualTo <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_IsNotEqualTo,

  // or <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_Or,

  // raise
  R_Machine_Code_Opcode_Raise, 

  // return
  R_Machine_Code_Opcode_Return,

  // subtract <target> <firstOperand> <secondOperand>
  R_Machine_Code_Opcode_Subtract,

  // invoke <target> <number of arguments>
  // <argument 1> <argument 2> ... <argument n>
  R_Machine_Code_Opcode_Invoke,

} R_Machine_Code_Opcode;

#define R_Machine_Code_InvalidIndexFlag  (0b00000000)
#define R_Machine_Code_RegisterIndexFlag (0b01000000)
#define R_Machine_Code_ConstantIndexFlag (0b10000000)
#define R_Machine_Code_ReservedIndexFlag (0b11000000)

// INDICES
// An index in an instruction is a multi-byte sequuence.
// 
// The first Byte of the sequence is of one of the following four forms.
// 00xx xxxx denotes an invalid index.
// 01xx xxxx denotes 00xx xxxx is a register index.
// 10xx xxxx denotes 00xx xxxx is a constant index.
// 11xx xxxx is reserved for future use.
//
// If the index is a constant index or register index,
// 
// Given the xx xxxx Bits, we can decode the register index / constant index.
// - 0a aa aa is a single byte index.
//   Used to encode indices [0 0000, 1 1111] in binary / [0, 31] in decimal.
//
// - 11 0a aa is the beginning two-byte sequence of the form
//   11 0a aa 10 bb bb bb 
//   A := aaa can encode [000, 111] in binary / [0,7] in decimal.
//   B := bb bbbb can encode [00 0000, 11 1111] in binary / [0,63] in decimal.
//   The final index is computed by A << 6 | B = A * 64 + B.
//   Used to encode the indices [0000*64 + 10 0000, 111*64 + 11 1111] in binary and
//   [0*64 + 32, 7 * 64 + 63] = [32, 511] in decimal.
//
// - 11 10 aa is the beginning of a three byte sequence of the form
//   11 10 aa 10 bb bb bb 10 cc cc cc
//   A := aa can encode [00, 11] in binary / [0,3] in decimal.
//   B := bb bbbb and C := cc cccc each can encode [00 0000, 11 1111] in binary / [0,63] in decimal.
//   The final index is computed by A << 12 | B << 6 | C = A * 4096 + B * 64 + C.
//   Used to encode the indices [00*4096+64*001000 + 00 0000, 11*4096+64*11 1111+11 1111] in binary and
//   [0*4096+64*8+0, 3*4096+64*63+63] = [512, 16383] in decimal.
//
// - 11110 a is the beginning of a four Byte sequence of the form
//   11 11 0a 10 bb bb bb 10 cc cc cc 10 dd dd dd
//   Threee more Bytes each of the form 10bb bbbb, 10cc ccccc, and 10dd ddddd follow.
//   A := a can encode [0, 1] in binary / [0,1] in decimal.
//   B := bb bbbb, C := cc cccc, and D:= dd ddddd each can encode [00 0000, 11 1111] in binary / [0,63] in decimal.
//   The final index is computed by A << 18 | B << 12 | C << 6 | D = A * 262144 + B * 4096 + C * 64 + D.
//   Used to encode the indices [0 * 262144 + 00 0100 * 4096 + 64 * 00 0000 + 00 0000, 1 * 262144 + 11 1111 * 4096 + 64 * 11 1111 + 11 11111] in binary and
//   [0 * 262144 + 4 * 4096 + 64 * 0 + 0, 1 * 262144 + 63 * 4096 + 64 * 63 + 63] = [16 384, 524 287] in decimal.
//
// A program with more than 524 287 constants or more than 524 287 registers is rejected.
//
// COUNTS
// A count is a value between Arcadia_Natural32Value_Minimum and Arcadia_Natural32Value_Maximum.

void
R_Instructions_add
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_and
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_concatenate
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_divide
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_isEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_isGreaterThan
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_isGreaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_idle
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_isLowerThan
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_isLowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_multiply
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_negate
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_not
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_isNotEqualTo
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_or
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

void
R_Instructions_subtract
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  );

#endif // R_INTERPRETER_INSTRUCTION_H_INCLUDED
