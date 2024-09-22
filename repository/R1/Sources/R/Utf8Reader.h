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

// Last modified: 2024-09-20

#if !defined(R_UTF8READER_H_INCLUDED)
#define R_UTF8READER_H_INCLUDED

#include "R/Boolean.h"
#include "R/Natural32.h"
#include "R/Size.h"

#define R_UTF8READER(x) ((R_Utf8Reader*)(x))
typedef struct R_Utf8Reader R_Utf8Reader;
void _R_Utf8Reader_registerType();

struct R_Utf8Reader {
  void (*next)(R_Utf8Reader* self);
  R_Natural32Value (*getCodePoint)(R_Utf8Reader* self);
  R_BooleanValue (*hasCodePoint)(R_Utf8Reader* self);
  R_SizeValue (*getByteIndex)(R_Utf8Reader* self);
};

void
R_Utf8Reader_construct
  (
    R_Utf8Reader* self
  );

void
R_Utf8Reader_next
  (
    R_Utf8Reader* self
  );

R_Natural32Value
R_Utf8Reader_getCodePoint
  (
    R_Utf8Reader* self
  );

R_BooleanValue
R_Utf8Reader_hasCodePoint
  (
    R_Utf8Reader* self
  );

/// @return The index of the current Byte.
R_SizeValue
R_Utf8Reader_getByteIndex
  (
    R_Utf8Reader* self
  );

#endif // R_UTF8READER_H_INCLUDED
