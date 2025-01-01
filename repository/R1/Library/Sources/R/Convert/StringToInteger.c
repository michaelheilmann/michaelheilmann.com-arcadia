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

#include "R/Convert/StringToInteger.h"

#include "R/Convert/parse.i"

static Arcadia_Integer8Value
toInteger8
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_Integer16Value
toInteger16
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_Integer32Value
toInteger32
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_Integer64Value
toInteger64
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_Integer8Value
toInteger8
  (
    Arcadia_Process* process,
    State* state
  )
{
  Arcadia_Integer64Value v = toInteger64(process, state);
  if (v < Arcadia_Integer8Value_Minimum || v > Arcadia_Integer8Value_Maximum) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  return (Arcadia_Integer8Value)v;
}

static Arcadia_Integer16Value
toInteger16
  (
    Arcadia_Process* process,
    State* state
  )
{
  Arcadia_Integer64Value v = toInteger64(process, state);
  if (v < Arcadia_Integer16Value_Minimum || v > Arcadia_Integer16Value_Maximum) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  return (Arcadia_Integer16Value)v;
}

static Arcadia_Integer32Value
toInteger32
  (
    Arcadia_Process* process,
    State* state
  )
{
  Arcadia_Integer64Value v = toInteger64(process, state);
  if (v < Arcadia_Integer32Value_Minimum || v > Arcadia_Integer32Value_Maximum) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  return (Arcadia_Integer32Value)v;
}

static Arcadia_Integer64Value
toInteger64
  (
    Arcadia_Process* process,
    State* state
  )
{
  static const Arcadia_Integer64Value BASE = 10;
  // The maximum decimal value of an Arcadia_Integer64Value is -9,223,372,036,854,775,808. These are 19 decimal digits.
  // The minimum decimal value of an Arcadia_Integer64Value is +9,223,372,036,854,775,807. These are 19 decimal digits.
  // 18 = 19 - 1 is the number of decimal digits which always fit into an Arcadia_Integer64Value.
  static const Arcadia_SizeValue SAFEDIGITSBASE10 = 18;
#if 0
  // Precondition prevents that.
  if (CodePoint_Start != state->symbol) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
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
  Arcadia_Integer64Value v = 0;
  if (!isDigit(state)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  // Skip leading zeroes.
  while (isZero(state)) {
    next(state);
  }
  while (isDigit(state)) {
    Arcadia_Integer64Value w = 0; 
    // We accumulate up to 18 decimal digits in w.
    Arcadia_SizeValue i = 0, n = SAFEDIGITSBASE10;
    for (; isDigit(state) && i < n; ++i) {
      Arcadia_Integer64Value digit = (Arcadia_Integer64Value)(state->symbol - '0');
      w = w * BASE + digit;
      next(state);
    }
    // We need to multiply v by the number of digits in w.
    while (i > 0) {
      if (v < Arcadia_Integer64Value_Minimum / 10) {
        Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
        Arcadia_Process_jump(process);
      }
      v = v * i;
      i--;
    }
    // If we cannot subtract w from v, then this number is not representable.
    if (v < Arcadia_Integer16Value_Minimum + w) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
      Arcadia_Process_jump(process);
    }
    v -= w;
  }
  if (CodePoint_End != state->symbol) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  if (negative) {
    return v;
  }
  if (v == Arcadia_Integer64Value_Minimum) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
  v = -v;
  return v;
}

Arcadia_Integer8Value
R_toInteger8
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
  return toInteger8(process, &state);
}

Arcadia_Integer16Value
R_toInteger16
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
  return toInteger16(process, &state);
}

Arcadia_Integer32Value
R_toInteger32
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
  return toInteger32(process, &state);
}

Arcadia_Integer64Value
R_toInteger64
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
  return toInteger64(process, &state);
}
