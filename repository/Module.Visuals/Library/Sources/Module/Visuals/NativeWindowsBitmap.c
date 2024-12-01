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
NativeWindowsBitmap_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
NativeWindowsBitmap_destruct
  (
    NativeWindowsBitmap* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &NativeWindowsBitmap_constructImpl,
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

static void
NativeWindowsBitmap_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  NativeWindowsBitmap* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _NativeWindowsBitmap_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
 
  if (2 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Value_isInteger32Value(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Value_isInteger32Value(&argumentValues[1])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }

  _self->hBitmap = NULL;
  _self->hDeviceContext = NULL;

  HDC hScreenDeviceContext = GetDC(NULL);
  if (!hScreenDeviceContext) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  _self->hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
  if (!_self->hDeviceContext) {
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  ReleaseDC(NULL, hScreenDeviceContext);
  hScreenDeviceContext = NULL;

  BITMAPINFO bmi;
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = R_Value_getInteger32Value(&argumentValues[0]);
  bmi.bmiHeader.biHeight = R_Value_getInteger32Value(&argumentValues[1]);
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biSizeImage = (bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight) * 3;

  _self->hBitmap = CreateDIBSection(_self->hDeviceContext, &bmi, DIB_RGB_COLORS, NULL, NULL, 0);
  if (!_self->hBitmap) {
    DeleteDC(_self->hDeviceContext);
    _self->hDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  if (bmi.bmiHeader.biBitCount != 24) {
    DeleteObject(_self->hBitmap);
    _self->hBitmap = NULL;
    DeleteDC(_self->hDeviceContext);
    _self->hDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  _self->width = R_Value_getInteger32Value(&argumentValues[0]);
  _self->height = R_Value_getInteger32Value(&argumentValues[1]);
  DWORD lineStride = ((((bmi.bmiHeader.biWidth * bmi.bmiHeader.biBitCount) + 31) & ~31) >> 3);
  DWORD linePadding = lineStride - ((bmi.bmiHeader.biWidth * bmi.bmiHeader.biBitCount) >> 3);
  if (lineStride > INT32_MAX) {
    DeleteObject(_self->hBitmap);
    _self->hBitmap = NULL;
    DeleteDC(_self->hDeviceContext);
    _self->hDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  _self->lineStride = (int32_t)lineStride;
  _self->linePadding = (uint32_t)linePadding;
  _self->numberOfBitsPerPixel = 24;
  _self->pixelFormat = PixelFormat_Bn8Gn8Rn8;

  HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
  if (!hBrush) {
    DeleteObject(_self->hBitmap);
    _self->hBitmap = NULL;
    DeleteDC(_self->hDeviceContext);
    _self->hDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  SelectObject(_self->hDeviceContext, _self->hBitmap);
  RECT fillRetc = { .left = 0, .top = 0, .right = _self->width, .bottom = _self->height };
  FillRect(_self->hDeviceContext, &fillRetc, hBrush);
  DeleteObject(hBrush);
  hBrush = NULL;

  R_Object_setType(_self, _type);
}

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

NativeWindowsBitmap*
NativeWindowsBitmap_create
  (
    R_Integer32Value width,
    R_Integer32Value height
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Integer32, .integer32Value = width },
                               {.tag = R_ValueTag_Integer32, .integer32Value = height } };
  NativeWindowsBitmap* self = R_allocateObject(_NativeWindowsBitmap_getType(), 2, &argumentValues[0]);
  return self;
}

void
NativeWindowsBitmap_fill
  (
    NativeWindowsBitmap* self,
    R_Natural8Value r,
    R_Natural8Value g,
    R_Natural8Value b
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
      uint8_t* source = sourceBytes + sourceOffset;
      PixelBuffer_setPixelRgba(pixelBuffer, x, y, source[2], source[1], source[0], 255);
    }
  }
  PixelBuffer_reflectHorizontally(pixelBuffer);
  return pixelBuffer;
}
