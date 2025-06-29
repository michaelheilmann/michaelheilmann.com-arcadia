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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/getNumberOfCores.h"

#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/Thread.h"

#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  // SYSTEM_INFO, GetSystemInfo
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  // sysconf
  #include <unistd.h>
#else
  #error("operating system not (yet) supported")
#endif

Arcadia_Natural64Value
Arcadia_getNumberOfCores
  (
    Arcadia_Thread* thread
  )
{
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
  if (systemInfo.dwNumberOfProcessors > Arcadia_Natural64Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_Natural64Value)systemInfo.dwNumberOfProcessors;
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  long temporary = sysconf(_SC_NPROCESSORS_ONLN);
  if (temporary < Arcadia_Natural64Value_Minimum || temporary > Arcadia_Natural64Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_Natural64Value)temporary;
#else
  #error("environment not (yet) supported")
#endif
}
