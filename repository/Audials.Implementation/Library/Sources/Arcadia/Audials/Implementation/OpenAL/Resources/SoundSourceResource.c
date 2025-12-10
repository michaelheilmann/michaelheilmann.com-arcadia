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

#include "Arcadia/Audials/Implementation/OpenAL/Resources/SoundSourceResource.h"

#include "Arcadia/Audials/Implementation/OpenAL/BackendContext.h"
#include "Arcadia/Audials/Implementation/Synthesis/sine.h"
#include <assert.h>

#define DataDirty (1)
#define VolumeDirty (2)

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_initializeDispatchImpl
  ( 
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResourceDispatch* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static Arcadia_BooleanValue
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_isPlaying
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_pause
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_play
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_stop
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_setVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self,
    Arcadia_Real32Value volume
  );

static Arcadia_Real32Value
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_getVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Audials.Implementation.OpenAL.SoundSourceResource", Arcadia_Audials_Implementation_OpenAL_SoundSourceResource,
                         u8"Arcadia.Audials.Implementation.SoundSourceResource", Arcadia_Audials_Implementation_SoundSourceResource,
                         &_typeOperations);

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->volume = 1.f;
  //
  self->dirtyBits = DataDirty | VolumeDirty;
  self->byteBuffer = Arcadia_ByteBuffer_create(thread);
  self->alBufferID = 0;
  self->alSourceID = 0;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResourceDispatch* self
  )
{
  //
  ((Arcadia_Audials_Implementation_SoundSourceResourceDispatch*)self)->isPlaying = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_isPlaying;
  ((Arcadia_Audials_Implementation_SoundSourceResourceDispatch*)self)->play = (void (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_play;
  ((Arcadia_Audials_Implementation_SoundSourceResourceDispatch*)self)->pause = (void (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_pause;
  ((Arcadia_Audials_Implementation_SoundSourceResourceDispatch*)self)->stop = (void (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_stop;
  ((Arcadia_Audials_Implementation_SoundSourceResourceDispatch*)self)->setVolume = (void (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*, Arcadia_Real32Value)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_setVolume;
  ((Arcadia_Audials_Implementation_SoundSourceResourceDispatch*)self)->getVolume = (Arcadia_Real32Value(*)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_getVolume;
  //
  ((Arcadia_Audials_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_Resource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_loadImpl;
  ((Arcadia_Audials_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_Resource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_unlinkImpl;
  ((Arcadia_Audials_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_Resource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_unloadImpl;
  ((Arcadia_Audials_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_Resource*)) & Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_renderImpl;
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  assert(0 == self->alBufferID);
  assert(0 == self->alSourceID);
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  if (self->byteBuffer) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->byteBuffer);
  }
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  //Arcadia_Audials_Implementation_OpenAL_BackendContext* context = (Arcadia_Audials_Implementation_OpenAL_BackendContext*)((Arcadia_Audials_Implementation_Resource*)self)->context;
  if (0 == self->alBufferID) {
    alGenBuffers(1, &self->alBufferID);
    if (alGetError()) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->dirtyBits |= DataDirty | VolumeDirty;
  }
  if (0 == self->alSourceID) {
    alGenSources(1, &self->alSourceID);
    if (alGetError()) {
      alDeleteBuffers(1, &self->alBufferID);
      self->alBufferID = 0;
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    alSourcei(self->alSourceID, AL_LOOPING, AL_FALSE);
    alSourcei(self->alSourceID, AL_SOURCE_RELATIVE, AL_TRUE);
    self->dirtyBits |= DataDirty | VolumeDirty;
  }
  if (self->dirtyBits & VolumeDirty) {
    alSourcef(self->alSourceID, AL_GAIN, 1.0f);
    self->dirtyBits &= ~VolumeDirty;
  }
  if (self->dirtyBits & DataDirty) {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_ByteBuffer* sourceVoiceBuffer = Arcadia_ByteBuffer_create(thread);
      Arcadia_Natural8Value numberOfChannels;
      Arcadia_Natural16Value sampleRate;
      Arcadia_Audials_Synthesis_generateSineWave(thread, sourceVoiceBuffer, &numberOfChannels, &sampleRate);
      if (numberOfChannels == 1) {
        alBufferData(self->alBufferID, AL_FORMAT_MONO16,   Arcadia_ByteBuffer_getBytes(thread, sourceVoiceBuffer),
                                                           Arcadia_ByteBuffer_getNumberOfBytes(thread, sourceVoiceBuffer),
                                                           sampleRate);
      } else if (numberOfChannels == 2) {
        alBufferData(self->alBufferID, AL_FORMAT_STEREO16, Arcadia_ByteBuffer_getBytes(thread, sourceVoiceBuffer),
                                                           Arcadia_ByteBuffer_getNumberOfBytes(thread, sourceVoiceBuffer),
                                                           sampleRate);
      }
      alSourcei(self->alSourceID, AL_BUFFER, self->alBufferID);
      if (alGetError()) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Thread_popJumpTarget(thread);
      self->dirtyBits &= ~DataDirty;
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_loadImpl(thread, self);
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  assert(0 == self->alBufferID);
  assert(0 == self->alSourceID);
  ((Arcadia_Audials_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  //Arcadia_Audials_Implementation_OpenAL_BackendContext* context = (Arcadia_Audials_Implementation_OpenAL_BackendContext*)((Arcadia_Audials_Implementation_Resource*)self)->context;
  if (self->alSourceID) {
    alDeleteSources(1, &self->alSourceID);
    self->alSourceID = 0;
  }
  if (self->alBufferID) {
    alDeleteBuffers(1, &self->alBufferID);
    self->alBufferID = 0;
  }
}

static Arcadia_BooleanValue
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_isPlaying
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  if (!self->alSourceID) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  ALint alSourceState;
  alGetSourcei(self->alSourceID, AL_SOURCE_STATE, &alSourceState);
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  return AL_PLAYING == alSourceState;
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_pause
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  if (!self->alSourceID) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  alSourcePause(self->alSourceID);
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_play
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  if (!self->alSourceID) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_isPlaying(thread, self)) {
    alSourcePlay(self->alSourceID);
    if (alGetError()) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_stop
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{
  if (!self->alSourceID) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  alSourceStop(self->alSourceID);
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_setVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self,
    Arcadia_Real32Value volume
  )
{
  if (!self->alSourceID || !Arcadia_Real32Value_isFinite(thread, volume)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  ALfloat minimumGain, maximumGain;
  alGetSourcef(self->alSourceID, AL_MIN_GAIN, &minimumGain);
  alGetSourcef(self->alSourceID, AL_MAX_GAIN, &maximumGain);
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (volume < minimumGain) volume = minimumGain;
  if (volume > maximumGain) volume = maximumGain;
  alSourcef(self->alSourceID, AL_GAIN, volume);
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  self->volume = volume;
}

static Arcadia_Real32Value
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_getVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* self
  )
{ return self->volume; }

Arcadia_Audials_Implementation_OpenAL_SoundSourceResource*
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Audials_Implementation_OpenAL_SoundSourceResource);
}
