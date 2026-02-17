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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/BackendIncludes.h"
#include <assert.h>
#include "Arcadia/Visuals/Implementation/VPL/GLSL/Include.h"

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResourceDispatch* self
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

typedef enum ShaderType {
  VertexShader,
  FragmentShader,
} ShaderType;

static Arcadia_BooleanValue
createOrUpdateShader
  (
    Arcadia_Thread* thread,
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl,
    Arcadia_BooleanValue* dirty,
    GLuint* id,
    ShaderType shaderType,
    Arcadia_Visuals_VPL_Program* program
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_loadImpl
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
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self,
    Arcadia_Visuals_Implementation_EnterPassResource* renderingContextNode
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_destructImpl,
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
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->dirty = Arcadia_BooleanValue_True;
  self->vertexShaderID = 0;
  self->fragmentShaderID = 0;
  self->programID = 0;
  self->program = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_VPL_Program_getType(thread));

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResourceDispatch* self
  )
{
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_EnterPassResource*)) & Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_renderImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  assert(0 == self->vertexShaderID);
  assert(0 == self->fragmentShaderID);
  assert(0 == self->programID);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  if (self->program) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->program);
  }
}

static Arcadia_BooleanValue
createOrUpdateShader
  (
    Arcadia_Thread* thread,
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl,
    Arcadia_BooleanValue *dirty,
    GLuint* id,
    ShaderType shaderType,
    Arcadia_Visuals_VPL_Program* program
  )
{
  if (0 == *id) {
    switch (shaderType) {
      case VertexShader: {
        *id = gl->glCreateShader(GL_VERTEX_SHADER);
        *dirty = Arcadia_BooleanValue_True;
      } break;
      case FragmentShader: {
        *id = gl->glCreateShader(GL_FRAGMENT_SHADER);
        *dirty = Arcadia_BooleanValue_True;
      } break;
      default: {
        return Arcadia_BooleanValue_False;
      } break;
    };
    if (0 == *id) {
      return Arcadia_BooleanValue_False;
    }
  }
  if (*dirty) {
    Arcadia_ByteBuffer* code = Arcadia_ByteBuffer_create(thread);
    switch (shaderType) {
      case VertexShader: {
        Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* transpiler = Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_create(thread);
        Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_writeDefaultVertexShader(thread, transpiler, program, code);
      } break;
      case FragmentShader: {
        Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* transpiler = Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_create(thread);
        Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader(thread, transpiler, program, code);
      } break;
      default: {
        return Arcadia_BooleanValue_False;
      } break;
    };
    // (1) set shader source
    while (gl->glGetError()) { }
    const GLchar* temporary = Arcadia_ByteBuffer_getBytes(thread, code);
    gl->glShaderSource(*id, 1, &temporary, NULL);
    if (gl->glGetError()) {
      return Arcadia_BooleanValue_False;
    }
    // (2) compile shader
    while (gl->glGetError()) { }
    gl->glCompileShader(*id);
    if (gl->glGetError()) {
      return Arcadia_BooleanValue_False;
    }
    // (3) check if compilation was successful
    GLint success = GL_FALSE;
    gl->glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
    if (!success) {
      GLuint infoLogLength;
      gl->glGetShaderiv(*id, GL_INFO_LOG_LENGTH, &infoLogLength);
      GLchar* infoLog = malloc(sizeof(GLchar) + (infoLogLength + 1));
      if (!infoLog) {
        return Arcadia_BooleanValue_False;
      }
      gl->glGetShaderInfoLog(*id, infoLogLength, NULL, infoLog);
      free(infoLog);
      infoLog = NULL;
      return Arcadia_BooleanValue_False;
    } else {
      *dirty = Arcadia_BooleanValue_False;
    }
  }
  return Arcadia_BooleanValue_True;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
  _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);

  Arcadia_BooleanValue vertexShaderDirty = Arcadia_BooleanValue_False,
                       fragmentShaderDirty = Arcadia_BooleanValue_False;
  if (!createOrUpdateShader(thread, gl, &vertexShaderDirty, &self->vertexShaderID, VertexShader, self->program)) {
    return;
  }
  if (!createOrUpdateShader(thread, gl, &fragmentShaderDirty, &self->fragmentShaderID, FragmentShader, self->program)) {
    return;
  }
  if (0 == self->programID) {
    self->programID = gl->glCreateProgram();
    if (0 == self->programID) {
      return;
    }
  }
  if (self->dirty) {
    // (1) attach vertex program
    while (gl->glGetError()) { }
    gl->glAttachShader(self->programID, self->vertexShaderID);
    if (gl->glGetError()) {
      return;
    }
    // (2) attach fragment program
    while (gl->glGetError()) { }
    gl->glAttachShader(self->programID, self->fragmentShaderID);
    if (gl->glGetError()) {
      return;
    }
    // (3) link program
    while (gl->glGetError()) { }
    gl->glLinkProgram(self->programID);
    GLint success = GL_FALSE;
    gl->glGetProgramiv(self->programID, GL_LINK_STATUS, &success);
    if (!success) {
      return;
    } else {
      self->dirty = Arcadia_BooleanValue_False;
    }
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  if (self->programID) {
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
    gl->glDeleteProgram(self->programID);
    self->programID = 0;
  }
  if (self->fragmentShaderID) {
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
    gl->glDeleteShader(self->fragmentShaderID);
    self->fragmentShaderID = 0;
  }
  if (self->vertexShaderID) {
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* context = (Arcadia_Visuals_Implementation_OpenGL4_BackendContext*)((Arcadia_Visuals_Implementation_Resource*)self)->context;
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* gl = Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getFunctions(thread, context);
    gl->glDeleteShader(self->vertexShaderID);
    self->vertexShaderID = 0;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self
  )
{
  assert(0 == self->vertexShaderID);
  assert(0 == self->fragmentShaderID);
  assert(0 == self->programID);
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* self,
    Arcadia_Visuals_Implementation_EnterPassResource* renderingContextNode
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_loadImpl(thread, self);
}

Arcadia_Visuals_Implementation_OpenGL4_ProgramResource*
Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_VPL_Program* program
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (program) Arcadia_ValueStack_pushObjectReferenceValue(thread, program); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_ProgramResource);
}
