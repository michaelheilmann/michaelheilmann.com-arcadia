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

#if !defined(ARCADIA_RING2_TESTS_UTF8_READ_H_INCLUDED)
#define ARCADIA_RING2_TESTS_UTF8_READ_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

void
Arcadia_Tests_Utf8_read2
  (
    Arcadia_Thread* thread
  );

/// @brief
/// Let x := [x1, ..., xn] be a sequence of pairs such that x[i] is a pair (a_i, b_i) with a_i being a valid UTF-8 Byte sequence and b_i being a sequence of
/// Unicode code points corresponding to a_i.
/// This test then performs for each x[i] the followin test:
/// - store x[i].a in a Byte buffer
/// - decode the Byte buffer into a sequence of Unicode code points using an UTF-8 Byte buffer reader
/// - compare the decoded sequence to b[i]
/// - success if they are equal
/// - failure otherwise
void
Arcadia_Tests_Utf8_read1
  (
    Arcadia_Thread* threadprocess
  );

#endif // ARCADIA_RING2_TESTS_UTF8_READ_H_INCLUDED

