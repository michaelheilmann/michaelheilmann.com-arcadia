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

// Last modified: 2024-09-29

#include <stdlib.h>

#include "R.h"
#include "Module/Audials/Include.h"
#include "Module/Visuals/Include.h"
#include "Arcadia/Ring1/Include.h"

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char **argv
  )
{ 
  // (1) Initialize Audials.
  Audials_startup(process);
  
  // (2) Play sine wave.
  Audials_playSine(process);

  // (3) Create a window.
  NativeWindow* window = (NativeWindow*)NativeWindowsWindow_create(process);
  Arcadia_Object_lock(process, window);

  // (4) Ensure the window is opened.
  NativeWindow_open(process, window);
  
  Arcadia_Integer32Value width, height;
  NativeIcon* icon;

  // (5) Set the big icon.
  NativeWindow_getRequiredBigIconSize(window, &width, &height);
  icon = (NativeIcon*)NativeWindowsIcon_create(process, width, height, 47, 47, 47);
  NativeWindow_setBigIcon(window, icon);
  
  // (6) Set the small icon.
  NativeWindow_getRequiredSmallIconSize(window, &width, &height);
  icon = (NativeIcon*)NativeWindowsIcon_create(process, width, height, 47, 47, 47);
  NativeWindow_setSmallIcon(window, icon);

  // (7) Set the title.
  NativeWindow_setTitle(process, window, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, u8"Michael Heilmann's Liminality", sizeof(u8"Michael Heilmann's Liminality") - 1)));

  // (8) Enter the message loop.
  while (!NativeWindow_getQuitRequested(window)) {
    Arcadia_Process_stepArms(process);
    NativeWindow_update(window);
  }

  // (9) Ensure the window is closed.
  NativeWindow_close(process, window);

  // (10) Shutdown audials.
  // TODO: Causes a leak if not invoked.
  Audials_shutdown(process);

  Arcadia_Object_unlock(process, window);
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    R_shutdown();
    return EXIT_FAILURE;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  status[0] = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
