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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_VPL_GLSL_TRANSPILER_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_VPL_GLSL_TRANSPILER_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_Visuals_VPL_Program Arcadia_Visuals_VPL_Program;

typedef enum Context{
  Context_VertexShader,
  Context_FragmentShader,
} Context;

// Programs are managed by the program manager.
// Each program has a unique numeric ID.
// Using this ID, backends can determine if they already have a uploaded a variant of that program.
Arcadia_declareObjectType(u8"Arcadia.Visuals.VPL.Backends.GLSL.Transpiler", Arcadia_Visuals_VPL_Backends_GLSL_Transpiler,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_VPL_Backends_GLSL_TranspilerDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Visuals_VPL_Backends_GLSL_Transpiler {
  Arcadia_Object _parent;
  // 'mat4' as used by the VPL.
  // happens that this currently coincides with 'vec4' in GLSL.
  Arcadia_String* MAT4;
  // 'vec4' as used by the VPL.
  // happens that this currently coincides with 'vec4' in GLSL.
  Arcadia_String* VEC4;
  // 'vec3' as used by the VPL.
  // happens that this currently coincides with 'vec3' in GLSL.
  Arcadia_String* VEC3;
};

Arcadia_Visuals_VPL_Backends_GLSL_Transpiler*
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_writeDefaultVertexShader
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Program* program,
    Arcadia_ByteBuffer* target
  );

void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Program* program,
    Arcadia_ByteBuffer* target
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_VPL_GLSL_TRANSPILER_H_INCLUDED
