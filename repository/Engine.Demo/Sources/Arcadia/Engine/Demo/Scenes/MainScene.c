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

#include "Arcadia/Engine/Demo/AssetUtilities.h"

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
  self->definitions = Arcadia_ADL_Definitions_create(thread);
  //
  self->cameraNode = NULL;
  self->enterPassNode = NULL;
  for (Arcadia_SizeValue i = 0; i < 3; ++i) {
    self->modelNode[i] = NULL;
    self->viewportNodes[i] = NULL;
  }
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
  if (self->definitions) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitions);
  }

  if (self->enterPassNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->enterPassNode);
  }

  if (self->cameraNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cameraNode);
  }

  for (Arcadia_SizeValue i = 0; i < 3; ++i) {
    if (self->modelNode[i]) {
      Arcadia_Object_visit(thread, (Arcadia_Object*)self->modelNode[i]);
    }
    if (self->viewportNodes[i]) {
      Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewportNodes[i]);
    }
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
      Arcadia_Engine_Audials_NodeFactory_createSoundSourceNode
        (
          thread,
          (Arcadia_Engine_Audials_NodeFactory*)engine->audialsNodeFactory,
          (Arcadia_Engine_Audials_BackendContext*)engine->audialsBackendContext
        );
  }
  Arcadia_Engine_Node_setAudialsBackendContext(thread, (Arcadia_Engine_Node*)self->soundSourceNode, (Arcadia_Engine_Audials_BackendContext*)engine->audialsBackendContext);
  Arcadia_Engine_Audials_Node_render(thread, (Arcadia_Engine_Audials_Node*)self->soundSourceNode);
  Arcadia_Engine_Audials_SoundSourceNode_setVolume(thread, self->soundSourceNode, 0.125f);
  if (!Arcadia_Engine_Audials_SoundSourceNode_isPlaying(thread, self->soundSourceNode)) {
    Arcadia_Engine_Audials_SoundSourceNode_stop(thread, self->soundSourceNode);
    Arcadia_Engine_Audials_SoundSourceNode_play(thread, self->soundSourceNode);
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

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_ADL_Context* context = Arcadia_ADL_Context_getOrCreate(thread);
  Arcadia_List* files = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Engine_Demo_AssetUtilities_enumerateFiles(thread, Arcadia_FilePath_parseGeneric(thread, "Assets/LogoScene", sizeof("Assets/LogoScene") - 1), files);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)files); i < n; ++i) {
    Arcadia_FilePath* filePath = (Arcadia_FilePath*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, files, i, _Arcadia_FilePath_getType(thread));
    Arcadia_ByteBuffer* fileBytes = Arcadia_FileSystem_getFileContents(thread, fileSystem, filePath);
    Arcadia_ADL_Context_readFromString(thread, context, self->definitions, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(fileBytes)), Arcadia_BooleanValue_True);
  }

  if (!self->enterPassNode) {
    self->enterPassNode =
      Arcadia_Engine_Visuals_NodeFactory_createEnterPassNode
        (
          thread,
          (Arcadia_Engine_Visuals_NodeFactory*)engine->visualsNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
  }


  if (!self->cameraNode) {
    self->cameraNode =
      (Arcadia_Engine_Visuals_CameraNode*)
      Arcadia_Engine_Visuals_NodeFactory_createCameraNode
        (
          thread,
          (Arcadia_Engine_Visuals_NodeFactory*)engine->visualsNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
  }

  Arcadia_ADL_ColorDefinition* CLEARCOLORS[] = 
    {
      getColorDefinition(thread, self->definitions, Arcadia_String_createFromCxxString(thread, "Assets/Colors/CSS/Red.adl"),
                                                    Arcadia_String_createFromCxxString(thread, "Colors.Red")),
      getColorDefinition(thread, self->definitions, Arcadia_String_createFromCxxString(thread, "Assets/Colors/CSS/Green.adl"),
                                                    Arcadia_String_createFromCxxString(thread, "Colors.Green")),
      getColorDefinition(thread, self->definitions, Arcadia_String_createFromCxxString(thread, "Assets/Colors/CSS/Blue.adl"),
                                                    Arcadia_String_createFromCxxString(thread, "Colors.Blue")),
    };

  Arcadia_ADL_ModelDefinition* MODELS[] =
    {
      getModelDefinition(thread, self->definitions, Arcadia_String_createFromCxxString(thread, "Assets/LogoScene/MeshColorModel.adl"),
                                                    Arcadia_String_createFromCxxString(thread, "LogoScene.MeshColorModel")),
      getModelDefinition(thread, self->definitions, Arcadia_String_createFromCxxString(thread, "Assets/LogoScene/VertexColorModel.adl"),
                                                    Arcadia_String_createFromCxxString(thread, "LogoScene.VertexColorModel")),
      getModelDefinition(thread, self->definitions, Arcadia_String_createFromCxxString(thread, "Assets/LogoScene/TextureColorModel.adl"),
                                                    Arcadia_String_createFromCxxString(thread, "LogoScene.TextureColorModel")),
    };

  for (Arcadia_SizeValue i = 0; i < 3; ++i) {
    if (!self->viewportNodes[i]) {
      Arcadia_ADL_ColorDefinition* d = CLEARCOLORS[i];
      self->viewportNodes[i] =
        (Arcadia_Engine_Visuals_ViewportNode*)
        Arcadia_Engine_Visuals_NodeFactory_createViewportNode
          (
            thread,
            (Arcadia_Engine_Visuals_NodeFactory*)engine->visualsNodeFactory,
            (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
          );
      Arcadia_Engine_Visuals_ViewportNode_setClearColor(thread, self->viewportNodes[i], Arcadia_Math_Color4Real32_create4(thread, d->red / 255.f, d->green / 255.f, d->blue / 255.f, 1.f));
      Arcadia_Engine_Visuals_ViewportNode_setRelativeViewportRectangle(thread, self->viewportNodes[i], (i + 0) * 1.f / 3.f, 0.f, (i + 1) * 1.f / 3.f, 1.f);
    }

    if (!self->modelNode[i]) {
      Arcadia_ADL_ModelDefinition* modelDefinition = MODELS[i];
      if (NULL == modelDefinition) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_ADL_Definition_link(thread, (Arcadia_ADL_Definition*)modelDefinition);
      self->modelNode[i] =
        (Arcadia_Engine_Visuals_ModelNode*)
        Arcadia_Engine_Visuals_NodeFactory_createModelNode
          (
            thread,
            (Arcadia_Engine_Visuals_NodeFactory*)engine->visualsNodeFactory,
            (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext,
            modelDefinition
          );
    }

    Arcadia_Engine_Visuals_ViewportNode_setCanvasSize(thread, self->viewportNodes[i], width, height);
    // Assign the "viewport" node and "camera" node to the "enter pass" node.
    Arcadia_Engine_Visuals_EnterPassNode_setViewportNode(thread, self->enterPassNode, self->viewportNodes[i]);
    Arcadia_Engine_Visuals_EnterPassNode_setCameraNode(thread, self->enterPassNode, self->cameraNode);
    // Render the scene.
    Arcadia_Engine_Visuals_renderScene(thread, self->enterPassNode, self->modelNode[i], (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);

  }
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
