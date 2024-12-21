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

// Last modified: 2024-09-26

#include "R/Convert/StringToNatural.h"

#include "R/Convert/parse.i"

static R_Natural8Value
toNatural8
  (
    State* state
  );

static R_Natural16Value
toNatural16
  (
    State* state
  );

static R_Natural32Value
toNatural32
  (
    State* state
  );

static R_Natural64Value
toNatural64
  (
    State* state
  );

static R_Natural8Value
toNatural8
  (
    State* state
  )
{
  R_Natural64Value w = toNatural64(state);
  if (w > R_Natural8Value_Maximum) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  R_Natural8Value v = (R_Natural8Value)w;
  return v;
}

static R_Natural16Value
toNatural16
  (
    State* state
  )
{
  R_Natural64Value w = toNatural64(state);
  if (w > R_Natural16Value_Maximum) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  R_Natural16Value v = (R_Natural16Value)w;
  return v;
}

static R_Natural32Value
toNatural32
  (
    State* state
  )
{
  R_Natural64Value w = toNatural64(state);
  if (w > R_Natural32Value_Maximum) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  R_Natural32Value v = (R_Natural32Value)w;
  return v;
}

static R_Natural64Value
toNatural64
  (
    State* state
  )
{
  static const R_Natural64Value BASE = 10;
  // The maximum decimal value of an R_Natural64Value is +18,446,744,073,709,551,615. These are 20 decimal digits.
  // The minimum decimal value of an R_Integer64Value is +0. This 1 one decimal digit.
  // 19 = 20 - 1 is the number of decimal digits which always fit into an R_Integer64Value.
  static const R_SizeValue SAFEDIGITSBASE10 = 19;
#if 0
  // Precondition prevents that.
  if (CodePoint_Start != state->symbol) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
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
  R_Natural64Value v = 0;
  if (!isDigit(state)) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  while (isDigit(state)) {
    R_Integer64Value w = 0;
    // We accumulate up to 19 decimal digits in w.
    R_SizeValue i = 0, n = SAFEDIGITSBASE10;
    for (; isDigit(state) && i < n; ++i) {
      R_Natural64Value digit = (R_Natural64Value)(state->symbol - '0');
      w = w * BASE + digit;
      next(state);
    }
    // We would have to multiply v by the number of digits in w.
    while (i > 0) {
      if (v < R_Integer64Value_Minimum / 10) {
        R_setStatus(R_Status_ConversionFailed);
        R_jump();
      }
      v = v * i;
      i--;
    }
    if (v > R_Natural64Value_Maximum - w) {
      R_setStatus(R_Status_ConversionFailed);
      R_jump();
    }
    v = v + w;
  }
  if (CodePoint_End != state->symbol) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  return v;
}

R_Natural8Value
R_toNatural8
  (
    const char* p,
    R_SizeValue n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toNatural8(&state);
}

R_Natural16Value
R_toNatural16
  (
    const char* p,
    R_SizeValue n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toNatural32(&state);
}

R_Natural32Value
R_toNatural32
  (
    const char* p,
    R_SizeValue n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toNatural32(&state);
}

R_Natural64Value
R_toNatural64
  (
    const char* p,
    R_SizeValue n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toNatural64(&state);
}
