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

// Last modified: 2025-02-16

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.h"

#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String.h"

static Arcadia_Integer64Value
_toInteger64Internal
  (
    Arcadia_Process1* process,
    _State* state
  )
{
  static const Arcadia_Integer64Value BASE = 10;
  // The maximum decimal value of an Arcadia_Integer64Value is -9,223,372,036,854,775,808. These are 19 decimal digits.
  // The minimum decimal value of an Arcadia_Integer64Value is +9,223,372,036,854,775,807. These are 19 decimal digits.
  // 18 = 19 - 1 is the number of decimal digits which always fit into an Arcadia_Integer64Value.
  static const Arcadia_SizeValue SAFEDIGITSBASE10 = 18;
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
    Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process1_jump(process);
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
      Arcadia_Integer64Value digit = (Arcadia_Integer64Value)(state->codePoint - '0');
      w = w * BASE + digit;
      next(state);
    }
    // We need to multiply v by the number of digits in w.
    while (i > 0) {
      if (v < Arcadia_Integer64Value_Minimum / 10) {
        Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed);
        Arcadia_Process1_jump(process);
      }
      v = v * i;
      i--;
    }
    // If we cannot subtract w from v, then this number is not representable.
    if (v < Arcadia_Integer16Value_Minimum + w) {
      Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed);
      Arcadia_Process1_jump(process);
    }
    v -= w;
  }
  if (_Unicode_CodePoint_End != state->codePoint) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process1_jump(process);
  }
  if (negative) {
    return v;
  }
  if (v == Arcadia_Integer64Value_Minimum) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process1_jump(process);
  }
  v = -v;
  return v;
}

Arcadia_Integer16Value
_toInteger16
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  Arcadia_Integer64Value v = _toInteger64(process, immutableUtf8StringValue);
  if (v < Arcadia_Integer16Value_Minimum || v > Arcadia_Integer16Value_Maximum) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process1_jump(process);
  }
  return (Arcadia_Integer16Value)v;
}

Arcadia_Integer32Value
_toInteger32
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  Arcadia_Integer64Value v = _toInteger64(process, immutableUtf8StringValue);
  if (v < Arcadia_Integer32Value_Minimum || v > Arcadia_Integer32Value_Maximum) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process1_jump(process);
  }
  return (Arcadia_Integer32Value)v;
}

Arcadia_Integer64Value
_toInteger64
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  _State state;
  _State_init(&state, Arcadia_ImmutableUtf8String_getBytes(process, immutableUtf8StringValue),
                      Arcadia_ImmutableUtf8String_getNumberOfBytes(process, immutableUtf8StringValue));
  Arcadia_Integer64Value value;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process1_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    value = _toInteger64Internal(process, &state);
    _State_uninit(&state);
    Arcadia_Process1_popJumpTarget(process);
  } else {
    _State_uninit(&state);
    Arcadia_Process1_popJumpTarget(process);
    Arcadia_Process1_jump(process);
  }
  return value;
}

Arcadia_Integer8Value
_toInteger8
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  Arcadia_Integer64Value v = _toInteger64(process, immutableUtf8StringValue);
  if (v < Arcadia_Integer8Value_Minimum || v > Arcadia_Integer8Value_Maximum) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process1_jump(process);
  }
  return (Arcadia_Integer8Value)v;
}
