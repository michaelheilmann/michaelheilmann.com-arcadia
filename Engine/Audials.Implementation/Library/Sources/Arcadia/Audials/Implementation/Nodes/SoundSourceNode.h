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

#if !defined(ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_NODES_SOUNDSOURCENODE_H_INCLUDED)
#define ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_NODES_SOUNDSOURCENODE_H_INCLUDED

#include "Arcadia/Engine/Include.h"
#include "Arcadia/Audials/Implementation/BackendContext.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Audials.Implementation.SoundSourceNode", Arcadia_Engine_Audials_Implementation_SoundSourceNode,
                          u8"Arcadia.Audials.SoundSourceNodeNode");

struct Arcadia_Engine_Audials_Implementation_SoundSourceNodeDispatch {
  Arcadia_Engine_Audials_SoundSourceNodeDispatch _parent;
};

struct Arcadia_Engine_Audials_Implementation_SoundSourceNode {
  Arcadia_Engine_Audials_SoundSourceNode _parent;

  Arcadia_Engine_Audials_Implementation_BackendContext* backendContext;
  Arcadia_Engine_Audials_Implementation_SoundSourceResource* soundSourceResource;


  Arcadia_Natural8Value dirtyBits;
  Arcadia_BooleanValue isLooping;
  Arcadia_Real32Value volume;
};

Arcadia_Engine_Audials_Implementation_SoundSourceNode*
Arcadia_Engine_Audials_Implementation_SoundSourceNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_NODES_SOUNDSOURCENODE_H_INCLUDED
