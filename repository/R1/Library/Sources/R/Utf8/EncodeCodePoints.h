// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-06

#if !defined(R_UTF8_ENCODECODEPOINTS_H_INCLUDED)
#define R_UTF8_ENCODECODEPOINTS_H_INCLUDED

#if defined(R_EXPORTED_INCLUDE)
  #error("R/Utf8/EncodeCodePoints.h must not be included from public header")
#endif

#include "R/Natural8.h"
#include "R/Natural32.h"
#include "R/Size.h"

/// @brief Encode a sequence of Unicode code points to their corresponding sequence of UTF-8 Bytes.
/// Given a sequence of code points x_1, ..., x_n then callbackFunction is invoked for each code point in ascending order at most once.
/// If an error is encountered at x_i, then the function is not invoked for that and all subsequent code points.
/// If invoked for a code point x_i, then it receives in numberOfBytes the number of Bytes the code point decodes to and in bytes a pointer to an array containing those Bytes.
void
R_Utf8_encodeCodePoints
  (
    R_Natural32Value const* codePoints,
    R_SizeValue numberOfCodePoints,
    void* callbackContext,
    void (*callbackFunction)(void *callbackContext, R_Natural8Value const* bytes, R_SizeValue numberOfBytes)
  );

#endif // R_UTF8_ENCODECODEPOINTS_H_INCLUDED
