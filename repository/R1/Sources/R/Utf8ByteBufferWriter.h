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

// Last modified: 2024-09-22

#if !defined(R_UTF8BYTEBUFFERWRITER_H_INCLUDED)
#define R_UTF8BYTEBUFFERWRITER_H_INCLUDED

#include "R/Utf8Writer.h"
typedef struct R_ByteBuffer R_ByteBuffer;

#define R_UTF8BYTEBUFFERWRITER(x) ((R_Utf8ByteBufferWriter*)(x))
typedef struct R_Utf8ByteBufferWriter R_Utf8ByteBufferWriter;
void _R_Utf8ByteBufferWriter_registerType();

struct R_Utf8ByteBufferWriter {
  R_Utf8Writer parent;
  R_ByteBuffer* target; 
};

R_Utf8ByteBufferWriter*
R_Utf8ByteBufferWriter_create
  (
    R_ByteBuffer* target
  );

#endif // R_UTF8BYTEBUFFERWRITER_H_INCLUDED
