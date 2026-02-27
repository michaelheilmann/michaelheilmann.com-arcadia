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

#define ARCADIA_MEDIA_PRIVATE (1)
#include "Arcadia/Media/SampleBufferOperations/SineWave.h"

#include "Arcadia/Media/Quantization.h"

static void
Arcadia_Media_SampleBufferOperations_SineWave_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferOperations_SineWave* self
  );

static void
Arcadia_Media_SampleBufferOperations_SineWave_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferOperations_SineWaveDispatch* self
  );

static void
Arcadia_Media_SampleBufferOperations_SineWave_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferOperations_SineWave* self
  );

static void
Arcadia_Media_SampleBufferOperations_SineWave_apply
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferOperations_SineWave* self,
    Arcadia_Media_SampleBuffer* target
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Media_SampleBufferOperations_SineWave_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Media_SampleBufferOperations_SineWave_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Media.SampleBufferOperations.SineWave", Arcadia_Media_SampleBufferOperations_SineWave,
                         u8"Arcadia.Media.SampleBufferOperation", Arcadia_Media_SampleBufferOperation,
                         &_typeOperations);

static void
Arcadia_Media_SampleBufferOperations_SineWave_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferOperations_SineWave* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Media_SampleBufferOperations_SineWave);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->frequency = Arcadia_ValueStack_getInteger32Value(thread, 1);
  if (self->frequency < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_Media_SampleBufferOperations_SineWave);
}

static void
Arcadia_Media_SampleBufferOperations_SineWave_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferOperations_SineWaveDispatch* self
  )
{
  ((Arcadia_Media_SampleBufferOperationDispatch*)self)->apply = (void (*)(Arcadia_Thread*, Arcadia_Media_SampleBufferOperation*, Arcadia_Media_SampleBuffer*)) & Arcadia_Media_SampleBufferOperations_SineWave_apply;
}

static void
Arcadia_Media_SampleBufferOperations_SineWave_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferOperations_SineWave* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Media_SampleBufferOperations_SineWave_apply
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferOperations_SineWave* self,
    Arcadia_Media_SampleBuffer* target
  )
{
  static const Arcadia_Real32Value PI = 3.14159265358979323846;
  const Arcadia_Integer32Value SAMPLERATE = Arcadia_Media_SampleBuffer_getSampleRate(thread, target);
  const Arcadia_Integer32Value NUMBEROFSAMPLES = SAMPLERATE * Arcadia_Media_SampleBuffer_getLength(thread, target);

  switch (Arcadia_Media_SampleBuffer_getSampleFormat(thread, target)) {
    case Arcadia_Media_SampleFormat_Integer16: {
      const Arcadia_Real32Value CONSTANT = 2.f * PI * (Arcadia_Real32Value)self->frequency / (Arcadia_Real32Value)SAMPLERATE;
      Arcadia_Integer16Value* p = (Arcadia_Integer16Value*)target->bytes;
      for (Arcadia_SizeValue i = 0; i < NUMBEROFSAMPLES; ++i) {
        Arcadia_Integer16Value sample = Arcadia_Media_quantizeInteger16(thread, sinf(CONSTANT * (Arcadia_Real32Value)i));
        p[i] = sample;
      }
    } break;
    case Arcadia_Media_SampleFormat_Integer8: {
      const Arcadia_Real32Value CONSTANT = 2.f * PI * (Arcadia_Real32Value)self->frequency / (Arcadia_Real32Value)SAMPLERATE;
      Arcadia_Integer8Value* p = (Arcadia_Integer8Value*)target->bytes;
      for (Arcadia_SizeValue i = 0; i < NUMBEROFSAMPLES; ++i) {
        Arcadia_Integer8Value sample = Arcadia_Media_quantizeInteger8(thread, sinf(CONSTANT * (Arcadia_Real32Value)i));
        p[i] = sample;
      }
    } break;
    case Arcadia_Media_SampleFormat_Natural16: {
      const Arcadia_Real32Value CONSTANT = 2.f * PI * (Arcadia_Real32Value)self->frequency / (Arcadia_Real32Value)SAMPLERATE;
      Arcadia_Natural16Value* p = (Arcadia_Natural16Value*)target->bytes;
      for (Arcadia_SizeValue i = 0; i < NUMBEROFSAMPLES; ++i) {
        Arcadia_Natural16Value sample = Arcadia_Media_quantizeNatural16(thread, sinf(CONSTANT * (Arcadia_Real32Value)i));
        p[i] = sample;
      }
    } break;
    case Arcadia_Media_SampleFormat_Natural8: {
      const Arcadia_Real32Value CONSTANT = 2.f * PI * (Arcadia_Real32Value)self->frequency / (Arcadia_Real32Value)SAMPLERATE;
      Arcadia_Natural8Value* p = (Arcadia_Natural8Value*)target->bytes;
      for (Arcadia_SizeValue i = 0; i < NUMBEROFSAMPLES; ++i) {
        Arcadia_Natural8Value sample = Arcadia_Media_quantizeNatural8(thread, sinf(CONSTANT * (Arcadia_Real32Value)i));
        p[i] = sample;
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

Arcadia_Media_SampleBufferOperations_SineWave*
Arcadia_Media_SampleBufferOperations_SineWave_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value frequency
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, frequency);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Media_SampleBufferOperations_SineWave);
}
