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

#if !defined(R_REAL32VALUE_H_INCLUDED)
#define R_REAL32VALUE_H_INCLUDED

#include "R/cstdlib.h"
typedef void R_Type;

typedef float R_Real32Value;

#define R_Real32Value_Minimum (-FLOAT_MAX)

#define R_Real32Value_Maximum (+FLOAT_MAX)

#define R_Real32Value_NumberOfBytes (sizeof(float))

c_static_assert(R_Real32Value_NumberOfBytes == 4, "R.Real32Value.NumberOfByes must be 4");

#define R_Real32Value_NumberOfBits (R_Real32Value_NumberOfBytes * 8)

#define R_Real32Value_Literal(x) (x##f)

R_Type*
_R_Real32Value_getType
  (
  );

#endif // R_REAL32VALUE_H_INCLUDED
