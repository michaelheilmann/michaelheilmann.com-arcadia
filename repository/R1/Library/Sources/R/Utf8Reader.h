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

// Last modified: 2024-09-20

#if !defined(R_UTF8READER_H_INCLUDED)
#define R_UTF8READER_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "R/Object.h"
#include "Arcadia/Ring1/Implementation/Size.h"

Rex_declareObjectType(u8"R.Utf8Reader", R_Utf8Reader, u8"R.Object");

struct R_Utf8Reader {
  R_Object _parent;
  void (*next)(Arcadia_Process*, R_Utf8Reader* self);
  Arcadia_Natural32Value (*getCodePoint)(Arcadia_Process*, R_Utf8Reader* self);
  Arcadia_BooleanValue (*hasCodePoint)(Arcadia_Process*, R_Utf8Reader* self);
  Arcadia_SizeValue (*getByteIndex)(R_Utf8Reader* self);
};

void
R_Utf8Reader_next
  (
    Arcadia_Process* process,
    R_Utf8Reader* self
  );

Arcadia_Natural32Value
R_Utf8Reader_getCodePoint
  (
    Arcadia_Process* process,
    R_Utf8Reader* self
  );

Arcadia_BooleanValue
R_Utf8Reader_hasCodePoint
  (
    Arcadia_Process* process,
    R_Utf8Reader* self
  );

/// @return The index of the current Byte.
Arcadia_SizeValue
R_Utf8Reader_getByteIndex
  (
    R_Utf8Reader* self
  );

#endif // R_UTF8READER_H_INCLUDED
