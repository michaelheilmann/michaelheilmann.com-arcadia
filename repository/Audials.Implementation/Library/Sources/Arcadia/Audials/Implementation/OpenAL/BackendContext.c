// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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
#include "Arcadia/Audials/Implementation/OpenAL/BackendContext.h"

#include "Arcadia/Audials/Implementation/Configure.h"
#include "Arcadia/Audials/Implementation/OpenAL/Backend.h"

static Arcadia_Audials_Implementation_OpenAL_BackendContext* g_instance = NULL;

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_playSineImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_BackendContext_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_BackendContext_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_BackendContext_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Audials.Implementation.OpenAL.BackendContext", Arcadia_Audials_Implementation_OpenAL_BackendContext,
                         u8"Arcadia.Audials.BackendContext", Arcadia_Audials_BackendContext,
                         &_typeOperations);

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_playSineImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{
  alcMakeContextCurrent(self->alcContext);

  // Set the position of the listener.
  ALfloat position[] = { 0.f, 0.f, 0.f };
  alListenerfv(AL_POSITION, position);
  alListenerf(AL_GAIN, 0.1f);
  if (AL_NO_ERROR != alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alSourcef(self->alSourceId, AL_GAIN, 1.0f);
  alSourcei(self->alSourceId, AL_BUFFER, self->alBufferId);
  alSourcei(self->alSourceId, AL_LOOPING, AL_FALSE);
  alSourcei(self->alSourceId, AL_SOURCE_RELATIVE, AL_TRUE);
  alSourcePlay(self->alSourceId);
  if (AL_NO_ERROR != alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Audials_Implementation_OpenAL_BackendContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->alcDevice = NULL;
  self->alcContext = NULL;
  self->alBufferId = 0;
  self->alSourceId = 0;

  // Select the default audio device on the system.
  self->alcDevice = alcOpenDevice(NULL);
  if (!self->alcDevice) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  // Create a context on the device.
  self->alcContext = alcCreateContext(self->alcDevice, NULL);
  if (!self->alcContext) {
    alcCloseDevice(self->alcDevice);
    self->alcDevice = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alcMakeContextCurrent(self->alcContext);
  if (alGetError()) {
    alcCloseDevice(self->alcDevice);
    self->alcDevice = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alGenBuffers(1, &self->alBufferId);
  if (alGetError()) {
    alcMakeContextCurrent(NULL);
    alcDestroyContext(self->alcContext);
    self->alcContext = NULL;
    alcCloseDevice(self->alcDevice);
    self->alcDevice = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alGenSources(1, &self->alSourceId);
  if (alGetError()) {
    alDeleteBuffers(1, &self->alBufferId);
    self->alBufferId = 0;
    alcDestroyContext(self->alcContext);
    self->alcContext = NULL;
    alcCloseDevice(self->alcDevice);
    self->alcDevice = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      static const float PI = 3.14159265358979323846;
      const int channels = 1;
      const int frequency = 110.0f;
      const int seconds = 6.f;
      const int sampleRate = 44100;
      const int numberOfSamples = channels * sampleRate * seconds;

      Arcadia_ByteBuffer* sourceVoiceBuffer = Arcadia_ByteBuffer_create(thread);

      const float constant = 2.f * PI * (float)frequency / (float)sampleRate;
      if (channels == 1) {
        for (size_t i = 0; i < numberOfSamples; ++i) {
          int16_t sample = 32760 * sin(constant * i);
          Arcadia_ByteBuffer_append_pn(thread, sourceVoiceBuffer, &sample, 2);
        }
      } else if (channels == 2) {
        for (size_t i = 0; i < numberOfSamples; ++i) {
          int16_t sample = 32760 * sin(constant * i);
          Arcadia_ByteBuffer_append_pn(thread, sourceVoiceBuffer, &sample, 2);
          Arcadia_ByteBuffer_append_pn(thread, sourceVoiceBuffer, &sample, 2);
        }
      }
      if (channels == 1) {
        alBufferData(self->alBufferId, AL_FORMAT_MONO16, Arcadia_ByteBuffer_getBytes(thread, sourceVoiceBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, sourceVoiceBuffer), sampleRate);
      } else if (channels == 2) {
        alBufferData(self->alBufferId, AL_FORMAT_STEREO16, Arcadia_ByteBuffer_getBytes(thread, sourceVoiceBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, sourceVoiceBuffer), sampleRate);
      }
      if (alGetError()) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      alDeleteSources(1, &self->alSourceId);
      self->alSourceId = 0;
      alDeleteBuffers(1, &self->alBufferId);
      self->alBufferId = 0;
      alcDestroyContext(self->alcContext);
      self->alcContext = NULL;
      alcCloseDevice(self->alcDevice);
      self->alcDevice = NULL;
      Arcadia_Thread_jump(thread);
    }
  }

  ((Arcadia_Audials_BackendContext*)self)->update = (void(*)(Arcadia_Thread*, Arcadia_Audials_BackendContext*)) & Arcadia_Audials_Implementation_OpenAL_BackendContext_updateImpl;
  ((Arcadia_Audials_BackendContext*)self)->playSine = (void(*)(Arcadia_Thread*, Arcadia_Audials_BackendContext*)) & Arcadia_Audials_Implementation_OpenAL_BackendContext_playSineImpl;


  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{
  if (self->alSourceId) {
    alSourceStop(self->alSourceId);
    alDeleteSources(1, &self->alSourceId);
    self->alSourceId = 0;
  }
  if (self->alBufferId) {
    alDeleteBuffers(1, &self->alBufferId);
    self->alBufferId = 0;
  }
  if (self->alcContext) {
    if (alcGetCurrentContext() == self->alcContext) {
      alcMakeContextCurrent(NULL);
    }
    if (self->alcContext) {
      alcDestroyContext(self->alcContext);
      self->alcContext = NULL;
    }
  }
  if (self->alcDevice) {
    alcCloseDevice(self->alcDevice);
    self->alcDevice = NULL;
  }
}

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{/*Intentionally empty.*/}

static void
destroyCallback
  (
    void* argument1,
    void* argument2
  )
{
  g_instance = NULL;
}

Arcadia_Audials_Implementation_OpenAL_BackendContext*
Arcadia_Audials_Implementation_OpenAL_BackendContext_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Audials_Implementation_OpenAL_BackendContext);
}

Arcadia_Audials_Implementation_OpenAL_BackendContext*
Arcadia_Audials_Implementation_OpenAL_BackendContext_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_Audials_Implementation_OpenAL_BackendContext* instance = Arcadia_Audials_Implementation_OpenAL_BackendContext_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}
