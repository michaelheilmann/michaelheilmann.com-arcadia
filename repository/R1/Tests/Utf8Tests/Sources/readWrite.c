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

// Last modified: 2024-08-27

#include "readWrite.h"

#include "R/Include.h"

/// @brief
/// - create a Byte buffer holding the sequence (source)
/// - create an empty Byte buffer (target)
/// - read its unicode code points using Utf8ByteBufferReader from source
/// - write each unicode code point into target using Utf8ByteBufferWriter
/// - compare the contents of both Byte buffer
/// - success if thes contents are equal
/// - failure otherwise
static void
onReadWrite
  (
    Arcadia_Process* process,
    char const* p,
    size_t n
  )
{
  Arcadia_ByteBuffer* sourceByteBuffer = Arcadia_ByteBuffer_create(process);
  Arcadia_ByteBuffer_append_pn(process, sourceByteBuffer, p, n);
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(process);
  Arcadia_Utf8Reader* reader = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(process, sourceByteBuffer);
  Arcadia_Utf8Writer* writer = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, targetByteBuffer);
  while (Arcadia_Utf8Reader_hasCodePoint(process, reader)) {
    Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(process, reader);
    Arcadia_Utf8Writer_writeCodePoints(process, writer, &codePoint, 1);
    Arcadia_Utf8Reader_next(process, reader);
  }
  if (!Arcadia_ByteBuffer_isEqualTo(process, sourceByteBuffer, targetByteBuffer)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
}

void
Arcadia_Tests_Utf8_readWrite1
  (
    Arcadia_Process* process
  )
{
  onReadWrite(process, u8"abc", sizeof(u8"abc") - 1);
  onReadWrite(process, u8"xyz", sizeof(u8"xyz") - 1);
}
