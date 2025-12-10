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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/FileSystem/FileHandleExtensions.h"

#include "Arcadia/Ring2/FileSystem/FileHandle.h"
#include "Arcadia/Ring2/FileSystem/FileSystem.h"
#include "Arcadia/Ring2/Strings/String.h"
#include "Arcadia/Ring2/Strings/StringBuffer.h"

void
Arcadia_FileHandle_writeString
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_String* string
  )
{
  Arcadia_SizeValue bytesToWrite = Arcadia_String_getNumberOfBytes(thread, string), bytesWritten = 0;
  Arcadia_Natural8Value const* bytes = Arcadia_String_getBytes(thread, string);
  while (bytesToWrite > bytesWritten) {
    Arcadia_SizeValue bytesWritteNow = 0;
    Arcadia_FileHandle_write(thread, self, bytes + bytesWritten, bytesToWrite - bytesWritten, &bytesWritteNow);
    bytesWritten += bytesWritteNow;
  }
}

void
Arcadia_FileHandle_writeStringBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_SizeValue bytesToWrite = Arcadia_StringBuffer_getNumberOfBytes(thread, stringBuffer), bytesWritten = 0;
  Arcadia_Natural8Value const* bytes = Arcadia_StringBuffer_getBytes(thread, stringBuffer);
  while (bytesToWrite > bytesWritten) {
    Arcadia_SizeValue bytesWritteNow = 0;
    Arcadia_FileHandle_write(thread, self, bytes + bytesWritten, bytesToWrite - bytesWritten, &bytesWritteNow);
    bytesWritten += bytesWritteNow;
  }
}
