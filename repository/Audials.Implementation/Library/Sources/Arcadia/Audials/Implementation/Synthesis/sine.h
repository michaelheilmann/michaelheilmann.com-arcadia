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

#if !defined(ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_SYNTHESIS_SINE_H_INCLUDED)
#define ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_SYNTHESIS_SINE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

typedef enum Arcadia_Engine_Audials_Format {

  /// Symmetric format. [0,255]. Silence at 0.
  Arcadia_Engine_Audials_Format_Natural8,

  /// Asymmetic format. [-32768,+32767]. Silence at 0.
  Arcadia_Engine_Audials_Format_Integer16

} Arcadia_Engine_Audials_Format;

void
Arcadia_Engine_Audials_Synthesis_generateSineWave
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* targetBuffer,
    Arcadia_Engine_Audials_Format format,
    Arcadia_Integer32Value seconds,
    Arcadia_Natural8Value* channels,
    Arcadia_Natural16Value* sampleRate
  );

#endif // ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_SYNTHESIS_SINE_H_INCLUDED
