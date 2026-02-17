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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Audials/Nodes/SoundSourceNode.h"

static void
Arcadia_Engine_Audials_SoundSourceNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  );

static void
Arcadia_Engine_Audials_SoundSourceNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNodeDispatch* self
  );

static void
Arcadia_Engine_Audials_SoundSourceNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Audials_SoundSourceNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Audials_SoundSourceNode_destructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Audials.SoundSourceNode", Arcadia_Engine_Audials_SoundSourceNode,
                         u8"Arcadia.Engine.Audials.Node", Arcadia_Engine_Audials_Node,
                         &_typeOperations);

static void
Arcadia_Engine_Audials_SoundSourceNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Audials_SoundSourceNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_Audials_SoundSourceNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNodeDispatch* self
  )
{ }

static void
Arcadia_Engine_Audials_SoundSourceNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  )
{/*Intentionally empty.*/}

Arcadia_BooleanValue
Arcadia_Engine_Audials_SoundSourceNode_isPlaying
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Audials_SoundSourceNode, isPlaying, self); }

void
Arcadia_Engine_Audials_SoundSourceNode_pause
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Audials_SoundSourceNode, pause, self); }

void
Arcadia_Engine_Audials_SoundSourceNode_play
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Audials_SoundSourceNode, play, self); }

void
Arcadia_Engine_Audials_SoundSourceNode_stop
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Audials_SoundSourceNode, stop, self); }

void
Arcadia_Engine_Audials_SoundSourceNode_setIsLooping
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self,
    Arcadia_BooleanValue isLooping
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Audials_SoundSourceNode, setIsLooping, self, isLooping); }

Arcadia_BooleanValue
Arcadia_Engine_Audials_SoundSourceNode_getIsLooping
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Audials_SoundSourceNode, getIsLooping, self); }

void
Arcadia_Engine_Audials_SoundSourceNode_setVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self,
    Arcadia_Real32Value volume
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Audials_SoundSourceNode, setVolume, self, volume); }

Arcadia_Real32Value
Arcadia_Engine_Audials_SoundSourceNode_getVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_SoundSourceNode* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Engine_Audials_SoundSourceNode, getVolume, self); }
