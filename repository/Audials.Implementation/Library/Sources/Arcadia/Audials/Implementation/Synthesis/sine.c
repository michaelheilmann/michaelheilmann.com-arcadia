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

#define ARCADIA_AUDIALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Audials/Implementation/Synthesis/sine.h"

void
Arcadia_Audials_Synthesis_generateSineWave
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* targetBuffer,
    Arcadia_Natural8Value* channels,
    Arcadia_Natural16Value* sampleRate
  )
{
  static const float PI = 3.14159265358979323846;
  const int CHANNELS = 1;
  const int FREQUENCY = 110.0f;
  const int SECONDS = 6.f;
  const int SAMPLERATE = 44100;
  const int NUMBEROFSAMPLES = CHANNELS * SAMPLERATE * SECONDS;

  const float CONSTANT = 2.f * PI * (float)FREQUENCY / (float)SAMPLERATE;
  if (CHANNELS == 1) {
    for (size_t i = 0; i < NUMBEROFSAMPLES; ++i) {
      int16_t sample = 32760 * sin(CONSTANT * i);
      Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 2);
    }
  } else if (CHANNELS == 2) {
    for (size_t i = 0; i < NUMBEROFSAMPLES; ++i) {
      int16_t sample = 32760 * sin(CONSTANT * i);
      Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 2);
      Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 2);
    }
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  *channels = CHANNELS;
  *sampleRate = SAMPLERATE;
}
