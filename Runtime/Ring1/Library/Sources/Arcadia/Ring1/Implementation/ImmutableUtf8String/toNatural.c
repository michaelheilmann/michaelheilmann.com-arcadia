// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.h"

#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String.h"
#include "Arcadia/Ring1/Implementation/NumberLiteral.h"
#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/safeAdd.h"
#include "Arcadia/Ring1/Implementation/safeMultiply.h"
#include "Arcadia/Ring1/Implementation/Thread.h"

static Arcadia_Natural64Value
_toNatural64Internal
  (
    Arcadia_Thread* thread,
    _State* state
  )
{
  static const Arcadia_Natural64Value baseTen = 10;
  // The maximum decimal value of an Arcadia_Natural64Value is +18,446,744,073,709,551,615. These are 20 decimal digits.
  // The minimum decimal value of an Arcadia_Integer64Value is +0. This 1 one decimal digit.
  // 19 = 20 - 1 is the number of decimal digits which always fit into an Arcadia_Integer64Value.
  static const Arcadia_SizeValue safeDigitsBaseTen = 19;
  next(state);
  if (isPlus(state)) {
    next(state);
  }
  static const Arcadia_Natural64Value powersOfTen[] = {
    Arcadia_Natural64Value_Literal(1),
    Arcadia_Natural64Value_Literal(10),
    Arcadia_Natural64Value_Literal(100),

    Arcadia_Natural64Value_Literal(1000),
    Arcadia_Natural64Value_Literal(10000),
    Arcadia_Natural64Value_Literal(100000),

    Arcadia_Natural64Value_Literal(1000000),
    Arcadia_Natural64Value_Literal(10000000),
    Arcadia_Natural64Value_Literal(100000000),

    Arcadia_Natural64Value_Literal(1000000000),
    Arcadia_Natural64Value_Literal(10000000000),
    Arcadia_Natural64Value_Literal(100000000000),

    Arcadia_Natural64Value_Literal(1000000000000),
    Arcadia_Natural64Value_Literal(10000000000000),
    Arcadia_Natural64Value_Literal(100000000000000),

    Arcadia_Natural64Value_Literal(1000000000000000),
    Arcadia_Natural64Value_Literal(10000000000000000),
    Arcadia_Natural64Value_Literal(100000000000000000),

    Arcadia_Natural64Value_Literal(1000000000000000000),
  };
  Arcadia_Natural64Value v = 0;
  if (!isDigit(state)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  // Skip leading zeroes.
  while (isZero(state)) {
    next(state);
  }
  while (isDigit(state)) {
    Arcadia_Natural64Value w = 0;
    // We accumulate up to 19 decimal digits in w.
    Arcadia_SizeValue i = 0, n = safeDigitsBaseTen;
    for (; isDigit(state) && i < n; ++i) {
      Arcadia_Natural64Value digit = (Arcadia_Natural64Value)(state->codePoint - '0');
      w = w * baseTen + digit;
      next(state);
    }
    // Multiply v by 10 raised to the power equal to the number of digits accumulated in w, then add w to v.
    // Both operations might overflow.
    Arcadia_Natural64Value hi;
    if (!Arcadia_safeMultiplyNatural64Value(thread, v, powersOfTen[i], &hi, &v)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_safeAddFullNatural64Value(thread, v, w, &hi, &v);
    if (hi) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
      Arcadia_Thread_jump(thread);
    }
  }
  if (!isEnd(state)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return v;
}

Arcadia_Natural16Value
_toNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  Arcadia_Natural64Value w = _toNatural64(thread, immutableUtf8StringValue);
  if (w > Arcadia_Natural16Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural16Value v = (Arcadia_Natural16Value)w;
  return v;
}

Arcadia_Natural32Value
_toNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  Arcadia_Natural64Value w = _toNatural64(thread, immutableUtf8StringValue);
  if (w > Arcadia_Natural32Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural32Value v = (Arcadia_Natural32Value)w;
  return v;
}

Arcadia_Natural64Value
_toNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  _State state;
  _State_init(&state, Arcadia_ImmutableUtf8String_getBytes(thread, immutableUtf8StringValue),
                      Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, immutableUtf8StringValue));
  Arcadia_Natural64Value value;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    value = _toNatural64Internal(thread, &state);
    _State_uninit(&state);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    _State_uninit(&state);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
  return value;
}

Arcadia_Natural8Value
_toNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  Arcadia_Natural64Value w = _toNatural64(thread, immutableUtf8StringValue);
  if (w > Arcadia_Natural8Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value v = (Arcadia_Natural8Value)w;
  return v;
}
