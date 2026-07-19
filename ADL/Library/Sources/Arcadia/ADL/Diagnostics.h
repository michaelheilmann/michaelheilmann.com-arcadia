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

#if !defined(ARCADIA_ADL_DIAGNOSTICS_H_INCLUDED)
#define ARCADIA_ADL_DIAGNOSTICS_H_INCLUDED

#if !defined(ARCADIA_ADL_MODULE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/FileSystem/Include.h"
#include "Arcadia/ADL/Definition.h"

Arcadia_NoReturn() static inline void
Arcadia_ADL_Diagnostics_raiseNotAPixelBufferDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  )
{
  Arcadia_StringBuilder* message = Arcadia_StringBuilder_create(thread);
  Arcadia_StringBuilder_insertBackCxxString(thread, message, u8"ADL definition `");
  Arcadia_StringBuilder_insertBackString(thread, message, key);
  Arcadia_StringBuilder_insertBackCxxString(thread, message, u8"` is not a pixel buffer definition\n");

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);

  Arcadia_FileHandle_writeStringBuffer(thread, fileHandle, message);

  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

Arcadia_NoReturn() static inline void
Arcadia_ADL_Diagnostics_raisePixelBufferOperationNotYetSupported
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  )
{
  Arcadia_StringBuilder* message = Arcadia_StringBuilder_create(thread);
  Arcadia_StringBuilder_insertBackCxxString(thread, message, u8"ADL pixel buffer operation `");
  Arcadia_StringBuilder_insertBackString(thread, message, key);
  Arcadia_StringBuilder_insertBackCxxString(thread, message, u8"` is not (yet) supported\n");

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);

  Arcadia_FileHandle_writeStringBuffer(thread, fileHandle, message);

  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

Arcadia_NoReturn() static inline void
Arcadia_ADL_Diagnostics_raiseDefinitionNotFound
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  )
{
  Arcadia_StringBuilder* message = Arcadia_StringBuilder_create(thread);
  Arcadia_StringBuilder_insertBackCxxString(thread, message, u8"starting ADL definition `");
  Arcadia_StringBuilder_insertBackString(thread, message, key);
  Arcadia_StringBuilder_insertBackCxxString(thread, message, u8"` not found\n");

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);

  Arcadia_FileHandle_writeStringBuffer(thread, fileHandle, message);

  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

#endif  // ARCADIA_ADL_DIAGNOSTICS_H_INCLUDED
