// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-01

#if !defined(R_UTF8_H_INCLUDED)
#define R_UTF8_H_INCLUDED

#include "R/cstdlib.h"
#include "R/ByteBuffer.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"

#define R_Utf8CodePoint_Last (0x0010ffff)
c_static_assert(R_Utf8CodePoint_Last <= Arcadia_Natural32Value_Maximum - 3, "<internal error>");

Arcadia_BooleanValue
R_isUtf8
  (
    void const* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  );

#endif // R_UTF8_H_INCLUDED
