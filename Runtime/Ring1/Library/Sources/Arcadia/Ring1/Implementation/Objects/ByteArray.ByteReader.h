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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAY_BYTEREADER_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAY_BYTEREADER_H_INCLUDED

#if !defined(ARCADIA_RING1_MODULE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Objects/ByteReader.h"
typedef struct Arcadia_ByteArray Arcadia_ByteArray;

Arcadia_declareObjectType(u8"Arcadia.ByteArray.ByteReader", Arcadia_ByteArray_ByteReader,
                          u8"Arcadia.ByteReader");

struct Arcadia_ByteArray_ByteReaderDispatch {
  Arcadia_ByteReaderDispatch _parent;
};

struct Arcadia_ByteArray_ByteReader {
  Arcadia_ByteReader _parent;
  Arcadia_ByteArray* source;
  Arcadia_SizeValue index;
};

Arcadia_ByteArray_ByteReader*
Arcadia_ByteArray_ByteReader_create
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray* source
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAY_BYTEREADER_H_INCLUDED
