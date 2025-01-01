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

#include "R/Object.h"
#include "R/Value.h"
#include "R/ImmutableByteArray.h"

Rex_declareObjectType("R.String", R_String, "R.Object");

struct R_String {
  R_Object _parent;
  Arcadia_ImmutableByteArray* immutableByteArray;
  // We could compute this lazily if we had the "mutable" keyword in C.
  Arcadia_SizeValue hash;
};

// https://michaelheilmann.com/repository/R1/#r-string-create-pn
R_String*
R_String_create_pn
  (
    Arcadia_Process* process,
    Arcadia_ImmutableByteArray* immutableByteArray
  );

// https://michaelheilmann.com/repository/R1/#r-string-create
R_String*
R_String_create
  (
    Arcadia_Process* process,
    R_Value value
  );

// https://michaelheilmann.com/repository/R1/#r-string-endswith-pn
Arcadia_BooleanValue
R_String_endsWith_pn
  (
    R_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-startswith-pn
Arcadia_BooleanValue
R_String_startsWith_pn
  (
    R_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-getnumberofbytes
Arcadia_SizeValue
R_String_getNumberOfBytes
  (
    R_String const* self
  );

Arcadia_Natural8Value const*
R_String_getBytes
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-getbyteat
Arcadia_Natural8Value
R_String_getByteAt
  (
    Arcadia_Process* process,
    R_String const* self,
    Arcadia_SizeValue index
  );

// https://michaelheilmann.com/repository/R1/#r-string-getnumberofsymbols
Arcadia_SizeValue
R_String_getNumberOfSymbols
  (
    R_String const* self
  );

#if 0
// https://michaelheilmann.com/repository/R1/#r-string-getsubstring
R_String*
R_String_getSubString
  (
    R_String const* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue length
  );
#endif

// https://michaelheilmann.com/repository/R1/#r-string-isequalto-pn
Arcadia_BooleanValue
R_String_isEqualTo_pn
  (
    R_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-toboolean
Arcadia_BooleanValue
R_String_toBoolean
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger16
Arcadia_Integer16Value
R_String_toInteger16
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger32
Arcadia_Integer32Value
R_String_toInteger32
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger64
Arcadia_Integer64Value
R_String_toInteger64
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger8
Arcadia_Integer8Value
R_String_toInteger8
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural16
Arcadia_Natural16Value
R_String_toNatural16
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatura32
Arcadia_Natural32Value
R_String_toNatural32
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural64
Arcadia_Natural64Value
R_String_toNatural64
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural8
Arcadia_Natural8Value
R_String_toNatural8
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-toreal32
Arcadia_Real32Value
R_String_toReal32
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-toreal64
Arcadia_Real64Value
R_String_toReal64
  (
    Arcadia_Process* process,
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-void
Arcadia_VoidValue
R_String_toVoid
  (
    Arcadia_Process* process,
    R_String const* self
  );

#endif // R_STRING_H_INCLUDED
