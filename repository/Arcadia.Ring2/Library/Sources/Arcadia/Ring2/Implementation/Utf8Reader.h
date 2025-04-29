// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2025-02-15

#if !defined(ARCADIA_RING2_IMPLEMENTATION_UTF8READER_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_UTF8READER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Utf8Reader", Arcadia_Utf8Reader, u8"Arcadia.Object");

struct Arcadia_Utf8Reader {
  Arcadia_Object _parent;
  void (*next)(Arcadia_Thread*, Arcadia_Utf8Reader* self);
  Arcadia_Natural32Value (*getCodePoint)(Arcadia_Thread* thread, Arcadia_Utf8Reader* self);
  Arcadia_BooleanValue (*hasCodePoint)(Arcadia_Thread* thread, Arcadia_Utf8Reader* self);
  Arcadia_SizeValue (*getByteIndex)(Arcadia_Thread* thread, Arcadia_Utf8Reader* self);
};

void
Arcadia_Utf8Reader_next
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  );

Arcadia_Natural32Value
Arcadia_Utf8Reader_getCodePoint
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  );

Arcadia_BooleanValue
Arcadia_Utf8Reader_hasCodePoint
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  );

/// @return The index of the current Byte.
Arcadia_SizeValue
Arcadia_Utf8Reader_getByteIndex
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_UTF8READER_H_INCLUDED
