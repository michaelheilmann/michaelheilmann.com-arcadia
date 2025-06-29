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

#if !defined(ARCADIA_RING1_BIGINTEGER_TOTWOSCOMPLEMENT_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_TOTWOSCOMPLEMENT_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/BigInteger/BigInteger.h"

/// Convert to an array (*limps) of length (*numberOfLimps) of Arcadia_BigInteger_Limp values.
/// The array elements contain the two's complement representation of the value of the big integer in little endian form.
/// The array must be deallocated using Arcadia_Process_deallocateMemory when no longer required.
void
Arcadia_BigInteger_toTwosComplement
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger_Limp** limps,
    Arcadia_SizeValue* numberOfLimps
  );

#endif // ARCADIA_RING1_BIGINTEGER_TOTWOSCOMPLEMENT_H_INCLUDED
