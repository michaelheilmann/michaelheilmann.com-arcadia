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

#if !defined(ARCADIA_MEDIA_SAMPLEBUFFEROPERATIONS_SINEWAVE_H_INCLUDED)
#define ARCADIA_MEDIA_SAMPLEBUFFEROPERATIONS_SINEWAVE_H_INCLUDED

#include "Arcadia/ADL/Include.h"
#include "Arcadia/Media/SampleBufferOperation.h"

Arcadia_declareObjectType(u8"Arcadia.Media.SampleBufferOperations.SineWave", Arcadia_Media_SampleBufferOperations_SineWave,
                          u8"Arcadia.Media.SampleBufferOperation");

struct Arcadia_Media_SampleBufferOperations_SineWaveDispatch {
  Arcadia_Media_SampleBufferOperationDispatch parent;
};

struct Arcadia_Media_SampleBufferOperations_SineWave {
  Arcadia_Media_SampleBufferOperation parent;
  Arcadia_Integer32Value frequency;
  //Arcadia_ADL_SampleBufferOperations_SineWaveOperationDefinition* definition;
};

Arcadia_Media_SampleBufferOperations_SineWave*
Arcadia_Media_SampleBufferOperations_SineWave_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value frequency
  );

#endif // ARCADIA_MEDIA_SAMPLEBUFFEROPERATIONS_SINEWAVE_H_INCLUDED
