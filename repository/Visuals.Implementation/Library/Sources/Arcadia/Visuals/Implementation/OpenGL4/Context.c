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

#define ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Visuals/Implementation/OpenGL4/Context.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <GL/gl.h>
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_getClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value* red,
    Arcadia_Real32Value* green,
    Arcadia_Real32Value* blue,
    Arcadia_Real32Value* alpha
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_getClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value* depth
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_getViewportImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* top,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* bottom
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value depth
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_setViewportImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value top,
    Arcadia_Real32Value right,
    Arcadia_Real32Value bottom
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self
  );
  
static void
Arcadia_Visuals_Implementation_OpenGL4_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Visuals_Implementation_OpenGL4_Context_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_Context_construct,
  .destruct = &Arcadia_Visuals_Implementation_OpenGL4_Context_destruct,
  .visit = &Arcadia_Visuals_Implementation_OpenGL4_Context_visit,
};

static const Arcadia_Type_Operations _Arcadia_Visuals_Implementation_OpenGL4_Context_typeOperations = {
  .objectTypeOperations = &_Arcadia_Visuals_Implementation_OpenGL4_Context_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"Arcardia.Visuals.Implementation.OpenGL4.Context", Arcadia_Visuals_Implementation_OpenGL4_Context,
                         u8"Arcadia.Visuals.Context", Arcadia_Visuals_Context,
                         &_Arcadia_Visuals_Implementation_OpenGL4_Context_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_getClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value* red,
    Arcadia_Real32Value* green,
    Arcadia_Real32Value* blue,
    Arcadia_Real32Value* alpha
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_getClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value* depth
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_getViewportImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* bottom,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* top
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
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
  self->hasRenderTarget = Arcadia_BooleanValue_False;
  self->renderTargetSize.width = 320;
  self->renderTargetSize.height = 240;
  glClearColor(self->clearColor.red, self->clearColor.green, self->clearColor.blue, self->clearColor.alpha);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value depth
  )
{
  self->clearDepth = depth;
  glClearDepth(self->clearDepth);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_setViewportImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  )
{
  self->viewport.left = left;
  self->viewport.bottom = bottom;
  self->viewport.right = right;
  self->viewport.top = top;
  glViewport(left, self->viewport.bottom, self->viewport.right - self->viewport.left, self->viewport.top - self->viewport.bottom);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_Context_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->clearColor.red = 193;
  self->clearColor.green = 216;
  self->clearColor.blue = 195;
  self->clearColor.alpha = 255;

  self->clearDepth = 1.f;

  self->viewport.left = 0.f;
  self->viewport.bottom = 0.f;
  self->viewport.right = 1.f;
  self->viewport.top = 1.f;

  ((Arcadia_Visuals_Context*)self)->setClearColor = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Context*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value))& Arcadia_Visuals_Implementation_OpenGL4_Context_setClearColorImpl;
  ((Arcadia_Visuals_Context*)self)->setClearDepth = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Context*, Arcadia_Real32Value))& Arcadia_Visuals_Implementation_OpenGL4_Context_setClearDepthImpl;
  ((Arcadia_Visuals_Context*)self)->setViewport = (void (*)(Arcadia_Thread * thread, Arcadia_Visuals_Context*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value))& Arcadia_Visuals_Implementation_OpenGL4_Context_setViewportImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self
  )
{/*Intentionally empty.*/}

Arcadia_Visuals_Implementation_OpenGL4_Context*
Arcadia_Visuals_Implementation_OpenGL4_Context_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_Context);
}

void
Arcadia_Visuals_Implementation_OpenGL4_Context_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self,
    Arcadia_Visuals_Window* window
  )
{
  Arcadia_Integer32Value width, height;
  Arcadia_Visuals_Window_getCanvasSize(thread, window, &width, &height);
  
  glViewport(0, 0, width, height);
  glEnable(GL_SCISSOR_TEST);
  glScissor(0, 0, width, height);

  glClearDepth(self->clearDepth);
  glClear(GL_DEPTH_BUFFER_BIT);

  glClearColor((Arcadia_Real32Value)self->clearColor.red / 255.0f,
               (Arcadia_Real32Value)self->clearColor.green / 255.0f,
               (Arcadia_Real32Value)self->clearColor.blue / 255.0f,
               (Arcadia_Real32Value)self->clearColor.alpha / 255.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
