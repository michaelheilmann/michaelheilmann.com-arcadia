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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_MAKEBITMASK_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_MAKEBITMASK_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#include "Arcadia/Ring1/Implementation/Size.h"

/// @brief Create a bitmask.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param i The index of the first 1 bit.
/// @param n The number of 1 bits.
/// @return A bitmask such that the bits [i, i + n) are 1 and all other bits are zero.
/// @error Arcadia_Status_ArgumentValueInvalid <code>i + n</code> is greater than 16.
Arcadia_Natural16Value
Arcadia_makeBitmaskN16
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue i,
    Arcadia_SizeValue n
  );

/// @brief Create a bitmask.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param i The index of the first 1 bit.
/// @param n The number of 1 bits.
/// @return A bitmask such that the bits [i, i + n) are 1 and all other bits are zero.
/// @error Arcadia_Status_ArgumentValueInvalid <code>i + n</code> is greater than 32.
Arcadia_Natural32Value
Arcadia_makeBitmaskN32
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue i,
    Arcadia_SizeValue n
  );

/// @brief Create a bitmask.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param i The index of the first 1 bit.
/// @param n The number of 1 bits.
/// @return A bitmask such that the bits [i, i + n) are 1 and all other bits are zero.
/// @error Arcadia_Status_ArgumentValueInvalid <code>i + n</code> is greater than 64.
Arcadia_Natural64Value
Arcadia_makeBitmaskN64
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue i,
    Arcadia_SizeValue n
  );

/// @brief Create a bitmask.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param i The index of the first 1 bit.
/// @param n The number of 1 bits.
/// @return A bitmask such that the bits [i, i + n) are 1 and all other bits are zero.
/// @error Arcadia_Status_ArgumentValueInvalid <code>i + n</code> is greater than 8.
Arcadia_Natural8Value
Arcadia_makeBitmaskN8
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue i,
    Arcadia_SizeValue n
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_MAKEBITMASK_H_INCLUDED
