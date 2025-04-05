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

// Last modified: 2024-09-19

#if !defined(MODULE_VISUALS_IMAGEWRITER_H_INCLUDED)
#define MODULE_VISUALS_IMAGEWRITER_H_INCLUDED

#include "R/Include.h"
#include "Module/Visuals/PixelBuffer.h"

Arcadia_declareObjectType(u8"ImageWriter", ImageWriter, u8"Arcadia.Object");

struct ImageWriter {
  Arcadia_Object _parent;
  void (*writePngToPath)(Arcadia_Thread* thread, ImageWriter* self, PixelBuffer* sourcePixelBuffer, Arcadia_String* targetPath);
  void (*writePngToByteBuffer)(Arcadia_Thread* thread, ImageWriter* self, PixelBuffer* sourcePixelBuffer, Arcadia_ByteBuffer* targetByteBuffer);
  void (*writeBmpToPath)(Arcadia_Thread* thread, ImageWriter* self, PixelBuffer* sourcePixelBuffer, Arcadia_String* targetPath);
  void (*writeBmpToByteBuffer)(Arcadia_Thread* thread, ImageWriter* self, PixelBuffer* sourcePixelBuffer, Arcadia_ByteBuffer* targetByteBuffer);
  void (*writeIcoToPath)(Arcadia_Thread* thread, ImageWriter* self, Arcadia_List* sourcePixelBuffers, Arcadia_String* targetPath);
  void (*writeIcoToByteBuffer)(Arcadia_Thread* thread, ImageWriter* self, Arcadia_List* sourcePixelBuffers, Arcadia_ByteBuffer* targetByteBuffer);
};

void
ImageWriter_writePngToPath
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

void
ImageWriter_writePngToByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

void
ImageWriter_writeBmpToPath
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

void
ImageWriter_writeBmpToByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

void
ImageWriter_writeIcoToPath
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

void
ImageWriter_writeIcoToByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

#endif // MODULE_VISUALS_IMAGEWRITER_H_INCLUDED
