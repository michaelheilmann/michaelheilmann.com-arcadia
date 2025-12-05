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

#if !defined(ARCADIA_RING2_TESTS_UTF8_READWRITE_H_INCLUDED)
#define ARCADIA_RING2_TESTS_UTF8_READWRITE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

/// @summary
/// Let x := [x[1], ..., x[n]] be a sequence such that each x[i] is an UTF-8 Byte sequence.
/// This test then performs for each x[i] the followin test:
/// - create a Byte buffer holding x[i]
/// - create an empty Byte buffer (target)
/// - read its unicode code points using UTF8ByteBufferReader from source
/// - write each unicode code point into target using UTF8ByteBufferWriter
/// - compare the contents of both Byte buffers
/// - success if their contents are equal
/// - failure otherwise
void
Arcadia_Tests_UTF8_readWrite1
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING2_TESTS_UTF8_READWRITE_H_INCLUDED

