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

#ifndef ARCADIA_ENGINE_VISUALS_FILLMODE_H_INCLUDED
#define ARCADIA_ENGINE_VISUALS_FILLMODE_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

Arcadia_declareEnumerationType("Arcadia.Engine.Visuals.FillMode",
                               Arcadia_Engine_Visuals_FillMode);

enum Arcadia_Engine_Visuals_FillMode {

  Arcadia_Engine_Visuals_FillMode_Point = 0,

  Arcadia_Engine_Visuals_FillMode_Line = 1,

  Arcadia_Engine_Visuals_FillMode_Solid = 2,

};

#endif // ARCADIA_ENGINE_VISUALS_FILLMODE_H_INCLUDED
