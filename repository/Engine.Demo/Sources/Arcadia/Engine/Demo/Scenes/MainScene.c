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

#include "Arcadia/Engine/Demo/Scenes/MainScene.h"

static void
Arcadia_Engine_Demo_MainScene_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  );

static void
Arcadia_Engine_Demo_MainScene_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainSceneDispatch* self
  );

static void
Arcadia_Engine_Demo_MainScene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  );

static void
Arcadia_Engine_Demo_MainScene_updateAudials
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Engine_Demo_MainScene_updateLogics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self,
    Arcadia_Real64Value tick
  );

static void
Arcadia_Engine_Demo_MainScene_updateVisuals
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Demo_MainScene_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Demo_MainScene_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Demo_MainScene_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Demo_MainScene_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Demo_MainScene_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Demo.MainScene", Arcadia_Engine_Demo_MainScene,
                         u8"Arcadia.Engine.Demo.Scene", Arcadia_Engine_Demo_Scene,
                         &_Arcadia_Engine_Demo_MainScene_typeOperations);

static void
Arcadia_Engine_Demo_MainScene_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Demo_MainScene_getType(thread);
  {
    Arcadia_Value engine = Arcadia_ValueStack_getValue(thread, 1),
                  sceneManager = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &engine);
    Arcadia_ValueStack_pushValue(thread, &sceneManager);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->viewportNodes[0] = NULL;
  self->viewportNodes[1] = NULL;
  self->cameraNode = NULL;
  self->renderingContextNode = NULL;
  self->meshNode = NULL;
  //
  self->soundSourceNode = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_Engine_Demo_MainScene_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainSceneDispatch* self
  )
{
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateAudials = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Engine_Demo_MainScene_updateAudials;
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateLogics = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value)) & Arcadia_Engine_Demo_MainScene_updateLogics;
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateVisuals = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Engine_Demo_MainScene_updateVisuals;
}

static void
Arcadia_Engine_Demo_MainScene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  )
{
  if (self->renderingContextNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->renderingContextNode);
  }

  if (self->viewportNodes[0]) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewportNodes[0]);
  }
  if (self->viewportNodes[1]) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewportNodes[1]);
  }
  if (self->cameraNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cameraNode);
  }

  if (self->meshNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->meshNode);
  }

  if (self->soundSourceNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->soundSourceNode);
  }
}

static void
Arcadia_Engine_Demo_MainScene_updateAudials
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  Arcadia_Engine* engine = ((Arcadia_Engine_Demo_Scene*)self)->engine;
  if (!self->soundSourceNode) {
    self->soundSourceNode =
      Arcadia_Audials_SceneNodeFactory_createSoundSourceNode
        (
          thread,
          (Arcadia_Audials_SceneNodeFactory*)engine->audialsSceneNodeFactory,
          (Arcadia_Audials_BackendContext*)engine->audialsBackendContext
        );
  }
  Arcadia_Audials_Scene_Node_setBackendContext(thread, (Arcadia_Audials_Scene_Node*)self->soundSourceNode, (Arcadia_Audials_BackendContext*)engine->audialsBackendContext);
  Arcadia_Audials_Scene_Node_render(thread, (Arcadia_Audials_Scene_Node*)self->soundSourceNode);
  Arcadia_Audials_Scene_SoundSourceNode_setVolume(thread, self->soundSourceNode, 0.125f);
  if (!Arcadia_Audials_Scene_SoundSourceNode_isPlaying(thread, self->soundSourceNode)) {
    Arcadia_Audials_Scene_SoundSourceNode_stop(thread, self->soundSourceNode);
    Arcadia_Audials_Scene_SoundSourceNode_play(thread, self->soundSourceNode);
  }
}

static void
Arcadia_Engine_Demo_MainScene_updateLogics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self,
    Arcadia_Real64Value tick
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Demo_MainScene_updateVisuals
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  Arcadia_Engine* engine = ((Arcadia_Engine_Demo_Scene*)self)->engine;

  if (!self->renderingContextNode) {
    self->renderingContextNode =
      Arcadia_Visuals_SceneNodeFactory_createRenderingContextNode
        (
          thread,
          (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
  }

  if (!self->viewportNodes[0]) {
    self->viewportNodes[0] =
      (Arcadia_Visuals_Scene_ViewportNode*)
      Arcadia_Visuals_SceneNodeFactory_createViewportNode
        (
          thread,
          (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
    Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, self->viewportNodes[0], 255.f, 0.f, 0.f, 255.f);
    Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, self->viewportNodes[0], 0.f, 0.f, 0.5f, 1.f);
  }
  if (!self->viewportNodes[1]) {
    self->viewportNodes[1] =
      (Arcadia_Visuals_Scene_ViewportNode*)
      Arcadia_Visuals_SceneNodeFactory_createViewportNode
        (
          thread,
          (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
    Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, self->viewportNodes[1], 0.f, 255.f, 0.f, 255.f);
    Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, self->viewportNodes[1], 0.5f, 0.f, 1.0f, 1.f);
  }

  if (!self->cameraNode) {
    self->cameraNode =
      (Arcadia_Visuals_Scene_CameraNode*)
      Arcadia_Visuals_SceneNodeFactory_createCameraNode
        (
          thread,
          (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
  }
  if (!self->meshNode) {
    self->meshNode =
      (Arcadia_Visuals_Scene_MeshNode*)
      Arcadia_Visuals_SceneNodeFactory_createMeshNode
        (
          thread,
          (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
  }

  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, self->viewportNodes[0], width, height);
  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, self->viewportNodes[1], width, height);

  // Assign "viewport" node #1 to "camera" node.
  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, self->cameraNode, self->viewportNodes[0]);
  Arcadia_Visuals_Scene_RenderingContextNode_setCameraNode(thread, self->renderingContextNode, self->cameraNode);
  // Render the scene.
  // @todo Do not pass "Arcadia.Visuals.Scene.MeshNode". Create and pass "Arcadia.Visuals.Scene.Group".
  Arcadia_Visuals_renderScene(thread, self->renderingContextNode, self->meshNode, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);

  // Assign "viewport" node #2 to "camera" node.
  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, self->cameraNode, self->viewportNodes[1]);
  Arcadia_Visuals_Scene_RenderingContextNode_setCameraNode(thread, self->renderingContextNode, self->cameraNode);
  // Render the scene.
  // @todo Do not pass "Arcadia.Visuals.Scene.MeshNode". Create and pass "Arcadia.Visuals.Scene.Group".
  Arcadia_Visuals_renderScene(thread, self->renderingContextNode, self->meshNode, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
}

Arcadia_Engine_Demo_MainScene*
Arcadia_Engine_Demo_MainScene_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_Engine_Demo_SceneManager* sceneManager
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (engine) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)engine);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (sceneManager) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)sceneManager);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Demo_MainScene);
}
