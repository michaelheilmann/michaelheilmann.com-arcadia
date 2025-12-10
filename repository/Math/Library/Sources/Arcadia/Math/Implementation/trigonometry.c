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

#include "Arcadia/Math/Implementation/trigonometry.h"

// Symbolic constant for the Arcadia_Real32Value representation of PI.
#define Arcadia_PI_Real32Value 3.1415926f

// Symbolic constant for the Arcadia_Real64Value representation of PI.
#define Arcadia_PI_Real64Value 3.1415926

Arcadia_Real32Value
Arcadia_radiansToDegreesReal32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value a
  )
{
  static const Arcadia_Real32Value x = 180.f / Arcadia_PI_Real32Value;
  return a * x;
}

Arcadia_Real64Value
Arcadia_radiansToDegreesReal64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value a
  )
{
  static const Arcadia_Real64Value x = 180. / Arcadia_PI_Real64Value;
  return a * x;
}

Arcadia_Real32Value
Arcadia_degreesToRadiansReal32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value a
  )
{
  static const Arcadia_Real32Value x = Arcadia_PI_Real32Value / 180.f;
  return a * x;
}

Arcadia_Real64Value
Arcadia_degreesToRadiansReal64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value a
  )
{
  static const Arcadia_Real64Value x = Arcadia_PI_Real64Value / 180.;
  return a * x;
}
