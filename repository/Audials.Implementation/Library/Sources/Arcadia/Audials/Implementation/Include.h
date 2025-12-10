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

#if !defined(ARCADIA_AUDIALS_IMPLEMENTATION_INCLUDE_H_INCLUDED)
#define ARCADIA_AUDIALS_IMPLEMENTATION_INCLUDE_H_INCLUDED

#include "Arcadia/Audials/Include.h"
#include "Arcadia/Audials/Implementation/Configure.h"

#if Arcadia_Audials_Implementation_Configuration_OpenAL_Backend_Enabled
  #include "Arcadia/Audials/Implementation/OpenAL/Backend.h"
#endif

void
Arcadia_Audials_Implementation_registerSceneNodeFactories
  (
    Arcadia_Thread* thread,
    Arcadia_Set* types
  );

void
Arcadia_Audials_Implementation_registerBackends
  (
    Arcadia_Thread* thread,
    Arcadia_Set* types
  );

#endif // ARCADIA_AUDIALS_IMPLEMENTATION_INCLUDE_H_INCLUDED
