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

Rex_declareObjectType("NativeWindowsImageWriter", NativeWindowsImageWriter, "R.Object");

struct NativeWindowsImageWriter {
  R_Object _parent;
};

void
NativeWindowsImageWriter_construct
  (
    NativeWindowsImageWriter* self
  );

NativeWindowsImageWriter*
NativeWindowsImageWriter_create
  (
  );

void writePngToPath(PixelBuffer* sourcePixelBuffer, R_String* targetPath);

void writePngToByteBuffer(PixelBuffer* sourcePixelBuffer, R_ByteBuffer* targetByteBuffer);

void writeBmpToPath(PixelBuffer* sourcePixelBuffer, R_String* targetPath);

void writeBmpToByteBuffer(PixelBuffer* sourcePixelBuffer, R_ByteBuffer* targetByteBuffer);

// The "Windows Imaging Component" ("WIC") does not provide an encoder for "ico" files.
// See https://learn.microsoft.com/en-us/windows/win32/wic/ico-format-overview?redirectedfrom=MSDN for more information.
// 
// The "ico" file format is described on Wikipedia.
// See https://en.wikipedia.org/wiki/ICO_(file_format) for more information.
// 
// From the description of the file format:
// - The width and height of any image in an "ico" files may not exceed 256.
// - all source pixel buffers must be of format PixelBuffer_An8Rn8Gn8Bn8.
void writeIconToPath(R_List* sourcePixelBuffers, R_String* targetPath);

void writeIconToByteBuffer(R_List* sourcePixelBuffers, R_ByteBuffer* targetByteBuffer);

#endif // MODULE_VISUALS_IMAGEWRITER_H_INCLUDED
