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

#if !defined(R_INTEGER32VALUE_H_INCLUDED)
#define R_INTEGER32VALUE_H_INCLUDED

#include "R/cstdlib.h"
typedef void R_Type;

typedef int32_t R_Integer32Value;

#define R_Integer32Value_Minimum (INT32_MIN)

#define R_Integer32Value_Maximum (INT32_MAX)

#define R_Integer32Value_NumberOfBytes (sizeof(int32_t))

c_static_assert(R_Integer32Value_NumberOfBytes == 4, "R.Integer32Value.NumberOfBytes must be 4");

#define R_Integer32Value_NumberOfBits (R_Integer32Value_NumberOfBytes * 8)

#define R_Integer32Value_Literal(x) INT32_C(x)

R_Type*
_R_Integer32Value_getType
  (
  );

#endif // R_INTEGER32VALUE_H_INCLUDED
