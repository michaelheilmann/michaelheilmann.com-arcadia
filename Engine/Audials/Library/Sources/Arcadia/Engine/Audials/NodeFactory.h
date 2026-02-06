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

#if !defined(ARCADIA_AUDIALS_NODEFACTORY_H_INCLUDED)
#define ARCADIA_AUDIALS_NODEFACTORY_H_INCLUDED

#if !defined(ARCADIA_AUDIALS_PRIVATE) || 1 != ARCADIA_AUDIALS_PRIVATE
  #error("do not include directly, include `Arcadia/Audials/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Math/Include.h"
#include "Arcadia/Engine/Include.h"
#include "Arcadia/Engine/Audials/Nodes/SoundSourceNode.h"

/// The implementation of a node factory for audials nodes.
Arcadia_declareObjectType(u8"Arcadia.Audials.NodeFactory", Arcadia_Engine_Audials_NodeFactory,
                          Arcadia_Engine_NodeFactory);

struct Arcadia_Engine_Audials_NodeFactoryDispatch {
  Arcadia_Engine_NodeFactoryDispatch parent;

  Arcadia_Engine_Audials_SoundSourceNode*
  (*createSoundSourceNode)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Audials_NodeFactory* self,
      Arcadia_Engine_Audials_BackendContext* backendContext
    );
};

struct Arcadia_Engine_Audials_NodeFactory {
  Arcadia_Engine_NodeFactory parent;
};

Arcadia_Engine_Audials_SoundSourceNode*
Arcadia_Engine_Audials_NodeFactory_createSoundSourceNode
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_NodeFactory* self,
    Arcadia_Engine_Audials_BackendContext* backendContext
  );

#endif // ARCADIA_AUDIALS_NODEFACTORY_H_INCLUDED
