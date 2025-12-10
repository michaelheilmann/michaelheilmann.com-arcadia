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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_NUMBERLITERAL_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_NUMBERLITERAL_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Size.h"

typedef struct Arcadia_NumberLiteral_Sign {
  Arcadia_SizeValue start;
  Arcadia_SizeValue length;
} Arcadia_NumberLiteral_Sign;

typedef struct Arcadia_NumberLiteral_Fractional {
  Arcadia_SizeValue start;
  Arcadia_SizeValue length;
  struct {
    Arcadia_SizeValue start;
    Arcadia_SizeValue length;
  } trailingZeroes;
} Arcadia_NumberLiteral_Fractional;

typedef struct Arcadia_NumberLiteral_Integral {
  Arcadia_SizeValue start;
  Arcadia_SizeValue length;
  struct {
    Arcadia_SizeValue start;
    Arcadia_SizeValue length;
  } leadingZeroes;
} Arcadia_NumberLiteral_Integral;

typedef struct Arcadia_NumberLiteral_Exponent {
  Arcadia_SizeValue start;
  Arcadia_SizeValue length;
  Arcadia_NumberLiteral_Sign sign;
  struct {
    Arcadia_SizeValue start;
    Arcadia_SizeValue length;
  } powerSymbol;
  Arcadia_NumberLiteral_Integral integral;
} Arcadia_NumberLiteral_Exponent;

typedef struct Arcadia_NumberLiteral {
  struct {
    Arcadia_NumberLiteral_Sign sign;
    Arcadia_NumberLiteral_Integral integral;
    Arcadia_NumberLiteral_Fractional fractional;
    struct {
      Arcadia_SizeValue start;
      Arcadia_SizeValue length;
    } radixPoint;
  } significand;
  Arcadia_NumberLiteral_Exponent exponent;
} Arcadia_NumberLiteral;


Arcadia_BooleanValue
Arcadia_parseNumberLiteral
  (
    Arcadia_Thread* thread,
    Arcadia_NumberLiteral* result,
    const Arcadia_Natural8Value* bytes,
    Arcadia_SizeValue numberOfBytes
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_NUMBERLITERAL_H_INCLUDED
