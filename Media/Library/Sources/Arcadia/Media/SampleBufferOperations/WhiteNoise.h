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

#if !defined(ARCADIA_MEDIA_SAMPLEBUFFEROPERATIONS_WHITENOISE_H_INCLUDED)
#define ARCADIA_MEDIA_SAMPLEBUFFEROPERATIONS_WHITENOISE_H_INCLUDED

#include "Arcadia/ADL/Include.h"
#include "Arcadia/Media/SampleBufferOperation.h"

/// @brief Fill the buffer with white noise.
/// @todo We use rand() here. We must not use rand() as it is in general not thread safe.
Arcadia_declareObjectType(u8"Arcadia.Media.SampleBufferOperations.WhiteNoise", Arcadia_Media_SampleBufferOperations_WhiteNoise,
                          u8"Arcadia.Media.SampleBufferOperation");

struct Arcadia_Media_SampleBufferOperations_WhiteNoiseDispatch {
  Arcadia_Media_SampleBufferOperationDispatch parent;
};

struct Arcadia_Media_SampleBufferOperations_WhiteNoise {
  Arcadia_Media_SampleBufferOperation parent;
  //Arcadia_ADL_SampleBufferOperations_WhiteNoiseOperationDefinition* definition;
};

Arcadia_Media_SampleBufferOperations_WhiteNoise*
Arcadia_Media_SampleBufferOperations_WhiteNoise_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_MEDIA_SAMPLEBUFFEROPERATIONS_WHITENOISE_H_INCLUDED
