// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_SIZE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_SIZE_H_INCLUDED

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef size_t Arcadia_SizeValue;

#define Arcadia_SizeValue_Minimum ((size_t)0)

#define Arcadia_SizeValue_Maximum (SIZE_MAX)

#define Arcadia_SizeValue_NumberOfBytes (sizeof(size_t))
Arcadia_StaticAssert(Arcadia_SizeValue_NumberOfBytes == 4 || Arcadia_SizeValue_NumberOfBytes == 8, "Arcadia.SizeValue.NumberOfBytes must be one of 4 or 8");

#define Arcadia_SizeValue_NumberOfBits (Arcadia_SizeValue_NumberOfBytes * 8)

#define Arcadia_SizeValue_Literal(x) ((size_t)x)

Rex_declareScalarType(Arcadia_Size);

#endif // ARCADIA_RING1_IMPLEMENTATION_SIZE_H_INCLUDED
