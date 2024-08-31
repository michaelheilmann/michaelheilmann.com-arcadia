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

#include "R/Boolean.h"
#include "R/Natural8.h"
#include "R/Size.h"

typedef struct R_String R_String;

void _R_String_registerType();

struct R_String {
  uint8_t* p;
  R_SizeValue sz;
};

// https://michaelheilmann.com/repository/R1/#r-string-create
R_String*
R_String_create
  (
    void const* bytes,
    R_SizeValue numberOfBytes
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

// https://michaelheilmann.com/repository/R1/#r-string-getsize
R_SizeValue
R_String_getSize
  (
    R_String const* self
  );

// https://michaelheilmann.com/repository/R1/#r-string-getat
R_Natural8Value
R_String_getAt
  (
    R_String const* self,
    R_SizeValue index
  );

#endif // R_STRING_H_INCLUDED
