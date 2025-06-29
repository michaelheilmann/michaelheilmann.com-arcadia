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

#if !defined(ARCADIA_RING1_INCLUDE_H_INCLUDED)
#define ARCADIA_RING1_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_RING1_PRIVATE")
#undef ARCADIA_RING1_PRIVATE
#define ARCADIA_RING1_PRIVATE (1)

#include "Arcadia/Ring1/Implementation/Arrays.h"

#include "Arcadia/Ring1/Implementation/Atoms.h"

#include "Arcadia/Ring1/Implementation/BigInteger/Include.h"

#include "Arcadia/Ring1/Implementation/Boolean.h"

#include "Arcadia/Ring1/Implementation/Diagnostics.h"

#include "Arcadia/Ring1/Implementation/Enumeration.h"

#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"

#include "Arcadia/Ring1/Implementation/getTickCount.h"

#include "Arcadia/Ring1/Implementation/ImmutableByteArray.h"

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

#include "Arcadia/Ring1/Implementation/Unicode.h"

#include "Arcadia/Ring1/Implementation/makeBitmask.h"

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#include "Arcadia/Ring1/Implementation/Annotations/Likely.h"
#include "Arcadia/Ring1/Implementation/Annotations/NoReturn.h"
#include "Arcadia/Ring1/Implementation/Annotations/ThreadLocal.h"
#include "Arcadia/Ring1/Implementation/Annotations/Unlikely.h"

#include "Arcadia/Ring1/Implementation/NumberLiteral.h"

#include "Arcadia/Ring1/Implementation/Numerics/Include.h"

#include "Arcadia/Ring1/Implementation/Object.h"

#include "Arcadia/Ring1/Implementation/ObjectReference.h"

#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/ProcessExtensions.h"

#include "Arcadia/Ring1/Implementation/Real32.h"
#include "Arcadia/Ring1/Implementation/Real64.h"

#include "Arcadia/Ring1/Implementation/safeAdd.h"
#include "Arcadia/Ring1/Implementation/safeMultiply.h"

#include "Arcadia/Ring1/Implementation/Size.h"

#include "Arcadia/Ring1/Implementation/StaticAssert.h"

#include "Arcadia/Ring1/Implementation/Status.h"

#include "Arcadia/Ring1/Implementation/Thread.h"

#include "Arcadia/Ring1/Implementation/swap.h"

#include "Arcadia/Ring1/Implementation/Tests.h"

#include "Arcadia/Ring1/Implementation/RealToString/Include.h"

#include "Arcadia/Ring1/Implementation/StringToInteger/Include.h"
#include "Arcadia/Ring1/Implementation/StringToNatural/Include.h"
#include "Arcadia/Ring1/Implementation/StringToReal/toReal32.h"
#include "Arcadia/Ring1/Implementation/StringToReal/toReal64.h"

#include "Arcadia/Ring1/Implementation/Types.h"

#include "Arcadia/Ring1/Implementation/Value.h"

#include "Arcadia/Ring1/Implementation/Void.h"

#undef ARCADIA_RING1_PRIVATE
#pragma pop_macro("ARCADIA_RING1_PRIVATE")

#endif // ARCADIA_RING1_INCLUDE_H_INCLUDED
