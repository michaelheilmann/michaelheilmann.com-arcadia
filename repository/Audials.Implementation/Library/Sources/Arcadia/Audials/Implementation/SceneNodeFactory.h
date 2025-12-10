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

#if !defined(ARCADIA_AUDIALS_IMPLEMENTATION_SCENENODEFACTORY_H_INCLUDED)
#define ARCADIA_AUDIALS_IMPLEMENTATION_SCENENODEFACTORY_H_INCLUDED

#include "Arcadia/Audials/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Audials.Implementation.SceneNodeFactory", Arcadia_Audials_Implementation_SceneNodeFactory,
                          Arcadia_Audials_SceneNodeFactory);

struct Arcadia_Audials_Implementation_SceneNodeFactoryDispatch {
  Arcadia_Audials_SceneNodeFactoryDispatch parent;
};

struct Arcadia_Audials_Implementation_SceneNodeFactory {
  Arcadia_Audials_SceneNodeFactory parent;
};

Arcadia_Audials_Implementation_SceneNodeFactory*
Arcadia_Audials_Implementation_SceneNodeFactory_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_AUDIALS_IMPLEMENTATION_SCENENODEFACTORY_H_INCLUDED
