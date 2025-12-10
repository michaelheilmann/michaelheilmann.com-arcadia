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

#if !defined(ARCADIA_VISUALS_DEPTHCOMPAREFUNCTION_H_INCLUDED)
#define ARCADIA_VISUALS_DEPTHCOMPAREFUNCTION_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Visuals_DepthCompareFunction
Arcadia_declareEnumerationType(u8"Arcadia.Visuals.DepthCompareFunction", Arcadia_Visuals_DepthCompareFunction);

enum Arcadia_Visuals_DepthCompareFunction {

  Arcadia_Visuals_DepthCompareFunction_Always,

  Arcadia_Visuals_DepthCompareFunction_Never,

  Arcadia_Visuals_DepthCompareFunction_Equal,

  Arcadia_Visuals_DepthCompareFunction_NotEqual,

  Arcadia_Visuals_DepthCompareFunction_LessThan,

  Arcadia_Visuals_DepthCompareFunction_LessThanOrEqualTo,

  Arcadia_Visuals_DepthCompareFunction_GreaterThan,

  Arcadia_Visuals_DepthCompareFunction_GreaterThanOrEqualTo,

};

#endif // ARCADIA_VISUALS_DEPTHCOMPAREFUNCTION_H_INCLUDED
