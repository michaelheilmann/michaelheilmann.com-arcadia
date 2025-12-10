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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_SCENENODEFACTORY_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_SCENENODEFACTORY_H_INCLUDED

#include "Arcadia/Visuals/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.SceneNodeFactory", Arcadia_Visuals_Implementation_SceneNodeFactory,
                          Arcadia_Visuals_SceneNodeFactory);

struct Arcadia_Visuals_Implementation_SceneNodeFactoryDispatch {
  Arcadia_Visuals_SceneNodeFactoryDispatch parent;
};

struct Arcadia_Visuals_Implementation_SceneNodeFactory {
  Arcadia_Visuals_SceneNodeFactory parent;
};

Arcadia_Visuals_Implementation_SceneNodeFactory*
Arcadia_Visuals_Implementation_SceneNodeFactory_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_SCENENODEFACTORY_H_INCLUDED
