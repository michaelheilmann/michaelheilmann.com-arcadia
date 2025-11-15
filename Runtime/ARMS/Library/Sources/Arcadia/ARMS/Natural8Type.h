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

#if !defined(ARCADIA_ARMS_NATURAL8TYPE_H_INCLUDED)
#define ARCADIA_ARMS_NATURAL8TYPE_H_INCLUDED

#include "Arcadia/ARMS/Configure.h"

// uint8_t, UINT8_C, UINT8_MAX
#include <stdint.h>

// An unsigned binary integer of a width of 8 Bits.
typedef uint8_t Arms_Natural8;

/// The minimum value of Arms_Natural8.
/// Guaranteed to be @a 0.
#define Arms_Natural8_Minimum (UINT8_C(0))

/// The maximum value of Arms_Natural8.
#define Arms_Natural8_Maximum (UINT8_MAX)

#endif // ARCADIA_ARMS_NATURAL8TYPE_H_INCLUDED
