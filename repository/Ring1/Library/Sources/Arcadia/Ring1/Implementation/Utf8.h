// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_UTF8_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_UTF8_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"

#define Arcadia_Utf8CodePoint_Last (0x0010ffff)
Arcadia_StaticAssert(Arcadia_Utf8CodePoint_Last <= Arcadia_Natural32Value_Maximum - 3, "<internal error>");

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia_isUtf8
Arcadia_BooleanValue
Arcadia_isUtf8
  (
    Arcadia_Thread* thread,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  );

/// @brief Encode a sequence of Unicode code points to their corresponding sequence of UTF-8 Bytes.
/// @remarks
/// This function also validates if the sequence of Natural32 values is a valid sequence of Unicode code points.
void
Arcadia_Utf8_encodeCodePoints
  (
    Arcadia_Process* process,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints,
    void* callbackContext,
    void (*callbackFunction)(Arcadia_Process*, void *callbackContext, Arcadia_Natural8Value const* bytes, Arcadia_SizeValue numberOfBytes)
  );

/// @brief Encode a sequence of Bytes into their corresponding sequence of UTF8 Bytes.
/// @remarks
/// This function also validates if the sequence of Natural8 values is a valid code points.
void
Arcadia_Utf8_encodeBytes
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes,
    void* callbackContext,
    void (*callbackFunction)(Arcadia_Process*, void* callbackContext, Arcadia_Natural8Value const* bytes, Arcadia_SizeValue numberOfBytes)
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_UTF8_H_INCLUDED
