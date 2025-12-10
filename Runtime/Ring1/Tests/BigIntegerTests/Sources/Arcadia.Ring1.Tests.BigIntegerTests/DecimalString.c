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

#include "Arcadia.Ring1.Tests.BigIntegerTests/DecimalString.h"

// string v to big integer to string w and assert v and w are equal
static void
testRoundTrip
  (
    Arcadia_Thread* thread
  )
{
  static const Arcadia_Natural8Value* bytes = u8"1982";
  static const Arcadia_SizeValue numberOfBytes = sizeof(u8"1982") - 1;
  Arcadia_BigInteger* x = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_fromDecimalString(thread, x, bytes, numberOfBytes);
  Arcadia_ImmutableUtf8String* s = Arcadia_BigInteger_toDecimalString(thread, x);
  Arcadia_Tests_assertTrue(thread, numberOfBytes == s->numberOfBytes);
  Arcadia_Tests_assertTrue(thread, Arcadia_Integer32Value_Literal(0) == Arcadia_Memory_compare(thread, bytes, s->bytes, numberOfBytes));
}

static void
testFixture
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value naturalValue,
    Arcadia_ImmutableUtf8String* expectedValueString
  )
{
  Arcadia_BigInteger* v = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural32(thread, v, naturalValue);
  Arcadia_ImmutableUtf8String* receivedValueString = Arcadia_BigInteger_toDecimalString(thread, v);
  Arcadia_Value x = Arcadia_Value_makeImmutableUtf8StringValue(receivedValueString);
  Arcadia_Value y = Arcadia_Value_makeImmutableUtf8StringValue(expectedValueString);
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isEqualTo(thread, &x, &y));
}

void
Arcadia_Ring1_Tests_BigInteger_decimalStringOperations
  (
    Arcadia_Thread* thread
  )
{
  testFixture(thread, 0, Arcadia_ImmutableUtf8String_create(thread, u8"0", sizeof(u8"0") - 1));
  testFixture(thread, 1, Arcadia_ImmutableUtf8String_create(thread, u8"1", sizeof(u8"1") - 1));
  testFixture(thread, 12, Arcadia_ImmutableUtf8String_create(thread, u8"12", sizeof(u8"12") - 1));
  testFixture(thread, 123, Arcadia_ImmutableUtf8String_create(thread, u8"123", sizeof(u8"123") - 1));
  testRoundTrip(thread);
}
