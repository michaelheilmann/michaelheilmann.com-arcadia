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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ViewportResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self,
    Arcadia_Visuals_Implementation_MeshContextResource* meshContextResource
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.ViewportResource", Arcadia_Visuals_Implementation_OpenGL4_ViewportResource,
                         u8"Arcadia.Visuals.Implementation.ViewportResource", Arcadia_Visuals_Implementation_ViewportResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->clearColor.red = 193;
  self->clearColor.green = 216;
  self->clearColor.blue = 195;
  self->clearColor.alpha = 255;

  self->clearDepth = 1.f;

  self->relativeViewportRectangle.left = 0.f;
  self->relativeViewportRectangle.bottom = 0.f;
  self->relativeViewportRectangle.right = 1.f;
  self->relativeViewportRectangle.top = 1.f;

  self->canvasSize.width = 320.f;
  self->canvasSize.height = 240.f;

  ((Arcadia_Visuals_Implementation_ViewportResource*)self)->setCanvasSize = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ViewportResource*, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setCanvasSizeImpl;
  ((Arcadia_Visuals_Implementation_ViewportResource*)self)->setClearColor = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ViewportResource*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setClearColorImpl;
  ((Arcadia_Visuals_Implementation_ViewportResource*)self)->setRelativeViewportRectangle = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ViewportResource*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value)) & Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setRelativeViewportRectangleImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_loadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_MeshContextResource*)) & Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_renderImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  )
{
  self->clearColor.red = red;
  self->clearColor.green = green;
  self->clearColor.blue = blue;
  self->clearColor.alpha = alpha;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setRelativeViewportRectangleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  )
{
  self->relativeViewportRectangle.left = left;
  self->relativeViewportRectangle.bottom = bottom;
  self->relativeViewportRectangle.right = right;
  self->relativeViewportRectangle.top = top;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_setCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  )
{
  self->canvasSize.width = width;
  self->canvasSize.height = height;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  )
{ }

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  )
{ }

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self
  )
{
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ViewportResource* self,
    Arcadia_Visuals_Implementation_MeshContextResource* meshContextResource
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  Arcadia_Real32Value l = self->canvasSize.width * self->relativeViewportRectangle.left,
                      b = self->canvasSize.height * self->relativeViewportRectangle.bottom,
                      w = self->canvasSize.width * self->relativeViewportRectangle.right - self->canvasSize.width * self->relativeViewportRectangle.left,
                      h = self->canvasSize.height * self->relativeViewportRectangle.top - self->canvasSize.height * self->relativeViewportRectangle.bottom;
  gl->glViewport(l, b, w, h);
  gl->glEnable(GL_SCISSOR_TEST);
  gl->glScissor(l, b, w, h);

  gl->glClearDepth(self->clearDepth);
  gl->glClear(GL_DEPTH_BUFFER_BIT);

  gl->glClearColor((Arcadia_Real32Value)self->clearColor.red / 255.0f,
                   (Arcadia_Real32Value)self->clearColor.green / 255.0f,
                   (Arcadia_Real32Value)self->clearColor.blue / 255.0f,
                   (Arcadia_Real32Value)self->clearColor.alpha / 255.0f);
  gl->glClear(GL_COLOR_BUFFER_BIT);
}

Arcadia_Visuals_Implementation_OpenGL4_ViewportResource*
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_ViewportResource);
}
