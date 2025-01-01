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

#include "R.h"

void
R1_Tests_Utf8_readWrite
  (
    Arcadia_Process* process,
    char const* p,
    size_t n
  )
{
  R_ByteBuffer* sourceByteBuffer = R_ByteBuffer_create(process);
  R_ByteBuffer_append_pn(process, sourceByteBuffer, p, n);
  R_ByteBuffer* targetByteBuffer = R_ByteBuffer_create(process);
  R_Utf8Reader* reader = (R_Utf8Reader*)R_Utf8ByteBufferReader_create(process, sourceByteBuffer);
  R_Utf8Writer* writer = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(process, targetByteBuffer);
  while (R_Utf8Reader_hasCodePoint(process, reader)) {
    Arcadia_Natural32Value codePoint = R_Utf8Reader_getCodePoint(process, reader);
    R_Utf8Writer_writeCodePoints(process, writer, &codePoint, 1);
    R_Utf8Reader_next(process, reader);
  }
  if (!R_ByteBuffer_isEqualTo(sourceByteBuffer, targetByteBuffer)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
}
