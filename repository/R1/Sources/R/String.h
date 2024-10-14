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

// Last modified: 2024-09-01

#if !defined(R_STRING_H_INCLUDED)
#define R_STRING_H_INCLUDED

#include "R/Object.h"
#include "R/Value.h"

Rex_declareObjectType("R.String", R_String, "R.Object");

struct R_String {
  R_Object _parent;
  R_Natural8Value* p;
  R_SizeValue numberOfBytes;
  // We could compute this lazily if we had the "mutable" keyword in C.
  R_SizeValue hash;
};

void
R_String_construct_pn
  (
    R_String* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-create-pn
R_String*
R_String_create_pn
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

void
R_String_construct
  (
    R_String* self,
    R_Value value
  );

// https://michaelheilmann.com/repository/R1/#r-string-create
R_String*
R_String_create
  (
    R_Value value
  );

// https://michaelheilmann.com/repository/R1/#r-string-endswith-pn
R_BooleanValue
R_String_endsWith_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-startswith-pn
R_BooleanValue
R_String_startsWith_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-isequalto
R_BooleanValue
R_String_isEqualTo
  (
    R_String const* self,
    R_String const* other
  );

// https://michaelheilmann.com/repository/R1/#r-string-getnumberofbytes
R_SizeValue
R_String_getNumberOfBytes
  (
    R_String const* self
  );

R_Natural8Value const*
R_String_getBytes
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-getbyteat
R_Natural8Value
R_String_getByteAt
  (
    R_String const* self,
    R_SizeValue index
  );

R_SizeValue
R_String_getHash
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-getnumberofsymbols
R_SizeValue
R_String_getNumberOfSymbols
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-getsubstring
R_String*
R_String_getSubString
  (
    R_String const* self,
    R_SizeValue index,
    R_SizeValue length
  );

// https://michaelheilmann.com/repository/R1/#r-string-isequalto-pn
R_BooleanValue
R_String_isEqualTo_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger8
R_Integer8Value
R_String_toInteger8
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger16
R_Integer16Value
R_String_toInteger16
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger32
R_Integer32Value
R_String_toInteger32
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tointeger64
R_Integer64Value
R_String_toInteger64
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural8
R_Integer8Value
R_String_toNatural8
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural16
R_Natural16Value
R_String_toNatural16
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatura32
R_Natural32Value
R_String_toNatural32
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-tonatural64
R_Natural64Value
R_String_toNatural64
  (
    R_String const* self
  );

#endif // R_STRING_H_INCLUDED
