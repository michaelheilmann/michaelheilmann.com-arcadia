// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/Visuals/Implementation/Windows/TextureFont.h"

static void
Arcadia_Visuals_Windows_TextureFont_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFont* self
  );

static void
Arcadia_Visuals_Windows_TextureFont_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFontDispatch* self
  );

static void
Arcadia_Visuals_Windows_TextureFont_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFont* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Windows_TextureFont_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Windows_TextureFont_destruct,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.TextureFont", Arcadia_Visuals_Windows_TextureFont,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_Windows_TextureFont_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFont* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_TextureFont_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
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
  self->codePoint = 'A';
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_UTF8Writer* utf8ByteBufferWriter = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, byteBuffer);
  Arcadia_UTF8Writer_writeCodePoints(thread, utf8ByteBufferWriter, &self->codePoint, 1);
  RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
  DrawTextA(hDeviceContext, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
  int32_t width = textRect.right - textRect.left;
  int32_t height = textRect.bottom - textRect.top;
  DeleteDC(hDeviceContext);
  hDeviceContext = NULL;
  // Create a bitmap of that size. Draw the symbol to the bitmap.
  self->bitmap = Arcadia_Visuals_Windows_Bitmap_create(thread, width, height);
  DrawTextA(self->bitmap->hDeviceContext, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_Visuals_Windows_TextureFont_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFontDispatch* self
  )
{ }

static void
Arcadia_Visuals_Windows_TextureFont_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFont* self
  )
{
  if (NULL != self->hFont) {
    DeleteObject(self->hFont);
    self->hFont = NULL;
  }
}

Arcadia_Visuals_Windows_TextureFont*
Arcadia_Visuals_Windows_TextureFont_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Windows_TextureFont);
}

void
Arcadia_Visuals_Windows_TextureFont_setCodePoint
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFont* self,
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
    Arcadia_UTF8Writer* utf8ByteBufferWriter = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, byteBuffer);
    Arcadia_UTF8Writer_writeCodePoints(thread, utf8ByteBufferWriter, &self->codePoint, 1);
    RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
    DrawTextA(hDeviceContext, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
    int32_t width = textRect.right - textRect.left;
    int32_t height = textRect.bottom - textRect.top;
    DeleteDC(hDeviceContext);
    hDeviceContext = NULL;
    // Create a bitmap of that size. Draw the symbol to the bitmap.
    self->bitmap = Arcadia_Visuals_Windows_Bitmap_create(thread, width, height);
    DrawTextA(self->bitmap->hDeviceContext, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  }
}

Arcadia_Imaging_PixelBuffer*
Arcadia_Visuals_Windows_TextureFont_getPixelBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFont* self
  )
{
  return Arcadia_Visuals_Windows_Bitmap_toPixelBuffer(thread, self->bitmap);
}
