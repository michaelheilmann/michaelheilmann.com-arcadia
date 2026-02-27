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

#if !defined(ARCADIA_MEDIA_SAMPLEBUFFER_H_INCLUDED)
#define ARCADIA_MEDIA_SAMPLEBUFFER_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Media/SampleFormat.h"

// https://michaelheilmann.com/Arcadia/Media/#Arcadia_Media_SampleBuffer
Arcadia_declareObjectType(u8"Arcadia.Media.SampleBuffer", Arcadia_Media_SampleBuffer,
                          u8"Arcadia.Object");

struct Arcadia_Media_SampleBufferDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_Media_SampleBuffer {
  Arcadia_Object _parent;
  /// A pointer to the Bytes of this sample buffer.
  Arcadia_Natural8Value* bytes;
  /// The sample format of this sample buffer.
  Arcadia_Media_SampleFormat sampleFormat;
  /// The length, in seconds, of this sample buffer.
  Arcadia_Integer32Value length;
  /// The sample rate, in Hz, of this sample buffer.
  Arcadia_Integer32Value sampleRate;
};

/// @brief Get the sample format of this sample buffer.
/// @param self A pointer to this sample buffer.
/// @return The sample format of this sample buffer.
Arcadia_Media_SampleFormat
Arcadia_Media_SampleBuffer_getSampleFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  );

/// @brief Get the sample rate of this sample buffer.
/// @param self A pointer to this sample buffer.
/// @return The sample rate, in Hertz, of this sample buffer.
Arcadia_Integer32Value
Arcadia_Media_SampleBuffer_getSampleRate
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  );

/// @brief Get the length, in seconds, of this sample buffer.
/// @param self A pointer to this sample buffer.
/// @return The length, in seconds, of this sample buffer.
Arcadia_Integer32Value
Arcadia_Media_SampleBuffer_getLength
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self
  );

// https://michaelheilmann.com/Arcadia/Media/#Arcadia_Media_SampleBuffer_create
Arcadia_Media_SampleBuffer*
Arcadia_Media_SampleBuffer_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value length,
    Arcadia_Integer32Value sampleRate,
    Arcadia_Media_SampleFormat sampleFormat
  );

Arcadia_Media_SampleBuffer*
Arcadia_Media_SampleBuffer_createClone
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* other
  );


void
Arcadia_Media_sampleBuffer_setFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self,
    Arcadia_Media_SampleFormat format
  );

/// @brief Swap the contents of this sample buffer with the contents of another sample buffer.
/// @param thread A pointer to this thread.
/// @param self A pointer to this sample buffer.
/// @param other A pointer to the other sample buffer.
void
Arcadia_Media_SampleBuffer_swap
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleBuffer* self,
    Arcadia_Media_SampleBuffer* other
  );

#endif // ARCADIA_MEDIA_SAMPLEBUFFER_H_INCLUDED
