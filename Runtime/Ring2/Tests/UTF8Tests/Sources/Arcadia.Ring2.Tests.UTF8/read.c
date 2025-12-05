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

#include "Arcadia.Ring2.Tests.UTF8/read.h"

#include "Arcadia/Ring2/Include.h"

void
Arcadia_Tests_UTF8_read2
  (
    Arcadia_Thread* thread
  )
{
  // Test if the parser detects overlong UTF-8.
  // https://datatracker.ietf.org/doc/html/rfc3629#page-5
  Arcadia_ByteBuffer* sourceByteBuffer = Arcadia_ByteBuffer_create(thread);
  uint8_t sourceBytes[] = {
    0xC1,
    0xA1,
  };
  size_t numberOfSourceBytes = sizeof(sourceBytes) / sizeof(uint8_t);
  for (uint8_t i = 0, n = numberOfSourceBytes; i < n; ++i) {
    Arcadia_ByteBuffer_insertBackBytes(thread, sourceByteBuffer, &sourceBytes[i], sizeof(uint8_t));
  }
  Arcadia_UTF8Reader* reader = (Arcadia_UTF8Reader*)Arcadia_UTF8ByteBufferReader_create(thread, sourceByteBuffer);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    while (Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
      Arcadia_UTF8Reader_getCodePoint(thread, reader);
      Arcadia_UTF8Reader_next(thread, reader);
    }
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
  }
}


void
Arcadia_Tests_UTF8_read1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_ByteBuffer* sourceByteBuffer = Arcadia_ByteBuffer_create(thread);
  uint8_t sourceBytes[] = {
    'a',
    'b',
    'y',
    'z',
    0xCF, 0x80, // "GREEK SMALL LETTER PI"/U+03C0/https://www.fileformat.info/info/unicode/char/03c0/index.htm
    0xE2, 0x80, 0x93, // "EN DASH"/U+2013/https://www.fileformat.info/info/unicode/char/2013/index.htm

  };
  size_t numberOfSourceBytes = sizeof(sourceBytes) / sizeof(uint8_t);
  for (uint8_t i = 0, n = numberOfSourceBytes; i < n; ++i) {
    Arcadia_ByteBuffer_insertBackBytes(thread, sourceByteBuffer, &sourceBytes[i], sizeof(uint8_t));
  }

  uint32_t expectedCodePoints[] = {
    'a',
    'b',
    'y',
    'z',
    0x3c0, // "GREEK SMALL LETTER PI"/U+03C0/https://www.fileformat.info/info/unicode/char/03c0/index.htm
    0x2013, // "EN DASH"/U+2013/https://www.fileformat.info/info/unicode/char/2013/index.htm
  };
  size_t numberOfExpectedCodePoints = sizeof(expectedCodePoints) / sizeof(uint32_t);

  Arcadia_UTF8Reader* reader = (Arcadia_UTF8Reader*)Arcadia_UTF8ByteBufferReader_create(thread, sourceByteBuffer);
  Arcadia_SizeValue numberOfReceivedCodePoints = 0;

  while (Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    Arcadia_Natural32Value receivedCodePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
    if (numberOfReceivedCodePoints >= numberOfExpectedCodePoints) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    }
    if (receivedCodePoint != expectedCodePoints[numberOfReceivedCodePoints]) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_UTF8Reader_next(thread, reader);
    numberOfReceivedCodePoints++;
  }
  if (numberOfReceivedCodePoints != numberOfExpectedCodePoints) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
}
