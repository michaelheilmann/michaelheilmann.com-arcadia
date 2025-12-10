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

#if !defined(ARCADIA_AUDIALS_SCENE_SOUNDSOURCENODE_H_INCLUDED)
#define ARCADIA_AUDIALS_SCENE_SOUNDSOURCENODE_H_INCLUDED

#include "Arcadia/Audials/Scene/Node.h"
typedef struct Arcadia_Audials_BackendContext Arcadia_Audials_BackendContext;

// A simple mono sound source with position and velocity.
// Think of it like someone carrying a boombox: At any point of time, it as a location and a velocity.
// Unlike a real boombox, it emanates sound in all directions the same way.
// It operates like a cassette player: Start, stop, pause, fast forward, and rewind.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.SoundSourceNode", Arcadia_Audials_Scene_SoundSourceNode,
                          u8"Arcadia.Visuals.Scene.Node");

struct Arcadia_Audials_Scene_SoundSourceNodeDispatch {
  Arcadia_Audials_Scene_NodeDispatch parent;

  Arcadia_BooleanValue(*isPlaying)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*);
  void (*pause)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*);
  void (*play)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*);
  void (*stop)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*);
  void (*setVolume)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*, Arcadia_Real32Value);
  Arcadia_Real32Value(*getVolume)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*);
};

struct Arcadia_Audials_Scene_SoundSourceNode {
  Arcadia_Audials_Scene_Node _parent;
};

/* Get if playing.
   Raises an error if this is invoked before the resource was rendered. */
Arcadia_BooleanValue
Arcadia_Audials_Scene_SoundSourceNode_isPlaying
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Scene_SoundSourceNode* self
  );

/* Pause: If playing, halt playback.
   Raises an error if this is invoked before the resource was rendered. */
void
Arcadia_Audials_Scene_SoundSourceNode_pause
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Scene_SoundSourceNode* self
  );

/* Play: If stopped or paused. Start playback at current position.
   Raises an error if this is invoked before the resource was rendered. */
void
Arcadia_Audials_Scene_SoundSourceNode_play
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Scene_SoundSourceNode* self
  );

/* Stop: If playing, halt playback. Rewind.
   Raises an error if this is invoked before the resource was rendered. */
void
Arcadia_Audials_Scene_SoundSourceNode_stop
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Scene_SoundSourceNode* self
  );

/* Sets the volume. The parameter value is clamped to [0,1].
   Raises an error if this is invoked before the resource was rendered. */
void
Arcadia_Audials_Scene_SoundSourceNode_setVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Scene_SoundSourceNode* self,
    Arcadia_Real32Value volume
  );

/* Gets the volume. The return value is within [0,1]. Default is 1.
   Raises an error if this is invoked before the resource was rendered. */
Arcadia_Real32Value
Arcadia_Audials_Scene_SoundSourceNode_getVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Scene_SoundSourceNode* self
  );

#endif // ARCADIA_AUDIALS_SCENE_SOUNDSOURCENODE_H_INCLUDED
