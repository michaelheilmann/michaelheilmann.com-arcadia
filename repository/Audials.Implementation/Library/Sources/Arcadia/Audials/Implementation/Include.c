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

#define ARCADIA_AUDIALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Audials/Implementation/Include.h"

#if Arcadia_Audials_Implementation_Configuration_OpenAL_Backend_Enabled
  #include "Arcadia/Audials/Implementation/OpenAL/Backend.h"
#endif

#include "Arcadia/Audials/Implementation/SceneNodeFactory.h"

void
Arcadia_Audials_Implementation_registerSceneNodeFactories
  (
    Arcadia_Thread* thread,
    Arcadia_Set* types
  )
{
  Arcadia_Set_add(thread, types, Arcadia_Value_makeTypeValue(_Arcadia_Audials_Implementation_SceneNodeFactory_getType(thread)), NULL);
}

void
Arcadia_Audials_Implementation_registerBackends
  (
    Arcadia_Thread* thread,
    Arcadia_Set* types
  )
{
#if Arcadia_Audials_Implementation_Configuration_OpenAL_Backend_Enabled
  Arcadia_Set_add(thread, types, Arcadia_Value_makeTypeValue(_Arcadia_Audials_Implementation_OpenAL_Backend_getType(thread)), NULL);
#endif
}
