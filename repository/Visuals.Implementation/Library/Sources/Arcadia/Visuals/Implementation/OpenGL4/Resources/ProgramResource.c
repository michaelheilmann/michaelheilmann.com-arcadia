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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/Utilities.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/FragmentProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexProgramResource.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.ProgramResource", Arcadia_Visuals_Implementation_OpenGL4_ProgramResource,
                         u8"Arcadia.Visuals.Implementation.ProgramResource", Arcadia_Visuals_Implementation_ProgramResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 3);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->dirty = Arcadia_BooleanValue_True;
  self->id = 0;
  self->vertexProgram = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Implementation_OpenGL4_VertexProgramResource_getType(thread));
  self->fragmentProgram = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_getType(thread));
  if (((Arcadia_Visuals_Implementation_Resource*)self->vertexProgram)->referenceCount == Arcadia_Integer32Value_Maximum | ((Arcadia_Visuals_Implementation_Resource*)self->fragmentProgram)->referenceCount == Arcadia_Integer32Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  ((Arcadia_Visuals_Implementation_Resource*)self->vertexProgram)->referenceCount++;
  ((Arcadia_Visuals_Implementation_Resource*)self->fragmentProgram)->referenceCount++;

  ((Arcadia_Visuals_Implementation_Resource*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_renderImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  assert(0 == self->id);
  assert(NULL == self->vertexProgram);
  assert(NULL == self->fragmentProgram);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  if (self->id) {
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
    gl->glDeleteProgram(self->id);
    self->id = 0;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  assert(0 == self->id);
  if (self->vertexProgram) {
    ((Arcadia_Visuals_Implementation_Resource*)self->vertexProgram)->referenceCount--;
    self->vertexProgram = NULL;
  }
  if (self->fragmentProgram) {
    ((Arcadia_Visuals_Implementation_Resource*)self->fragmentProgram)->referenceCount--;
    self->fragmentProgram = NULL;
  }
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  if (0 == self->id) {
    self->id = gl->glCreateProgram();
    if (0 == self->id) {
      return;
    }
  }
  if (self->dirty) {
    // (1) attach vertex program
    Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->vertexProgram);
    if (!self->vertexProgram->id) {
      return;
    }
    while (gl->glGetError()) { }
    gl->glAttachShader(self->id, self->vertexProgram->id);
    if (gl->glGetError()) {
      return;
    }
    // (2) attach fragment program
    Arcadia_Visuals_Implementation_Resource_render(thread, (Arcadia_Visuals_Implementation_Resource*)self->fragmentProgram);
    if (!self->fragmentProgram->id) {
      return;
    }
    while (gl->glGetError()) { }
    gl->glAttachShader(self->id, self->fragmentProgram->id);
    if (gl->glGetError()) {
      return;
    }
    // (3) link program
    while (gl->glGetError()) { }
    gl->glLinkProgram(self->id);
    GLint success = GL_FALSE;
    gl->glGetProgramiv(self->id, GL_LINK_STATUS, &success);
    if (!success) {
      return;
    } else {
      self->dirty = Arcadia_BooleanValue_False;
    }
  }
}

Arcadia_Visuals_Implementation_OpenGL4_ProgramResource*
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_OpenGL4_VertexProgramResource* vertexProgram,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* fragmentProgram
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (vertexProgram) Arcadia_ValueStack_pushObjectReferenceValue(thread, vertexProgram); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (fragmentProgram) Arcadia_ValueStack_pushObjectReferenceValue(thread, fragmentProgram); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_ProgramResource);
}
