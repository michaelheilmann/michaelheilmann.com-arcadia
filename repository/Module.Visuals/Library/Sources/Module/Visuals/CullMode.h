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

// Last modified: 2025-03-30

#if !defined(MODULE_VISUALS_CULLMODE_H_INCLUDED)
#define MODULE_VISUALS_CULLMODE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// https://michaelheilmann.com/repository/Arcadia.Visuals/#Arcadia_Visuals_CullMode
Arcadia_declareEnumerationType(u8"Arcadia.Visuals.CullMode", Arcadia_Visuals_CullMode);

enum Arcadia_Visuals_CullMode {
  
  Arcadia_Visuals_CullMode_None,
  
  Arcadia_Visuals_CullMode_Front,

  Arcadia_Visuals_CullMode_Back,

  Arcadia_Visuals_CullMode_FrontAndBack,

  Arcadia_Visuals_CullMode_BackAndFront,

};

#endif // MODULE_VISUALS_CULLMODE_H_INCLUDED
