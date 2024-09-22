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

#if !defined(TOOLS_VISUALS2D_PIXELBUFFER_H_INCLUDED)
#define TOOLS_VISUALS2D_PIXELBUFFER_H_INCLUDED

#include "R.h"

#define PixelFormat_An8Rn8Gn8Bn8 (1)
#define PixelFormat_Rn8Gn8Bn8 (2)

/// - width: The width, in Pixels, of the image.
/// - height: The height, in Pixels, of the image.
/// - pixel format: The pixel format of the image.
/// - line padding: The number of Bytes after the last Byte of a line.
/// - line stride: The number of Bytes between the first Bytes of two consecutive lines.
///                width * bytesPerPixel + linePadding
typedef struct PixelBuffer PixelBuffer;

void _PixelBuffer_registerType();

struct PixelBuffer {
  uint8_t* bytes;
  uint8_t pixelFormat;
  R_SizeValue width;
  R_SizeValue height;
  R_SizeValue linePadding;
};

uint8_t
PixelBuffer_getFormat
  (
    PixelBuffer* self
  );

/// Set the line padding of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param linePadding The line padding.
/// @warning Can result in reallocation.
/// @warning The contents of the padding Bytes are unspecified.
void
PixelBuffer_setLinePadding
  (
    PixelBuffer* self,
    size_t linePadding
  );

R_SizeValue
PixelBuffer_getLinePadding
  (
    PixelBuffer* self
  );

PixelBuffer*
PixelBuffer_createOpaqueRed
  (
    R_SizeValue linePadding,
    R_SizeValue width,
    R_SizeValue height,
    uint8_t pixelFormat
  );

PixelBuffer*
PixelBuffer_createOpaqueBlack
  (
    R_SizeValue linePadding,
    R_SizeValue width,
    R_SizeValue height,
    uint8_t pixelFormat
  );

/// @brief Get the width of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The width of this pixel buffer.
R_SizeValue
PixelBuffer_getWidth
  (
    PixelBuffer* self
  );

/// @brief Get the height of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The height of this pixel buffer.
R_SizeValue
PixelBuffer_getHeight
  (
    PixelBuffer* self
  );

/// @brief Get the line stride of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The line stride of this pixel buffer.
R_SizeValue
PixelBuffer_getLineStride
  (
    PixelBuffer* self
  );

/// @brief Get the Bytes per pixel of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The line stride of this pixel buffer.
R_SizeValue
PixelBuffer_getBytesPerPixel
  (
    PixelBuffer* self
  );

#endif // TOOLS_VISUALS2D_PIXELBUFFER_H_INCLUDED
