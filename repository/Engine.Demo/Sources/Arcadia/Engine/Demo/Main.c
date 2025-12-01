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

#include "Arcadia/Engine/Demo/Configuration.h"
#include <stdlib.h>

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Audials/Include.h"
#include "Arcadia/Visuals/Include.h"
#include "Arcadia/DDL/Include.h"

#include "Arcadia/Engine/Demo/Audials.h"
#include "Arcadia/Engine/Demo/Visuals.h"

// @todo Remove references to `stdio.h`.
static void
render
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  Arcadia_Visuals_Scene_MeshContext* meshContext =
    Arcadia_Visuals_SceneNodeFactory_createMeshContext
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  Arcadia_Visuals_Scene_MeshContext_setBackendContext(thread, (Arcadia_Visuals_Scene_MeshContext*)meshContext, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
  Arcadia_Visuals_Scene_MeshContext_render(thread, (Arcadia_Visuals_Scene_MeshContext*)meshContext); // TODO: Remove this.

  Arcadia_Visuals_Scene_ViewportNode* viewportNode1 =
    (Arcadia_Visuals_Scene_ViewportNode*)
    Arcadia_Visuals_SceneNodeFactory_createViewportNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );

  Arcadia_Visuals_Scene_ViewportNode* viewportNode2 =
    (Arcadia_Visuals_Scene_ViewportNode*)
    Arcadia_Visuals_SceneNodeFactory_createViewportNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );

  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)viewportNode1, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
  Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, viewportNode1, 255.f, 0.f, 0.f, 255.f);
  Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, viewportNode1, 0.f, 0.f, 0.5f, 1.f);
  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, viewportNode1, width, height);

  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)viewportNode2, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
  Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, viewportNode2, 0.f, 255.f, 0.f, 255.f);
  Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, viewportNode2, 0.5f, 0.f, 1.0f, 1.f);
  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, viewportNode2, width, height);

  Arcadia_Visuals_Scene_CameraNode* cameraNode =
    (Arcadia_Visuals_Scene_CameraNode*)
    Arcadia_Visuals_SceneNodeFactory_createCameraNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );

  Arcadia_Visuals_Scene_MeshNode* meshNode =
    (Arcadia_Visuals_Scene_MeshNode*)
    Arcadia_Visuals_SceneNodeFactory_createMeshNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)meshNode, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);

  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, cameraNode, viewportNode1);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)viewportNode1, meshContext);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)cameraNode, meshContext);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)meshNode, meshContext);

  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, cameraNode, viewportNode2);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)viewportNode2, meshContext);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)cameraNode, meshContext);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)meshNode, meshContext);
}

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char **argv
  )
{
  Arcadia_BooleanValue quit = Arcadia_BooleanValue_False;
  Arcadia_Engine* engine = NULL;
  Arcadia_Visuals_Window* window = NULL;
  Arcadia_DDL_Node* configuration = NULL;

  Arcadia_Thread* thread = Arcadia_Process_getThread(process);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {

    {
      Arcadia_DDL_Node* temporary = (Arcadia_DDL_Node*)Cfg_loadConfiguration(thread);
      Arcadia_Object_lock(thread,  (Arcadia_Object*)temporary);
      configuration = temporary;
    }

    {
      Arcadia_Engine* temporary = Arcadia_Engine_getOrCreate(thread);
      Arcadia_Object_lock(thread, (Arcadia_Object*)temporary);
      engine = temporary;
    }
    Arcadia_String* windowMode = NULL;
    Arcadia_Visuals_DisplayDevice* displayDevice = NULL;
    Arcadia_Engine_Demo_startupVisuals(thread, engine, configuration, &displayDevice, &windowMode, &window);

    Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
    Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
    Arcadia_FileHandle_openStandardOutput(thread, fileHandle);

    // (1) Initialize Audials.
    Arcadia_Engine_Demo_startupAudials(thread, engine, configuration);

    // (2) Play sine wave.
    Arcadia_Audials_BackendContext_playSine(thread, (Arcadia_Audials_BackendContext*)engine->audialsBackendContext);

    Arcadia_Process_stepArms(process);

    // (8) Enter the message loop.
    while (!quit) {
      Arcadia_Process_stepArms(process);
      Arcadia_Audials_BackendContext_update(thread, (Arcadia_Audials_BackendContext*)engine->audialsBackendContext);
      Arcadia_Visuals_BackendContext_update(thread, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
      Arcadia_Visuals_Window_beginRender(thread, window);
      {
        Arcadia_Integer32Value width, height;
        Arcadia_Visuals_Window_getCanvasSize(thread, window, &width, &height);
        render(thread, engine, width, height);
      }
      Arcadia_Visuals_Window_endRender(thread, window);

      Arcadia_Engine_Event* event = Arcadia_Engine_dequeEvent(thread, engine);
      if (NULL != event) {
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_WindowClosedEvent_getType(thread))) {
          quit = Arcadia_BooleanValue_True;
        }
        if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_KeyboardKeyEvent_getType(thread))) {
          Arcadia_Visuals_KeyboardKeyEvent* keyboardKeyEvent = (Arcadia_Visuals_KeyboardKeyEvent*)event;
          if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, keyboardKeyEvent) == Arcadia_Visuals_KeyboardKeyAction_Released &&
              Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, keyboardKeyEvent) == Arcadia_Visuals_KeyboardKey_Escape) {
            quit = Arcadia_BooleanValue_True;
          } else if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, keyboardKeyEvent) == Arcadia_Visuals_KeyboardKeyAction_Released &&
                     Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, keyboardKeyEvent) == Arcadia_Visuals_KeyboardKey_R) {
            Arcadia_logf(Arcadia_LogFlags_Info, "re-initializing backends\n");
          }
        }
      }
    }

    // (9) Ensure the window is closed.
    Arcadia_Visuals_Window_close(thread, window);

    Cfg_saveConfiguration(thread, configuration);

    Arcadia_Thread_popJumpTarget(thread);

    // (10) Clean the message queue. FIXME: The messages prevent the engine from being gc'ed.
    while (Arcadia_Engine_dequeEvent(thread, engine)) {
      Arcadia_logf(Arcadia_LogFlags_Info, "%s:%d: purging message\n", __FILE__, __LINE__);
    }

    if (window) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (engine->audialsBackendContext) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->audialsBackendContext);
      engine->audialsBackendContext = NULL;
    }
    if (engine->visualsBackendContext) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->visualsBackendContext);
      engine->visualsBackendContext = NULL;
    }
    if (engine) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine);
      engine = NULL;
    }
    if (configuration) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)configuration);
      configuration = NULL;
    }
  } else {
    Arcadia_Thread_popJumpTarget(thread);

    if (window) {
      // (9) Ensure the window is closed.
      Arcadia_Visuals_Window_close(thread, window);
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (engine && engine->audialsBackendContext) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->audialsBackendContext);
      engine->audialsBackendContext = NULL;
    }
    if (engine && engine->visualsBackendContext) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->visualsBackendContext);
      engine->visualsBackendContext = NULL;
    }
    if (engine) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine);
      engine = NULL;
    }
    if (configuration) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)configuration);
      configuration = NULL;
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
