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
Arcadia_Visuals_OpenGl_Context_getClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value* red,
    Arcadia_Real32Value* green,
    Arcadia_Real32Value* blue,
    Arcadia_Real32Value* alpha
  );

static void
Arcadia_Visuals_OpenGl_Context_getClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value* depth
  );

static void
Arcadia_Visuals_OpenGl_Context_getViewportImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* top,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* bottom
  );

static void
Arcadia_Visuals_OpenGl_Context_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  );

static void
Arcadia_Visuals_OpenGl_Context_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value depth
  );

static void
Arcadia_Visuals_OpenGl_Context_setViewportImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value top,
    Arcadia_Real32Value right,
    Arcadia_Real32Value bottom
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Visuals_OpenGl_Context_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_OpenGl_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self
  );
  
static void
Arcadia_Visuals_OpenGl_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Visuals_OpenGl_Context_objectTypeOperations = {
  .construct = &Arcadia_Visuals_OpenGl_Context_construct,
  .destruct = &Arcadia_Visuals_OpenGl_Context_destruct,
  .visit = &Arcadia_Visuals_OpenGl_Context_visit,
};

static const Arcadia_Type_Operations _Arcadia_Visuals_Context_typeOperations = {
  .objectTypeOperations = &_Arcadia_Visuals_OpenGl_Context_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcardia.Visuals.OpenGl.Context", Arcadia_Visuals_OpenGl_Context,
                         u8"Arcadia.Visuals.Context", Arcadia_Visuals_Context,
                         &_Arcadia_Visuals_Context_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Visuals_OpenGl_Context_getClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value* red,
    Arcadia_Real32Value* green,
    Arcadia_Real32Value* blue,
    Arcadia_Real32Value* alpha
  );

static void
Arcadia_Visuals_OpenGl_Context_getClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value* depth
  );

static void
Arcadia_Visuals_OpenGl_Context_getViewportImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* bottom,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* top
  );

static void
Arcadia_Visuals_OpenGl_Context_setClearColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
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
Arcadia_Visuals_OpenGl_Context_setClearDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
    Arcadia_Real32Value depth
  )
{
  self->clearDepth = depth;
  glClearDepth(self->clearDepth);
}

static void
Arcadia_Visuals_OpenGl_Context_setViewportImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self,
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
Arcadia_Visuals_OpenGl_Context_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_OpenGl_Context* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_OpenGl_Context_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  _self->clearColor.red = 0.f;
  _self->clearColor.green = 0.f;
  _self->clearColor.blue = 0.f;
  _self->clearColor.alpha = 1.f;

  _self->clearDepth = 1.f;

  _self->viewport.left = 0.f;
  _self->viewport.bottom = 0.f;
  _self->viewport.right = 1.f;
  _self->viewport.top = 1.f;

  ((Arcadia_Visuals_Context*)_self)->setClearColor = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Context*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value))&Arcadia_Visuals_OpenGl_Context_setClearColorImpl;
  ((Arcadia_Visuals_Context*)_self)->setClearDepth = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Context*, Arcadia_Real32Value))&Arcadia_Visuals_OpenGl_Context_setClearDepthImpl;
  ((Arcadia_Visuals_Context*)_self)->setViewport = (void (*)(Arcadia_Thread * thread, Arcadia_Visuals_Context*, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value, Arcadia_Real32Value))&Arcadia_Visuals_OpenGl_Context_setViewportImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Visuals_OpenGl_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_OpenGl_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGl_Context* self
  )
{/*Intentionally empty.*/}
