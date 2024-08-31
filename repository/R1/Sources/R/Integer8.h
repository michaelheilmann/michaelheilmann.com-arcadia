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

// Last modified: 2024-08-25

#if !defined(R_INTEGER8VALUE_H_INCLUDED)
#define R_INTEGER8VALUE_H_INCLUDED

#include <inttypes.h>

typedef int8_t R_Integer8Value;

#define R_Integer8Value_Minimum (INT8_MIN)

#define R_Integer8Value_Maximum (INT8_MAX)

#define R_Integer8Value_NumberOfBytes (sizeof(int8_t))

static_assert(R_Integer8Value_NumberOfBytes == 1, "R.Integer8Value.NumberOfBytes must be 1");

#define R_Integer8Value_NumberOfBits (R_Integer8Value_NumberOfBytes * 8)

#define R_Integer8Value_Literal(x) INT8_C(x)

#endif // R_INTEGER8VALUE_H_INCLUDED
