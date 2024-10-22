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

// Last modified: 2024-10-07

#include "Tools/Visuals2d/PixelBuffer.h"

#include "R.h"
// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

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
PixelBuffer_destruct
  (
    PixelBuffer* self
  );

static void
PixelBuffer_destruct
  (
    PixelBuffer* self
  )
{
  if (self->bytes) {
    R_deallocateUnmanaged_nojump(self->bytes);
    self->bytes = NULL;
  }
}

Rex_defineObjectType("PixelBuffer", PixelBuffer, "R.Object", R_Object, NULL, &PixelBuffer_destruct);

R_Natural8Value
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
    R_Natural8Value* oldBytes = self->bytes;
    R_Natural8Value* newBytes = NULL;
    if (!R_allocateUnmanaged_nojump(&newBytes, (self->width * bytesPerPixel + newLinePadding) * self->height)) {
      R_jump();
    }
    for (size_t y = 0; y < self->height; ++y) {
      R_Natural8Value* oldLine = oldBytes + y * (self->width * bytesPerPixel + oldLinePadding);
      R_Natural8Value* newLine = newBytes + y * (self->width * bytesPerPixel + newLinePadding);
      memcpy(newLine, oldLine, self->width * bytesPerPixel);
    }
    R_deallocateUnmanaged_nojump(oldBytes);
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

void
PixelBuffer_constructOpaqueRed
  (
    PixelBuffer* self,
    R_SizeValue linePadding,
    R_SizeValue width,
    R_SizeValue height,
    R_Natural8Value pixelFormat
  )
{
  R_Type* _type = _PixelBuffer_getType();
  R_Object_construct((R_Object*)self);
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
  if (!R_allocateUnmanaged_nojump(&self->bytes, (width * bytesPerPixel + linePadding) * height)) {
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
  R_Object_setType((R_Object*)self, _type);
}

PixelBuffer*
PixelBuffer_createOpaqueRed
  (
    R_SizeValue linePadding,
    R_SizeValue width,
    R_SizeValue height,
    R_Natural8Value pixelFormat
  )
{
  PixelBuffer* self = R_allocateObject(_PixelBuffer_getType());
  PixelBuffer_constructOpaqueRed(self, linePadding, width, height, pixelFormat);
  return self;
}

void
PixelBuffer_constructOpaqueBlack
  (
    PixelBuffer* self,
    R_SizeValue linePadding,
    R_SizeValue width,
    R_SizeValue height,
    R_Natural8Value pixelFormat
  )
{
  R_Type* _type = _PixelBuffer_getType();
  R_Object_construct((R_Object*)self);
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
  if (!R_allocateUnmanaged_nojump(&self->bytes, (width * bytesPerPixel + linePadding) * height)) {
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
  R_Object_setType((R_Object*)self, _type);
}

PixelBuffer*
PixelBuffer_createOpaqueBlack
  (
    R_SizeValue linePadding,
    R_SizeValue width,
    R_SizeValue height,
    R_Natural8Value pixelFormat
  )
{
  PixelBuffer* self = R_allocateObject(_PixelBuffer_getType());
  PixelBuffer_constructOpaqueBlack(self, linePadding, width, height, pixelFormat);
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
