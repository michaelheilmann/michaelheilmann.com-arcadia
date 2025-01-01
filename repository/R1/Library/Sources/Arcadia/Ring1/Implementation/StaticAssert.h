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

// Last modified: 2025-01-01

#if !defined(ARCADIA_RING1_IMPLEMENTATION_STATICASSERT_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_STATICASSERT_H_INCLUDED

#include "Arcadia/Ring1/Implementation//Configure.h"

#if __STDC_VERSION__ < 202311L 
  #define Arcadia_StaticAssert(expression, message) _Static_assert(expression, message)
#else
  #define Arcadia_StaticAssert(expression, message) static_assert(expression, message)
#endif

#endif // ARCADIA_RING1_IMPLEMENTATION_STATICASSERT_H_INCLUDED
