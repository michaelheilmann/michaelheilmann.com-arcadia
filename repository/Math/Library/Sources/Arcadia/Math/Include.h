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

#if !defined(ARCADIA_MATH_INCLUDE_H_INCLUDED)
#define ARCADIA_MATH_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_MATH_PRIVATE")
#undef ARCADIA_MATH_PRIVATE
#define ARCADIA_MATH_PRIVATE (1)

#include "Arcadia/Math/Implementation/Configure.h"
#include "Arcadia/Math/Implementation/Color4Real32.h"
#include "Arcadia/Math/Implementation/Color4Real64.h"
#include "Arcadia/Math/Implementation/setOrthographicProjection.h"
#include "Arcadia/Math/Implementation/setPerspectiveProjection.h"
#include "Arcadia/Math/Implementation/setRotationX.h"
#include "Arcadia/Math/Implementation/setRotationY.h"
#include "Arcadia/Math/Implementation/setRotationZ.h"
#include "Arcadia/Math/Implementation/setScaling.h"
#include "Arcadia/Math/Implementation/setTranslation.h"
#include "Arcadia/Math/Implementation/Vector3Real32.h"
#include "Arcadia/Math/Implementation/Vector3Real64.h"

#undef ARCADIA_MATH_PRIVATE
#pragma pop_macro("ARCADIA_MATH_PRIVATE")

#endif // ARCADIA_MATH_INCLUDE_H_INCLUDED
