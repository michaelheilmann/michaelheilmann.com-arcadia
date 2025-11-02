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

#if !defined(ARCADIA_VISUALS_VPL_BACKENDS_GLSL_FIELD_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_BACKENDS_GLSL_FIELD_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.VPL.Backends.GLSL.Field", Arcadia_Visuals_VPL_Backends_GLSL_Field,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_VPL_Backends_GLSL_Field {
  Arcadia_Object _parent;
  Arcadia_String* name;
  Arcadia_String* type;
};

Arcadia_Visuals_VPL_Backends_GLSL_Field*
Arcadia_Visuals_VPL_Backends_GLSL_Field_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_String* type
  );

#endif // ARCADIA_VISUALS_VPL_BACKENDS_GLSL_FIELD_H_INCLUDED
