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

#include "Arcadia.Ring2.Tests.UTF8/readWrite.h"

#include "Arcadia/Ring2/Include.h"

/// @brief
/// - create a Byte buffer holding the sequence (source)
/// - create an empty Byte buffer (target)
/// - read its unicode code points using UTF8ByteBufferReader from source
/// - write each unicode code point into target using UTF8ByteBufferWriter
/// - compare the contents of both Byte buffers
/// - success if thes contents are equal
/// - failure otherwise
static void
onReadWriteTestFixture
  (
    Arcadia_Thread* thread,
    char const* p,
    size_t n
  )
{
  Arcadia_ByteArrayBuilder* sourceByteArrayBuilder = Arcadia_ByteArrayBuilder_create(thread);
  Arcadia_ByteArrayBuilder_insertBackBytes(thread, sourceByteArrayBuilder, p, n);
  Arcadia_ByteArrayBuilder* targetByteArrayBuilder = Arcadia_ByteArrayBuilder_create(thread);
  Arcadia_UnicodeCodePointReader* reader = (Arcadia_UnicodeCodePointReader*)Arcadia_ByteReader_UnicodeCodePointReader_create(thread, (Arcadia_ByteReader*)Arcadia_ByteArrayBuilder_ByteReader_create(thread, sourceByteArrayBuilder));

  Arcadia_Unicode_Encoder* writer = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);
  while (Arcadia_UnicodeCodePointReader_hasValue(thread, reader)) {
    Arcadia_Natural32Value codePoint = Arcadia_UnicodeCodePointReader_getValue(thread, reader);
    Arcadia_Unicode_Encoder_encodeCodePoints(thread, writer, &codePoint, 1, targetByteArrayBuilder);
    Arcadia_UnicodeCodePointReader_nextValue(thread, reader);
  }
  if (!Arcadia_ByteArrayBuilder_isEqualTo(thread, sourceByteArrayBuilder, targetByteArrayBuilder)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Tests_UTF8_readWrite1
  (
    Arcadia_Thread* thread
  )
{
  onReadWriteTestFixture(thread, u8"abc", sizeof(u8"abc") - 1);
  onReadWriteTestFixture(thread, u8"xyz", sizeof(u8"xyz") - 1);
}
