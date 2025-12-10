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

#if !defined(ARCADIA_AUDIALS_IMPLEMENTATION_SCENE_SOUNDSOURCENODE_H_INCLUDED)
#define ARCADIA_AUDIALS_IMPLEMENTATION_SCENE_SOUNDSOURCENODE_H_INCLUDED

#include "Arcadia/Audials/Include.h"
#include "Arcadia/Audials/Implementation/BackendContext.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.Scene.SoundSourceNode", Arcadia_Audials_Implementation_Scene_SoundSourceNode,
                          u8"Arcadia.Visuals.Scene.SoundSourceNodeNode");

struct Arcadia_Audials_Implementation_Scene_SoundSourceNodeDispatch {
  Arcadia_Audials_Scene_SoundSourceNodeDispatch _parent;
};

struct Arcadia_Audials_Implementation_Scene_SoundSourceNode {
  Arcadia_Audials_Scene_SoundSourceNode _parent;

  Arcadia_Audials_Implementation_BackendContext* backendContext;
  Arcadia_Audials_Implementation_SoundSourceResource* soundSourceResource;

  Arcadia_Natural8Value dirtyBits;
  Arcadia_Real32Value volume;
};

Arcadia_Audials_Implementation_Scene_SoundSourceNode*
Arcadia_Audials_Implementation_Scene_SoundSourceNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_BackendContext* backendContext
  );

#endif // ARCADIA_AUDIALS_IMPLEMENTATION_SCENE_SOUNDSOURCENODE_H_INCLUDED
