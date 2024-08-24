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

#if !defined(ARCADIA_INTEGER64VALUE_H_INCLUDED)
#define ARCADIA_INTEGER64VALUE_H_INCLUDED

#include <inttypes.h>

typedef int64_t R_Integer64Value;

#define R_Integer64Value_Minimum (INT64_MIN)

#define R_Integer64Value_Maximum (INT64_MAX)

#define R_Integer64Value_NumberOfBytes (sizeof(int64_t))

static_assert(R_Integer64Value_NumberOfBytes == 8, "R.Integer64Value.NumberOfByes must be 8");

#define R_Integer64Value_NumberOfBits (R_Integer64Value_NumberOfBytes * 8)

#endif // ARCADIA_INTEGER64VALUE_H_INCLUDED
