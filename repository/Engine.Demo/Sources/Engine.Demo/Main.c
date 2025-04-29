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

// Last modified: 2024-09-29

#include <stdlib.h>

#include "R/Include.h"
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
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);

  // (1) Initialize Audials.
  Audials_startup(thread);
  
  // (2) Play sine wave.
  Audials_playSine(thread);

  // (3) Create a window.
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  NativeWindow* window = (NativeWindow*)Windows_NativeWindow_create(thread);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  NativeWindow* window = (NativeWindow*)Linux_NativeWindow_create(thread);
#else
  #error("environment system not (yet) supported")
#endif
  Arcadia_Object_lock(thread, window);

  // (4) Ensure the window is opened.
  NativeWindow_open(thread, window);
  
  Arcadia_Integer32Value width, height;
  NativeIcon* icon;

  // (5) Set the big icon.
  NativeWindow_getRequiredBigIconSize(thread, window, &width, &height);
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  icon = (NativeIcon*)Windows_NativeIcon_create(thread, width, height, 47, 47, 47, 255);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  icon = (NativeIcon*)Linux_NativeIcon_create(thread, width, height, 47, 47, 47, 255);
#else
  #error("environment system not (yet) supported")
#endif
  NativeWindow_setBigIcon(thread, window, icon);
  
  // (6) Set the small icon.
  NativeWindow_getRequiredSmallIconSize(thread, window, &width, &height);
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  icon = (NativeIcon*)Windows_NativeIcon_create(thread, width, height, 47, 47, 47, 255);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  icon = (NativeIcon*)Linux_NativeIcon_create(thread, width, height, 47, 47, 47, 255);
#else
  #error("environment system not (yet) supported")
#endif
  NativeWindow_setSmallIcon(thread, window, icon);

  // (7) Set the title.
  NativeWindow_setTitle(thread, window, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"Michael Heilmann's Liminality", sizeof(u8"Michael Heilmann's Liminality") - 1)));

  // (8) Enter the message loop.
  while (!NativeWindow_getQuitRequested(thread, window)) {
    Arcadia_Process_stepArms(process);
    NativeWindow_update(thread, window);
    NativeWindow_beginRender(thread, window);
    NativeWindow_endRender(thread, window);
  }

  // (9) Ensure the window is closed.
  NativeWindow_close(thread, window);

  // (10) Shutdown audials.
  // TODO: Causes a leak if not invoked.
  Audials_shutdown(thread);

  Arcadia_Object_unlock(thread, window);
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
  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  Arcadia_Status status = Arcadia_Thread_getStatus(Arcadia_Process_getThread(process));
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
