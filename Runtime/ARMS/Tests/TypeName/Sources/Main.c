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

// EXIT_SUCCESS, EXIT_FAILURE
#include <stdlib.h>
// strlen
#include <string.h>

#include "Arcadia/ARMS/Include.h"

static Arcadia_ARMS_Status
check1
  (
  ) 
{
  Arcadia_ARMS_TypeName* a, * b;
  if (Arcadia_ARMS_TypeName_getOrCreate(&a, u8"a", strlen(u8"a"))) {
    return Arcadia_ARMS_Status_EnvironmentFailed;
  }
  if (Arcadia_ARMS_TypeName_getOrCreate(&b, u8"a", strlen(u8"a"))) {
    Arcadia_ARMS_shutdown();
    return Arcadia_ARMS_Status_EnvironmentFailed;
  }
  if (a != b) {
    return Arcadia_ARMS_Status_EnvironmentFailed;
  }
  return Arcadia_ARMS_Status_Success;
}

static Arcadia_ARMS_Status
check2
  (
  )
{
  Arcadia_ARMS_TypeName* a, * b;
  if (Arcadia_ARMS_TypeName_getOrCreate(&a, u8"a", strlen(u8"a"))) {
    return Arcadia_ARMS_Status_EnvironmentFailed;
  }
  if (Arcadia_ARMS_TypeName_getOrCreate(&b, u8"b", strlen(u8"b"))) {
    Arcadia_ARMS_shutdown();
    return Arcadia_ARMS_Status_EnvironmentFailed;
  }
  if (a == b) {
    return Arcadia_ARMS_Status_EnvironmentFailed;
  }
  return Arcadia_ARMS_Status_Success;
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (Arcadia_ARMS_startup()) {
    return EXIT_FAILURE;
  }
  if (check1()) {
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  if (check2()) {
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  Arcadia_ARMS_shutdown();
  return EXIT_SUCCESS;
}
