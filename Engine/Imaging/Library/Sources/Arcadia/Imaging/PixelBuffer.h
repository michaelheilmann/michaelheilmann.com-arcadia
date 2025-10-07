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

#if !defined(ARCADIA_IMAGING_PIXELBUFFER_H_INCLUDED)
#define ARCADIA_IMAGING_PIXELBUFFER_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Imaging/PixelFormat.h"

/// - number of columns: The number of columns of the image.
///   A column is adressed by zero-based consecutive integral ascending indices (0,1,2,...)
/// - number of rows: The number of rows of the image.
///   A row is adressed by zero-based consecutive integral ascending indices (0,1,2,...)
/// - pixel format: The pixel format of the image.
/// - line padding: The number of Bytes after the last Byte of a line.
/// - line stride: The number of Bytes between the first Bytes of two consecutive lines.
///                number of columns * bytesPerPixel + line padding
/// - cell: A cell is uniquely adressed by its column index and its row index.
///         Each cell accomodates one pixel.
Arcadia_declareObjectType(u8"Arcadia.Imaging.PixelBuffer", Arcadia_Imaging_PixelBuffer,
                          u8"Arcadia.Object");

struct Arcadia_Imaging_PixelBuffer {
  Arcadia_Object _parent;
  /// A pointer to the Bytes of this pixel buffer.
  Arcadia_Natural8Value* bytes;
  /// The pixel format of this pixel buffer.
  Arcadia_Natural8Value pixelFormat;
  /// The height, in pixels, of this pixel buffer.
  Arcadia_Integer32Value height;
  /// The width, in pixels, of this pixel buffer.
  Arcadia_Integer32Value width;
  /// The line padding of this pixel buffer.
  Arcadia_Integer32Value linePadding;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the pixel format of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The pixel format of this pixel buffer.
Arcadia_Natural8Value
Arcadia_Imaging_PixelBuffer_getPixelFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/// @brief Get the pixel format of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param format The format.
/// @remarks
/// When converting from BGR or RGB to ABGR, ARGB, BGRA, or RGBA,
/// an alpha component with value 255 is added.
/// When converting from ABGR, ARGB, BGRA, or RGBA to BGR or RGB,
/// the alpha component is removed.
void
Arcadia_Imaging_PixelBuffer_setPixelFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Natural8Value pixelFormat
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the line padding of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The line padding of this pixel buffer. Always non-negative.
Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getLinePadding
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/// @brief Set the line padding of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param linePadding The line padding. Must be non-negative.
/// @warning Can result in reallocation.
/// @warning The contents of the padding Bytes are unspecified.
void
Arcadia_Imaging_PixelBuffer_setLinePadding
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value linePadding
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get component values of a pixel at the specified position in this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param column The column index of the pixel.
/// Must be non-negative. Must be smaller than or equal to the number of columns.
/// @param row The row of the pixel.
/// Must be non-negative. Must be smaller than or equal to the number of rows.
/// @param r A pointer to a <code>Arcadia_Natural8Value</code> variable.
/// @param g A pointer to a <code>Arcadia_Natural8Value</code> variable.
/// @param b A pointer to a <code>Arcadia_Natural8Value</code> variable.
/// @param a A pointer to a <code>Arcadia_Natural8Value</code> variable.
/// @pre The pixel buffer must of a format ABGR, ARGB, BGR, BGRA, RGB, or RGBA.
/// The component values of the format must be an integer within the range of of [0,255].
/// @post
/// On success:
/// <code>*r</code> is assigned the red component of the pixel.
/// <code>*g</code> is assigned the green component of the pixel.
/// <code>*b</code> is assigned the blue component of the pixel.
/// <code>*a</code> is assigned the alpha component of the pixel
/// if the pixel has an alpha component.
/// Otherwise it is assigned 255.
void
Arcadia_Imaging_PixelBuffer_getPixelRgba
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value column,
    Arcadia_Integer32Value row,
    Arcadia_Natural8Value* r,
    Arcadia_Natural8Value* g,
    Arcadia_Natural8Value* b,
    Arcadia_Natural8Value* a
  );

/// @brief Set component values of a pixel at the specified position in this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param column The column index of the pixel.
/// Must be non-negative. Must be smaller than or equal to the number of columns.
/// @param row The row of the pixel.
/// Must be non-negative. Must be smaller than or equal to the number of rows.
/// @param r The red component value.
/// @param g The green component value.
/// @param b The blue component value.
/// @param a The alpha component value.
/// @pre The pixel buffer must of a format ABGR, ARGB, BGR, BGRA, RGB, or RGBA.
/// The component values of the format must be an integer within the range of of [0,255].
/// @post
/// On success:
/// <code>r</code> is assigned to the red component of the pixel.
/// <code>g</code> is assigned to the green component of the pixel.
/// <code>a</code> is assigned to the blue component of the pixel.
/// <code>a</code> is assigned to the alpha component of the pixel
/// if the pixel has an alpha component.
void
Arcadia_Imaging_PixelBuffer_setPixelRgba
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value column,
    Arcadia_Integer32Value row,
    Arcadia_Natural8Value r,
    Arcadia_Natural8Value g,
    Arcadia_Natural8Value b,
    Arcadia_Natural8Value a
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set component values of the pixels in this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param r The red component value.
/// @param g The green component value.
/// @param b The blue component value.
/// @param a The alpha component value.
/// @pre The pixel buffer must of a format ABGR, ARGB, BGR, BGRA, RGB, or RGBA.
/// The component values of the format must be an integer within the range of of [0,255].
/// @post
/// On success:
/// <code>r</code> is assigned to the red component of the pixel.
/// <code>g</code> is assigned to the green component of the pixel.
/// <code>a</code> is assigned to the blue component of the pixel.
/// <code>a</code> is assigned to the alpha component of the pixel
/// if the pixel has an alpha component.
void
Arcadia_Imaging_PixelBuffer_fill
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Natural8Value r,
    Arcadia_Natural8Value g,
    Arcadia_Natural8Value b,
    Arcadia_Natural8Value a
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Swap columns.
/// @param self A pointer to this pixel buffer.
/// @param column1 The first column.
/// @param column2 The second colum.
void
Arcadia_Imaging_PixelBuffer_swapColumns
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value column1,
    Arcadia_Integer32Value column2
  );

/// @brief Swap row.
/// @param self A pointer to this pixel buffer.
/// @param row1 The first row.
/// @param row2 The second row.
void
Arcadia_Imaging_PixelBuffer_swapRows
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value row1,
    Arcadia_Integer32Value row2
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Mirror this pixel buffer vertically.
/// @param self A pointer to this pixel buffer.
/// @post The pixel buffer was reflected horizontally.
/// That is, it was reflected by the axis starting at (width / 2, -infinity) to (width / 2, +infinity).
/// such that the pixel at position (column, row) is now at position (width - 1 - column, row).
void
Arcadia_Imaging_PixelBuffer_reflectVertically
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/// @brief Reflect this pixel buffer horizontally.
/// @param self A pointer to this pixel buffer.
/// @post The pixel buffer was reflected horizontally.
/// That is, it was reflected by the axis starting at (-infinity, height / 2) to (+infinity, height / 2).
/// such that the pixel at position (column, row) is now at position (column, height - 1 - row).
void
Arcadia_Imaging_PixelBuffer_reflectHorizontally
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the number of columns of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The number of columns of this pixel buffer.
Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getNumberOfColumns
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/// @brief Get the number of rows of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The number of rows of this pixel buffer.
Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getNumberOfRows
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the line stride of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The line stride of this pixel buffer.
Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getLineStride
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the Bytes per pixel of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The line stride of this pixel buffer.
Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getBytesPerPixel
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// Create a pixel buffer of the specified width, height, and pixel format.
/// Its default color is opaque black.
Arcadia_Imaging_PixelBuffer*
Arcadia_Imaging_PixelBuffer_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value linePadding,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value pixelFormat
  );

Arcadia_Imaging_PixelBuffer*
Arcadia_Imaging_PixelBuffer_createClone
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* other
  );

/// @brief Get the width of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The width of this pixel buffer.
Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

/// @brief Get the height of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The height of this pixel buffer.
Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

#endif // ARCADIA_IMAGING_PIXELBUFFER_H_INCLUDED
