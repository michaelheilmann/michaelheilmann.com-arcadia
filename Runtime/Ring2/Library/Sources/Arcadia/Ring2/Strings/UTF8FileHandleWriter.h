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

#if !defined(ARCADIA_RING2_STRINGS_UTF8FILEHANDLEWRITER_H_INCLUDED)
#define ARCADIA_RING2_STRINGS_UTF8FILEHANDLEWRITER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Strings/UTF8Writer.h"

#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/FileSystem/FileHandle.h"

Arcadia_declareObjectType(u8"Arcadia.UTF8FileHandleReader", Arcadia_UTF8FileHandleWriter,
                          u8"Arcadia.UTF8Writer");

struct Arcadia_UTF8FileHandleWriter {
  Arcadia_UTF8Writer parent;
  Arcadia_FileHandle* target;
  Arcadia_ByteBuffer* temporary;
};

Arcadia_UTF8FileHandleWriter*
Arcadia_UTF8FileHandleWriter_create
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* target
  );

#endif // ARCADIA_RING2_STRINGS_UTF8FILEHANDLEWRITER_H_INCLUDED

