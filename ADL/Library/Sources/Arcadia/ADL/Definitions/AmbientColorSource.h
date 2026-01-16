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

#if !defined(ARCADIA_ADL_DEFINITIONS_AMBIENTCOLORSOURCE_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_AMBIENTCOLORSOURCE_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"

// Enumeration of ambient color sources.
//
// @code
// enumeration Arcadia.ADL.AmbientSource {
//   Mesh,
//   Vertex,
//   Texture
// };
// @endcode
Arcadia_declareEnumerationType(u8"Arcadia.ADL.AmbientColorSource", Arcadia_ADL_AmbientColorSource);

enum Arcadia_ADL_AmbientColorSource {
  Arcadia_ADL_AmbientColorSource_Mesh,
  Arcadia_ADL_AmbientColorSource_Vertex,
  Arcadia_ADL_AmbientColorSource_Texture,
};

#endif  // ARCADIA_ADL_DEFINITIONS_AMBIENTCOLORSOURCE_H_INCLUDED
