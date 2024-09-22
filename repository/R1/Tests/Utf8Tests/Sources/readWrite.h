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

#if !defined(R1_TESTS_UTF8_READWRITE_H_INCLUDED)
#define R1_TESTS_UTF8_READWRITE_H_INCLUDED

#include "R.h"

/// @brief
/// - create a Byte buffer holding the sequence (source)
/// - create an empty Byte buffer (target)
/// - read its unicode code points using Utf8ByteBufferReader from source
/// - write each unicode code point into target using Utf8ByteBufferWriter
/// - compare the contents of both Byte buffer
/// - success if thes contents are equal
/// - failure otherwise
void
R1_Tests_Utf8_readWrite
  (
    char const* p,
    size_t n
  );

#endif // R1_TESTS_UTF8_READWRITE_H_INCLUDED

