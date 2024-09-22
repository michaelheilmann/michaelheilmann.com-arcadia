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

#include "Tools/Visuals2d/PixelBuffer.h"

#include "R/ArmsIntegration.h"
#include <string.h>
#include <malloc.h>

static void inline
ENCODE_ARGB
  (
    uint32_t* p,
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a
  )
{
  (*p) =  ((uint32_t)a) << 24
       |  ((uint32_t)r) << 16
       |  ((uint32_t)g) <<  8
       |  ((uint32_t)b) <<  0;
}

static void inline
ENCODE_RGBA
  (
    uint32_t* p,
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a
  )
{
  (*p) = ((uint32_t)g) << 24
       | ((uint32_t)r) << 16
       | ((uint32_t)b) << 8
       | ((uint32_t)a) << 0;
}

static void
PixelBuffer_finalize
  (
    PixelBuffer* self
  );

static void
PixelBuffer_finalize
  (
    PixelBuffer* self
  )
{
  if (self->bytes) {
    R_Arms_deallocateUnmanaged_nojump(self->bytes);
    self->bytes = NULL;
  }
}

void
_PixelBuffer_registerType
  (
  )
{ R_registerObjectType("PixelBuffer", sizeof("PixelBuffer") - 1, sizeof(PixelBuffer), NULL, NULL, &PixelBuffer_finalize); }

uint8_t
PixelBuffer_getFormat
  (
    PixelBuffer* self
  )
{
  return self->pixelFormat;
}

void
PixelBuffer_setLinePadding
  (
    PixelBuffer* self,
    R_SizeValue linePadding
  )
{
  if (self->linePadding != linePadding) {
    size_t bytesPerPixel = 0;
    switch (self->pixelFormat) {
      case PixelFormat_An8Rn8Gn8Bn8: {
        bytesPerPixel = 4;
      } break;
      case PixelFormat_Rn8Gn8Bn8: {
        bytesPerPixel = 3;
      } break;
      default: {
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
    }
    size_t oldLinePadding = self->linePadding;
    size_t newLinePadding = linePadding;
    uint8_t* oldBytes = self->bytes;
    uint8_t* newBytes = NULL;
    if (!R_Arms_allocateUnmanaged_nojump(&newBytes, (self->width * bytesPerPixel + newLinePadding) * self->height)) {
      R_jump();
    }
    for (size_t y = 0; y < self->height; ++y) {
      uint8_t* oldLine = oldBytes + y * (self->width * bytesPerPixel + oldLinePadding);
      uint8_t* newLine = newBytes + y * (self->width * bytesPerPixel + newLinePadding);
      memcpy(newLine, oldLine, self->width * bytesPerPixel);
    }
    R_Arms_deallocateUnmanaged_nojump(oldBytes);
    self->bytes = newBytes;
    self->linePadding = linePadding;
  }
}

R_SizeValue
PixelBuffer_getLinePadding
  (
    PixelBuffer* self
  )
{ return self->linePadding; }

PixelBuffer*
PixelBuffer_createOpaqueRed
  (
    size_t linePadding,
    size_t width,
    size_t height,
    uint8_t pixelFormat
  )
{
  PixelBuffer* self = R_allocateObject(R_getObjectType("PixelBuffer", sizeof("PixelBuffer") - 1));
  self->bytes = NULL;
  self->height = 0;
  self->linePadding = 0;
  self->pixelFormat = 0;
  self->width = 0;
  size_t bytesPerPixel = 0;
  switch (pixelFormat) {
    case PixelFormat_An8Rn8Gn8Bn8: {
      bytesPerPixel = 4;
    } break;
    case PixelFormat_Rn8Gn8Bn8: {
      bytesPerPixel = 3;
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  }
  if (!R_Arms_allocateUnmanaged_nojump(&self->bytes, (width * bytesPerPixel + linePadding) * height)) {
    R_jump();
  }
  self->pixelFormat = pixelFormat;
  self->width = width;
  self->height = height;
  self->linePadding = linePadding;
  uint32_t pixelValue;
  ENCODE_ARGB(&pixelValue, 255, 0, 0, 255);
  size_t lineStride = self->width * bytesPerPixel + self->linePadding;
  for (size_t y = 0; y < self->height; ++y) {
    uint32_t* p = (uint32_t*)(self->bytes + y * lineStride);
    for (size_t x = 0; x < self->width; ++x) {
      // ARGB
      p[x] = pixelValue;
    }
  }
  return self;
}

PixelBuffer*
PixelBuffer_createOpaqueBlack
  (
    size_t linePadding,
    size_t width,
    size_t height,
    uint8_t pixelFormat
  )
{
  PixelBuffer* self = R_allocateObject(R_getObjectType("PixelBuffer", sizeof("PixelBuffer") - 1));
  self->bytes = NULL;
  self->height = 0;
  self->linePadding = 0;
  self->pixelFormat = 0;
  self->width = 0;
  size_t bytesPerPixel = 0;
  switch (pixelFormat) {
    case PixelFormat_An8Rn8Gn8Bn8: {
      bytesPerPixel = 4;
    } break;
    case PixelFormat_Rn8Gn8Bn8: {
      bytesPerPixel = 3;
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  }
  if (!R_Arms_allocateUnmanaged_nojump(&self->bytes, (width * bytesPerPixel + linePadding) * height)) {
    R_jump();
  }
  self->pixelFormat = pixelFormat;
  self->width = width;
  self->height = height;
  self->linePadding = linePadding;
  uint32_t pixelValue;
  ENCODE_ARGB(&pixelValue, 0, 0, 0, 255);
  size_t lineStride = self->width * bytesPerPixel + self->linePadding;
  for (size_t y = 0; y < self->height; ++y) {
    uint32_t* p = (uint32_t*)(self->bytes + y * lineStride);
    for (size_t x = 0; x < self->width; ++x) {
      // ARGB
      p[x] = pixelValue;
    }
  }
  return self;
}

R_SizeValue
PixelBuffer_getWidth
  (
    PixelBuffer* self
  )
{
  return self->width;
}

R_SizeValue
PixelBuffer_getHeight
  (
    PixelBuffer* self
  )
{
  return self->height;
}

R_SizeValue
PixelBuffer_getLineStride
  (
    PixelBuffer* self
  )
{
  return PixelBuffer_getWidth(self) * PixelBuffer_getBytesPerPixel(self) + PixelBuffer_getLinePadding(self);
}

R_SizeValue
PixelBuffer_getBytesPerPixel
  (
    PixelBuffer* self
  )
{
  size_t bytesPerPixel = 0;
  switch (self->pixelFormat) {
    case PixelFormat_An8Rn8Gn8Bn8: {
      bytesPerPixel = 4;
    } break;
    case PixelFormat_Rn8Gn8Bn8: {
      bytesPerPixel = 3;
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  }
  return bytesPerPixel;
}
