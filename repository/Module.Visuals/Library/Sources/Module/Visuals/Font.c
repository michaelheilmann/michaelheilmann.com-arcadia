// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Module/Visuals/Font.h"

static void
TextureFontWindows_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
TextureFontWindows_destruct
  (
    Arcadia_Process* process,
    TextureFontWindows* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &TextureFontWindows_constructImpl,
  .destruct = &TextureFontWindows_destruct,
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

Rex_defineObjectType(u8"TextureFontWindows", TextureFontWindows, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
TextureFontWindows_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  TextureFontWindows* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _TextureFontWindows_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  //
  HDC hScreenDeviceContext = GetDC(NULL);
  if (!hScreenDeviceContext) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  HDC hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
  if (!hDeviceContext) {
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  ReleaseDC(NULL, hScreenDeviceContext);
  hScreenDeviceContext = NULL;
  // Get the size of the symbol.
  _self->codePoint = 'A';
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create(process);
  R_Utf8Writer* utf8ByteBufferWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(process, byteBuffer);
  R_Utf8Writer_writeCodePoints(process, utf8ByteBufferWriter, &_self->codePoint, 1);
  RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
  DrawTextA(hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
  int32_t width = textRect.right - textRect.left;
  int32_t height = textRect.bottom - textRect.top;
  DeleteDC(hDeviceContext);
  hDeviceContext = NULL;
  // Create a bitmap of that size. Draw the symbol to the bitmap.
  _self->bitmap = NativeWindowsBitmap_create(process, width, height);
  DrawTextA(_self->bitmap->hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  //
  Arcadia_Object_setType(process, _self, _type);
}

static void
TextureFontWindows_destruct
  (
    Arcadia_Process* process,
    TextureFontWindows* self
  )
{
  if (NULL != self->hFont) {
    DeleteObject(self->hFont);
    self->hFont = NULL;
  }
}

TextureFontWindows*
TextureFontWindows_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  TextureFontWindows* self = R_allocateObject(process, _TextureFontWindows_getType(process), 0, &argumentValues[0]);
  return self;
}

void
TextureFontWindows_setCodePoint
  (
    Arcadia_Process* process,
    TextureFontWindows* self,
    Arcadia_Natural32Value codePoint
  )
{
  if (self->codePoint != codePoint) {
    HDC hScreenDeviceContext = GetDC(NULL);
    if (!hScreenDeviceContext) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    HDC hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
    if (!hDeviceContext) {
      ReleaseDC(NULL, hScreenDeviceContext);
      hScreenDeviceContext = NULL;
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    // Get the size of the symbol.
    self->codePoint = codePoint;
    R_ByteBuffer* byteBuffer = R_ByteBuffer_create(process);
    R_Utf8Writer* utf8ByteBufferWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(process, byteBuffer);
    R_Utf8Writer_writeCodePoints(process, utf8ByteBufferWriter, &self->codePoint, 1);
    RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
    DrawTextA(hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
    int32_t width = textRect.right - textRect.left;
    int32_t height = textRect.bottom - textRect.top;
    DeleteDC(hDeviceContext);
    hDeviceContext = NULL;
    // Create a bitmap of that size. Draw the symbol to the bitmap.
    self->bitmap = NativeWindowsBitmap_create(process, width, height);
    DrawTextA(self->bitmap->hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  }
}

PixelBuffer*
TextureFontWindows_getPixelBuffer
  (
    Arcadia_Process* process,
    TextureFontWindows* self
  )
{
  return NativeWindowsBitmap_toPixelBuffer(process, self->bitmap);
}
