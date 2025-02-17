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

// Last modified: 2024-10-18

#include <stdlib.h>
#include <string.h>
#include "R/Include.h"

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  Arcadia_String* s = Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"Hello, World!\n", sizeof(u8"Hello, World!\n") - 1));
  Arcadia_Object_lock(process, s);
  Arcadia_Process_stepArms(process);
  Arcadia_Process_stepArms(process);
  Arcadia_Object_unlock(process, s);
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  Arcadia_Status status = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
