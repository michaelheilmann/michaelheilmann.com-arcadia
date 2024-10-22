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

#if !defined(R_REAL64VALUE_H_INCLUDED)
#define R_REAL64VALUE_H_INCLUDED

#include <limits.h>
typedef void R_Type;

typedef double R_Real64Value;

#define R_Real64Value_Minimum (-DBL_MAX)

#define R_Real64Value_Maximum (+DBL_MAX)

#define R_Real64Value_NumberOfBytes (sizeof(double))

static_assert(R_Real64Value_NumberOfBytes == 8, "R.Real64Value.NumberOfBytes must be 8");

#define R_Real64Value_NumberOfBits (R_Real64Value_NumberOfBytes * 8)

#define R_Real64Value_Literal(x) (x)

R_Type*
_R_Real64Value_getType
  (
  );

#endif // R_REAL64VALUE_H_INCLUDED
