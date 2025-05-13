// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_ARMS_SIZETYPE_H_INCLUDED)
#define ARCADIA_ARMS_SIZETYPE_H_INCLUDED

#include "Arcadia/Arms/Configure.h"

// size_t
#include <stddef.h>
// SIZE_MAX
#include <stdint.h>

// A non-negative binary integer.
// Its width, in Bits, is at least 16.
// It is large enough to fit the result of Arms_SizeOf, Arms_AlignOf, and Arms_OffsetOf.
typedef size_t Arcadia_Arms_Size;

/// The minimum value of Arms_Size.
/// Guaranteed to be @a 0.
#define Arcadia_Arms_Size_Minimum ((Arcadia_Arms_Size)0)

/// The maximum value of Arms_Size.
#define Arcadia_Arms_Size_Maximum (SIZE_MAX)

#endif // ARCADIA_ARMS_SIZETYPE_H_INCLUDED
