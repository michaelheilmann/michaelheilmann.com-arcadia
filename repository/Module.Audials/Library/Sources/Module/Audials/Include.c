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

// Last modified: 2024-11-13

#include "Module/Audials/Include.h"

#define AL_LIBTYPE_STATIC
#include <AL/al.h>
#include <AL/alc.h>
#include <math.h>

#include "R/ArgumentsValidation.h"

static ALCdevice* g_device = NULL;
static ALCcontext* g_context = NULL;
static ALuint g_bufferId  = 0;
static ALuint g_sourceId = 0;

void
Audials_playSine
  (
    Arcadia_Thread* thread
  )
{
  alcMakeContextCurrent(g_context);

  // Set the position of the listener.
  ALfloat position[] = { 0.f, 0.f, 0.f };
  alListenerfv(AL_POSITION, position);
  alListenerf(AL_GAIN, 0.4f);
  if (AL_NO_ERROR != alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alSourcef(g_sourceId, AL_GAIN, 1.0f);
  alSourcei(g_sourceId, AL_BUFFER, g_bufferId);
  alSourcei(g_sourceId, AL_LOOPING, AL_FALSE);
  alSourcei(g_sourceId, AL_SOURCE_RELATIVE, AL_TRUE);
  alSourcePlay(g_sourceId);
  if (AL_NO_ERROR != alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

void
Audials_startup
  (
    Arcadia_Thread* thread
  )
{
  // Select the default audio device on the system.
  g_device = alcOpenDevice(NULL);
  if (!g_device) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  // Create a context on the device.
  g_context = alcCreateContext(g_device, NULL);
  if (!g_context) {
    alcCloseDevice(g_device);
    g_device = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alcMakeContextCurrent(g_context);
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alGenBuffers(1, &g_bufferId);
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alGenSources(1, &g_sourceId);
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  {
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
      alBufferData(g_bufferId, AL_FORMAT_MONO16, Arcadia_ByteBuffer_getBytes(thread, sourceVoiceBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, sourceVoiceBuffer), sampleRate);
    } else if (channels == 2) {
      alBufferData(g_bufferId, AL_FORMAT_STEREO16, Arcadia_ByteBuffer_getBytes(thread, sourceVoiceBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, sourceVoiceBuffer), sampleRate);
    }
  }
  if (alGetError()) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

void
Audials_shutdown
  (
    Arcadia_Thread* thread
  )
{
  if (g_sourceId) {
    alSourceStop(g_sourceId);
    alDeleteSources(1, &g_sourceId);
    g_sourceId = 0;
  }
  if (g_bufferId) {
    alDeleteBuffers(1, &g_bufferId),
    g_bufferId = 0;
  }
  if (alcGetCurrentContext() == g_context) {
    alcMakeContextCurrent(NULL);
  }
  // Destroy the context.
  if (g_context) {
    alcDestroyContext(g_context);
    g_context = NULL;
  }
  // Destroy the device.
  if (g_device) {
    alcCloseDevice(g_device);
    g_device = NULL;
  }
}
