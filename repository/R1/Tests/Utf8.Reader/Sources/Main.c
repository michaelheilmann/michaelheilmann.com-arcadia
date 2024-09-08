// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#include <stdlib.h>

#include "R.h"

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    R_setStatus(R_Status_TestFailed); \
    R_jump(); \
  }

static void utf8ReaderTest1() {
  R_ByteBuffer* sourceByteBuffer = R_ByteBuffer_create();
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
    R_ByteBuffer_append_pn(sourceByteBuffer, &sourceBytes[i], sizeof(uint8_t));
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

  R_Utf8Reader* reader = R_Utf8Reader_create(sourceByteBuffer);
  R_SizeValue numberOfReceivedCodePoints = 0;
  
  while (R_Utf8Reader_hasCodePoint(reader)) {
    R_Natural32Value receivedCodePoint = R_Utf8Reader_getCodePoint(reader);
    if (numberOfReceivedCodePoints >= numberOfExpectedCodePoints) {
      R_setStatus(R_Status_TestFailed);
      R_jump();
    }
    if (receivedCodePoint != expectedCodePoints[numberOfReceivedCodePoints]) {
      R_setStatus(R_Status_TestFailed);
      R_jump();
    }
    R_Utf8Reader_next(reader);
    numberOfReceivedCodePoints++;
  }
  if (numberOfReceivedCodePoints != numberOfExpectedCodePoints) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
}

static bool safeExecute(void (*f)()) {
  bool result = true;
  R_Status status = R_startup();
  if (status) {
    result = false;
    return result;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    (*f)();
  } else {
    result = false;
  }
  R_popJumpTarget();
  status = R_shutdown();
  if (status) {
    result = false;
  }
  return result;
}

int main(int argc, char **argv) {
  if (!safeExecute(&utf8ReaderTest1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
