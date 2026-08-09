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

#if !defined(ARCADIA_MILC_TYPE_H_INCLUDED)
#define ARCADIA_MILC_TYPE_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

/// @brief The base of all types.
Arcadia_declareObjectType(u8"Arcadia.MILC.Type", Arcadia_MILC_Type,
                          u8"Arcadia.Object");

struct Arcadia_MILC_TypeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_Type {
  Arcadia_Object _parent;
};

#endif // ARCADIA_MILC_TYPE_H_INCLUDED
