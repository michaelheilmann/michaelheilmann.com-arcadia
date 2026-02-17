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

#if !defined(ARCADIA_ENGINE_VISUALS_CULLMODE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_CULLMODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

// https://michaelheilmann.com/Arcadia/Engine/#Arcadia_Engine_Visuals_CullMode
Arcadia_declareEnumerationType(u8"Arcadia.Engine.Visuals.CullMode", Arcadia_Engine_Visuals_CullMode);

enum Arcadia_Engine_Visuals_CullMode {

  Arcadia_Engine_Visuals_CullMode_None,

  Arcadia_Engine_Visuals_CullMode_Front,

  Arcadia_Engine_Visuals_CullMode_Back,

  Arcadia_Engine_Visuals_CullMode_FrontAndBack,

  Arcadia_Engine_Visuals_CullMode_BackAndFront,

};

#endif // ARCADIA_ENGINE_VISUALS_CULLMODE_H_INCLUDED
