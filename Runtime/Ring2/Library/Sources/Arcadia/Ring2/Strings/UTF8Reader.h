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

#if !defined(ARCADIA_RING2_STRINGS_UTF8READER_H_INCLUDED)
#define ARCADIA_RING2_STRINGS_UTF8READER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

/// @brief An UTF8 reader for possible infinite streams of UTF8 Bytes.
Arcadia_declareObjectType(u8"Arcadia.UTF8Reader", Arcadia_UTF8Reader,
                          u8"Arcadia.Object");

struct Arcadia_UTF8ReaderDispatch {
  Arcadia_ObjectDispatch _parent;
  void (*next)(Arcadia_Thread*, Arcadia_UTF8Reader* self);
  Arcadia_Natural32Value(*getCodePoint)(Arcadia_Thread* thread, Arcadia_UTF8Reader* self);
  Arcadia_BooleanValue(*hasCodePoint)(Arcadia_Thread* thread, Arcadia_UTF8Reader* self);
  Arcadia_Natural32Value(*getLength)(Arcadia_Thread* thread, Arcadia_UTF8Reader* self);
};

struct Arcadia_UTF8Reader {
  Arcadia_Object _parent;
};

void
Arcadia_UTF8Reader_next
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* self
  );

Arcadia_Natural32Value
Arcadia_UTF8Reader_getCodePoint
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* self
  );

Arcadia_BooleanValue
Arcadia_UTF8Reader_hasCodePoint
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* self
  );

/// @return The length, in Bytes, of the code point in UTF8.
Arcadia_Natural32Value
Arcadia_UTF8Reader_getLength
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* self
  );

#endif // ARCADIA_RING2_STRINGS_UTF8READER_H_INCLUDED
