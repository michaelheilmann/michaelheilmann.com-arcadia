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

// Last modified: 2024-09-20

#include "R/getTickCount.h"

#include "R/Object.h"

#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  #include <time.h>
  #include <math.h> // round
#else
  #error("operating system not (yet) supported")
#endif

R_Natural64Value
R_getTickCount
  (
  )
{
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  return GetTickCount64();
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  // This is incorrect. It provides the time since some unspecified point in the past and not since the start of the process.
  struct timespec t;
  //t = (struct timespec *)malloc(sizeof(t)); 
  clock_gettime(CLOCK_MONOTONIC, &t);
  R_Natural64Value milliseconds = 0;
  // Nanoseconds to milliseconds.
  milliseconds = round(t.tv_nsec / 1.0e6);
  // Seconds to milliseconds.
  milliseconds += t.tv_sec*1000;
  return milliseconds;
#else
  #error("operating system not (yet) supported")
#endif
}
