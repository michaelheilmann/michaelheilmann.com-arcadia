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
#include "Arcadia/Ring2/FileSystem/Windows/getLocalFolder.h"

#include "Arcadia/Ring2/FileSystem/FilePath.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows

  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
  #include <Shlobj.h>

#endif

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows

Arcadia_FilePath*
Arcadia_DefaultFileSystem_getLocalFolderHelper
  (
    Arcadia_Thread* thread,
    Arcadia_DefaultFileSystem* self
  )
{
  PWSTR p = NULL;
  HRESULT hResult = SHGetKnownFolderPath(&FOLDERID_LocalAppData, 0, NULL, &p);
  if (FAILED(hResult)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  int iResult;
  iResult = WideCharToMultiByte(CP_UTF8, 0, p, -1, NULL, 0, NULL, NULL);
  if (!iResult) {
    CoTaskMemFree(p);
    p = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  char *q = malloc(sizeof(char) * iResult);
  if (!q) {
    CoTaskMemFree(p);
    p = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  iResult = WideCharToMultiByte(CP_UTF8, 0, p, -1, q, iResult, NULL, NULL);
  CoTaskMemFree(p);
  p = NULL;
  if (!iResult) {
    free(q);
    q = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_FilePath* filePath = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    filePath = Arcadia_FilePath_parseWindows(thread, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, q, iResult - 1))));
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
    Arcadia_Thread_jump(thread);
  }
  return filePath;
}

#endif
