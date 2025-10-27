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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/FragmentProgramResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.FragmentProgramResource", Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource,
                         u8"Arcadia.Visuals.Implementation.FragmentProgramResource", Arcadia_Visuals_Implementation_FragmentProgramResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_getType(thread);
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

  self->dirty = Arcadia_BooleanValue_True;
  self->id = 0;

  ((Arcadia_Visuals_Implementation_Resource*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_Resource*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_renderImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  )
{
  assert(0 == self->id);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  )
{
  if (self->id) {
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
    gl->glDeleteShader(self->id);
    self->id = 0;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  )
{
  assert(0 == self->id);
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
  static const char* program =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main() {\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n"
    ;
  if (0 == self->id) {
    // (1) create shader
    self->id = gl->glCreateShader(GL_FRAGMENT_SHADER);
    if (!self->id) {
      return;
    }
  }
  if (self->dirty) {
    // (1) set shader source
    while (gl->glGetError()) { }
    gl->glShaderSource(self->id, 1, &program, NULL);
    if (gl->glGetError()) {
      return;
    }
    // (2) compile shader
    while (gl->glGetError()) { }
    gl->glCompileShader(self->id);
    if (gl->glGetError()) {
      return;
    }
    // (3) check if compilation was successful
    GLint success = GL_FALSE;
    gl->glGetShaderiv(self->id, GL_COMPILE_STATUS, &success);
    if (!success) {
      return;
    } else {
      self->dirty = Arcadia_BooleanValue_False;
    }
  }
}

Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource*
Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_FragmentProgramResource);
}
