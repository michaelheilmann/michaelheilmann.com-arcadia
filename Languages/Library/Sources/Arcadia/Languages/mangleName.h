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

#if !defined(ARCADIA_LANGUAGES_MANGLENAME_H_INCLUDED)
#define ARCADIA_LANGUAGES_MANGLENAME_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// The name mangler encodes the sequence of UTF-8 Bytes (x_1, ..., x_n) of an input string
// as a prefix 'x' plus a sequence of hexadeicmal numbers y_1, ..., y_, that is as ('x', y_1, ..., y_n).
// Each hexadecimal numbers are using small caps and is padded with a zero
// if its number of hex digits is smaller than 2.
// For example:
// a) the single Byte sequence (0) would be represented as ('x', '00')
// b) the single Byte sequence (7) would be represented by ('x', '07')
// c) the single Byte sequence (15) would be represented as ('x','0f')
// d) the single Byte sequence (128) would be represented as ('x', '80')
// e) the single Byte sequence (255) would be represented as xff.
// f) the two Byte sequence (1, 128) would be encoded as ('x', '01', '80').
// @param source The value of type Arcadia.String or Arcadia.StringBuffer.
Arcadia_String*
Arcadia_Languages_mangleName
  (
    Arcadia_Thread* thread,
    Arcadia_Value source
  );

#endif // ARCADIA_LANGUAGES_MANGLENAME_H_INCLUDED
