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

#if !defined(ARCADIA_VISUALS_VPL_PROGRAM_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_PROGRAM_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/Languages/Include.h"

typedef struct Arcadia_VPL_ConstantRecord Arcadia_VPL_ConstantRecord;
typedef struct Arcadia_VPL_BuiltinType Arcadia_VPL_BuiltinType;
typedef struct Arcadia_VPL_Tree_Node Arcadia_VPL_Tree_Node;

// Mutually exclusive to Arcadia_VPL_ProgramFlags_VertexAmbientColor and Arcdia_Visuals_VPL_ProgramFlags_TextureAmbientColor.
#define Arcadia_VPL_ProgramFlags_MeshAmbientColor (1)

// Mutually exclusive to Arcadia_VPL_ProgramFlags_MeshAmbientColor and Arcadia_VPL_ProgramFlags_TextureAmbientColor.
#define Arcadia_VPL_ProgramFlags_VertexAmbientColor (2)

// Mutually exclusive to Arcadia_VPL_ProgramFlags_MeshAmbientColor and Arcadia_VPL_ProgramFlags_VertexAmbientColor.
#define Arcadia_VPL_ProgramFlags_TextureAmbientColor (3)

// Programs are managed by the program manager.
// Each program has a unique numeric ID.
// Using this ID, backends can determine if they already have a uploaded a variant of that program.
Arcadia_declareObjectType(u8"Arcadia.VPL.Program", Arcadia_VPL_Program,
                          u8"Arcadia.Object");

struct Arcadia_VPL_ProgramDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_VPL_Program {
  Arcadia_Object _parent;
  /// The flags for this program.
  /// Must be one of Arcadia_VPL_ProgramFlags_PerMeshColor or Arcadia_VPL_ProgramFlags_PerVertexColor.
  Arcadia_Natural8Value flags;

  // `mat4` as used by the VPL.
  // Happens that this currently coincides with `mat4` in GLSL.
  Arcadia_VPL_BuiltinType* MAT4;

  // `vec4` as used by the VPL.
  // Happens that this currently coincides with `vec4` in GLSL.
  Arcadia_VPL_BuiltinType* VEC4;

  // `vec3` as used by the VPL.
  // Happens that this currently coincides with `vec3` in GLSL.
  Arcadia_VPL_BuiltinType* VEC3;

  // `vec2` as used by the VPL.
  // Happens that this currently coincides with `vec2` in GLSL.
  Arcadia_VPL_BuiltinType* VEC2;

  // `sampler2D` as used by the VPL.
  // Happens that this currently coincides with `sampler2D` in GLSL.
  Arcadia_VPL_BuiltinType* SAMPLER2D;

  /// The program scope.
  /// The following symbols are added:
  /// the "mat4", "sampler2D", "vec2", "vec3", "vec4" built-in types
  /// all "constant records" and "constant scalars"
  Arcadia_Languages_Scope* scope;

  /// The "main" function of the vertex program.
  Arcadia_VPL_Tree_Node* vertexProgramMain;
  /// The "main" function of the fragment program.
  Arcadia_VPL_Tree_Node* fragmentProgramMain;  

  // The list of constants (e.g., constant records, constant scalars, etc.) of this program.
  Arcadia_List* constants;
  // The main function of the vertex shader.
  // The main function of the fragment shader.

  // The list of vertex program variable scalars of this program.
  Arcadia_List* variableScalars;
};

Arcadia_VPL_Program*
Arcadia_VPL_Program_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags
  );

/// @return A pointer to the constant block if it was found. The null pointer if it was not found.
Arcadia_VPL_ConstantRecord*
Arcadia_VPL_Program_getConstantBlockByName
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self,
    Arcadia_String* name
  );

Arcadia_List*
Arcadia_VPL_Program_getConstantBlocks
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self
  );

Arcadia_VPL_Program*
Arcadia_VPL_Program_createProgram
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags
  );

#endif // ARCADIA_VISUALS_VPL_PROGRAM_H_INCLUDED
