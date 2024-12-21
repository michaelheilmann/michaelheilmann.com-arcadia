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

#include "R/Convert/StringToInteger.h"

#include "R/Convert/parse.i"

static R_Integer8Value
toInteger8
  (
    State* state
  );

static R_Integer16Value
toInteger16
  (
    State* state
  );

static R_Integer32Value
toInteger32
  (
    State* state
  );

static R_Integer64Value
toInteger64
  (
    State* state
  );

static R_Integer8Value
toInteger8
  (
    State* state
  )
{
  R_Integer64Value v = toInteger64(state);
  if (v < R_Integer8Value_Minimum || v > R_Integer8Value_Maximum) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  return (R_Integer8Value)v;
}

static R_Integer16Value
toInteger16
  (
    State* state
  )
{
  R_Integer64Value v = toInteger64(state);
  if (v < R_Integer16Value_Minimum || v > R_Integer16Value_Maximum) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  return (R_Integer16Value)v;
}

static R_Integer32Value
toInteger32
  (
    State* state
  )
{
  R_Integer64Value v = toInteger64(state);
  if (v < R_Integer32Value_Minimum || v > R_Integer32Value_Maximum) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  return (R_Integer32Value)v;
}

static R_Integer64Value
toInteger64
  (
    State* state
  )
{
  static const R_Integer64Value BASE = 10;
  // The maximum decimal value of an R_Integer64Value is -9,223,372,036,854,775,808. These are 19 decimal digits.
  // The minimum decimal value of an R_Integer64Value is +9,223,372,036,854,775,807. These are 19 decimal digits.
  // 18 = 19 - 1 is the number of decimal digits which always fit into an R_Integer64Value.
  static const R_SizeValue SAFEDIGITSBASE10 = 18;
#if 0
  // Precondition prevents that.
  if (CodePoint_Start != state->symbol) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
#endif
  next(state);
  bool negative = false;
  if (isMinus(state)) {
    negative = true;
    next(state);
  } else if (isPlus(state)) {
    next(state);
  }
  R_Integer64Value v = 0;
  if (!isDigit(state)) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  // Skip leading zeroes.
  while (isZero(state)) {
    next(state);
  }
  while (isDigit(state)) {
    R_Integer64Value w = 0; 
    // We accumulate up to 18 decimal digits in w.
    R_SizeValue i = 0, n = SAFEDIGITSBASE10;
    for (; isDigit(state) && i < n; ++i) {
      R_Integer64Value digit = (R_Integer64Value)(state->symbol - '0');
      w = w * BASE + digit;
      next(state);
    }
    // We need to multiply v by the number of digits in w.
    while (i > 0) {
      if (v < R_Integer64Value_Minimum / 10) {
        R_setStatus(R_Status_ConversionFailed);
        R_jump();
      }
      v = v * i;
      i--;
    }
    // If we cannot subtract w from v, then this number is not representable.
    if (v < R_Integer16Value_Minimum + w) {
      R_setStatus(R_Status_ConversionFailed);
      R_jump();
    }
    v -= w;
  }
  if (CodePoint_End != state->symbol) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  if (negative) {
    return v;
  }
  if (v == R_Integer64Value_Minimum) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  v = -v;
  return v;
}

R_Integer8Value
R_toInteger8
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
  return toInteger8(&state);
}

R_Integer16Value
R_toInteger16
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
  return toInteger16(&state);
}

R_Integer32Value
R_toInteger32
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
  return toInteger32(&state);
}

R_Integer64Value
R_toInteger64
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
  return toInteger64(&state);
}
