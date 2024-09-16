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

// Last modified: 2024-09-16


#if !defined(TOOLS_VISUALS2D_IMAGEWRITERPARAMETERS_H_INCLUDED)
#define TOOLS_VISUALS2D_IMAGEWRITERPARAMETERS_H_INCLUDED

#include "R.h"

typedef enum ImageWriterFormat {
  ImageWriterFormat_Undefined = 0,
  ImageWriterFormat_Tiff,
  ImageWriterFormat_Png,
  ImageWriterFormat_Bmp,
} ImageWriterFormat;

typedef struct ImageWriterParameters ImageWriterParameters;

void _ImageWriterParameters_registerType();

ImageWriterParameters*
ImageWriterParameters_createFile
  (
    R_String* path,
    ImageWriterFormat format
  );

ImageWriterParameters*
ImageWriterParameters_createByteBuffer
  (
    R_ByteBuffer* byteBuffer,
    ImageWriterFormat format
  );

R_BooleanValue
ImageWriterParameters_hasPath
  (
    ImageWriterParameters* self
  );

R_String*
ImageWriterParameters_getPath
  (
    ImageWriterParameters* self
  );

R_BooleanValue
ImageWriterParameters_hasByteBuffer
  (
    ImageWriterParameters* self
  );

R_ByteBuffer*
ImageWriterParameters_getByteBuffer
  (
    ImageWriterParameters* self
  );

ImageWriterFormat
ImageWriterParameters_getFormat
  (
    ImageWriterParameters* self
  );

#endif // TOOLS_VISUALS2D_IMAGEWRITERPARAMETERS_H_INCLUDED
