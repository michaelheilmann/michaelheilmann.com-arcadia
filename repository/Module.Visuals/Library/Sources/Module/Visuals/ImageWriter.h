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

// Last modified: 2024-09-19

#if !defined(MODULE_VISUALS_IMAGEWRITER_H_INCLUDED)
#define MODULE_VISUALS_IMAGEWRITER_H_INCLUDED

#include "R.h"
#include "Module/Visuals/PixelBuffer.h"

Rex_declareObjectType("ImageWriter", ImageWriter, "R.Object");

struct ImageWriter {
  R_Object _parent;
  void (*writePngToPath)(ImageWriter* self, PixelBuffer* sourcePixelBuffer, R_String* targetPath);
  void (*writePngToByteBuffer)(ImageWriter* self, PixelBuffer* sourcePixelBuffer, R_ByteBuffer* targetByteBuffer);
  void (*writeBmpToPath)(ImageWriter* self, PixelBuffer* sourcePixelBuffer, R_String* targetPath);
  void (*writeBmpToByteBuffer)(ImageWriter* self, PixelBuffer* sourcePixelBuffer, R_ByteBuffer* targetByteBuffer);
  void (*writeIcoToPath)(ImageWriter* self, R_List* sourcePixelBuffers, R_String* targetPath);
  void (*writeIcoToByteBuffer)(ImageWriter* self, R_List* sourcePixelBuffers, R_ByteBuffer* targetByteBuffer);
};

void
ImageWriter_writePngToPath
  (
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_String* targetPath
  );

void
ImageWriter_writePngToByteBuffer
  (
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  );

void
ImageWriter_writeBmpToPath
  (
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_String* targetPath
  );

void
ImageWriter_writeBmpToByteBuffer
  (
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  );

void
ImageWriter_writeIcoToPath
  (
    ImageWriter* self,
    R_List* sourcePixelBuffers,
    R_String* targetPath
  );

void
ImageWriter_writeIcoToByteBuffer
  (
    ImageWriter* self,
    R_List* sourcePixelBuffers,
    R_ByteBuffer* targetByteBuffer
  );

#endif // MODULE_VISUALS_IMAGEWRITER_H_INCLUDED
