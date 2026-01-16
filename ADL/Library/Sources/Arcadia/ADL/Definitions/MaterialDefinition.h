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

#if !defined(ARCADIA_ADL_DEFINITIONS_MATERIALDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_MATERIALDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"
#include "Arcadia/ADL/Definitions/AmbientColorSource.h"
#include "Arcadia/ADL/Definitions/MaterialType.h"
#include "Arcadia/ADL/Reference.h"

// The definition of a color.
//
// @code
// {
//   type  : "Material",
//   name  : "MyGame.Materials.MyMaterial",
//   materialType : "Blinn-Phong",
//   ambientSource : "Mesh",
// }
// @endcode
//
// @code
// 
// enumeration Arcadia.ADL.MaterialType {
//   BlinnPhong,
// }
// 
// enumeration Arcadia.ADL.AmbientSource {
//   Mesh,
//   Vertex,
//   Texture,
// }
// 
// class Arcadia.ADL.MaterialDefinition extends Arcadia.ADL.Definition {
//
//   constructor(definitions : Arcadia.ADL.Definitions, name : Arcadia.String,
//               materialType : Arcadial.ADL.MaterialType, ambientColorSource : Arcadia.ADL.AmbientColorSource)
//
// };
// 
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.MaterialDefinition", Arcadia_ADL_MaterialDefinition,
                          u8"Arcadia.ADL.Definition");

struct Arcadia_ADL_MaterialDefinitionDispatch {
  Arcadia_ADL_DefinitionDispatch _parent;
};

struct Arcadia_ADL_MaterialDefinition {
  Arcadia_ADL_Definition _parent;
  Arcadia_ADL_MaterialType materialType;
  Arcadia_ADL_AmbientColorSource ambientColorSource;
  Arcadia_ADL_Reference* ambientColorTexture;
};

Arcadia_ADL_MaterialDefinition*
Arcadia_ADL_MaterialDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_ADL_MaterialType materialType,
    Arcadia_ADL_AmbientColorSource ambientColorSource,
    Arcadia_String* ambientColorTextureName
  );

#endif  // ARCADIA_ADL_DEFINITIONS_MATERIALDEFINITION_H_INCLUDED
