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

#if !defined(R_NATURAL32VALUE_H_INCLUDED)
#define R_NATURAL32VALUE_H_INCLUDED

#include <inttypes.h>
typedef void R_Type;

typedef uint32_t R_Natural32Value;

#define R_Natural32Value_Minimum (UINT32_C(0))

#define R_Natural32Value_Maximum (UINT32_MAX)

#define R_Natural32Value_NumberOfBytes (sizeof(uint32_t))

static_assert(R_Natural32Value_NumberOfBytes == 4, "R.Natural32Value.NumberOfBytes must be 4");

#define R_Natural32Value_NumberOfBits (R_Natural32Value_NumberOfBytes * 8)

#define R_Natural32Value_Literal(x) UINT32_C(x)

R_Type*
_R_Natural32Value_getType
  (
  );

#endif // R_NATURAL32VALUE_H_INCLUDED
