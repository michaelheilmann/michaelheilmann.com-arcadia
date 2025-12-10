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

#include "Arcadia/Engine/Demo/Scenes/ArcadiaLogoScene.h"

#include "Arcadia/Engine/Demo/SceneManager.h"
#include "Arcadia/Engine/Demo/Scenes/MainScene.h"

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self
  );

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoSceneDispatch* self
  );

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self
  );

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_updateAudials
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_updateLogics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self,
    Arcadia_Real64Value tick
  );

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_updateVisuals
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Demo_ArcadiaLogoScene_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Demo_ArcadiaLogoScene_construct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Demo_ArcadiaLogoScene_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Demo_ArcadiaLogoScene_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Demo_ArcadiaLogoScene_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Demo.ArcadiaLogoScene", Arcadia_Engine_Demo_ArcadiaLogoScene,
                         u8"Arcadia.Engine.Demo.Scene", Arcadia_Engine_Demo_Scene,
                         &_Arcadia_Engine_Demo_ArcadiaLogoScene_typeOperations);

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Demo_ArcadiaLogoScene_getType(thread);
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
  self->duration = 0.;
  //
  self->frameBufferNode = NULL;
  //
  self->viewportNode = NULL;
  self->cameraNode = NULL;
  self->renderingContextNode = NULL;
  //
  self->meshNode = NULL;
  //
  self->definitions = Arcadia_ADL_Definitions_create(thread);
  self->toLoad = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  //
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FilePath* path = Arcadia_FileSystem_getWorkingDirectory(thread, fileSystem);
  Arcadia_FilePath_append(thread, path, Arcadia_FilePath_parseGeneric(thread, "Colors/CSS", sizeof("Colors/CSS") - 1));
  Arcadia_DirectoryIterator* directoryIterator = Arcadia_FileSystem_createDirectoryIterator(thread, fileSystem, path);
  Arcadia_FilePath* dot = Arcadia_FilePath_parseGeneric(thread, u8".", sizeof(u8".") - 1),
                  * dotdot = Arcadia_FilePath_parseGeneric(thread, u8"..", sizeof(u8"..") - 1);
  while (Arcadia_DirectoryIterator_hasValue(thread, directoryIterator)) {
    Arcadia_FilePath* elementPath = Arcadia_DirectoryIterator_getValue(thread, directoryIterator);
    if (Arcadia_FilePath_isEqualTo(thread, elementPath, dot) || Arcadia_FilePath_isEqualTo(thread, elementPath, dotdot)) {
      Arcadia_DirectoryIterator_nextValue(thread, directoryIterator);
    } else {
      Arcadia_FilePath* temporary = Arcadia_FilePath_clone(thread, path);
      Arcadia_FilePath_append(thread, temporary, elementPath);
      elementPath = temporary;
      //Arcadia_String* elementPathString = Arcadia_FilePath_toNative(thread, elementPath);
      Arcadia_List_insertBackObjectReferenceValue(thread, self->toLoad, (Arcadia_Object*)elementPath);
      //Arcadia_logf(Arcadia_LogFlags_Debug, "%s\n", Arcadia_String_getBytes(thread, elementPathString));
      Arcadia_DirectoryIterator_nextValue(thread, directoryIterator);
    }
  }
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoSceneDispatch* self
  )
{
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateAudials = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Engine_Demo_ArcadiaLogoScene_updateAudials;
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateLogics = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value)) & Arcadia_Engine_Demo_ArcadiaLogoScene_updateLogics;
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateVisuals = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Engine_Demo_ArcadiaLogoScene_updateVisuals;
}

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self
  )
{
  if (self->definitions) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitions);
  }

  if (self->frameBufferNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->frameBufferNode);
  }

  if (self->viewportNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewportNode);
  }
  if (self->cameraNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cameraNode);
  }
  if (self->renderingContextNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->renderingContextNode);
  }

  if (self->meshNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->meshNode);
  }

  if (self->toLoad) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->toLoad);
  }
}

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_updateAudials
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_updateLogics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self,
    Arcadia_Real64Value tick
  )
{
  self->duration += tick;
  /* The loading screen fades in and fades out over a duration of 3 secods. After 3.25 seconds we move to the next scene. */
  if (self->duration > 3250 && 0 == Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->toLoad)) {
    Arcadia_Engine_Demo_SceneManager_setScene(thread, ((Arcadia_Engine_Demo_Scene*)self)->sceneManager,
                                              (Arcadia_Engine_Demo_Scene*)Arcadia_Engine_Demo_MainScene_create(thread, ((Arcadia_Engine_Demo_Scene*)self)->engine, ((Arcadia_Engine_Demo_Scene*)self)->sceneManager));
  }
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_SizeValue n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->toLoad);
  if (n) {
    Arcadia_SizeValue i = n - 1;
    Arcadia_FilePath* filePath = (Arcadia_FilePath*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, self->toLoad, i, _Arcadia_FilePath_getType(thread));
    Arcadia_List_removeAt(thread, self->toLoad, i, 1);
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_ADL_Context* context = Arcadia_ADL_Context_getOrCreate(thread);
      Arcadia_ByteBuffer* fileBytes = Arcadia_FileSystem_getFileContents(thread, fileSystem, filePath);
      Arcadia_ADL_Context_readFromString(thread, context, self->definitions, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(fileBytes)));
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_String* temporary = Arcadia_FilePath_toNative(thread, filePath);
      Arcadia_logf(Arcadia_LogFlags_Debug, "problem loading asset `%s`\n", Arcadia_String_getBytes(thread, temporary));
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
renderToFrameBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  Arcadia_Engine* engine = ((Arcadia_Engine_Demo_Scene*)self)->engine;

  // Ensure the "frame buffer" node exist.
  if (!self->frameBufferNode) {
    self->frameBufferNode =
      Arcadia_Visuals_SceneNodeFactory_createFrameBufferNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  }
  // Ensure the "rendering context" node exists.
  if (!self->renderingContextNode) {
    self->renderingContextNode =
      Arcadia_Visuals_SceneNodeFactory_createRenderingContextNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  }
  // Ensure the "viewport" node exists.
  // Set its clear color and relative viewport rectangle.
  if (!self->viewportNode) {
    self->viewportNode =
      (Arcadia_Visuals_Scene_ViewportNode*)
      Arcadia_Visuals_SceneNodeFactory_createViewportNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
    Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, self->viewportNode, 0.f, 255.f, 0.f, 255.f);
    Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, self->viewportNode, 0.f, 0.f, 1.f, 1.f);
  }
  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, self->viewportNode, width, height);

  // Ensure the "camera" node exists.
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

  // Ensure the "mesh" node exists.
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

  // Assign the "viewport" node to the "camera" node.
  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, self->cameraNode, self->viewportNode);
  // Assign the "camera" node to the "rendering context" node.
  Arcadia_Visuals_Scene_RenderingContextNode_setCameraNode(thread, self->renderingContextNode, self->cameraNode);
  // Assign the "frame buffer" node to the "rendering context" node.
  Arcadia_Visuals_Scene_RenderingContextNode_setFrameBufferNode(thread, self->renderingContextNode, self->frameBufferNode);
  // Render the scene.
  // @todo Do not pass "Arcadia.Visuals.Scene.MeshNode". Create and pass "Arcadia.Visuals.Scene.Group".
  Arcadia_Visuals_renderScene(thread, self->renderingContextNode, self->meshNode, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
}

static void
renderToDefaultFrameBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  Arcadia_Engine* engine = ((Arcadia_Engine_Demo_Scene*)self)->engine;

  // Ensure the "frame buffer" node exist.
  if (!self->frameBufferNode) {
    self->frameBufferNode =
      Arcadia_Visuals_SceneNodeFactory_createFrameBufferNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  }
  // Ensure the "rendering context" node exists.
  if (!self->renderingContextNode) {
    self->renderingContextNode =
      Arcadia_Visuals_SceneNodeFactory_createRenderingContextNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  }
  // Ensure the "viewport" node exists.
  // Set its clear color and relative viewport rectangle.
  if (!self->viewportNode) {
    self->viewportNode =
      (Arcadia_Visuals_Scene_ViewportNode*)
      Arcadia_Visuals_SceneNodeFactory_createViewportNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
    Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, self->viewportNode, 0.f, 255.f, 0.f, 255.f);
    Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, self->viewportNode, 0.f, 0.f, 1.f, 1.f);
  }
  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, self->viewportNode, width, height);

  // Ensure the "camera" node exists.
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

  // Ensure the "mesh" node exists.
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

  // Assign the "viewport" node to the "camera" node.
  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, self->cameraNode, self->viewportNode);
  // Assign the "camera" node to the "rendering context" node.
  Arcadia_Visuals_Scene_RenderingContextNode_setCameraNode(thread, self->renderingContextNode, self->cameraNode);
#if 1
  // Assign the "frame buffer" node to the "rendering context" node.
  Arcadia_Visuals_Scene_RenderingContextNode_setFrameBufferNode(thread, self->renderingContextNode, NULL);
#endif
  // Render the scene.
  // @todo Do not pass "Arcadia.Visuals.Scene.MeshNode". Create and pass "Arcadia.Visuals.Scene.Group".
  Arcadia_Visuals_renderScene(thread, self->renderingContextNode, self->meshNode, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
}

static void
Arcadia_Engine_Demo_ArcadiaLogoScene_updateVisuals
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ArcadiaLogoScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  renderToFrameBuffer(thread, self, tick, width, height);
  renderToDefaultFrameBuffer(thread, self, tick, width, height);
}

Arcadia_Engine_Demo_ArcadiaLogoScene*
Arcadia_Engine_Demo_ArcadiaLogoScene_create
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
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Demo_ArcadiaLogoScene);
}
