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

#include "Arcadia/Ring2/Include.h"

#include "Arcadia/Visuals/VPL/Program.h"

// Mutually exclusive to Arcadia_Visuals_VPL_ProgramFlags_VertexAmbientColor and Arcdia_Visuals_VPL_ProgramFlags_TextureAmbientColor.
#define Arcadia_Visuals_VPL_ProgramFlags_MeshAmbientColor (1)

// Mutually exclusive to Arcadia_Visuals_VPL_ProgramFlags_MeshAmbientColor and Arcadia_Visuals_VPL_ProgramFlags_TextureAmbientColor.
#define Arcadia_Visuals_VPL_ProgramFlags_VertexAmbientColor (2)

// Mutually exclusive to Arcadia_Visuals_VPL_ProgramFlags_MeshAmbientColor and Arcadia_Visuals_VPL_ProgramFlags_VertexAmbientColor.
#define Arcadia_Visuals_VPL_ProgramFlags_TextureAmbientColor (3)

// Programs are managed by the program manager.
// Each program has a unique numeric ID.
// Using this ID, backends can determine if they already have a uploaded a variant of that program.
Arcadia_declareObjectType(u8"Arcadia.Visuals.VPL.Program", Arcadia_Visuals_VPL_Program,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_VPL_ProgramDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Visuals_VPL_Program {
  Arcadia_Object _parent;
  /// The flags for this program.
  /// Must be one of Arcadia_Visuals_VPL_ProgramFlags_PerMeshColor or Arcadia_Visuals_VPL_ProgramFlags_PerVertexColor.
  Arcadia_Natural8Value flags;
  // 'mat4' as used by the VPL.
  // happens that this currently coincides with 'vec4' in GLSL.
  Arcadia_String* MAT4;
  // 'vec4' as used by the VPL.
  // happens that this currently coincides with 'vec4' in GLSL.
  Arcadia_String* VEC4;
  // 'vec3' as used by the VPL.
  // happens that this currently coincides with 'vec3' in GLSL.
  Arcadia_String* VEC3;
  // The list of vertex program constant blocks of this program.
  Arcadia_List* constantBlocks;
  // The list of vertex program variable scalars of this program.
  Arcadia_List* variableScalars;
};

Arcadia_Visuals_VPL_Program*
Arcadia_Visuals_VPL_Program_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags
  );

#endif // ARCADIA_VISUALS_VPL_PROGRAM_H_INCLUDED
