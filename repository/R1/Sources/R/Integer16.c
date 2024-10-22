// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-27

#include "R/Integer16.h"

#include "R/Types.h"

static R_Type* g_type = NULL;

static void
typeDestructing
  (
    void* context
  )
{ g_type = NULL; }

R_Type*
_R_Integer16Value_getType
  (
  )
{
  if (!g_type) {
    R_registerIntegerType(u8"R.Integer16", sizeof("R.Integer16") - 1, &typeDestructing);
    g_type = R_getType(u8"R.Integer16", sizeof("R.Integer16") - 1);
  }
  return g_type;
}
