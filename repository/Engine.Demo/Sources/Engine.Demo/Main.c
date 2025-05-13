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

#include <stdlib.h>

#include "Arcadia/Ring2/Include.h"
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
  Arcadia_Visuals_Application* application = NULL;
  Arcadia_Visuals_Window* window = NULL;
  Arcadia_BooleanValue audialsInitialized = Arcadia_BooleanValue_False;

  Arcadia_Thread* thread = Arcadia_Process_getThread(process);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
  #if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
    application = (Arcadia_Visuals_Application*)Arcadia_Visuals_Windows_Application_create(thread);
  #elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
    application = (Arcadia_Visuals_Application*)Arcadia_Visuals_Linux_Application_create(thread);
  #else
    #error("environment system not (yet) supported")
  #endif
    Arcadia_Object_lock(thread, (Arcadia_Object*)application);

    // (1) Initialize Audials.
    Audials_startup(thread);
    audialsInitialized = Arcadia_BooleanValue_True;

    // (2) Play sine wave.
    Audials_playSine(thread);

    // (3) Create a window.
    Arcadia_Visuals_Window* window = Arcadia_Visuals_Application_createWindow(thread, application);
    Arcadia_Object_lock(thread, (Arcadia_Object*)window);

    // (4) Ensure the window is opened.
    Arcadia_Visuals_Window_open(thread, window);

    Arcadia_Integer32Value width, height;
    Arcadia_Visuals_Icon* icon;

    // (5) Set the big icon.
    Arcadia_Visuals_Window_getRequiredBigIconSize(thread, window, &width, &height);
    icon = Arcadia_Visuals_Application_createIcon(thread, application, width, height, 47, 47, 47, 255);
    Arcadia_Visuals_Window_setBigIcon(thread, window, icon);

    // (6) Set the small icon.
    Arcadia_Visuals_Window_getRequiredSmallIconSize(thread, window, &width, &height);
    icon = Arcadia_Visuals_Application_createIcon(thread, application, width, height, 47, 47, 47, 255);
    Arcadia_Visuals_Window_setSmallIcon(thread, window, icon);

    // (7) Set the title.
    Arcadia_Visuals_Window_setTitle(thread, window, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"Michael Heilmann's Liminality", sizeof(u8"Michael Heilmann's Liminality") - 1)));

    // (8) Enter the message loop.
    while (!Arcadia_Visuals_Window_getQuitRequested(thread, window)) {
      Arcadia_Process_stepArms(process);
      Arcadia_Visuals_Window_update(thread, window);
      Arcadia_Visuals_Window_beginRender(thread, window);
      Arcadia_Visuals_Window_endRender(thread, window);
    }

    // (9) Ensure the window is closed.
    Arcadia_Visuals_Window_close(thread, window);

    if (audialsInitialized) {
      Audials_shutdown(thread);
      audialsInitialized = Arcadia_BooleanValue_False;
    }

    Arcadia_Thread_popJumpTarget(thread);

    if (window) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (application) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)application);
      application = NULL;
    }

  } else {
    Arcadia_Thread_popJumpTarget(thread);

    if (audialsInitialized) {
      Audials_shutdown(thread);
      audialsInitialized = Arcadia_BooleanValue_False;
    }

    if (window) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (application) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)application);
      application = NULL;
    }
  }
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
