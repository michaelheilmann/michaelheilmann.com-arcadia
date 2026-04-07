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

#include "Arcadia/SampleBufferIO/Include.h"

#define FLAC__NO_DLL
#include "FLAC/metadata.h"
#include "FLAC/stream_encoder.h"

void
Arcadia_SampleBufferIO_encodeFLAC
  (
    Arcadia_Thread* thread
  )
{
  // (1) Open the encoder.
  FLAC__StreamEncoder* encoder = FLAC__stream_encoder_new();
  if (!encoder) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // (2) Close the encoder.
  FLAC__stream_encoder_finish(encoder);
  encoder = NULL;
}
