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

// Last modified: 2024-08-27

#if !defined(R1_TESTS_UTF8_READ_H_INCLUDED)
#define R1_TESTS_UTF8_READ_H_INCLUDED

#include "R.h"

/// @brief
/// - provides a set of Unicode code points and their corresponding UTF8 Byte sequences
/// - store these UTF8 Byte sequences in a Byte buffer
/// - decode them from the Byte buffer using Utf8ByteBufferReader and compare the decoded Unicode code point to the corresponding Unicode code point of the decoded UTF8 Byte sequence 
/// - success if they are equal
/// - failure otherwise
void R1_Tests_Utf8_read1();

#endif // R1_TESTS_UTF8_READ_H_INCLUDED

