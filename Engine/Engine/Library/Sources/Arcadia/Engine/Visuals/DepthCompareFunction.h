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

#ifndef ARCADIA_ENGINE_VISUALS_DEPTHCOMPAREFUNCTION_H_INCLUDED
#define ARCADIA_ENGINE_VISUALS_DEPTHCOMPAREFUNCTION_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

Arcadia_declareEnumerationType("Arcadia.Engine.Visuals.DepthCompareFunction",
                               Arcadia_Engine_Visuals_DepthCompareFunction);

enum Arcadia_Engine_Visuals_DepthCompareFunction {

  Arcadia_Engine_Visuals_DepthCompareFunction_Always = 0,

  Arcadia_Engine_Visuals_DepthCompareFunction_Never = 1,

  Arcadia_Engine_Visuals_DepthCompareFunction_Equal = 2,

  Arcadia_Engine_Visuals_DepthCompareFunction_NotEqual = 3,

  Arcadia_Engine_Visuals_DepthCompareFunction_LessThan = 4,

  Arcadia_Engine_Visuals_DepthCompareFunction_LessThanOrEqualTo = 5,

  Arcadia_Engine_Visuals_DepthCompareFunction_GreaterThan = 6,

  Arcadia_Engine_Visuals_DepthCompareFunction_GreaterThanOrEqualTo = 7,

};

#endif // ARCADIA_ENGINE_VISUALS_DEPTHCOMPAREFUNCTION_H_INCLUDED
