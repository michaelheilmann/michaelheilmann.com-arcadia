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

#if !defined(ARCADIA_MEDIA_SAMPLEBUFFEROPERATION_H_INCLUDED)
#define ARCADIA_MEDIA_SAMPLEBUFFEROPERATION_H_INCLUDED

#include "Arcadia/Media/SampleBuffer.h"

Arcadia_declareObjectType(u8"Arcadia.Media.DSP", Arcadia_Media_DSP,
                          u8"Arcadia.Object");

struct Arcadia_Media_DSPDispatch {
  Arcadia_ObjectDispatch parent;

  void (*generate)(Arcadia_Thread* thread, Arcadia_Media_DSP* self, Arcadia_Natural32Value samples, Arcadia_Natural32Value numberOfSamples, Arcadia_ByteArrayBuilder* target);
};

struct Arcadia_Media_DSP {
  Arcadia_Object parent;
};

/// @brief Generate a number of samples.
/// @param thread A pointer to this thread.
/// @param self A pointer to this DSP.
/// @param sampleRate The sample rate.
/// @param numberOfSamples The number of samples.
/// @param buffer A pointer to a buffer of @a numberOfSamples Arcadia_Real32Value.
void
Arcadia_Media_DSP_generate
  (
    Arcadia_Thread* thread,
    Arcadia_Media_DSP* self,
    Arcadia_Natural32Value sampleRate,
    Arcadia_Natural32Value numberOfSamples,
    Arcadia_ByteArrayBuilder* target
  );

#endif // ARCADIA_MEDIA_SAMPLEBUFFEROPERATION_H_INCLUDED
