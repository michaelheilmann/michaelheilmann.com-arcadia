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

#if !defined(ARCADIA_RING1_CONCURRENCY_COMPAREANDSWAP_H_INCLUDED)
#define ARCADIA_RING1_CONCURRENCY_COMPAREANDSWAP_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Configure.h"
#include <stddef.h>

/// @brief Compare the old value of a pointer to a value. If the comparison yields true, then replace the old value by a specified value.
/// @param comperand The value to compare the old value of *destination to.
/// @param exchange The new value of *destination if the comparison yields true.
/// @return The old value of *destination.
/// @warning The parameters must be aligned to 64 bit boundaries.
/// @warning This function does not check for the alignment of parameters to 64 bit boundaries.
void*
Arcadia_Memory_compareAndSwap
  (
    void* volatile *destination,
    void* comperand,
    void* exchange
  );

#endif // ARCADIA_RING1_CONCURRENCY_COMPAREANDSWAP_H_INCLUDED
