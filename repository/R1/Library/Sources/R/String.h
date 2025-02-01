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

// Last modified: 2024-09-01

#if !defined(R_STRING_H_INCLUDED)
#define R_STRING_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

Rex_declareObjectType("Arcadia.String", Arcadia_String, "Arcadia.Object");

struct Arcadia_String {
  Arcadia_Object _parent;
  Arcadia_ImmutableByteArray* immutableByteArray;
  // We could compute this lazily if we had the "mutable" keyword in C.
  Arcadia_SizeValue hash;
};

// https://michaelheilmann.com/repository/R1/#r-string-create-pn
Arcadia_String*
Arcadia_String_create_pn
  (
    Arcadia_Process* process,
    Arcadia_ImmutableByteArray* immutableByteArray
  );

// https://michaelheilmann.com/repository/R1/#r-string-create
Arcadia_String*
Arcadia_String_create
  (
    Arcadia_Process* process,
    Arcadia_Value value
  );

// https://michaelheilmann.com/repository/R1/#r-string-endswith-pn
Arcadia_BooleanValue
Arcadia_String_endsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-startswith-pn
Arcadia_BooleanValue
Arcadia_String_startsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-getnumberofbytes
Arcadia_SizeValue
Arcadia_String_getNumberOfBytes
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

Arcadia_Natural8Value const*
Arcadia_String_getBytes
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-getbyteat
Arcadia_Natural8Value
Arcadia_String_getByteAt
  (
    Arcadia_Process* process,
    Arcadia_String const* self,
    Arcadia_SizeValue index
  );

// https://michaelheilmann.com/repository/R1/#r-string-getnumberofsymbols
Arcadia_SizeValue
Arcadia_String_getNumberOfSymbols
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

#if 0
// https://michaelheilmann.com/repository/R1/#r-string-getsubstring
Arcadia_String*
Arcadia_String_getSubString
  (
    Arcadia_String const* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue length
  );
#endif

// https://michaelheilmann.com/repository/R1/#r-string-isequalto-pn
Arcadia_BooleanValue
Arcadia_String_isEqualTo_pn
  (
    Arcadia_Process* process,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-toboolean
Arcadia_BooleanValue
Arcadia_String_toBoolean
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger16
Arcadia_Integer16Value
Arcadia_String_toInteger16
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger32
Arcadia_Integer32Value
Arcadia_String_toInteger32
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger64
Arcadia_Integer64Value
Arcadia_String_toInteger64
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger8
Arcadia_Integer8Value
Arcadia_String_toInteger8
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural16
Arcadia_Natural16Value
Arcadia_String_toNatural16
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatura32
Arcadia_Natural32Value
Arcadia_String_toNatural32
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural64
Arcadia_Natural64Value
Arcadia_String_toNatural64
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural8
Arcadia_Natural8Value
Arcadia_String_toNatural8
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-toreal32
Arcadia_Real32Value
Arcadia_String_toReal32
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-toreal64
Arcadia_Real64Value
Arcadia_String_toReal64
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-void
Arcadia_VoidValue
Arcadia_String_toVoid
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  );

#endif // R_STRING_H_INCLUDED
