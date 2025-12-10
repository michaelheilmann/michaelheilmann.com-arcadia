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

#if !defined(ARCADIA_ENGINE_SCENENODEFACTORY_H_INCLUDED)
#define ARCADIA_ENGINE_SCENENODEFACTORY_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

/// The base of all scene node factories.
/// The bases of implementations specific to audials and visuals can be found in Arcadia.Audials and Arcadia.Visuals, respectively.
Arcadia_declareObjectType(u8"Arcadia.Engine.SceneNodeFactory", Arcadia_Engine_SceneNodeFactory,
                          Arcadia_Object);

struct Arcadia_Engine_SceneNodeFactoryDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Engine_SceneNodeFactory {
  Arcadia_Object _parent;
};

#endif // ARCADIA_ENGINE_SCENENODEFACTORY_H_INCLUDED
