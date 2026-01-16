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

#if !defined(ARCADIA_ADL_DEFINITIONS_MESHDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_MESHDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"
#include "Arcadia/ADL/Reference.h"

// The definition of a color.
//
// @code
// {
//   type  : "Mesh",
//   name  : "MyGame.Meshes.MyMesh",
// }
// @endcode
//
// @code
// class Arcadia.ADL.MeshDefinition extends Arcadia.ADL.Definition {
//
//   constructor(definitions : Arcadia.ADL.Definitions, name : Arcadia.String)
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.MeshDefinition", Arcadia_ADL_MeshDefinition,
                          u8"Arcadia.ADL.Definition");

struct Arcadia_ADL_MeshDefinitionDispatch {
  Arcadia_ADL_DefinitionDispatch _parent;
};

struct Arcadia_ADL_MeshDefinition {
  Arcadia_ADL_Definition _parent;
  Arcadia_SizeValue numberOfVertices;
  Arcadia_InternalImmutableByteArray* vertexPositions;
  Arcadia_InternalImmutableByteArray* vertexAmbientColors;
  Arcadia_InternalImmutableByteArray* vertexAmbientTextureCoordinates;
  Arcadia_ADL_Reference* ambientColor;
  Arcadia_ADL_Reference* material;
};

Arcadia_ADL_MeshDefinition*
Arcadia_ADL_MeshDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_SizeValue numberOfVertices,
    Arcadia_InternalImmutableByteArray* vertexPositions,
    Arcadia_InternalImmutableByteArray* vertexAmbientColors,
    Arcadia_InternalImmutableByteArray* vertexAmbientTextureCoordinates,
    Arcadia_String* ambientColorName,
    Arcadia_String* materialName
  );

Arcadia_SizeValue
Arcadia_ADL_MeshDefinition_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  );

Arcadia_InternalImmutableByteArray*
Arcadia_ADL_MeshDefinition_getVertexPositions
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  );

Arcadia_InternalImmutableByteArray*
Arcadia_ADL_MeshDefinition_getVertexAmbientColors
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  );

Arcadia_InternalImmutableByteArray*
Arcadia_ADL_MeshDefinition_getVertexAmbientTextureCoordinates
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  );

#endif  // ARCADIA_ADL_DEFINITIONS_MESHDEFINITION_H_INCLUDED
