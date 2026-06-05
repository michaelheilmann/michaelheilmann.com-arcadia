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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEREADER_UNICODECODEPOINTREADER_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEREADER_UNICODECODEPOINTREADER_H_INCLUDED

#if !defined(ARCADIA_RING1_MODULE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Objects/UnicodeCodePointReader.h"
typedef struct Arcadia_ByteReader Arcadia_ByteReader;

/// @code
/// class Arcadia.ByteReader.UnicodeCodePointReader extends Arcadia.UnicodeCodePointReader {
///   construct(source:Arcadia.ByteReader)
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.ByteReader.UnicodeCodePointReader", Arcadia_ByteReader_UnicodeCodePointReader,
                          u8"Arcadia.UnicodeCodePointReader");

struct Arcadia_ByteReader_UnicodeCodePointReaderDispatch {
  Arcadia_UnicodeCodePointReaderDispatch _parent;
};

struct Arcadia_ByteReader_UnicodeCodePointReader {
  Arcadia_UnicodeCodePointReader parent;

  Arcadia_Natural32Value codePoint;
  Arcadia_SizeValue codePointByteLength;
  Arcadia_SizeValue codePointByteIndex;

  Arcadia_ByteReader* source;

  Arcadia_SizeValue numberOfBytes;
  Arcadia_Natural8Value bytes[4];
};

Arcadia_ByteReader_UnicodeCodePointReader*
Arcadia_ByteReader_UnicodeCodePointReader_create
  (
    Arcadia_Thread* thread,
    Arcadia_ByteReader* source
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEREADER_UNICODECODEPOINTREADER_H_INCLUDED
