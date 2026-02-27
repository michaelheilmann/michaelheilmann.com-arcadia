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

#if !defined(ARCADIA_VPL_CONSTANTSCALAR_H_INCLUDED)
#define ARCADIA_VPL_CONSTANTSCALAR_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Symbols/Constant.h"
typedef struct Arcadia_VPL_Program Arcadia_VPL_Program;

// A constant scalar.
// The "constant scalar" maps to an "uniform block" of the scalar's name containing a single field called "value".
//
// ```
// 'constant' 'scalar' <name> ':' <type> ';'
// ```
Arcadia_declareObjectType(u8"Arcadia.VPL.ConstantScalar", Arcadia_VPL_ConstantScalar,
                          u8"Arcadia.VPL.Constant");

struct Arcadia_VPL_ConstantScalarDispatch {
  Arcadia_VPL_ConstantDispatch _parent;
};

struct Arcadia_VPL_ConstantScalar {
  Arcadia_VPL_Constant _parent;
  Arcadia_String* name;
  Arcadia_String* type;
  /// The program owning this constant scalar.
  Arcadia_VPL_Program* program;
};

/// @brief Create a constant scalar.
/// @param thread A pointer to this thread.
/// @param name The name.
/// @param type The type.
/// @param program The program.
Arcadia_VPL_ConstantScalar*
Arcadia_VPL_ConstantScalar_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_String* type,
    Arcadia_VPL_Program* program
  );

#endif // ARCADIA_VPL_CONSTANTSCALAR_H_INCLUDED
