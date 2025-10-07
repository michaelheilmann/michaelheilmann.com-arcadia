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

#include "Arcadia/Visuals/Implementation/OpenGL4/Mesh.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #define WIN32_LEAN_AND_MEAN
  #define NOCOMM
  #include <Windows.h>
  #include <GL/gl.h>
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include <GL/gl.h>
#else
  #error("environment not (yet) supported")
#endif

static void
Arcadia_Visuals_Implementation_OpenGL4_Mesh_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Mesh* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Mesh_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Mesh* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Mesh_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Mesh* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_Mesh_constructImpl,
  .destruct = &Arcadia_Visuals_Implementation_OpenGL4_Mesh_destructImpl,
  .visit = &Arcadia_Visuals_Implementation_OpenGL4_Mesh_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.Mesh", Arcadia_Visuals_Implementation_OpenGL4_Mesh,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_Mesh_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Mesh* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_Mesh_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->clearColor.red = 193;
  self->clearColor.green = 216;
  self->clearColor.blue = 195;
  self->clearColor.alpha = 255;
  self->clearDepth = 1.0f;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_Mesh_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Mesh* self
  )
{ }

static void
Arcadia_Visuals_Implementation_OpenGL4_Mesh_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Mesh* self
  )
{ }

Arcadia_Visuals_Implementation_OpenGL4_Mesh*
Arcadia_Visuals_Implementation_OpenGL4_Mesh_create
  (
    Arcadia_Thread* thread
  ) 
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_Mesh);
}

void
Arcadia_Visuals_Implementation_OpenGL4_Mesh_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Mesh* self,
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
