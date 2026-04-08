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

#if !defined(ARCADIA_MATH_INCLUDE_H_INCLUDED)
#define ARCADIA_MATH_INCLUDE_H_INCLUDED

// If a file x belongs to a module a and ARCADIA_a_MODULE is not defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_MATH_MODULE")
#define ARCADIA_MATH_MODULE (1)

// If a file x of a module a is not an export file of that module and ARCADIA_a_EXPORT is defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_MATH_EXPORT")
#define ARCADIA_MATH_EXPORT (1)

#include "Arcadia/Math/Implementation/crossProduct.h"
#include "Arcadia/Math/Implementation/Configure.h"
#include "Arcadia/Math/Implementation/Color4Real32.h"
#include "Arcadia/Math/Implementation/Color4Real64.h"
#include "Arcadia/Math/Implementation/QuaternionReal32.h"
#include "Arcadia/Math/Implementation/setOrthographicProjection.h"
#include "Arcadia/Math/Implementation/setPerspectiveProjection.h"
#include "Arcadia/Math/Implementation/setRotationX.h"
#include "Arcadia/Math/Implementation/setRotationY.h"
#include "Arcadia/Math/Implementation/setRotationZ.h"
#include "Arcadia/Math/Implementation/setScaling.h"
#include "Arcadia/Math/Implementation/setTranslation.h"
#include "Arcadia/Math/Implementation/Vector3Real32.h"
#include "Arcadia/Math/Implementation/Vector3Real64.h"

#undef ARCADIA_MATH_EXPORT
#pragma pop_macro("ARCADIA_MATH_EXPORT")

#undef ARCADIA_MATH_MODULE
#pragma pop_macro("ARCADIA_MATH_MODULE")

#endif // ARCADIA_MATH_INCLUDE_H_INCLUDED
