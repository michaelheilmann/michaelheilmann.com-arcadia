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

#include "read.h"

#include "R.h"

void
R1_Tests_Utf8_read1
  (
    Arcadia_Process* process
  )
{
  R_ByteBuffer* sourceByteBuffer = R_ByteBuffer_create(process);
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
    R_ByteBuffer_append_pn(process, sourceByteBuffer, &sourceBytes[i], sizeof(uint8_t));
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

  R_Utf8Reader* reader = (R_Utf8Reader*)R_Utf8ByteBufferReader_create(process, sourceByteBuffer);
  Arcadia_SizeValue numberOfReceivedCodePoints = 0;

  while (R_Utf8Reader_hasCodePoint(process, reader)) {
    Arcadia_Natural32Value receivedCodePoint = R_Utf8Reader_getCodePoint(process, reader);
    if (numberOfReceivedCodePoints >= numberOfExpectedCodePoints) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
    if (receivedCodePoint != expectedCodePoints[numberOfReceivedCodePoints]) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
      Arcadia_Process_jump(process);
    }
    R_Utf8Reader_next(process, reader);
    numberOfReceivedCodePoints++;
  }
  if (numberOfReceivedCodePoints != numberOfExpectedCodePoints) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
}
