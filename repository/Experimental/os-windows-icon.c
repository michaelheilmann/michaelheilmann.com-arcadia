<<<<<<<< HEAD:repository/Module.Visuals/Library/Sources/Module/Visuals/NativeWindowsIcon.c
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

// Last modified: 2024-11-13

#include "Module/Visuals/NativeWindowsIcon.h"
========
#include "os-windows-icon.h"
>>>>>>>> 53828c6 (Update Week 2 November 2024):repository/Experimental/os-windows-icon.c

// EXIT_FAILURE, EXIT_SUCCESS
#include <stdlib.h>

// fprintf, stderr
#include <stdio.h>

// malloc, free, realloc
#include <malloc.h>

<<<<<<<< HEAD:repository/Module.Visuals/Library/Sources/Module/Visuals/NativeWindowsIcon.c
static void
NativeWindowsIcon_destruct
  (
    NativeWindowsIcon* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = &NativeWindowsIcon_destruct,
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

Rex_defineObjectType("NativeWindowsIcon", NativeWindowsIcon, "R.Object", R_Object, &_typeOperations);

static void
NativeWindowsIcon_destruct
  (
    NativeWindowsIcon* self
  )
{
  if (self->hIcon) {
    DestroyIcon(self->hIcon);
    self->hIcon = NULL;
  }
}

void
NativeWindowsIcon_construct
  (
    NativeWindowsIcon* self,
    R_Integer32Value width,
    R_Integer32Value height,
    R_Natural8Value red,
    R_Natural8Value green,
    R_Natural8Value blue
  )
{
  R_Type* _type = _NativeWindowsIcon_getType();
  R_Object_construct((R_Object*)self);

========
int window_icon_create(struct window_icon_t** result, int width, int height) {
  struct window_icon_t* self = malloc(sizeof(struct window_icon_t));
  if (!self) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct window_icon_t));
    return EXIT_FAILURE;
  }
>>>>>>>> 53828c6 (Update Week 2 November 2024):repository/Experimental/os-windows-icon.c
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
  // The following mask specification specifies a supported 32 BPP
  // alpha format for Windows XP.
  bi.bV5RedMask = 0x00FF0000;
  bi.bV5GreenMask = 0x0000FF00;
  bi.bV5BlueMask = 0x000000FF;
  bi.bV5AlphaMask = 0xFF000000;

  HDC hDC;
  hDC = GetDC(NULL);

  // Create the DIB section with an alpha channel.
  hBitmap = CreateDIBSection(hDC, (BITMAPINFO*)&bi, DIB_RGB_COLORS, (void**)&lpBits, NULL, (DWORD)0);
  if (!hBitmap) {
    ReleaseDC(NULL, hDC);
    hDC = NULL;
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }

  hMemDC = CreateCompatibleDC(hDC);
  if (!hMemDC) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    ReleaseDC(NULL, hDC);
    hDC = NULL;
    free(self);
    self = NULL;
    return EXIT_FAILURE;
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
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  PatBlt(hMemDC, 0, 0, width, height, WHITENESS);
  if (HGDI_ERROR == SelectObject(hMemDC, hOldBitmap)) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    DeleteDC(hMemDC);
    hMemDC = NULL;
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }

  DeleteDC(hMemDC);
  hMemDC = NULL;

   // Create an empty mask bitmap.
  HBITMAP hMonoBitmap = CreateBitmap(width, height, 1, 1, NULL);
  if (!hMonoBitmap) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    free(self);
    self = NULL;
    return EXIT_FAILURE;
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
      pixel |= /*0x9F000000*/0xFF000000;
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
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }

  self->hIcon = hIcon;
  self->reference_count = 1;
  *result = self;
  return EXIT_SUCCESS;
}

int window_icon_ref(struct window_icon_t* self) {
  if (!self || self->reference_count == INT32_MAX) {
    return EXIT_FAILURE;
  }
  self->reference_count++;
  return EXIT_SUCCESS;
}

int window_icon_unref(struct window_icon_t* self) {
  if (!self || self->reference_count == 0) {
    return EXIT_FAILURE;
  }
  self->reference_count--;
  if (self->reference_count == 0) {
    DestroyIcon(self->hIcon);
    self->hIcon = NULL;
  }
  return EXIT_SUCCESS;
}

NativeWindowsIcon*
NativeWindowsIcon_create
  (
    R_Integer32Value width,
    R_Integer32Value height,
    R_Natural8Value red,
    R_Natural8Value green,  
    R_Natural8Value blue
  )
{
  NativeWindowsIcon* self = R_allocateObject(_NativeWindowsIcon_getType());
  NativeWindowsIcon_construct(self, width, height, red, green, blue);
  return self;
}
