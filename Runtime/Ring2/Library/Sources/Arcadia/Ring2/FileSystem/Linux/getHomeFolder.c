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
#include "Arcadia/Ring2/FileSystem/Linux/getHomeFolder.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux || \
    Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Cygwin

  #include <string.h> // strlen
  #include <sys/stat.h> // stat
  #include <errno.h> // errno
  #include <linux/limits.h> // PATH_MAX
  #include <pwd.h> // struct passwd
  #include <sys/types.h>
  #include <fcntl.h>
  #include <unistd.h> // getcwd, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO

#endif

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux || \
    Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Cygwin

Arcadia_FilePath*
Arcadia_DefaultFileSystem_getHomeFolderHelper
  (
    Arcadia_Thread* thread,
    Arcadia_DefaultFileSystem* self
  )
{
  size_t n = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (n == -1) {
    n = 0x4000; // = all zeroes with the 14th bit set (1 << 14)
  }
  char* p = malloc(n);
  if (NULL == p) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  struct passwd pwd;
  struct passwd* ppwd;
  int s = getpwuid_r(getuid(), &pwd, p, n, &ppwd);
  if (ppwd == NULL) {
    // if s is 0 the no entry for this user id was found.
    free(p);
    p = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_FilePath* filePath = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_String* filePathString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, ppwd->pw_dir, strlen(ppwd->pw_dir))));
    filePath = Arcadia_FilePath_parseUnix(thread, filePathString);
    Arcadia_Thread_popJumpTarget(thread);
    free(p);
    p = NULL;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(p);
    p = NULL;
    Arcadia_Thread_jump(thread);
  }
  return filePath;
}

#endif
