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

// Last modified: 2024-09-27

#include "Arcadia/Ring1/Implementation/hash.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_SizeValue
Arcadia_hashAtomValue
  (
    Arcadia_AtomValue x
  )
{ return Arcadia_Atom_getHash(x); }

Arcadia_SizeValue
Arcadia_hashBooleanValue
  (
    Arcadia_BooleanValue x
  )
{ return x ? 1231 : 1237; }

Arcadia_SizeValue
Arcadia_hashForeignProcedureValue
  (
    Arcadia_ForeignProcedureValue x
  )
{
  return (Arcadia_SizeValue)(uintptr_t)x;
}

Arcadia_SizeValue
Arcadia_hashInteger16Value
  (
    Arcadia_Integer16Value x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashInteger32Value
  (
    Arcadia_Integer32Value x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashInteger64Value
  (
    Arcadia_Integer64Value x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashInteger8Value
  (
    Arcadia_Integer8Value x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashNatural16Value
  (
    Arcadia_Natural16Value x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashNatural32Value
  (
    Arcadia_Natural32Value x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashNatural64Value
  (
    Arcadia_Natural64Value x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashNatural8Value
  (
    Arcadia_Natural8Value x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashReal32Value
  (
    Arcadia_Real32Value x
  )
{
  if (x == 0.f) {
    x = +0.f;
  }
  typedef struct Union {
    Arcadia_Real32Value real32Value;
    Arcadia_Natural32Value natural32Value;
  } Union;
  Union v = { .real32Value = x };
  return Arcadia_hashNatural32Value(v.natural32Value);
}

Arcadia_SizeValue
Arcadia_hashReal64Value
  (
    Arcadia_Real64Value x
  )
{
  if (x == 0.) {
    x = +0.;
  }
  typedef struct Union {
    Arcadia_Real64Value real64Value;
    Arcadia_Natural64Value natural64Value;
  } Union;
  Union v = { .real64Value = x };
  return Arcadia_hashNatural64Value(v.natural64Value);
}

Arcadia_SizeValue
Arcadia_hashSizeValue
  (
    Arcadia_SizeValue x
  )
{
  return (Arcadia_SizeValue)x;
}

Arcadia_SizeValue
Arcadia_hashTypeValue
  (
    Arcadia_TypeValue x
  )
{
  return Arcadia_Type_hash(x);
}

Arcadia_SizeValue
Arcadia_hashVoidValue
  (
    Arcadia_VoidValue x
  )
{
  return (Arcadia_SizeValue)71;
}
