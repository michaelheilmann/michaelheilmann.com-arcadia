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

// Last modified: 2024-09-28

#include <stdlib.h>

#include "Arcadia/Ring1/Include.h"

#define Define(Type, A, B, H, L) \
{ \
  Arcadia_##Type##Value h, l; \
  Arcadia_safeMultiply##Type##Value(thread, A, B, &h, &l); \
  Arcadia_Tests_assertTrue (thread, h == H); \
  Arcadia_Tests_assertTrue (thread, l == L); \
}

static void
safeMultiplyNatural8Tests
  (
    Arcadia_Thread* thread
  )
{
  // 0 * 0 = (0, 0)
  Define(Natural8, 0, 0, 0, 0);
  // MAX * 0 = (0, 0)
  Define(Natural8, Arcadia_Natural8Value_Maximum, 0, 0, 0);
  // 0 * MAX = (0, 0)
  Define(Natural8, 0, Arcadia_Natural8Value_Maximum, 0, 0);
  // MAX * 1 = (MAX, 0)
  Define(Natural8, Arcadia_Natural8Value_Maximum, 1, 0, Arcadia_Natural8Value_Maximum);
  // 1 * MAX = (MAX, 0)
  Define(Natural8, 1, Arcadia_Natural8Value_Maximum, 0, Arcadia_Natural8Value_Maximum);
  static const Arcadia_SizeValue bits = 8;
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural8Value lower, upper;
    Arcadia_Natural8Value u, v;
    // The lower Arcadia_Natural8 value.
    // All bits are one except for the LSB.
    lower = Arcadia_Natural8Value_Maximum;
    Arcadia_Natural8Value mask = Arcadia_makeBitmaskN8(thread, bits - 1, 1);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural8 value.
    // All bits are zero except for the LSB.
    upper = 1;
    // MAX * 2 = (lower, upper)
    Arcadia_safeMultiplyNatural8Value(thread, Arcadia_Natural8Value_Maximum, 2, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural8Value lower, upper;
    Arcadia_Natural8Value u, v;
    // The lower Arcadia_Natural8 value.
    // All bits are one except for the LSB.
    lower = Arcadia_Natural8Value_Maximum;
    Arcadia_Natural8Value mask = Arcadia_makeBitmaskN8(thread, bits - 1, 1);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural8 value.
    // All bits are zero except for the LSB.
    upper = 1;
    // 2 * MAX = (lower, upper))
    Arcadia_safeMultiplyNatural8Value(thread, 2, Arcadia_Natural8Value_Maximum, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural8Value upper, lower;
    Arcadia_Natural8Value u, v;
    // The lower Arcadia_Natural8 value.
    // All bits are one except for LSB + 0 and LSB + 1.
    lower = Arcadia_Natural8Value_Maximum;
    Arcadia_Natural8Value mask = Arcadia_makeBitmaskN8(thread, bits - 2, 2);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural16 value.
    // All bits are zero except for LSB + 0 and LSB + 1.
    upper = 3;
    // MAX * 4 = (lower, upper)
    Arcadia_safeMultiplyNatural8Value(thread, Arcadia_Natural8Value_Maximum, 4, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural8Value upper, lower;
    Arcadia_Natural8Value u, v;
    // The lower Arcadia_Natural8 value.
    // All bits are one except for LSB + 0 and LSB + 1.
    lower = Arcadia_Natural8Value_Maximum;
    Arcadia_Natural8Value mask = Arcadia_makeBitmaskN8(thread, bits - 2, 2);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural16 value.
    // All bits are zero except for LSB + 0 and LSB + 1.
    upper = 3;
    // 4 * MAX = (lower, upper)
    Arcadia_safeMultiplyNatural8Value(thread, 4, Arcadia_Natural8Value_Maximum, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
}

static void
safeMultiplyNatural16Tests
  (
    Arcadia_Thread* thread
  )
{
  // 0 * 0 = (0, 0)
  Define(Natural16, 0, 0, 0, 0);
  // MAX * 0 = (0, 0)
  Define(Natural16, Arcadia_Natural16Value_Maximum, 0, 0, 0);
  // 0 * MAX = (0, 0)
  Define(Natural16, 0, Arcadia_Natural16Value_Maximum, 0, 0);
  // MAX * 1 = (MAX, 0)
  Define(Natural16, Arcadia_Natural16Value_Maximum, 1, 0, Arcadia_Natural16Value_Maximum);
  // 1 * MAX = (MAX, 0)
  Define(Natural16, 1, Arcadia_Natural16Value_Maximum, 0, Arcadia_Natural16Value_Maximum);
  static const Arcadia_SizeValue bits = 16;
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural16Value lower, upper;
    Arcadia_Natural16Value u, v;
    // The lower Arcadia_Natural8 value.
    // All bits are one except for the LSB.
    lower = Arcadia_Natural16Value_Maximum;
    Arcadia_Natural16Value mask = Arcadia_makeBitmaskN16(thread, bits - 1, 1);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural8 value.
    // All bits are zero except for the LSB.
    upper = 1;
    // MAX * 2 = (lower, upper)
    Arcadia_safeMultiplyNatural16Value(thread, Arcadia_Natural16Value_Maximum, 2, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural16Value lower, upper;
    Arcadia_Natural16Value u, v;
    // The lower Arcadia_Natural8 value.
    // All bits are one except for the LSB.
    lower = Arcadia_Natural16Value_Maximum;
    Arcadia_Natural16Value mask = Arcadia_makeBitmaskN16(thread, bits - 1, 1);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural8 value.
    // All bits are zero except for the LSB.
    upper = 1;
    // 2 * MAX = (lower, upper))
    Arcadia_safeMultiplyNatural16Value(thread, 2, Arcadia_Natural16Value_Maximum, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural16Value upper, lower;
    Arcadia_Natural16Value u, v;
    // The lower Arcadia_Natural16 value.
    // All bits are one except for LSB + 0 and LSB + 1.
    lower = Arcadia_Natural16Value_Maximum;
    Arcadia_Natural16Value mask = Arcadia_makeBitmaskN16(thread, bits - 2, 2);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural16 value.
    // All bits are zero except for LSB + 0 and LSB + 1.
    upper = 3;
    // MAX * 4 = (lower, upper)
    Arcadia_safeMultiplyNatural16Value(thread, Arcadia_Natural16Value_Maximum, 4, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural16Value upper, lower;
    Arcadia_Natural16Value u, v;
    // The lower Arcadia_Natural16 value.
    // All bits are one except for LSB + 0 and LSB + 1.
    lower = Arcadia_Natural16Value_Maximum;
    Arcadia_Natural16Value mask = Arcadia_makeBitmaskN16(thread, bits - 2, 2);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural16 value.
    // All bits are zero except for LSB + 0 and LSB + 1.
    upper = 3;
    // 4 * MAX = (lower, upper)
    Arcadia_safeMultiplyNatural16Value(thread, 4, Arcadia_Natural16Value_Maximum, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
}

static void
safeMultiplyNatural32Tests
  (
    Arcadia_Thread* thread
  )
{
  // 0 * 0 = (0, 0)
  Define(Natural32, 0, 0, 0, 0);
  // MAX * 0 = (0, 0)
  Define(Natural32, Arcadia_Natural32Value_Maximum, 0, 0, 0);
  // 0 * MAX = (0, 0)
  Define(Natural32, 0, Arcadia_Natural32Value_Maximum, 0, 0);
  // MAX * 1 = (MAX, 0)
  Define(Natural32, Arcadia_Natural32Value_Maximum, 1, 0, Arcadia_Natural32Value_Maximum);
  // 1 * MAX = (MAX, 0)
  Define(Natural32, 1, Arcadia_Natural32Value_Maximum, 0, Arcadia_Natural32Value_Maximum);
  static const Arcadia_SizeValue bits = 32;
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural32Value lower, upper;
    Arcadia_Natural32Value u, v;
    // The lower Arcadia_Natural32 value.
    // All bits are one except for the LSB.
    lower = Arcadia_Natural32Value_Maximum;
    Arcadia_Natural32Value mask = Arcadia_makeBitmaskN32(thread, bits - 1, 1);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural32 value.
    // All bits are zero except for the LSB.
    upper = 1;
    // MAX * 2 = (lower, upper)
    Arcadia_safeMultiplyNatural32Value(thread, Arcadia_Natural32Value_Maximum, 2, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural32Value lower, upper;
    Arcadia_Natural32Value u, v;
    // The lower Arcadia_Natural32 value.
    // All bits are one except for the LSB.
    lower = Arcadia_Natural32Value_Maximum;
    Arcadia_Natural32Value mask = Arcadia_makeBitmaskN32(thread, bits - 1, 1);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural32 value.
    // All bits are zero except for the LSB.
    upper = 1;
    // 2 * MAX = (lower, upper))
    Arcadia_safeMultiplyNatural32Value(thread, 2, Arcadia_Natural32Value_Maximum, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural32Value upper, lower;
    Arcadia_Natural32Value u, v;
    // The lower Arcadia_Natural32 value.
    // All bits are one except for LSB + 0 and LSB + 1.
    lower = Arcadia_Natural32Value_Maximum;
    Arcadia_Natural32Value mask = Arcadia_makeBitmaskN32(thread, bits - 2, 2);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural32 value.
    // All bits are zero except for LSB + 0 and LSB + 1.
    upper = 3;
    // MAX * 4 = (lower, upper)
    Arcadia_safeMultiplyNatural32Value(thread, Arcadia_Natural32Value_Maximum, 4, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural32Value upper, lower;
    Arcadia_Natural32Value u, v;
    // The lower Arcadia_Natural32 value.
    // All bits are one except for LSB + 0 and LSB + 1.
    lower = Arcadia_Natural32Value_Maximum;
    Arcadia_Natural32Value mask = Arcadia_makeBitmaskN32(thread, bits - 2, 2);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural32 value.
    // All bits are zero except for LSB + 0 and LSB + 1.
    upper = 3;
    // 4 * MAX = (lower, upper)
    Arcadia_safeMultiplyNatural32Value(thread, 4, Arcadia_Natural32Value_Maximum, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
}

static void
safeMultiplyNatural64Tests
  (
    Arcadia_Thread* thread
  )
{
  // 0 * 0 = (0, 0)
  Define(Natural64, 0, 0, 0, 0);
  // MAX * 0 = (0, 0)
  Define(Natural64, Arcadia_Natural64Value_Maximum, 0, 0, 0);
  // 0 * MAX = (0, 0)
  Define(Natural64, 0, Arcadia_Natural64Value_Maximum, 0, 0);
  // MAX * 1 = (MAX, 0)
  Define(Natural64, Arcadia_Natural64Value_Maximum, 1, 0, Arcadia_Natural64Value_Maximum);
  // 1 * MAX = (MAX, 0)
  Define(Natural64, 1, Arcadia_Natural64Value_Maximum, 0, Arcadia_Natural64Value_Maximum);
  static const Arcadia_SizeValue bits = 64;
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural64Value lower, upper;
    Arcadia_Natural64Value u, v;
    // The lower Arcadia_Natural64 value.
    // All bits are one except for the LSB.
    lower = Arcadia_Natural64Value_Maximum;
    Arcadia_Natural64Value mask = Arcadia_makeBitmaskN64(thread, bits - 1, 1);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural64 value.
    // All bits are zero except for the LSB.
    upper = 1;
    // MAX * 2 = (lower, upper)
    Arcadia_safeMultiplyNatural64Value(thread, Arcadia_Natural64Value_Maximum, 2, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural64Value lower, upper;
    Arcadia_Natural64Value u, v;
    // The lower Arcadia_Natural64 value.
    // All bits are one except for the LSB.
    lower = Arcadia_Natural64Value_Maximum;
    Arcadia_Natural64Value mask = Arcadia_makeBitmaskN64(thread, bits - 1, 1);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural64 value.
    // All bits are zero except for the LSB.
    upper = 1;
    // 2 * MAX = (lower, upper))
    Arcadia_safeMultiplyNatural64Value(thread, 2, Arcadia_Natural64Value_Maximum, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural64Value upper, lower;
    Arcadia_Natural64Value u, v;
    // The lower Arcadia_Natural64 value.
    // All bits are one except for LSB + 0 and LSB + 1.
    lower = Arcadia_Natural64Value_Maximum;
    Arcadia_Natural64Value mask = Arcadia_makeBitmaskN64(thread, bits - 2, 2);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural64 value.
    // All bits are zero except for LSB + 0 and LSB + 1.
    upper = 3;
    // MAX * 4 = (lower, upper)
    Arcadia_safeMultiplyNatural64Value(thread, Arcadia_Natural64Value_Maximum, 4, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  {
    Arcadia_Natural64Value upper, lower;
    Arcadia_Natural64Value u, v;
    // The lower Arcadia_Natural64 value.
    // All bits are one except for LSB + 0 and LSB + 1.
    lower = Arcadia_Natural64Value_Maximum;
    Arcadia_Natural64Value mask = Arcadia_makeBitmaskN64(thread, bits - 2, 2);
    mask = ~mask;
    lower &= mask;
    // The upper Arcadia_Natural64 value.
    // All bits are zero except for LSB + 0 and LSB + 1.
    upper = 3;
    // 4 * MAX = (lower, upper)
    Arcadia_safeMultiplyNatural64Value(thread, 4, Arcadia_Natural64Value_Maximum, &v, &u);
    Arcadia_Tests_assertTrue(thread, u == lower);
    Arcadia_Tests_assertTrue(thread, v == upper);
  }
  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
}

#undef Define

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&safeMultiplyNatural16Tests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&safeMultiplyNatural32Tests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&safeMultiplyNatural64Tests)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&safeMultiplyNatural8Tests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
