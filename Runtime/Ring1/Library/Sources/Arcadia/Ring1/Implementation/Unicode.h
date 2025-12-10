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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_UNICODE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_UNICODE_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Unicode/Unicode.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"

#include "Arcadia/Ring1/Implementation/Unicode/Unicode.h"
#include "Arcadia/Ring1/Implementation/Unicode/Utf8.h"

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Unicode_isUtf8
Arcadia_BooleanValue
Arcadia_Unicode_isUtf8
  (
    Arcadia_Thread* thread,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Unicode_EncodeCodePointCallbackContext
typedef void Arcadia_Unicode_EncodeCodePointCallbackContext;

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Unicode_EncodeCodePointCallbackFunction
typedef void (Arcadia_Unicode_EncodeCodePointCallbackFunction)(Arcadia_Thread*, Arcadia_Unicode_EncodeCodePointCallbackContext* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes);

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Unicode_encodeCodePointsUtf8
void
Arcadia_Unicode_encodeCodePointsUtf8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints,
    Arcadia_Unicode_EncodeCodePointCallbackContext* context,
    Arcadia_Unicode_EncodeCodePointCallbackFunction* function
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Unicode_encodeCodePointsUtf32Be
void
Arcadia_Unicode_encodeCodePointsUtf32Be
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints,
    Arcadia_Unicode_EncodeCodePointCallbackContext* context,
    Arcadia_Unicode_EncodeCodePointCallbackFunction* function
  );

// https://michaelheilmann.com/Arcadia.Ring1/#Arcadia_Unicode_encodeCodePointsUtf32Le
void
Arcadia_Unicode_encodeCodePointsUtf32Le
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints,
    Arcadia_Unicode_EncodeCodePointCallbackContext* context,
    Arcadia_Unicode_EncodeCodePointCallbackFunction* function
  );

/// @brief Encode a sequence of Bytes into their corresponding sequence of UTF8 Bytes.
/// @remarks
/// This function also validates if the sequence of Natural8 values is a valid code points.
void
Arcadia_Unicode_encodeBytesUtf8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_Unicode_EncodeCodePointCallbackContext* context,
    Arcadia_Unicode_EncodeCodePointCallbackFunction* function
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_UNICODE_H_INCLUDED
