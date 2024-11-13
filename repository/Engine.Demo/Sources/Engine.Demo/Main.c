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

// Last modified: 2024-09-29

#include <stdlib.h>

#include "R.h"
#include "Module/Audials/Include.h"
#include "Module/Visuals/Include.h"

void
main1
  (
    int argc,
    char **argv
  )
{ 
  // (1) Initialize Audials.
  Audials_startup();
  
  // (2) Play sine wave.
  Audials_playSine();

  // (3) Create a window.
  NativeWindowsWindow* window = NativeWindowsWindow_create();

  // (4) Ensure the window is opened.
  NativeWindowsWindow_open(window);
  
  R_Integer32Value width, height;
  NativeWindowsIcon* icon;

  // (5) Set the big icon.
  NativeWindowsWindow_getRequiredBigIconSize(window, &width, &height);
  icon = NativeWindowsIcon_create(width, height, 47, 47, 47);
  NativeWindowsWindow_setBigIcon(window, icon);
  
  // (6) Set the small icon.
  NativeWindowsWindow_getRequiredSmallIconSize(window, &width, &height);
  icon = NativeWindowsIcon_create(width, height, 47, 47, 47);
  NativeWindowsWindow_setSmallIcon(window, icon);

  // (7) Set the title.
  NativeWindowsWindow_setTitle(window, R_String_create_pn("Michael Heilmann's Liminality", sizeof("Michael Heilmann's Liminality") - 1));

  // (8) Enter the message loop.
  while (!NativeWindowsWindow_getQuitRequested(window)) {
    NativeWindowsWindow_update(window);
  }

  // (9) Ensure the window is closed.
  NativeWindowsWindow_close(window);

  // (10) Shutdown audials.
  // TODO: Causes a leak if not invoked.
  Audials_shutdown();
}

int
main
  (
    int argc,
    char** argv
  )
{
  R_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    main1(argc, argv);
    R_popJumpTarget();
  }
  status[0] = R_getStatus();
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
