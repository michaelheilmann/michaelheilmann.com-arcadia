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

#if !defined(ARCADIA_VISUALS_VPL_BACKENDS_GLSL_VARIABLESCALAR_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_BACKENDS_GLSL_VARIABLESCALAR_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

/// @brief Representation of an input/output variable scalar.
Arcadia_declareObjectType(u8"Arcadia.Visuals.VPL.Backends.GLSL.VariableScalar", Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_VPL_Backends_GLSL_VariableScalarDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar {
  Arcadia_Object _parent;
  Arcadia_Integer32Value location;
  Arcadia_BooleanValue isInput;
  Arcadia_String* name;
  Arcadia_String* type;
};

/// @brief Create a variable scalar.
/// @param thread A pointer to this thread.
/// @param location The location of the variable scalar.
/// @param isInput If the variable scalar is an input or an output.
/// @param name The name of the variable scalar.
/// @param type The type of the variable scalar.
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar*
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value location,
    Arcadia_BooleanValue isInput,
    Arcadia_String* name,
    Arcadia_String* type
  );

#endif // ARCADIA_VISUALS_VPL_BACKENDS_GLSL_VARIABLESCALAR_H_INCLUDED
