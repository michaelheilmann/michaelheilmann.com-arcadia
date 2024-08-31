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

#if !defined(R_VOIDVALUE_H_INCLUDED)
#define R_VOIDVALUE_H_INCLUDED

#include <stddef.h>

typedef uint8_t R_VoidValue;

#define R_VoidValue_Void ((size_t)0)

#define R_VoidValue_NumberOfBytes (sizeof(uint8_t))

#define R_VoidValue_NumberOfBits (R_VoidValue_NumberOfBytes * 8)

#endif // R_VOIDVALUE_H_INCLUDED
