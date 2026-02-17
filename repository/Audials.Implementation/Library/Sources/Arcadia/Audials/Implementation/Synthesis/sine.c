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

#define ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Audials/Implementation/Synthesis/sine.h"

/// ```
/// [sin(...) + 1] / 2 * 65535  - 32768
/// ```
/// The  minimum of
/// ```
/// [sin(...) + 1] / 2 * 65535
/// ```
/// is `0` and its maximum value is `65536`.
/// 
/// Hence the minium value of
/// ```
/// [sin(...) + 1] / 2 * 65535  - 32768
/// ```
/// is `0 - 32768 = -32768` and its maximum value is `65535 - 32768 = 32767`. 
static Arcadia_Integer16Value
doSampleInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value a,
    Arcadia_Real32Value x
  )
{
  Arcadia_Real32Value y  = (sinf(a * x) + 1.f) / 2.f * 65535.f - 32768.f;
  Arcadia_Integer16Value z;
  if (y < Arcadia_Integer32Value_Minimum) {
    z = Arcadia_Integer32Value_Minimum;
  } else if (y > Arcadia_Integer32Value_Maximum) {
    z = Arcadia_Integer32Value_Maximum;
  } else {
    z = (Arcadia_Integer32Value)y;
  }
  return z;
}

static Arcadia_Natural8Value
doSampleNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value a,
    Arcadia_Real32Value x
  )
{
  Arcadia_Real32Value y = sinf(a * x) * 255.f;
  Arcadia_Natural8Value z;
  if (y < Arcadia_Natural8Value_Minimum) {
    z = Arcadia_Natural8Value_Minimum;
  } else if (y > Arcadia_Natural8Value_Maximum) {
    z = Arcadia_Natural8Value_Maximum;
  } else {
    z = (Arcadia_Natural8Value)y;
  }
  return z;
}

void
Arcadia_Engine_Audials_Synthesis_generateSineWave
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* targetBuffer,
    Arcadia_Engine_Audials_Format format,
    Arcadia_Integer32Value seconds,
    Arcadia_Natural8Value* channels,
    Arcadia_Natural16Value* sampleRate
  )
{
  static const Arcadia_Real32Value PI = 3.14159265358979323846;
  const Arcadia_Integer32Value CHANNELS = 1;
  const Arcadia_Integer32Value FREQUENCY = 110.0f;
  const Arcadia_Integer32Value SAMPLERATE = 44100;
  const Arcadia_Integer32Value NUMBEROFSAMPLES = CHANNELS * SAMPLERATE * seconds;

  switch (format) {
    case Arcadia_Engine_Audials_Format_Natural8: {
      const float CONSTANT = 2.f * PI * (float)FREQUENCY / (float)SAMPLERATE;
      if (CHANNELS == 1) {
        for (Arcadia_SizeValue i = 0; i < NUMBEROFSAMPLES; ++i) {
          Arcadia_Natural8Value sample = doSampleNatural8(thread, CONSTANT, i);
          Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 1);
        }
      } else if (CHANNELS == 2) {
        for (Arcadia_SizeValue i = 0; i < NUMBEROFSAMPLES; ++i) {
          Arcadia_Natural8Value sample = doSampleNatural8(thread, CONSTANT, i);
          Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 1);
          Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 1);
        }
      } else {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      *channels = CHANNELS;
      *sampleRate = SAMPLERATE;
    } break;
    case Arcadia_Engine_Audials_Format_Integer16: {
      const float CONSTANT = 2.f * PI * (float)FREQUENCY / (float)SAMPLERATE;
      if (CHANNELS == 1) {
        for (Arcadia_SizeValue i = 0; i < NUMBEROFSAMPLES; ++i) {
          Arcadia_Integer16Value sample = doSampleInteger16(thread, CONSTANT, i);
          Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 2);
        }
      } else if (CHANNELS == 2) {
        for (Arcadia_SizeValue i = 0; i < NUMBEROFSAMPLES; ++i) {
          Arcadia_Integer16Value sample = doSampleInteger16(thread, CONSTANT, i);
          Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 2);
          Arcadia_ByteBuffer_insertBackBytes(thread, targetBuffer, &sample, 2);
        }
      } else {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      *channels = CHANNELS;
      *sampleRate = SAMPLERATE;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };

}