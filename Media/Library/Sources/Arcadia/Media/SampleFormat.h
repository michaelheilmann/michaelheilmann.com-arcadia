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

#if !defined(ARCADIA_MEDIA_SAMPLEFORMAT_H_INCLUDED)
#define ARCADIA_MEDIA_SAMPLEFORMAT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// https://michaelheilmann.com/Arcadia/Media/#Arcadia_Media_SampleFormat
Arcadia_declareEnumerationType(u8"Arcadia.Media.SampleFormat", Arcadia_Media_SampleFormat);

enum Arcadia_Media_SampleFormat {

  Arcadia_Media_SampleFormat_Integer16,

  Arcadia_Media_SampleFormat_Integer8,

  Arcadia_Media_SampleFormat_Natural16,

  Arcadia_Media_SampleFormat_Natural8,

  // TODO: Add to documentation.
  Arcadia_Media_SampleFormat_Real32,

};

// https://michaelheilmann.com/Arcadia/Media/#Arcadia_Media_SampleFormat_getNumberOfBytes
Arcadia_SizeValue
Arcadia_Media_SampleFormat_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Media_SampleFormat self
  );

#endif // ARCADIA_MEDIA_SAMPLEFORMAT_H_INCLUDED
