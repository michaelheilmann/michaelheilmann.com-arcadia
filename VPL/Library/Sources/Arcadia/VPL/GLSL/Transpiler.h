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
typedef struct Arcadia_VPL_Symbols_Program Arcadia_VPL_Symbols_Program;

typedef enum Context{
  Context_VertexShader,
  Context_FragmentShader,
} Context;


// Programs are managed by the program manager.
// Each program has a unique numeric ID.
// Using this ID, backends can determine if they already have a uploaded a variant of that program.
Arcadia_declareObjectType(u8"Arcadia.Visuals.VPL.Backends.GLSL.Transpiler", Arcadia_VPL_Backends_GLSL_Transpiler,
                          u8"Arcadia.Object");

struct Arcadia_VPL_Backends_GLSL_TranspilerDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_VPL_Backends_GLSL_Transpiler {
  Arcadia_Object _parent;

  /// @brief The number of constant blocks emitted so far.
  Arcadia_Natural32Value numberOfConstantBlocks;

  /// @brief A mapping from symbols to names.
  /// For example, we map the builtin procedure symbol "texture2D" to the name "texture2D" in the target language.
  /// For example, we map the name "fragmentProgram_inputs_vertex_ambientColor" to some computed name which does not cause conflicts in the target language.
  /// This mapping must be computed before emitting the target language code (obviously).
  Arcadia_Map* symbolNameMapping;
};

Arcadia_VPL_Backends_GLSL_Transpiler*
Arcadia_VPL_Backends_GLSL_Transpiler_create
  (
    Arcadia_Thread* thread
  );

/// @param constantMapping maps "VPL constant record names" / "VPL constant scalar names" to "OpenGL/GLSL uniform block names" and "OpenGL/GLSL uniform names".
void
Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultVertexShader
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Symbols_Program* program,
    Arcadia_Map* constantMapping,
    Arcadia_Map* vertexShaderVariableScalarMapping,
    Arcadia_ByteBuffer* target
  );

/// @param constantMapping maps "VPL constant record names" / "VPL constant scalar names" to "OpenGL/GLSL uniform block names" and "OpenGL/GLSL uniform names".
void
Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Symbols_Program* program,
    Arcadia_Map* constantMapping,
    Arcadia_Map* fragmentShaderVariableScalarMapping,
    Arcadia_String** fragmentColorOutput,
    Arcadia_ByteBuffer* target
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_VPL_GLSL_TRANSPILER_H_INCLUDED
