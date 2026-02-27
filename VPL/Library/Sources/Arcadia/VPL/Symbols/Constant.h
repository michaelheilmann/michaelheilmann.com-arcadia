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

#if !defined(ARCADIA_VPL_CONSTANT_H_INCLUDED)
#define ARCADIA_VPL_CONSTANT_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/Languages/Include.h"
#include "Arcadia/VPL/Symbols/ConstantKind.h"

// A constant. Can be either a constant record or a constant scalar.
Arcadia_declareObjectType(u8"Arcadia.VPL.Constant", Arcadia_VPL_Constant,
                          u8"Arcadia.Object");

struct Arcadia_VPL_ConstantDispatch {
  Arcadia_ObjectDispatch _parent;
  Arcadia_String* (*getName)(Arcadia_Thread*, Arcadia_VPL_Constant*);
  Arcadia_VPL_ConstantKind (*getKind)(Arcadia_Thread*, Arcadia_VPL_Constant*);
};

struct Arcadia_VPL_Constant {
  Arcadia_Object _parent;
  Arcadia_String* name;
};

/// @brief Get the name of this constant.
/// @param thread A pointer to this thread.
/// @param self A pointer to this constant.
/// @return The name of this constant.
Arcadia_String*
Arcadia_VPL_Constant_getName
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Constant* self
  );
  
/// @brief Get the kind of this constant.
/// @param thread A pointer to this thread.
/// @param self A pointer to this constant.
/// @return The kind of this constant.
Arcadia_VPL_ConstantKind
Arcadia_VPL_Constant_getKind
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Constant* self
  );

#endif // ARCADIA_VPL_CONSTANT_H_INCLUDED
