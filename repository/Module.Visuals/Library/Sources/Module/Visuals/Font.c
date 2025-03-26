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
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
TextureFontWindows_destruct
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  TextureFontWindows* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _TextureFontWindows_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  //
  HDC hScreenDeviceContext = GetDC(NULL);
  if (!hScreenDeviceContext) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  HDC hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
  if (!hDeviceContext) {
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  ReleaseDC(NULL, hScreenDeviceContext);
  hScreenDeviceContext = NULL;
  // Get the size of the symbol.
  _self->codePoint = 'A';
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_Utf8Writer* utf8ByteBufferWriter = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, byteBuffer);
  Arcadia_Utf8Writer_writeCodePoints(thread, utf8ByteBufferWriter, &_self->codePoint, 1);
  RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
  DrawTextA(hDeviceContext, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
  int32_t width = textRect.right - textRect.left;
  int32_t height = textRect.bottom - textRect.top;
  DeleteDC(hDeviceContext);
  hDeviceContext = NULL;
  // Create a bitmap of that size. Draw the symbol to the bitmap.
  _self->bitmap = NativeWindowsBitmap_create(thread, width, height);
  DrawTextA(_self->bitmap->hDeviceContext, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  //
  Arcadia_Object_setType(thread, _self, _type);
}

static void
TextureFontWindows_destruct
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  TextureFontWindows* self = Arcadia_allocateObject(thread, _TextureFontWindows_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
TextureFontWindows_setCodePoint
  (
    Arcadia_Thread* thread,
    TextureFontWindows* self,
    Arcadia_Natural32Value codePoint
  )
{
  if (self->codePoint != codePoint) {
    HDC hScreenDeviceContext = GetDC(NULL);
    if (!hScreenDeviceContext) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    HDC hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
    if (!hDeviceContext) {
      ReleaseDC(NULL, hScreenDeviceContext);
      hScreenDeviceContext = NULL;
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    // Get the size of the symbol.
    self->codePoint = codePoint;
    Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
    Arcadia_Utf8Writer* utf8ByteBufferWriter = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, byteBuffer);
    Arcadia_Utf8Writer_writeCodePoints(thread, utf8ByteBufferWriter, &self->codePoint, 1);
    RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
    DrawTextA(hDeviceContext, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
    int32_t width = textRect.right - textRect.left;
    int32_t height = textRect.bottom - textRect.top;
    DeleteDC(hDeviceContext);
    hDeviceContext = NULL;
    // Create a bitmap of that size. Draw the symbol to the bitmap.
    self->bitmap = NativeWindowsBitmap_create(thread, width, height);
    DrawTextA(self->bitmap->hDeviceContext, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  }
}

PixelBuffer*
TextureFontWindows_getPixelBuffer
  (
    Arcadia_Thread* thread,
    TextureFontWindows* self
  )
{
  return NativeWindowsBitmap_toPixelBuffer(thread, self->bitmap);
}
