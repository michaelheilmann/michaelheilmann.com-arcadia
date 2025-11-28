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

#include "Arcadia/Visuals/Scene/MeshContext.h"

static void
Arcadia_Visuals_Scene_MeshContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self
  );

static void
Arcadia_Visuals_Scene_MeshContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self
  );

static void
Arcadia_Visuals_Scene_MeshContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Scene_MeshContext_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Scene_MeshContext_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Scene_MeshContext_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.MeshContext", Arcadia_Visuals_Scene_MeshContext,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_MeshContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_MeshContext_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->viewToProjectionMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->viewToProjectionMatrix);

  self->worldToViewMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->worldToViewMatrix);

  self->viewportClearColor.red = 193;
  self->viewportClearColor.green = 216;
  self->viewportClearColor.blue = 195;
  self->viewportClearColor.alpha = 255;

  self->viewportClearDepth = 1.f;

  self->relativeViewportRectangle.left = 0.f;
  self->relativeViewportRectangle.bottom = 0.f;
  self->relativeViewportRectangle.right = 1.f;
  self->relativeViewportRectangle.top = 1.f;

  self->canvasSize.width = 320.f;
  self->canvasSize.height = 240.f;

  self->render = NULL;
  self->setBackendContext = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_MeshContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Scene_MeshContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self
  )
{
  if (self->viewToProjectionMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->viewToProjectionMatrix);
  }
  if (self->worldToViewMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->worldToViewMatrix);
  }
}

void
Arcadia_Visuals_Scene_MeshContext_setBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ self->setBackendContext(thread, self, backendContext); }

void
Arcadia_Visuals_Scene_MeshContext_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self
  )
{ self->render(thread, self); }
