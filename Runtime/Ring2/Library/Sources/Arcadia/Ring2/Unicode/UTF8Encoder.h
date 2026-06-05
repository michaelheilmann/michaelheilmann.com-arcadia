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

#if !defined(ARCADIA_RING2_UNICODE_UTF8ENCODER_H_INCLUDED)
#define ARCADIA_RING2_UNICODE_UTF8ENCODER_H_INCLUDED

#if !defined(ARCADIA_RING2_MODULE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Unicode/Encoder.h"
typedef struct Arcadia_ByteArrayBuilder Arcadia_ByteArrayBuilder;

Arcadia_declareObjectType(u8"Arcadia.Unicode.UTF8Encoder", Arcadia_Unicode_UTF8Encoder,
                          u8"Arcadia.Unicode.Encoder");

struct Arcadia_Unicode_UTF8EncoderDispatch {
  Arcadia_Unicode_EncoderDispatch _parent;
};

struct Arcadia_Unicode_UTF8Encoder {
  Arcadia_Unicode_Encoder parent;
};

Arcadia_Unicode_UTF8Encoder*
Arcadia_Unicode_UTF8Encoder_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING2_UNICODE_UTF8ENCODER_H_INCLUDED
