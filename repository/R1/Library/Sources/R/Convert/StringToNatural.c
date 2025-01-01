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

// Last modified: 2024-09-26

#include "R/Convert/StringToNatural.h"

#include "R/Convert/parse.i"

static Arcadia_Natural8Value
toNatural8
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_Natural16Value
toNatural16
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_Natural32Value
toNatural32
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_Natural64Value
toNatural64
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_Natural8Value
toNatural8
  (
    Arcadia_Process* process,
    State* state
  )
{
  Arcadia_Natural64Value w = toNatural64(process, state);
  if (w > Arcadia_Natural8Value_Maximum) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  Arcadia_Natural8Value v = (Arcadia_Natural8Value)w;
  return v;
}

static Arcadia_Natural16Value
toNatural16
  (
    Arcadia_Process* process,
    State* state
  )
{
  Arcadia_Natural64Value w = toNatural64(process, state);
  if (w > Arcadia_Natural16Value_Maximum) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  Arcadia_Natural16Value v = (Arcadia_Natural16Value)w;
  return v;
}

static Arcadia_Natural32Value
toNatural32
  (
    Arcadia_Process* process,
    State* state
  )
{
  Arcadia_Natural64Value w = toNatural64(process, state);
  if (w > Arcadia_Natural32Value_Maximum) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  Arcadia_Natural32Value v = (Arcadia_Natural32Value)w;
  return v;
}

static Arcadia_Natural64Value
toNatural64
  (
    Arcadia_Process* process,
    State* state
  )
{
  static const Arcadia_Natural64Value BASE = 10;
  // The maximum decimal value of an Arcadia_Natural64Value is +18,446,744,073,709,551,615. These are 20 decimal digits.
  // The minimum decimal value of an Arcadia_Integer64Value is +0. This 1 one decimal digit.
  // 19 = 20 - 1 is the number of decimal digits which always fit into an Arcadia_Integer64Value.
  static const Arcadia_SizeValue SAFEDIGITSBASE10 = 19;
#if 0
  // Precondition prevents that.
  if (CodePoint_Start != state->symbol) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
#endif
  next(state);
  if (isPlus(state)) {
    next(state);
  }
  // Skip leading zeroes.
  while (isZero(state)) {
    next(state);
  }
  Arcadia_Natural64Value v = 0;
  if (!isDigit(state)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  while (isDigit(state)) {
    Arcadia_Integer64Value w = 0;
    // We accumulate up to 19 decimal digits in w.
    Arcadia_SizeValue i = 0, n = SAFEDIGITSBASE10;
    for (; isDigit(state) && i < n; ++i) {
      Arcadia_Natural64Value digit = (Arcadia_Natural64Value)(state->symbol - '0');
      w = w * BASE + digit;
      next(state);
    }
    // We would have to multiply v by the number of digits in w.
    while (i > 0) {
      if (v < Arcadia_Integer64Value_Minimum / 10) {
        Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
        Arcadia_Process_jump(process);
      }
      v = v * i;
      i--;
    }
    if (v > Arcadia_Natural64Value_Maximum - w) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
      Arcadia_Process_jump(process);
    }
    v = v + w;
  }
  if (CodePoint_End != state->symbol) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  return v;
}

Arcadia_Natural8Value
R_toNatural8
  (
    Arcadia_Process* process,
    const char* p,
    Arcadia_SizeValue n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toNatural8(process, &state);
}

Arcadia_Natural16Value
R_toNatural16
  (
    Arcadia_Process* process,
    const char* p,
    Arcadia_SizeValue n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toNatural32(process, &state);
}

Arcadia_Natural32Value
R_toNatural32
  (
    Arcadia_Process* process,
    const char* p,
    Arcadia_SizeValue n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toNatural32(process, &state);
}

Arcadia_Natural64Value
R_toNatural64
  (
    Arcadia_Process* process,
    const char* p,
    Arcadia_SizeValue n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toNatural64(process, &state);
}
