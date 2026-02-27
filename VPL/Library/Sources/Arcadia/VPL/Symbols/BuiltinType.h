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

#if !defined(ARCADIA_VISUALS_VPL_BUILTINTYPE_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_BUILTINTYPE_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

// A member of a constant record.
Arcadia_declareObjectType(u8"Arcadia.VPL.BuiltinType", Arcadia_VPL_BuiltinType,
                          u8"Arcadia.Object");

struct Arcadia_VPL_BuiltinTypeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_VPL_BuiltinType {
  Arcadia_Object _parent;
  Arcadia_String* name;
  Arcadia_String* type;
};

Arcadia_VPL_BuiltinType*
Arcadia_VPL_BuiltinType_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

#endif // ARCADIA_VISUALS_VPL_BUILTINTYPE_H_INCLUDED
