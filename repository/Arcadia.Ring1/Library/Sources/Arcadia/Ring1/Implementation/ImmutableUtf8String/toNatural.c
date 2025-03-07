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
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.h"

#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String.h"

static Arcadia_Natural64Value
_toNatural64Internal
  (
    Arcadia_Thread* thread,
    _State* state
  )
{
  static const Arcadia_Natural64Value BASE = 10;
  // The maximum decimal value of an Arcadia_Natural64Value is +18,446,744,073,709,551,615. These are 20 decimal digits.
  // The minimum decimal value of an Arcadia_Integer64Value is +0. This 1 one decimal digit.
  // 19 = 20 - 1 is the number of decimal digits which always fit into an Arcadia_Integer64Value.
  static const Arcadia_SizeValue SAFEDIGITSBASE10 = 19;
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
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  while (isDigit(state)) {
    Arcadia_Integer64Value w = 0;
    // We accumulate up to 19 decimal digits in w.
    Arcadia_SizeValue i = 0, n = SAFEDIGITSBASE10;
    for (; isDigit(state) && i < n; ++i) {
      Arcadia_Natural64Value digit = (Arcadia_Natural64Value)(state->codePoint - '0');
      w = w * BASE + digit;
      next(state);
    }
    // We would have to multiply v by the number of digits in w.
    while (i > 0) {
      if (v < Arcadia_Integer64Value_Minimum / 10) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
        Arcadia_Thread_jump(thread);
      }
      v = v * i;
      i--;
    }
    if (v > Arcadia_Natural64Value_Maximum - w) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
      Arcadia_Thread_jump(thread);
    }
    v = v + w;
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
