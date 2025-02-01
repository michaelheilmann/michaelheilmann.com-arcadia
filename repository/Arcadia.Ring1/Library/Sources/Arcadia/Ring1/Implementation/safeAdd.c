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

// Last modified: 2025-01-26

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/safeAdd.h"

void
Arcadia_safeAdd_n16
  (
    Arcadia_Process1* process,
    Arcadia_Natural16Value augend,
    Arcadia_Natural16Value addend,
    Arcadia_Natural16Value* sumHigh,
    Arcadia_Natural16Value* sumLow
  )
{
  if (!sumHigh | !sumLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  uint32_t temporary = (uint32_t)augend + (uint32_t)addend;
  *sumHigh = (uint16_t)(temporary >> 16);
  *sumLow = (uint16_t)(temporary & 0x0000ffff);
}

void
Arcadia_safeAdd_n32
  (
    Arcadia_Process1* process,
    Arcadia_Natural32Value augend,
    Arcadia_Natural32Value addend,
    Arcadia_Natural32Value* sumHigh,
    Arcadia_Natural32Value* sumLow
  )
{
  if (!sumHigh | !sumLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  uint64_t temporary = (uint64_t)augend + (uint64_t)addend;
  *sumHigh = (uint32_t)(temporary >> 32);
  *sumLow = (uint32_t)(temporary & 0x00000000ffffffff);
}

#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_Compiler

void
Arcadia_mulex_n64_gcc
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value augend,
    Arcadia_Natural64Value addend,
    Arcadia_Natural64Value* sumHigh,
    Arcadia_Natural64Value* sumLow
  )
{
  if (!sumHigh | !sumLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  unsigned __int128 product = (unsigned __int128)augend + (unsigned __int128)addend;
  *sumHigh = product >> 64;
  *sumLow = (uint64_t)product;
}

#endif

void
Arcadia_safeAdd_n64
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value augend,
    Arcadia_Natural64Value addend,
    Arcadia_Natural64Value* sumHigh,
    Arcadia_Natural64Value* sumLow
  )
{
  if (!sumHigh | !sumLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }

  // if two unsigned n>0 bit values are added then the result is at most an unsigned n+1 bit value.
  // more precisely, the maximum value of the result is 2^(n + 1) - 2.
  // 
  // Proof:
  //   2^n - 1 + 2^n - 1
  // = 2 x 2^n - 2
  // = 2^(n+1) - 2
  // q.e.d.
  // 
  // Given unconstrained arithmetic:
  // (x + y) / n will return the topmost bit which is either 0 or 1 and is hi.
  // (x + y) % n will return the lower 64 bit which are lo.
  // Given the rules of C/C++ uintx_t arithmetic, (x + y) % n is actually computed by the standard addition so we can simply x + y to compute lo. 
  Arcadia_Natural64Value x = augend + addend;
  *sumHigh = x < augend ? 1 : 0;
  *sumLow = x;
}

void
Arcadia_safeAdd_n8
  (
    Arcadia_Process1* process,
    Arcadia_Natural8Value augend,
    Arcadia_Natural8Value addend,
    Arcadia_Natural8Value* sumHigh,
    Arcadia_Natural8Value* sumLow
  )
{
  if (!sumHigh | !sumLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  uint16_t temporary = (uint16_t)augend + (uint16_t)addend;
  *sumHigh = (uint8_t)(temporary >> 8);
  *sumLow = (uint8_t)(temporary & 0x00ff);
}
