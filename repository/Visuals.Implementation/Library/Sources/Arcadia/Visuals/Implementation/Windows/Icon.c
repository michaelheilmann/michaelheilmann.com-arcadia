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

#include "Arcadia/Visuals/Implementation/Windows/Icon.h"

static void
Arcadia_Visuals_Windows_Icon_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Windows_Icon_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Icon* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Windows_Icon_constructImpl,
  .destruct = &Arcadia_Visuals_Windows_Icon_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.Icon", Arcadia_Visuals_Windows_Icon,
                         u8"Arcadia.Visuals.Icon", Arcadia_Visuals_Icon,
                         &_typeOperations);

static void
Arcadia_Visuals_Windows_Icon_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Windows_Icon* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_Icon_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (6 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_Integer32Value width = Arcadia_ValueStack_getInteger32Value(thread, 6);
  Arcadia_Integer32Value height = Arcadia_ValueStack_getInteger32Value(thread, 5);
  Arcadia_Natural8Value red = Arcadia_ValueStack_getNatural8Value(thread, 4);
  Arcadia_Natural8Value green = Arcadia_ValueStack_getNatural8Value(thread, 3);
  Arcadia_Natural8Value blue = Arcadia_ValueStack_getNatural8Value(thread, 2);
  Arcadia_Natural8Value alpha = Arcadia_ValueStack_getNatural8Value(thread, 1);

  HDC hMemDC;
  BITMAPV5HEADER bi;
  HBITMAP hBitmap, hOldBitmap;
  void* lpBits;
  DWORD x, y;
  HCURSOR hIcon = NULL;

  ZeroMemory(&bi, sizeof(BITMAPV5HEADER));
  bi.bV5Size = sizeof(BITMAPV5HEADER);
  bi.bV5Width = width;
  bi.bV5Height = height;
  bi.bV5Planes = 1;
  bi.bV5BitCount = 32;
  bi.bV5Compression = BI_BITFIELDS;
  // The following mask specification specifies a supported 32 BPP alpha format for Windows XP.
  bi.bV5RedMask = 0x00FF0000;
  bi.bV5GreenMask = 0x0000FF00;
  bi.bV5BlueMask = 0x000000FF;
  bi.bV5AlphaMask = 0xFF000000;

  HDC hDC = GetDC(NULL);
  if (!hDC) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // Create the DIB section with an alpha channel.
  hBitmap = CreateDIBSection(hDC, (BITMAPINFO*)&bi, DIB_RGB_COLORS, (void**)&lpBits, NULL, (DWORD)0);
  if (!hBitmap) {
    ReleaseDC(NULL, hDC);
    hDC = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  hMemDC = CreateCompatibleDC(hDC);
  if (!hMemDC) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    ReleaseDC(NULL, hDC);
    hDC = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  ReleaseDC(NULL, hDC);
  hDC = NULL;

  // Draw something on the DIB section.
  hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
  if (HGDI_ERROR == hOldBitmap) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    DeleteDC(hMemDC);
    hMemDC = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  PatBlt(hMemDC, 0, 0, width, height, WHITENESS);
  if (HGDI_ERROR == SelectObject(hMemDC, hOldBitmap)) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    DeleteDC(hMemDC);
    hMemDC = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  DeleteDC(hMemDC);
  hMemDC = NULL;

   // Create an empty mask bitmap.
  HBITMAP hMonoBitmap = CreateBitmap(width, height, 1, 1, NULL);
  if (!hMonoBitmap) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // Set the alpha values for each pixel in the cursor so that
  // the complete cursor is semi-transparent.
  DWORD* lpdwPixel;
  lpdwPixel = (DWORD*)lpBits;
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      // Clear the alpha bits
      uint32_t pixel = 0x000000000;
      // Set the alpha bits to 0x9F (semi-transparent) or 0xFF000000 (opaque).
      pixel |= alpha << 24;
      pixel |= red << 16;
      pixel |= green << 8;
      pixel |= blue << 0;
      *lpdwPixel = pixel;
      lpdwPixel++;
    }
  }

  ICONINFO ii;
  ii.fIcon = FALSE;  // Change fIcon to TRUE to create an alpha icon
  ii.xHotspot = 0;
  ii.yHotspot = 0;
  ii.hbmMask = hMonoBitmap;
  ii.hbmColor = hBitmap;

  // Create the alpha cursor with the alpha DIB section.
  hIcon = CreateIconIndirect(&ii);

  DeleteObject(hMonoBitmap);
  hMonoBitmap = NULL;

  DeleteObject(hBitmap);
  hBitmap = NULL;

  if (!hIcon) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  _self->hIcon = hIcon;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_Visuals_Windows_Icon_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Icon* self
  )
{
  if (self->hIcon) {
    DestroyIcon(self->hIcon);
    self->hIcon = NULL;
  }
}

Arcadia_Visuals_Windows_Icon*
Arcadia_Visuals_Windows_Icon_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, width);
  Arcadia_ValueStack_pushInteger32Value(thread, height);
  Arcadia_ValueStack_pushNatural8Value(thread, red);
  Arcadia_ValueStack_pushNatural8Value(thread, green);
  Arcadia_ValueStack_pushNatural8Value(thread, blue);
  Arcadia_ValueStack_pushNatural8Value(thread, alpha);
  Arcadia_ValueStack_pushNatural8Value(thread, 6);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Windows_Icon);
}
