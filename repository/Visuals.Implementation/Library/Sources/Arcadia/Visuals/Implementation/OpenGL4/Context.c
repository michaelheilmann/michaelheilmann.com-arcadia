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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/FragmentProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ViewportResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"

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
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_Context_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_Context_visit,
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
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Window* window
  )
{
  Arcadia_Visuals_Implementation_ViewportResource* viewport1 = NULL,
                                                         * viewport2 = NULL;
  Arcadia_Visuals_Implementation_VertexBufferResource* vertexBuffer = NULL;
  Arcadia_Visuals_Implementation_ProgramResource* program = NULL;

  Arcadia_Integer32Value width, height;
  Arcadia_Visuals_Window_getCanvasSize(thread, window, &width, &height);

  {
    viewport1 =
      Arcadia_Visuals_Implementation_BackendContext_createViewportResource
        (
          thread,
          (Arcadia_Visuals_Implementation_BackendContext*)backendContext
        );
    Arcadia_Visuals_Implementation_ViewportResource_setClearColor(thread, viewport1, 255.f, 0.f, 0.f, 255.f);
    Arcadia_Visuals_Implementation_ViewportResource_setRelativeViewportRectangle(thread, viewport1, 0.f, 0.f, 0.5f, 1.f);
    Arcadia_Visuals_Implementation_ViewportResource_setCanvasSize(thread, viewport1, width, height);
  }
  {
    viewport2 =
      Arcadia_Visuals_Implementation_BackendContext_createViewportResource
        (
          thread,
          (Arcadia_Visuals_Implementation_BackendContext*)backendContext
        );
    Arcadia_Visuals_Implementation_ViewportResource_setClearColor(thread, viewport2, 0.f, 255.f, 0.f, 255.f);
    Arcadia_Visuals_Implementation_ViewportResource_setRelativeViewportRectangle(thread, viewport2, 0.5f, 0.f, 1.0f, 1.f);
    Arcadia_Visuals_Implementation_ViewportResource_setCanvasSize(thread, viewport2, width, height);
  }
  {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    vertexBuffer = Arcadia_Visuals_Implementation_BackendContext_createVertexBufferResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);
    Arcadia_Visuals_Implementation_VertexBufferResource_setData(thread, vertexBuffer, 3, (void*)vertices, sizeof(vertices));
    Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)vertexBuffer);
  }
  {
    Arcadia_Visuals_Implementation_VertexProgramResource* vertexProgram = NULL;
    Arcadia_Visuals_Implementation_FragmentProgramResource* fragmentProgram = NULL;

    vertexProgram = Arcadia_Visuals_Implementation_BackendContext_createVertexProgramResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);
    fragmentProgram = Arcadia_Visuals_Implementation_BackendContext_createFragmentProgramResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);

    program = Arcadia_Visuals_Implementation_BackendContext_createProgramResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext, vertexProgram, fragmentProgram);
    Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)program);
  }
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, backendContext);

  Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)viewport1);
  gl->glUseProgram(((Arcadia_Visuals_Implementation_OpenGL4_ProgramResource*)program)->id);
  gl->glBindVertexArray(((Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource*)vertexBuffer)->vertexArrayID);
  gl->glDrawArrays(GL_TRIANGLES, 0, 3);

  Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)viewport2);
  gl->glUseProgram(((Arcadia_Visuals_Implementation_OpenGL4_ProgramResource*)program)->id);
  gl->glBindVertexArray(((Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource*)vertexBuffer)->vertexArrayID);
  gl->glDrawArrays(GL_TRIANGLES, 0, 3);
}

void
Arcadia_Visuals_Implementation_OpenGL4_Context_invalidateAll
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Context* self
  )
{ }
