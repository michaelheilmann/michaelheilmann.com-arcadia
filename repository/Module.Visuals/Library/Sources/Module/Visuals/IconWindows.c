#include "Module/Visuals/IconWindows.h"

// EXIT_FAILURE, EXIT_SUCCESS
#include <stdlib.h>

// fprintf, stderr
#include <stdio.h>

// malloc, free, realloc
#include <malloc.h>

static void
IconWindows_destruct
  (
    IconWindows* self
  );

Rex_defineObjectType("IconWindows", IconWindows, "R.Object", R_Object, NULL, &IconWindows_destruct)

static void
IconWindows_destruct
  (
    IconWindows* self
  )
{
  if (self->hIcon) {
    DestroyIcon(self->hIcon);
    self->hIcon = NULL;
  }
}

void
IconWindows_construct
  (
    IconWindows* self,
    int width,
    int height
  )
{
  R_Type* _type = _IconWindows_getType();
  R_Object_construct((R_Object*)self);

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
    ReleaseDC(NULL, hDC);
    hDC = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  // Create the DIB section with an alpha channel.
  hBitmap = CreateDIBSection(hDC, (BITMAPINFO*)&bi, DIB_RGB_COLORS, (void**)&lpBits, NULL, (DWORD)0);
  if (!hBitmap) {
    ReleaseDC(NULL, hDC);
    hDC = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  hMemDC = CreateCompatibleDC(hDC);
  if (!hMemDC) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    ReleaseDC(NULL, hDC);
    hDC = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
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
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  PatBlt(hMemDC, 0, 0, width, height, WHITENESS);
  if (HGDI_ERROR == SelectObject(hMemDC, hOldBitmap)) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    DeleteDC(hMemDC);
    hMemDC = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  DeleteDC(hMemDC);
  hMemDC = NULL;

   // Create an empty mask bitmap.
  HBITMAP hMonoBitmap = CreateBitmap(width, height, 1, 1, NULL);
  if (!hMonoBitmap) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  // Set the alpha values for each pixel in the cursor so that
  // the complete cursor is semi-transparent.
  DWORD* lpdwPixel;
  lpdwPixel = (DWORD*)lpBits;
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
      // Clear the alpha bits
      *lpdwPixel &= 0x00FFFFFF;
      // Set the alpha bits to 0x9F (semi-transparent) or 0xFF000000 (opaque).
      *lpdwPixel |= /*0x9F000000*/0xFF000000;
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
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  self->hIcon = hIcon;
  R_Object_setType((R_Object*)self, _type);
}
