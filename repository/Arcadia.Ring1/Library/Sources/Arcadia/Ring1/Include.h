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

// Last modified: 2025-02-19

#if !defined(ARCADIA_RING1_INCLUDE_H_INCLUDED)
#define ARCADIA_RING1_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_RING1_PRIVATE")
#undef ARCADIA_RING1_PRIVATE
#define ARCADIA_RING1_PRIVATE (1)

#include "Arcadia/Ring1/Implementation/Arrays.h"

#include "Arcadia/Ring1/Implementation/Atoms.h"

#include "Arcadia/Ring1/Implementation/Boolean.h"

#include "Arcadia/Ring1/Implementation/clamp.h"

#include "Arcadia/Ring1/Implementation/countLeadingZeroes.h"

#include "Arcadia/Ring1/Implementation/Diagnostics.h"

#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"

#include "Arcadia/Ring1/Implementation/hash.h"

#include "Arcadia/Ring1/Implementation/getTickCount.h"

#include "Arcadia/Ring1/Implementation/ImmutableByteArray.h"

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

#include "Arcadia/Ring1/Implementation/isPowerOfTwo.h"

#include "Arcadia/Ring1/Implementation/Utf8.h"

#include "Arcadia/Ring1/Implementation/makeBitmask.h"

#include "Arcadia/Ring1/Implementation/maximum.h"
#include "Arcadia/Ring1/Implementation/minimum.h"

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#include "Arcadia/Ring1/Implementation/nextPowerOfTwoGreaterThan.h"
#include "Arcadia/Ring1/Implementation/nextPowerOfTwoGreaterThanOrEqualTo.h"

#include "Arcadia/Ring1/Implementation/NoReturn.h"

#include "Arcadia/Ring1/Implementation/Object.h"

#include "Arcadia/Ring1/Implementation/ObjectReference.h"

#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/Process1.h"

#include "Arcadia/Ring1/Implementation/Real32.h"
#include "Arcadia/Ring1/Implementation/Real64.h"

#include "Arcadia/Ring1/Implementation/safeAdd.h"
#include "Arcadia/Ring1/Implementation/safeMultiply.h"

#include "Arcadia/Ring1/Implementation/Size.h"

#include "Arcadia/Ring1/Implementation/StaticAssert.h"

#include "Arcadia/Ring1/Implementation/swap.h"

#include "Arcadia/Ring1/Implementation/Tests.h"

#include "Arcadia/Ring1/Implementation/Types.h"

#include "Arcadia/Ring1/Implementation/Value.h"

#include "Arcadia/Ring1/Implementation/Void.h"

#undef ARCADIA_RING1_PRIVATE
#pragma pop_macro("ARCADIA_RING1_PRIVATE")

#endif // ARCADIA_RING1_INCLUDE_H_INCLUDED
