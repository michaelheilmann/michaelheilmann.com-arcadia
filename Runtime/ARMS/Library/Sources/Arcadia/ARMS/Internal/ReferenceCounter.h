// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_ARMS_REFERENCECOUNTER_H_INCLUDED)
#define ARCADIA_ARMS_REFERENCECOUNTER_H_INCLUDED

#include "Arcadia/ARMS/Configure.h"
#include "Arcadia/ARMS/SizeType.h"
#include "Arcadia/ARMS/StatusType.h"

/* The type of a reference counter. */
typedef Arcadia_ARMS_Size Arcadia_ARMS_ReferenceCounter;

/* The minimum value of a reference counter. */
#define Arcadia_ARMS_ReferenceCounter_Minimum (Arcadia_ARMS_Size_Minimum)

/* The maximum value of a reference counter. */
#define Arcadia_ARMS_ReferenceCounter_Maximum (Arcadia_ARMS_Size_Maximum)

#endif // ARCADIA_ARMS_REFERENCECOUNTER_H_INCLUDED
