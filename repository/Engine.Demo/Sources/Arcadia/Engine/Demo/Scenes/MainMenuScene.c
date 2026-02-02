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

#include "Arcadia/Engine/Demo/Scenes/MainMenuScene.h"

#include "Arcadia/Engine/Demo/AssetUtilities.h"

static void
Arcadia_Engine_Demo_MainMenuScene_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self
  );

static void
Arcadia_Engine_Demo_MainMenuScene_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuSceneDispatch* self
  );

static void
Arcadia_Engine_Demo_MainMenuScene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self
  );

static void
Arcadia_Engine_Demo_MainMenuScene_updateAudialsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Engine_Demo_MainMenuScene_updateLogicsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Real64Value tick
  );

static void
Arcadia_Engine_Demo_MainMenuScene_updateVisualsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Engine_Demo_MainMenuScene_handleKeyboardKeyEventImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Visuals_KeyboardKeyEvent* event
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Demo_MainMenuScene_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Demo_MainMenuScene_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Demo_MainMenuScene_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Demo_MainMenuScene_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Demo_MainMenuScene_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Demo.MainMenuScene", Arcadia_Engine_Demo_MainMenuScene,
                         u8"Arcadia.Engine.Demo.Scene", Arcadia_Engine_Demo_Scene,
                         &_Arcadia_Engine_Demo_MainMenuScene_typeOperations);

static void
Arcadia_Engine_Demo_MainMenuScene_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Demo_MainMenuScene_getType(thread);
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
  self->definitions = Arcadia_ADL_Definitions_create(thread);
  //
  self->cameraNode = NULL;
  self->renderingContextNode = NULL;
  self->modelNode = NULL;
  self->viewportNode = NULL;

  //
  self->soundSourceNode = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_Engine_Demo_MainMenuScene_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuSceneDispatch* self
  )
{
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateAudials = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Engine_Demo_MainMenuScene_updateAudialsImpl;
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateLogics = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value)) & Arcadia_Engine_Demo_MainMenuScene_updateLogicsImpl;
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->updateVisuals = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Real64Value, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Engine_Demo_MainMenuScene_updateVisualsImpl;
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->handleKeyboardKeyEvent = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Visuals_KeyboardKeyEvent*)) & Arcadia_Engine_Demo_MainMenuScene_handleKeyboardKeyEventImpl;

}

static void
Arcadia_Engine_Demo_MainMenuScene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self
  )
{
  if (self->definitions) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitions);
  }

  if (self->renderingContextNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->renderingContextNode);
  }

  if (self->cameraNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cameraNode);
  }

  if (self->modelNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->modelNode);
  }
  if (self->viewportNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewportNode);
  }

  if (self->soundSourceNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->soundSourceNode);
  }
}

static void
Arcadia_Engine_Demo_MainMenuScene_updateAudialsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
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
Arcadia_Engine_Demo_MainMenuScene_updateLogicsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Real64Value tick
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Demo_MainMenuScene_updateVisualsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Real64Value tick,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  Arcadia_Engine* engine = ((Arcadia_Engine_Demo_Scene*)self)->engine;

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_ADL_Context* context = Arcadia_ADL_Context_getOrCreate(thread);
  Arcadia_List* files = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Engine_Demo_AssetUtilities_enumerateFiles(thread, Arcadia_FilePath_parseGeneric(thread, "Assets/LogoScene", sizeof("Assets/LogoScene") - 1), files);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)files); i < n; ++i) {
    Arcadia_FilePath* filePath = (Arcadia_FilePath*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, files, i, _Arcadia_FilePath_getType(thread));
    Arcadia_ByteBuffer* fileBytes = Arcadia_FileSystem_getFileContents(thread, fileSystem, filePath);
    Arcadia_ADL_Context_readFromString(thread, context, self->definitions, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(fileBytes)), Arcadia_BooleanValue_True);
  }

  if (!self->renderingContextNode) {
    self->renderingContextNode =
      Arcadia_Visuals_SceneNodeFactory_createRenderingContextNode
        (
          thread,
          (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
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
  Arcadia_Math_Matrix4Real32* viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4x4Real32_setOrthographicProjection(thread, viewToProjectionMatrix, -1, +1, -1, +1, -1, +1);
  Arcadia_Visuals_Scene_CameraNode_setViewToProjectionMatrix(thread, self->cameraNode, viewToProjectionMatrix);

  Arcadia_ADL_ColorDefinition* CLEARCOLORS[] = 
    {
      getColorDefinition(thread, self->definitions, Arcadia_String_createFromCxxString(thread, "Assets/Colors/CSS/Red.adl"),
                                                    Arcadia_String_createFromCxxString(thread, "Colors.Red")),
    };

  Arcadia_ADL_ModelDefinition* MODELS[] =
    {
      getModelDefinition(thread, self->definitions, Arcadia_String_createFromCxxString(thread, "Assets/LogoScene/TextureColorModel.adl"),
                                                    Arcadia_String_createFromCxxString(thread, "LogoScene.TextureColorModel")),
    };

  if (!self->viewportNode) {
    Arcadia_ADL_ColorDefinition* d = CLEARCOLORS[0];
    self->viewportNode =
      (Arcadia_Visuals_Scene_ViewportNode*)
      Arcadia_Visuals_SceneNodeFactory_createViewportNode
        (
          thread,
          (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
    Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, self->viewportNode, Arcadia_Math_Color4Real32_create4(thread, d->red / 255.f, d->green / 255.f, d->blue / 255.f, 1.f));
    Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, self->viewportNode, 0.f, 0.f, 1.f, 1.f);
  }

  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, self->viewportNode, width, height);

  if (!self->modelNode) {
    Arcadia_ADL_ModelDefinition* modelDefinition = MODELS[0];
    if (NULL == modelDefinition) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_ADL_Definition_link(thread, (Arcadia_ADL_Definition*)modelDefinition);
    self->modelNode =
      (Arcadia_Visuals_Scene_ModelNode*)
      Arcadia_Visuals_SceneNodeFactory_createModelNode
        (
          thread,
          (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext,
          modelDefinition
        );
  }

  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, self->viewportNode, width, height);
  // Assign "viewport" node to "camera" node.
  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, self->cameraNode, self->viewportNode);
  Arcadia_Visuals_Scene_RenderingContextNode_setCameraNode(thread, self->renderingContextNode, self->cameraNode);
  // Render the scene.
  Arcadia_Visuals_renderScene(thread, self->renderingContextNode, self->modelNode, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
}

static void
Arcadia_Engine_Demo_MainMenuScene_handleKeyboardKeyEventImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Visuals_KeyboardKeyEvent* event
  )
{
  if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, event) == Arcadia_Visuals_KeyboardKeyAction_Released &&
      Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, event) == Arcadia_Visuals_KeyboardKey_Escape) {
    Arcadia_Visuals_ApplicationQuitRequestedEvent* e = Arcadia_Visuals_ApplicationQuitRequestedEvent_create(thread, Arcadia_getTickCount(thread));
    Arcadia_ValueStack_pushObjectReferenceValue(thread,  (Arcadia_Object*)e);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);   
    Arcadia_Signal_emit(thread, ((Arcadia_Engine_Demo_Scene*)self)->applicationQuitRequestSignal, (Arcadia_Object*)self);
    Arcadia_ValueStack_popValues(thread, 2);
  } else if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, event) == Arcadia_Visuals_KeyboardKeyAction_Released &&
    Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, event) == Arcadia_Visuals_KeyboardKey_R) {
    Arcadia_logf(Arcadia_LogFlags_Info, "re-initializing backends\n");
  }
}

Arcadia_Engine_Demo_MainMenuScene*
Arcadia_Engine_Demo_MainMenuScene_create
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
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Demo_MainMenuScene);
}
