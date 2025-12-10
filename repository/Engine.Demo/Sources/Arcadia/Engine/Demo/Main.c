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

#include "Arcadia/Engine/Demo/Configuration.h"
#include <stdlib.h>

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Audials/Include.h"
#include "Arcadia/Visuals/Include.h"
#include "Arcadia/DDL/Include.h"

#include "Arcadia/Engine/Demo/Audials.h"
#include "Arcadia/Engine/Demo/Visuals.h"
// The application.
#include "Arcadia/Engine/Demo/Application.h"
// The main scene.
#include "Arcadia/Engine/Demo/Scenes/ArcadiaLogoScene.h"
#include "Arcadia/Engine/Demo/Scenes/MainScene.h"

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char **argv
  )
{
  Arcadia_Engine_Demo_Application* application = NULL;
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {

    Arcadia_Engine_Demo_Application* application1 = Arcadia_Engine_Demo_Application_create(thread);
    Arcadia_Object_lock(thread, (Arcadia_Object*)application1);
    application = application1;
    Arcadia_String* windowMode = NULL;
    Arcadia_Visuals_DisplayDevice* displayDevice = NULL;
    // (1) Startup visuals.
    Arcadia_Engine_Demo_startupVisuals(thread, application->engine, application->configuration, &displayDevice, &windowMode, &application->window);

    // (2) Startup audials.
    Arcadia_Engine_Demo_startupAudials(thread, application->engine, application->configuration);

    Arcadia_Engine_Demo_SceneManager_setScene(thread, application->sceneManager, (Arcadia_Engine_Demo_Scene*)Arcadia_Engine_Demo_ArcadiaLogoScene_create(thread, application->engine, application->sceneManager));


    Arcadia_Process_stepArms(process);

    // (8) Enter the message loop.
    Arcadia_Natural64Value oldTick, newTick, deltaTick;
    oldTick = Arcadia_getTickCount(thread);
    newTick = oldTick;
    deltaTick = (newTick > oldTick) ? newTick - oldTick : 0;
    while (!Arcadia_Engine_Demo_Application_getQuitRequested(thread, application)) {
      Arcadia_Process_stepArms(process);
      Arcadia_Audials_BackendContext_update(thread, (Arcadia_Audials_BackendContext*)application->engine->audialsBackendContext);
      Arcadia_Visuals_BackendContext_update(thread, (Arcadia_Visuals_BackendContext*)application->engine->visualsBackendContext);
      for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)application->windows); i < n; ++i) {
        Arcadia_Visuals_Window* window =
          (Arcadia_Visuals_Window*)
          Arcadia_List_getObjectReferenceValueCheckedAt
            (
              thread,
              application->windows,
              i,
              _Arcadia_Visuals_Window_getType(thread)
            );
        Arcadia_Visuals_Window_beginRender(thread, window);
        Arcadia_Visuals_Window_endRender(thread, window);
      }
      Arcadia_Visuals_Window_beginRender(thread, application->window);
      {
        Arcadia_Integer32Value width, height;
        Arcadia_Visuals_Window_getCanvasSize(thread, application->window, &width, &height);
        Arcadia_Engine_Demo_Scene_updateLogics(thread, Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager), deltaTick);
        Arcadia_Engine_Demo_Scene_updateAudials(thread, Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager), deltaTick, width, height);
        Arcadia_Engine_Demo_Scene_updateVisuals(thread, Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager), deltaTick, width, height);
      }
      Arcadia_Visuals_Window_endRender(thread, application->window);

      Arcadia_Engine_Event* event = Arcadia_Engine_dequeEvent(thread, application->engine);
      if (NULL != event) {
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_ApplicationQuitRequestedEvent_getType(thread))) {
          Arcadia_Visuals_ApplicationQuitRequestedEvent* applicationQuitRequestdEvent = (Arcadia_Visuals_ApplicationQuitRequestedEvent*)event;
          Arcadia_Engine_Demo_Application_onApplicationQuitRequestedEvent(thread, application, applicationQuitRequestdEvent);
        }
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_WindowClosedEvent_getType(thread))) {
          Arcadia_Visuals_WindowClosedEvent* windowClosedEvent = (Arcadia_Visuals_WindowClosedEvent*)event;
          Arcadia_Engine_Demo_Application_onWindowClosedEvent(thread, application, windowClosedEvent);
        }
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_KeyboardKeyEvent_getType(thread))) {
          Arcadia_Visuals_KeyboardKeyEvent* keyboardKeyEvent = (Arcadia_Visuals_KeyboardKeyEvent*)event;
          Arcadia_Engine_Demo_Application_onKeyboardKeyEvent(thread, application, keyboardKeyEvent);
        }
      }
      oldTick = newTick;
      newTick = Arcadia_getTickCount(thread);
      deltaTick = (newTick > oldTick) ? newTick - oldTick : 0;
    }

    // (9) Ensure the window is closed.
    Arcadia_Visuals_Window_close(thread, application->window);

    Cfg_saveConfiguration(thread, application->configuration);

    Arcadia_Thread_popJumpTarget(thread);

    // (10) Clean the message queue. FIXME: The messages prevent the engine from being gc'ed.
    while (Arcadia_Engine_dequeEvent(thread, application->engine)) {
      Arcadia_logf(Arcadia_LogFlags_Info, "%s:%d: purging message\n", __FILE__, __LINE__);
    }

    if (application->engine && application->engine->audialsBackendContext) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)application->engine->audialsBackendContext);
      application->engine->audialsBackendContext = NULL;
    }
    if (application->engine && application->engine->visualsBackendContext) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)application->engine->visualsBackendContext);
      application->engine->visualsBackendContext = NULL;
    }
    if (application) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)application);
      application = NULL;
    }
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (application) {
      if (application->window) {
        // (9) Ensure the window is closed.
        Arcadia_Visuals_Window_close(thread, application->window);
        application->window = NULL;
      }
      if (application->engine && application->engine->audialsBackendContext) {
        Arcadia_Object_unlock(thread, (Arcadia_Object*)application->engine->audialsBackendContext);
        application->engine->audialsBackendContext = NULL;
      }
      if (application->engine && application->engine->visualsBackendContext) {
        Arcadia_Object_unlock(thread, (Arcadia_Object*)application->engine->visualsBackendContext);
        application->engine->visualsBackendContext = NULL;
      }
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
