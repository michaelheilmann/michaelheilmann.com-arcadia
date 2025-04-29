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

// Last modified: 2025-02-12

#if !defined(ARCADIA_MIL_PASS_H_INCLUDED)
#define ARCADIA_MIL_PASS_H_INCLUDED

#include "R/Include.h"

/// Base of all passes of the compiler.
Arcadia_declareObjectType(u8"Arcadia.Mil.Pass", Arcadia_Mil_Pass, u8"Arcadia.Object");

struct Arcadia_Mil_Pass {
  Arcadia_Object _parent;
};

#endif // ARCADIA_MIL_PASS_H_INCLUDED
