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

static void
Arcadia_Engine_Demo_MainMenuScene_handleMouseButtonEventImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Visuals_MouseButtonEvent* event
  );

static void
Arcadia_Engine_Demo_MainMenuScene_handleMousePointerEventImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Visuals_MousePointerEvent* event
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
  Arcadia_EnterConstructor(Arcadia_Engine_Demo_MainMenuScene);
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
  self->modelNode = NULL;
  self->viewportNode = NULL;
  //
  self->soundSourceNode = NULL;
  //
  {
  Arcadia_Real32Value values[] = { 0.f, 0.f, +1.f };
  self->viewer.position = Arcadia_Math_Vector3Real32_createWithValues(thread, &values[0]);
  }
  {
  Arcadia_Real32Value values[] = { 0.f, 0.f, -1.f };
  self->viewer.forward = Arcadia_Math_Vector3Real32_createWithValues(thread, &values[0]);
  }
  {
  Arcadia_Real32Value values[] = { 0.f, +1.f, 0.f };
  self->viewer.up = Arcadia_Math_Vector3Real32_createWithValues(thread, &values[0]);
  }
  {
  Arcadia_Real32Value values[] = { +1.f, 0.f, 0.f };
  self->viewer.right = Arcadia_Math_Vector3Real32_createWithValues(thread, &values[0]);
  }
  self->viewer.yaw = 0.f;
  self->viewer.pitch = 0.f;
  self->viewer.roll = 0.f;
  //
  self->uiCanvasNode = Arcadia_Engine_UI_CanvasNode_create(thread);
  //
  self->latches[0] = Arcadia_BooleanValue_False;
  self->latches[1] = Arcadia_BooleanValue_False;
  self->latches[2] = Arcadia_BooleanValue_False;
  self->latches[3] = Arcadia_BooleanValue_False;
  self->mousePosition.oldx = 0;
  self->mousePosition.oldy = 0;
  self->mouseInWindow = Arcadia_BooleanValue_False;
  //
  Arcadia_LeaveConstructor(Arcadia_Engine_Demo_MainMenuScene);
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
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->handleMouseButtonEvent = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Visuals_MouseButtonEvent*)) & Arcadia_Engine_Demo_MainMenuScene_handleMouseButtonEventImpl;
  ((Arcadia_Engine_Demo_SceneDispatch*)self)->handleMousePointerEvent = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Visuals_MousePointerEvent*)) & Arcadia_Engine_Demo_MainMenuScene_handleMousePointerEventImpl;
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

  if (self->enterPassNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->enterPassNode);
  }

  if (self->cameraNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cameraNode);
  }

  if (self->viewer.forward) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewer.forward);
  }
  if (self->viewer.up) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewer.up);
  }
  if (self->viewer.right) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewer.right);
  }
  if (self->viewer.position) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewer.position);

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

  if (self->uiCanvasNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->uiCanvasNode);
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
  Arcadia_Engine_Audials_SoundSourceNode_setIsLooping(thread, self->soundSourceNode, Arcadia_BooleanValue_True);
  if (!Arcadia_Engine_Audials_SoundSourceNode_isPlaying(thread, self->soundSourceNode)) {
    Arcadia_Engine_Audials_SoundSourceNode_stop(thread, self->soundSourceNode);
    Arcadia_Engine_Audials_SoundSourceNode_play(thread, self->soundSourceNode);
  }
}

static void
Arcadia_Math_Matrix4x4Real32_transformDirection
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix4Real32* self,
    Arcadia_Math_Vector3Real32* direction
  )
{
  direction->elements[0] = self->elements[0][0] * direction->elements[0]
                         + self->elements[0][1] * direction->elements[1]
                         + self->elements[0][2] * direction->elements[2]
                         + self->elements[0][3] * 0.f;
  direction->elements[1] = self->elements[1][0] * direction->elements[0]
                         + self->elements[1][1] * direction->elements[1]
                         + self->elements[1][2] * direction->elements[2]
                         + self->elements[1][3] * 0.f;
  direction->elements[2] = self->elements[2][0] * direction->elements[0]
                         + self->elements[2][1] * direction->elements[1]
                         + self->elements[2][2] * direction->elements[2]
                         + self->elements[2][3] * 0.f;
}

static void
Arcadia_Engine_Demo_MainMenuScene_updateLogicsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Real64Value tick
  )
{
  Arcadia_Math_Matrix4Real32* rx = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4x4Real32Value_setRotationX(thread, rx, self->viewer.pitch);

  Arcadia_Math_Matrix4Real32* ry = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4x4Real32Value_setRotationY(thread, ry, self->viewer.yaw);

  Arcadia_Math_Matrix4Real32* tmp = Arcadia_Math_Matrix4Real32_multiply(thread, ry, rx);

  Arcadia_Math_Vector3Real32* v = Arcadia_Math_Vector3Real32_create(thread);

  if (self->latches[0]) {
    // 'W' / forward
    Arcadia_Real32Value values[] = { 0.f, 0.f, -1.f };
    Arcadia_Math_Vector3Real32* t = Arcadia_Math_Vector3Real32_createWithValues(thread, &values[0]);
    Arcadia_Math_Matrix4x4Real32_transformDirection(thread, tmp, t);
    Arcadia_Math_Vector3Real32_add(thread, v, t);
  }
  if (self->latches[1]) {
    // 'A' / left
    Arcadia_Real32Value values[] = { -1.f, 0.f, 0.f };
    Arcadia_Math_Vector3Real32* t = Arcadia_Math_Vector3Real32_createWithValues(thread, &values[0]);
    Arcadia_Math_Matrix4x4Real32_transformDirection(thread, tmp, t);
    Arcadia_Math_Vector3Real32_add(thread, v, t);
  }
  if (self->latches[2]) {
    // 'S' / backward
    Arcadia_Real32Value values[] = { 0.f, 0.f, +1.f };
    Arcadia_Math_Vector3Real32* t = Arcadia_Math_Vector3Real32_createWithValues(thread, &values[0]);
    Arcadia_Math_Matrix4x4Real32_transformDirection(thread, tmp, t);
    Arcadia_Math_Vector3Real32_add(thread, v, t);
  }
  if (self->latches[3]) {
    // 'D' / right
    Arcadia_Real32Value values[] = { +1.f, 0.f, 0.f };
    Arcadia_Math_Vector3Real32* t = Arcadia_Math_Vector3Real32_createWithValues(thread, &values[0]);
    Arcadia_Math_Matrix4x4Real32_transformDirection(thread, tmp, t);
    Arcadia_Math_Vector3Real32_add(thread, v, t);
  }
  if (Arcadia_Math_Vector3Real32_getSquaredLength(thread, v)) {
    Arcadia_Math_Vector3Real32_normalize(thread, v);
  }
  Arcadia_Math_Vector3Real32_multiplyScalar(thread, v, tick/1000.f*4.f); // TOOD: Remove magic constants. This is effectively 4 meters per second.
  Arcadia_Math_Vector3Real32_add(thread, self->viewer.position, v);

  if (!self->uiCanvasNode) {
    self->uiCanvasNode = Arcadia_Engine_UI_CanvasNode_create(thread);
  }
}

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
  // We use a right-handed coordinate system.  
  // -negative z-axis forward, positive z-axis backward
  // -negative y-axis down, positive y-axis up
  // -negative x-axis left, positive x-axis right
  // Viewer located at (0,0,+1).
  // Variant #1: Perspective projection looking down the negative z-axis.
  // Variant #2: Orthographic projection looking down the negative z-axis.
  Arcadia_Math_Matrix4Real32* viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4x4Real32_setPerspectiveProjection(thread, viewToProjectionMatrix, 60.f, 4.f/3.f, 0.1f, 100.f);
  //Arcadia_Math_Matrix4x4Real32_setOrthographicProjection(thread, viewToProjectionMatrix, -1, +1, -1, +1, -1, +1);
  Arcadia_Engine_Visuals_CameraNode_setViewToProjectionMatrix(thread, self->cameraNode, viewToProjectionMatrix);
  // The transformation matrix M of the viewer is given by
  // M = (T*Ry)*Rx
  // where
  // - Rx is the matrix to rotate around the x-axis
  // - Ry is the matrix to rotate around the y-axis
  // - T is the matrix to translate
  // The inverse inv(M) is given by
  //   inv(M)
  // = inv((T*Ry)*Rx)
  // = inv(Rx)*inv(T*Ry)
  // = inv(Rx)*(inv(Ry)*inv(T))
  Arcadia_Math_Matrix4Real32* rx = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4x4Real32Value_setRotationX(thread, rx, -self->viewer.pitch);

  Arcadia_Math_Matrix4Real32* ry = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4x4Real32Value_setRotationY(thread, ry, -self->viewer.yaw);

  Arcadia_Math_Matrix4Real32* t = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4x4Real32Value_setTranslation(thread, t, -self->viewer.position->elements[0], -self->viewer.position->elements[1], -self->viewer.position->elements[2]);

  Arcadia_Math_Matrix4Real32* tmp = Arcadia_Math_Matrix4Real32_multiply(thread, ry, t);
  tmp = Arcadia_Math_Matrix4Real32_multiply(thread, rx, tmp);

  Arcadia_Math_Matrix4Real32* worldToViewMatrix = tmp;
  Arcadia_Engine_Visuals_CameraNode_setWorldToViewMatrix(thread, self->cameraNode, worldToViewMatrix);

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
      (Arcadia_Engine_Visuals_ViewportNode*)
      Arcadia_Engine_Visuals_NodeFactory_createViewportNode
        (
          thread,
          (Arcadia_Engine_Visuals_NodeFactory*)engine->visualsNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
        );
    Arcadia_Engine_Visuals_ViewportNode_setClearColor(thread, self->viewportNode, Arcadia_Math_Color4Real32_create4(thread, d->red / 255.f, d->green / 255.f, d->blue / 255.f, 1.f));
    Arcadia_Engine_Visuals_ViewportNode_setRelativeViewportRectangle(thread, self->viewportNode, 0.f, 0.f, 1.f, 1.f);
  }

  Arcadia_Engine_Visuals_ViewportNode_setCanvasSize(thread, self->viewportNode, width, height);

  if (!self->modelNode) {
    Arcadia_ADL_ModelDefinition* modelDefinition = MODELS[0];
    if (NULL == modelDefinition) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_ADL_Definition_link(thread, (Arcadia_ADL_Definition*)modelDefinition);
    self->modelNode =
      (Arcadia_Engine_Visuals_ModelNode*)
      Arcadia_Engine_Visuals_NodeFactory_createModelNode
        (
          thread,
          (Arcadia_Engine_Visuals_NodeFactory*)engine->visualsNodeFactory,
          (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext,
          modelDefinition
        );
  }
  Arcadia_Engine_Visuals_ViewportNode_setCanvasSize(thread, self->viewportNode, width, height);
  // Assign the "viewport" node and "camera" node to the "enter pass" node.
  Arcadia_Engine_Visuals_EnterPassNode_setViewportNode(thread, self->enterPassNode, self->viewportNode);
  Arcadia_Engine_Visuals_EnterPassNode_setCameraNode(thread, self->enterPassNode, self->cameraNode);
  // Render the models.
  Arcadia_Engine_Visuals_renderScene(thread, self->enterPassNode, self->modelNode, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);

  if (!self->uiCanvasNode) {
    self->uiCanvasNode = Arcadia_Engine_UI_CanvasNode_create(thread);
  }
  // Tell the UI canvas the size of the visuals canvas.
  Arcadia_Engine_UI_CanvasNode_setVisualsCanvasSize(thread, self->uiCanvasNode, width, height);
  // The position and the size of tge UI canvas.
  Arcadia_Engine_UI_WidgetNode_setPosition(thread, (Arcadia_Engine_UI_WidgetNode*)self->uiCanvasNode, 0, 0);
  Arcadia_Engine_UI_WidgetNode_setSize(thread, (Arcadia_Engine_UI_WidgetNode*)self->uiCanvasNode, width, height);
  //Arcadia_Engine_UI_WidgetNode_updateVisuals(thread, self->uiCanvasNode);
}

static void
Arcadia_Engine_Demo_MainMenuScene_handleKeyboardKeyEventImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Visuals_KeyboardKeyEvent* event
  )
{
  // (1) Handle movement latches.
  if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, event) == Arcadia_Visuals_KeyboardKeyAction_Pressed) {
    switch (Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, event)) {
      case Arcadia_Visuals_KeyboardKey_W: {
        self->latches[0] = Arcadia_BooleanValue_True;
      } break;
      case Arcadia_Visuals_KeyboardKey_A: {
        self->latches[1] = Arcadia_BooleanValue_True;
      } break;
      case Arcadia_Visuals_KeyboardKey_S: {
        self->latches[2] = Arcadia_BooleanValue_True;
      } break;
      case Arcadia_Visuals_KeyboardKey_D: {
        self->latches[3] = Arcadia_BooleanValue_True;
      } break;
    };
  };

  if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, event) == Arcadia_Visuals_KeyboardKeyAction_Released) {
    switch (Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, event)) {
      case Arcadia_Visuals_KeyboardKey_W: {
        self->latches[0] = Arcadia_BooleanValue_False;
      } break;
      case Arcadia_Visuals_KeyboardKey_A: {
        self->latches[1] = Arcadia_BooleanValue_False;
      } break;
      case Arcadia_Visuals_KeyboardKey_S: {
        self->latches[2] = Arcadia_BooleanValue_False;
      } break;
      case Arcadia_Visuals_KeyboardKey_D: {
        self->latches[3] = Arcadia_BooleanValue_False;
      } break;
    };
  };

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

static void
Arcadia_Engine_Demo_MainMenuScene_handleMouseButtonEventImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Visuals_MouseButtonEvent* event
  )
{ }

static void
Arcadia_Engine_Demo_MainMenuScene_handleMousePointerEventImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainMenuScene* self,
    Arcadia_Visuals_MousePointerEvent* event
  )
{ 
  switch (event->action) {
    case Arcadia_Visuals_MousePointerAction_Entered: {
      self->mouseInWindow = Arcadia_BooleanValue_True;
      self->mousePosition.oldx = (Arcadia_Real32Value)event->x;
      self->mousePosition.oldy = (Arcadia_Real32Value)event->y;
    } break;
    case Arcadia_Visuals_MousePointerAction_Exited: {
      self->mouseInWindow =  Arcadia_BooleanValue_False;
    } break;
    case Arcadia_Visuals_MousePointerAction_Moved: {
      if (!self->mouseInWindow) {
        self->mouseInWindow = Arcadia_BooleanValue_True;
        self->mousePosition.oldx = (Arcadia_Real32Value)event->x;
        self->mousePosition.oldy = (Arcadia_Real32Value)event->y;
      }     
      Arcadia_Real32Value delta;
      // "yaw" is the counter-clockwise rotation around the y-axis in a right-handed coordinate system.
      // By the right-hand rule, we determine y-going up.
      // By the curled-fingers rule, we determine the positive rotation direction is left and the negative rotation direction is right.
      // When mouse moves right, the delta is positive, when the mouse moves left, the delta is negative.
      // So moving the mouse right (left), we would turn left (right).
      // The desired STANDARD behavior (input.mouse.invertx is false),
      // however, is that moving the mouse right (left) turns right (left). Hence we subtract the delta from the yaw.
      static const Arcadia_BooleanValue inputMouseInvertXAxis = Arcadia_BooleanValue_False; // TODO: Move this into the configuration.
      delta = (Arcadia_Real32Value)event->x - self->mousePosition.oldx;
      if (inputMouseInvertXAxis) delta = -delta;
      self->viewer.yaw -= delta;
      while (self->viewer.yaw <= -360.f) {
        self->viewer.yaw += 360.f;
      }
      while (self->viewer.yaw >= 360.f) {
        self->viewer.yaw -= 360.f;
      }
      // "pitch" is a counter-clockwise rotation around the x-axis in a right-handed coordinate system.
      // By the right-hand rule, we determine x-going right.
      // By the curled-fingers rule, we determine the positive rotation direction is up and the negative rotation direction is down.
      // When the mouse moves up, the delta is negative, when mouse moves down, the delta is positive.
      // So moving th mouse up (down), we would turn down (up).
      // The desired STANDARD behavior (input.mouse.inverty is false),
      // however, is that moving the mouse up (down) turns up (down). Hence we subtract the delta from the pitch.
      static const Arcadia_BooleanValue inputMouseInvertYAxis = Arcadia_BooleanValue_False; // TODO: Move this into the configuration.
      delta = (Arcadia_Real32Value)event->y - self->mousePosition.oldy;
      if (inputMouseInvertYAxis) delta = -delta;
      self->viewer.pitch -= delta;
      // Confine pitch to [-80,+80] degrees.
      if (self->viewer.pitch < -80.f) {
        self->viewer.pitch = -80.f;
      } else if (self->viewer.pitch > 80.f) {
        self->viewer.pitch = 80.f;
      }
      self->mousePosition.oldx = (Arcadia_Real32Value)event->x;
      self->mousePosition.oldy = (Arcadia_Real32Value)event->y;
    } break;
  };
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
