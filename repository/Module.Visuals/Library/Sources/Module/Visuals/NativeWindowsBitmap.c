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

// Last modified: 2024-11-11

#include "Module/Visuals/NativeWindowsBitmap.h"

static void
NativeWindowsBitmap_destruct
  (
    NativeWindowsBitmap* self
  )
{
  if (NULL != self->hBitmap) {
    DeleteObject(self->hBitmap);
    self->hBitmap = NULL;
  }
  if (NULL != self->hDeviceContext) {
    DeleteDC(self->hDeviceContext);
    self->hDeviceContext = NULL;
  }
}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = &NativeWindowsBitmap_destruct,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("NativeWindowsBitmap", NativeWindowsBitmap, "R.Object", R_Object, &_typeOperations);

void
NativeWindowsBitmap_construct
  (
    NativeWindowsBitmap* self,
    int width,
    int height
  )
{
  R_Type* _type = _NativeWindowsBitmap_getType();
  R_Object_construct((R_Object*)self);
  self->hBitmap = NULL;
  self->hDeviceContext = NULL;

  HDC hScreenDeviceContext = GetDC(NULL);
  if (!hScreenDeviceContext) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  self->hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
  if (!self->hDeviceContext) {
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  ReleaseDC(NULL, hScreenDeviceContext);
  hScreenDeviceContext = NULL;

  BITMAPINFO bmi;
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = width;
  bmi.bmiHeader.biHeight = height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biSizeImage = (width * height) * 3;

  self->hBitmap = CreateDIBSection(self->hDeviceContext, &bmi, DIB_RGB_COLORS, NULL, NULL, 0);
  if (!self->hBitmap) {
    DeleteDC(self->hDeviceContext);
    self->hDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  if (bmi.bmiHeader.biBitCount != 24) {
    DeleteObject(self->hBitmap);
    self->hBitmap = NULL;
    DeleteDC(self->hDeviceContext);
    self->hDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  self->width = width;
  self->height = height;
  DWORD lineStride = ((((bmi.bmiHeader.biWidth * bmi.bmiHeader.biBitCount) + 31) & ~31) >> 3);
  DWORD linePadding = lineStride - ((bmi.bmiHeader.biWidth * bmi.bmiHeader.biBitCount) >> 3);
  if (lineStride > INT32_MAX) {
    DeleteObject(self->hBitmap);
    self->hBitmap = NULL;
    DeleteDC(self->hDeviceContext);
    self->hDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  self->lineStride = (int32_t)lineStride;
  self->linePadding = (uint32_t)linePadding;
  self->numberOfBitsPerPixel = 24;
  self->pixelFormat = PixelFormat_Bn8Gn8Rn8;

  HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
  if (!hBrush) {
    DeleteObject(self->hBitmap);
    self->hBitmap = NULL;
    DeleteDC(self->hDeviceContext);
    self->hDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  SelectObject(self->hDeviceContext, self->hBitmap);
  RECT fillRetc = { .left = 0, .top = 0, .right = self->width, .bottom = self->height };
  FillRect(self->hDeviceContext, &fillRetc, hBrush);
  DeleteObject(hBrush);
  hBrush = NULL;

  R_Object_setType(self, _type);
}

NativeWindowsBitmap*
NativeWindowsBitmap_create
  (
    int width,
    int height
  )
{
  NativeWindowsBitmap* self = R_allocateObject(_NativeWindowsBitmap_getType());
  NativeWindowsBitmap_construct(self, width, height);
  return self;
}

void
NativeWindowsBitmap_fill
  (
    NativeWindowsBitmap* self,
    uint8_t r,
    uint8_t g,
    uint8_t b
  )
{
  HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b));
  if (!hBrush) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  SelectObject(self->hDeviceContext, self->hBitmap);
  RECT fillRetc = { .left = 0, .top = 0, .right = self->width, .bottom = self->height };
  FillRect(self->hDeviceContext, &fillRetc, hBrush);
  DeleteObject(hBrush);
  hBrush = NULL;
}

PixelBuffer*
NativeWindowsBitmap_toPixelBuffer
  (
    NativeWindowsBitmap* self
  )
{
  DIBSECTION dibSection;
  if (!GetObject(self->hBitmap, sizeof(DIBSECTION), &dibSection)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  uint8_t* sourceBytes = dibSection.dsBm.bmBits;
  // Currently, we assume that NativeWindowsBitmap is BGR format.
  PixelBuffer* pixelBuffer = PixelBuffer_create(0, self->width, self->height, PixelFormat_An8Rn8Gn8Bn8);
  for (int32_t y = 0; y < self->height; ++y) {
    for (int32_t x = 0; x < self->width; ++x) {
      int32_t sourceOffset = self->lineStride * y + (x * self->numberOfBitsPerPixel) / 8;
      int32_t targetOffset = PixelBuffer_getLineStride(pixelBuffer) * y + x * PixelBuffer_getBytesPerPixel(pixelBuffer);
      uint8_t* source = sourceBytes + sourceOffset;
      PixelBuffer_setPixelRgba(pixelBuffer, x, y, source[2], source[1], source[0], 255);
    }
  }
  PixelBuffer_reflectHorizontally(pixelBuffer);
  return pixelBuffer;
}

#if 0
static void
TextureFontWindows_destruct
  (
    TextureFontWindows* self
  )
{
  if (NULL != self->hFont) {
    DeleteObject(self->hFont);
    self->hFont = NULL;
  }
}

Rex_defineObjectType("TextureFontWindows", TextureFontWindows, "R.Object", R_Object, NULL, &TextureFontWindows_destruct);

void
TextureFontWindows_construct
  (
    TextureFontWindows* self
  )
{
  R_Type* _type = _TextureFontWindows_getType();
  R_Object_construct((R_Object*)self);
  //
  HDC hScreenDeviceContext = GetDC(NULL);
  if (!hScreenDeviceContext) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  HDC hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
  if (!hDeviceContext) {
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  ReleaseDC(NULL, hScreenDeviceContext);
  hScreenDeviceContext = NULL;
  // Get the size of the symbol.
  self->codePoint = 'A';
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  R_Utf8Writer* utf8ByteBufferWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(byteBuffer);
  R_Utf8Writer_writeCodePoints(utf8ByteBufferWriter, &self->codePoint, 1);
  RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
  DrawTextA(hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
  int32_t width = textRect.right - textRect.left;
  int32_t height = textRect.bottom - textRect.top;
  DeleteDC(hDeviceContext);
  hDeviceContext = NULL;
  // Create a bitmap of that size. Draw the symbol to the bitmap.
  self->bitmap = NativeWindowsBitmap_create(width, height);
  DrawTextA(self->bitmap->hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  //
  R_Object_setType(self, _type);
}

TextureFontWindows*
TextureFontWindows_create
  (
  )
{
  TextureFontWindows* self = R_allocateObject(_TextureFontWindows_getType());
  TextureFontWindows_construct(self);
  return self;
}

void
TextureFontWindows_setCodePoint
  (
    TextureFontWindows* self,
    R_Natural32Value codePoint
  )
{
  if (self->codePoint != codePoint) {
    HDC hScreenDeviceContext = GetDC(NULL);
    if (!hScreenDeviceContext) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    HDC hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
    if (!hDeviceContext) {
      ReleaseDC(NULL, hScreenDeviceContext);
      hScreenDeviceContext = NULL;
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    // Get the size of the symbol.
    self->codePoint = codePoint;
    R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
    R_Utf8Writer* utf8ByteBufferWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(byteBuffer);
    R_Utf8Writer_writeCodePoints(utf8ByteBufferWriter, &self->codePoint, 1);
    RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
    DrawTextA(hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
    int32_t width = textRect.right - textRect.left;
    int32_t height = textRect.bottom - textRect.top;
    DeleteDC(hDeviceContext);
    hDeviceContext = NULL;
    // Create a bitmap of that size. Draw the symbol to the bitmap.
    self->bitmap = NativeWindowsBitmap_create(width, height);
    DrawTextA(self->bitmap->hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  }
}

PixelBuffer*
TextureFontWindows_getPixelBuffer
  (
    TextureFontWindows* self
  )
{
  return NativeWindowsBitmap_toPixelBuffer(self->bitmap);
}
#endif
