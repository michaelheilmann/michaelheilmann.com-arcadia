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
#include "Arcadia/Media/SampleBuffer.h"

#include "Arcadia/Media/SampleFormat.h"

/// @code
/// construct(seconds:Integer32,sampleFormat:Arcadia.Media.SampleFormat)
/// @endcode
///
/// @code
/// construct(sampleBuffer:Arcadia.Media.SampleBuffer)
/// @endcode
static void
Arcadia_Media_SampleBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  );

static void
Arcadia_Media_SampleBuffer_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferDispatch* self
  );

static void
Arcadia_Media_SampleBuffer_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Media_SampleBuffer_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Media_SampleBuffer_destruct,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Media.SampleBuffer", Arcadia_Media_SampleBuffer,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Media_SampleBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Media_SampleBuffer);
  if (1 == _numberOfArguments) {
    {
      Arcadia_ValueStack_pushNatural8Value(thread, 0);
      Arcadia_superTypeConstructor(thread, _type, self);
    }
    Arcadia_Media_SampleBuffer* other = (Arcadia_Media_SampleBuffer*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Media_SampleBuffer_getType(thread));
    self->length = Arcadia_Media_SampleBuffer_getLength(thread, other);
    self->sampleRate = Arcadia_Media_SampleBuffer_getSampleRate(thread, other);
    self->sampleFormat = Arcadia_Media_SampleBuffer_getSampleFormat(thread, other);
    Arcadia_SizeValue bytesPerSample = Arcadia_Media_SampleFormat_getNumberOfBytes(thread, other->sampleFormat);
    Arcadia_SizeValue bytes = (bytesPerSample * self->length * self->sampleRate);
    self->bytes = Arcadia_Memory_allocateUnmanaged(thread, bytes);
    Arcadia_Memory_copy(thread, self->bytes, other->bytes, bytes);
    
    Arcadia_LeaveConstructor(Arcadia_Media_SampleBuffer);
  } else if (3 == _numberOfArguments) {
    {
      Arcadia_ValueStack_pushNatural8Value(thread, 0);
      Arcadia_superTypeConstructor(thread, _type, self);
    }
    self->bytes = NULL;
    self->length = Arcadia_ValueStack_getInteger32Value(thread, 3);
    self->sampleRate = Arcadia_ValueStack_getInteger32Value(thread, 2);
    Arcadia_EnumerationValue enumerationValue = Arcadia_ValueStack_getEnumerationValue(thread, 1);
    if (!Arcadia_Type_isDescendantType(thread, enumerationValue.type, _Arcadia_Media_SampleFormat_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    self->sampleFormat = enumerationValue.value;

    Arcadia_SizeValue bytesPerSample = Arcadia_Media_SampleFormat_getNumberOfBytes(thread, self->sampleFormat);
    self->bytes = Arcadia_Memory_allocateUnmanaged(thread, (bytesPerSample * self->length * self->sampleRate));
    switch (self->sampleFormat) {
      case Arcadia_Media_SampleFormat_Integer16: {
        for (Arcadia_SizeValue i = 0, n = self->length * self->sampleRate; i < n; ++i) {
          Arcadia_Integer16Value* p = ((Arcadia_Integer16Value*)self->bytes) + i;
          *p = Arcadia_Integer16Value_Literal(0);
        }
      } break;
      case Arcadia_Media_SampleFormat_Integer8: {
        for (Arcadia_SizeValue i = 0, n = self->length * self->sampleRate; i < n; ++i) {
          Arcadia_Integer8Value* p = ((Arcadia_Integer8Value*)self->bytes) + i;
          *p = Arcadia_Integer8Value_Literal(0);
        }
      } break;
      case Arcadia_Media_SampleFormat_Natural16: {
        static const Arcadia_Natural16Value silence = Arcadia_Natural16Value_Literal(32768);
        for (Arcadia_SizeValue i = 0, n = self->length * self->sampleRate; i < n; ++i) {
          Arcadia_Natural16Value* p = ((Arcadia_Natural16Value*)self->bytes) + i;
          *p = silence;
        }
      } break;
      case Arcadia_Media_SampleFormat_Natural8: {
        static const Arcadia_Natural8Value silence = Arcadia_Natural8Value_Literal(128);
        for (Arcadia_SizeValue i = 0, n = self->length * self->sampleRate; i < n; ++i) {
          Arcadia_Natural8Value* p = ((Arcadia_Natural8Value*)self->bytes) + i;
          *p = silence;
        }
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };

    Arcadia_LeaveConstructor(Arcadia_Media_SampleBuffer);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_Media_SampleBuffer_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBufferDispatch* self
  )
{ }

static void
Arcadia_Media_SampleBuffer_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  )
{
  if (self->bytes) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->bytes);
    self->bytes = NULL;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Media_SampleFormat
Arcadia_Media_SampleBuffer_getSampleFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  )
{ return self->sampleFormat; }

Arcadia_Integer32Value
Arcadia_Media_SampleBuffer_getSampleRate
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  )
{ return self->sampleRate; }

Arcadia_Integer32Value
Arcadia_Media_SampleBuffer_getLength
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  )
{ return self->length; }

Arcadia_Media_SampleBuffer*
Arcadia_Media_SampleBuffer_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value length,
    Arcadia_Integer32Value sampleRate,
    Arcadia_Media_SampleFormat sampleFormat
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, length);
  Arcadia_ValueStack_pushInteger32Value(thread, sampleRate);
  Arcadia_ValueStack_pushEnumerationValue(thread, Arcadia_EnumerationValue_make(_Arcadia_Media_SampleFormat_getType(thread), sampleFormat));
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Media_SampleBuffer);
}

Arcadia_Media_SampleBuffer*
Arcadia_Media_SampleBuffer_createClone
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* other
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (other) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, other);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Media_SampleBuffer);
}
