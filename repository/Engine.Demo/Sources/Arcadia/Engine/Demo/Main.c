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
#include "Arcadia/Engine/Demo/Audials.h"
#include "Arcadia/Engine/Demo/Visuals.h"
#include <stdlib.h>

#include "Arcadia/DDL/Include.h"

// The demo's application.
#include "Arcadia/Engine/Demo/Application.h"

// The demo's logo scene, the intial scene of the game.
#include "Arcadia/Engine/Demo/Scenes/ArcadiaLogoScene.h"

// [receiver, sender, argument]
static void
onQuitRequested
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Natural8Value numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues) {
    Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  // Receiver.
  Arcadia_Engine_Demo_Application* application =
    (Arcadia_Engine_Demo_Application*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_Engine_Demo_Application_getType(thread));
  // Argument.
  Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Engine_Demo_Application_getType(thread));
  // The sender is at index 1.
  Arcadia_Engine_Application_setQuitRequested(thread, (Arcadia_Engine_Application*)application, Arcadia_BooleanValue_True);
}

// [receiver, sender, oldScene, newScene]
static void
onSceneChanged
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Natural8Value numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (4 != numberOfArgumentValues) {
    Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Engine_Demo_Application* self = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 4, _Arcadia_Engine_Demo_Application_getType(thread));
    Arcadia_Engine_Demo_Scene* oldScene = NULL,
                             * newScene = NULL;
    //
    if (Arcadia_ValueStack_isVoidValue(thread, 2)) {
    } else if (Arcadia_ValueStack_isObjectReferenceValue(thread, 2)) {
      oldScene = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Engine_Demo_Scene_getType(thread));
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    //
    if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    } else if (Arcadia_ValueStack_isObjectReferenceValue(thread, 1)) {
      newScene = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Engine_Demo_Scene_getType(thread));
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (self->sceneOnQuitRequestedSlot) {
      Arcadia_Slot_disconnect(thread, self->sceneOnQuitRequestedSlot);
    }
    if (newScene) {
      self->sceneOnQuitRequestedSlot = Arcadia_Signal_connect(thread, newScene->applicationQuitRequestSignal, (Arcadia_Object*)self, &onQuitRequested);
    }
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

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
    // Startup the application.
    Arcadia_Engine_Application_startup(thread, (Arcadia_Engine_Application*)application);
    Arcadia_Signal_connect(thread, application->sceneManager->sceneChangedEvent, (Arcadia_Object*)application,
                                                                                 &onSceneChanged);

    Arcadia_Engine_Demo_SceneManager_setScene(thread, application->sceneManager, (Arcadia_Engine_Demo_Scene*)Arcadia_Engine_Demo_ArcadiaLogoScene_create(thread, ((Arcadia_Engine_Application*)application)->engine, application->sceneManager));

    // One run of the GC before entering the main loop.
    Arcadia_Process_stepArms(process);

    // (8) Enter the message loop.
    Arcadia_Natural64Value oldTick, newTick, deltaTick;
    oldTick = Arcadia_getTickCount(thread);
    newTick = oldTick;
    deltaTick = (newTick > oldTick) ? newTick - oldTick : 0;
    while (!Arcadia_Engine_Application_getQuitRequested(thread, (Arcadia_Engine_Application*)application)) {
      Arcadia_Process_stepArms(process);
      Arcadia_Audials_BackendContext_update(thread, (Arcadia_Audials_BackendContext*)((Arcadia_Engine_Application*)application)->engine->audialsBackendContext);
      Arcadia_Visuals_BackendContext_update(thread, (Arcadia_Visuals_BackendContext*)((Arcadia_Engine_Application*)application)->engine->visualsBackendContext);
      Arcadia_Engine_Demo_Scene_updateLogics(thread, Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager), deltaTick);

      for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)((Arcadia_Engine_Application*)application)->windows); i < n; ++i) {
        Arcadia_Visuals_Window* window =
          (Arcadia_Visuals_Window*)
          Arcadia_List_getObjectReferenceValueCheckedAt
            (
              thread,
              ((Arcadia_Engine_Application*)application)->windows,
              i,
              _Arcadia_Visuals_Window_getType(thread)
            );
        Arcadia_Visuals_Window_beginRender(thread, window);
        {
          Arcadia_Integer32Value width, height;
          Arcadia_Visuals_Window_getCanvasSize(thread, window, &width, &height);
          Arcadia_Engine_Demo_Scene_updateLogics(thread, Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager), deltaTick);
          Arcadia_Engine_Demo_Scene_updateAudials(thread, Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager), deltaTick, width, height);
          Arcadia_Engine_Demo_Scene_updateVisuals(thread, Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager), deltaTick, width, height);
        }
        Arcadia_Visuals_Window_endRender(thread, window);
      }
      Arcadia_Engine_Event* event = Arcadia_Engine_dequeEvent(thread, ((Arcadia_Engine_Application*)application)->engine);
      if (NULL != event) {
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_WindowClosedEvent_getType(thread))) {
          Arcadia_Visuals_WindowClosedEvent* windowClosedEvent = (Arcadia_Visuals_WindowClosedEvent*)event;
          Arcadia_Engine_Demo_Application_onWindowClosedEvent(thread, application, windowClosedEvent);
        }
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_MouseButtonEvent_getType(thread))) {
          Arcadia_Visuals_MouseButtonEvent* e = (Arcadia_Visuals_MouseButtonEvent*)event;
          Arcadia_Engine_Demo_Scene* scene = Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager);
          Arcadia_Engine_Demo_Scene_handleMouseButtonEvent(thread, scene, e);
        }
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_MousePointerEvent_getType(thread))) {
          Arcadia_Visuals_MousePointerEvent* e = (Arcadia_Visuals_MousePointerEvent*)event;
          Arcadia_Engine_Demo_Scene* scene = Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager);
          Arcadia_Engine_Demo_Scene_handleMousePointerEvent(thread, scene, e);
        }
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_KeyboardKeyEvent_getType(thread))) {
          Arcadia_Visuals_KeyboardKeyEvent* e = (Arcadia_Visuals_KeyboardKeyEvent*)event;
          Arcadia_Engine_Demo_Scene* scene = Arcadia_Engine_Demo_SceneManager_getScene(thread, application->sceneManager);
          Arcadia_Engine_Demo_Scene_handleKeyboardKeyEvent(thread, scene, e);
        }
      }
      oldTick = newTick;
      newTick = Arcadia_getTickCount(thread);
      deltaTick = (newTick > oldTick) ? newTick - oldTick : 0;
    }
    Arcadia_Engine_Application_shutdown(thread, (Arcadia_Engine_Application*)application);
    Arcadia_Thread_popJumpTarget(thread);
    if (application) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)application);
      application = NULL;
    }
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (application) {
      Arcadia_Engine_Application_shutdown(thread, (Arcadia_Engine_Application*)application);
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
