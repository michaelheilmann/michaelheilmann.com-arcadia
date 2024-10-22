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

// Last modified: 2024-09-27

#include "R/Hash.h"

R_SizeValue
R_hashBooleanValue
  (
    R_BooleanValue x
  )
{ return x ? 1231 : 1237; }

R_SizeValue
R_hashForeignProcedureValue
  (
    R_ForeignProcedureValue x
  )
{
  return (R_SizeValue)(uintptr_t)x;
}

R_SizeValue
R_hashInteger16Value
  (
    R_Integer16Value x
  )
{
  return (R_SizeValue)x;
}

R_SizeValue
R_hashInteger32Value
  (
    R_Integer32Value x
  )
{
  return (R_SizeValue)x;
}

R_SizeValue
R_hashInteger64Value
  (
    R_Integer64Value x
  )
{
  return (R_SizeValue)x;
}

R_SizeValue
R_hashInteger8Value
  (
    R_Integer8Value x
  )
{
  return (R_SizeValue)x;
}

R_SizeValue
R_hashNatural16Value
  (
    R_Natural16Value x
  )
{
  return (R_SizeValue)x;
}

R_SizeValue
R_hashNatural32Value
  (
    R_Natural32Value x
  )
{
  return (R_SizeValue)x;
}

R_SizeValue
R_hashNatural64Value
  (
    R_Natural64Value x
  )
{
  return (R_SizeValue)x;
}

R_SizeValue
R_hashNatural8Value
  (
    R_Natural8Value x
  )
{
  return (R_SizeValue)x;
}

R_SizeValue
R_hashReal32Value
  (
    R_Real32Value x
  )
{
  if (x == 0.f) {
    x = +0.f;
  }
  typedef struct Union {
    R_Real32Value real32Value;
    R_Natural32Value natural32Value;
  } Union;
  Union v = { .real32Value = x };
  return R_hashNatural32Value(v.natural32Value);
}

R_SizeValue
R_hashReal64Value
  (
    R_Real64Value x
  )
{
  if (x == 0.) {
    x = +0.;
  }
  typedef struct Union {
    R_Real64Value real64Value;
    R_Natural64Value natural64Value;
  } Union;
  Union v = { .real64Value = x };
  return R_hashNatural64Value(v.natural64Value);
}

R_SizeValue
R_hashSizeValue
  (
    R_SizeValue x
  )
{
  return (R_SizeValue)x;
}


R_SizeValue
R_hashVoidValue
  (
    R_VoidValue x
  )
{
  return (R_SizeValue)71;
}
