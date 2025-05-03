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

#include "Module/Visuals/Windows/Bitmap.h"

static void
Windows_NativeBitmap_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Windows_NativeBitmap_destruct
  (
    Arcadia_Thread* thread,
    Windows_NativeBitmap* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Windows_NativeBitmap_constructImpl,
  .destruct = &Windows_NativeBitmap_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Arcadia_defineObjectType(u8"Windows.NativeBitmap", Windows_NativeBitmap, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Windows_NativeBitmap_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Windows_NativeBitmap* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Windows_NativeBitmap_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
 
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Value_isInteger32Value(&argumentValues[0])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Value_isInteger32Value(&argumentValues[1])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }

  _self->hBitmap = NULL;
  _self->hDeviceContext = NULL;

  HDC hScreenDeviceContext = GetDC(NULL);
  if (!hScreenDeviceContext) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  _self->hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
  if (!_self->hDeviceContext) {
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  ReleaseDC(NULL, hScreenDeviceContext);
  hScreenDeviceContext = NULL;

  BITMAPINFO bmi;
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = Arcadia_Value_getInteger32Value(&argumentValues[0]);
  bmi.bmiHeader.biHeight = Arcadia_Value_getInteger32Value(&argumentValues[1]);
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biSizeImage = (bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight) * 3;

  _self->hBitmap = CreateDIBSection(_self->hDeviceContext, &bmi, DIB_RGB_COLORS, NULL, NULL, 0);
  if (!_self->hBitmap) {
    DeleteDC(_self->hDeviceContext);
    _self->hDeviceContext = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (bmi.bmiHeader.biBitCount != 24) {
    DeleteObject(_self->hBitmap);
    _self->hBitmap = NULL;
    DeleteDC(_self->hDeviceContext);
    _self->hDeviceContext = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  _self->width = Arcadia_Value_getInteger32Value(&argumentValues[0]);
  _self->height = Arcadia_Value_getInteger32Value(&argumentValues[1]);
  DWORD lineStride = ((((bmi.bmiHeader.biWidth * bmi.bmiHeader.biBitCount) + 31) & ~31) >> 3);
  DWORD linePadding = lineStride - ((bmi.bmiHeader.biWidth * bmi.bmiHeader.biBitCount) >> 3);
  if (lineStride > INT32_MAX) {
    DeleteObject(_self->hBitmap);
    _self->hBitmap = NULL;
    DeleteDC(_self->hDeviceContext);
    _self->hDeviceContext = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  _self->lineStride = (int32_t)lineStride;
  _self->linePadding = (uint32_t)linePadding;
  _self->numberOfBitsPerPixel = 24;
  _self->pixelFormat = Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8;

  HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
  if (!hBrush) {
    DeleteObject(_self->hBitmap);
    _self->hBitmap = NULL;
    DeleteDC(_self->hDeviceContext);
    _self->hDeviceContext = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  SelectObject(_self->hDeviceContext, _self->hBitmap);
  RECT fillRetc = { .left = 0, .top = 0, .right = _self->width, .bottom = _self->height };
  FillRect(_self->hDeviceContext, &fillRetc, hBrush);
  DeleteObject(hBrush);
  hBrush = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Windows_NativeBitmap_destruct
  (
    Arcadia_Thread* thread,
    Windows_NativeBitmap* self
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

Windows_NativeBitmap*
Windows_NativeBitmap_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  Arcadia_Value argumentValues[] = { 
    Arcadia_Value_makeInteger32Value(width),
    Arcadia_Value_makeInteger32Value(height),
  };
  Windows_NativeBitmap* self = Arcadia_allocateObject(thread, _Windows_NativeBitmap_getType(thread), 2, &argumentValues[0]);
  return self;
}

void
Windows_NativeBitmap_fill
  (
    Arcadia_Thread* thread,
    Windows_NativeBitmap* self,
    Arcadia_Natural8Value r,
    Arcadia_Natural8Value g,
    Arcadia_Natural8Value b
  )
{
  HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b));
  if (!hBrush) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  SelectObject(self->hDeviceContext, self->hBitmap);
  RECT fillRetc = { .left = 0, .top = 0, .right = self->width, .bottom = self->height };
  FillRect(self->hDeviceContext, &fillRetc, hBrush);
  DeleteObject(hBrush);
  hBrush = NULL;
}

Arcadia_Visuals_PixelBuffer*
Windows_NativeBitmap_toPixelBuffer
  (
    Arcadia_Thread* thread,
    Windows_NativeBitmap* self
  )
{
  DIBSECTION dibSection;
  if (!GetObject(self->hBitmap, sizeof(DIBSECTION), &dibSection)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  uint8_t* sourceBytes = dibSection.dsBm.bmBits;
  // Currently, we assume that NativeWindowsBitmap is BGR format.
  Arcadia_Visuals_PixelBuffer* pixelBuffer = Arcadia_Visuals_PixelBuffer_create(thread, 0, self->width, self->height, Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8);
  for (int32_t y = 0; y < self->height; ++y) {
    for (int32_t x = 0; x < self->width; ++x) {
      int32_t sourceOffset = self->lineStride * y + (x * self->numberOfBitsPerPixel) / 8;
      uint8_t* source = sourceBytes + sourceOffset;
      Arcadia_Visuals_PixelBuffer_setPixelRgba(thread, pixelBuffer, x, y, source[2], source[1], source[0], 255);
    }
  }
  Arcadia_Visuals_PixelBuffer_reflectHorizontally(thread, pixelBuffer);
  return pixelBuffer;
}
