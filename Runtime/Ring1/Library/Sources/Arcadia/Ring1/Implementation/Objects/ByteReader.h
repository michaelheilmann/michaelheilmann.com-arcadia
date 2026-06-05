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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEREADER_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEREADER_H_INCLUDED

#if !defined(ARCADIA_RING1_MODULE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Object.h"

Arcadia_declareObjectType(u8"Arcadia.ByteReader", Arcadia_ByteReader,
                          u8"Arcadia.Object");

struct Arcadia_ByteReaderDispatch {
  Arcadia_ObjectDispatch _parent;
  Arcadia_BooleanValue (*hasValue)(Arcadia_Thread*, Arcadia_ByteReader*);
  Arcadia_BooleanValue (*hasError)(Arcadia_Thread*, Arcadia_ByteReader*);
  Arcadia_Natural8Value (*getValue)(Arcadia_Thread*, Arcadia_ByteReader*);
  void (*nextValue)(Arcadia_Thread*, Arcadia_ByteReader*);
};

struct Arcadia_ByteReader {
  Arcadia_Object _parent;
};

Arcadia_BooleanValue
Arcadia_ByteReader_hasValue
  (
    Arcadia_Thread* thread,
    Arcadia_ByteReader* self
  );

Arcadia_BooleanValue
Arcadia_ByteReader_hasError
  (
    Arcadia_Thread* thread,
    Arcadia_ByteReader* self
  );

Arcadia_Natural8Value
Arcadia_ByteReader_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_ByteReader* self
  );

void
Arcadia_ByteReader_nextValue
  (
    Arcadia_Thread* thread,
    Arcadia_ByteReader* self
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEREADER_H_INCLUDED
