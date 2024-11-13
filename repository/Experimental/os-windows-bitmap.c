#include "os-windows-bitmap.h"

// malloc, free, realloc
#include <malloc.h>

// fprintf, stderr, stdout
#include <stdio.h>

// EXIT_SUCCESS, EXIT_FAILURE
#include <stdlib.h>

// uint32_t
#include <stdint.h>

// bool, true, false
#include <stdbool.h>

#define COBJMACROS

#include <Objbase.h>
#include <wincodec.h>
#include <Windows.h>
#include <Winerror.h>

#pragma comment(lib, "Windowscodecs.lib")

int write_bitmap(HBITMAP hBitmap, const wchar_t* pPathName) {

  HRESULT hr = S_OK;

  // (1) Retrieve properties from the source HBITMAP.
  BITMAP bm_info = { 0 };
  if (!GetObject(hBitmap, sizeof(bm_info), &bm_info)) {
    return EXIT_FAILURE;
  }

  // (2) Create an IWICImagingFactory instance.
  IWICImagingFactory* piFactory = NULL;
  hr = CoCreateInstance(&CLSID_WICImagingFactory,
                        NULL,
                        CLSCTX_INPROC_SERVER,
                        &IID_IWICImagingFactory,
                        &piFactory);
  if (FAILED(hr)) {
    IWICImagingFactory_Release(piFactory);
    piFactory = NULL;
    return EXIT_FAILURE;
  }

  // (3) Create an IWICBitmap instance from the HBITMAP.
  IWICBitmap* piBitmap = NULL;
  hr = IWICImagingFactory_CreateBitmapFromHBITMAP(piFactory,
                                                  piBitmap,
                                                  NULL,
                                                  WICBitmapIgnoreAlpha,
                                                  &piBitmap);
  if (FAILED(hr)) {
    IWICImagingFactory_Release(piFactory);
    piFactory = NULL;
    return EXIT_FAILURE;
  }

  // (4) Create an IWICStream instance, and attach it to a filename.
  IWICStream* piStream = NULL;
  hr = IWICImagingFactory_CreateStream(piFactory, &piStream);
  if (FAILED(hr)) {
    IWICBitmap_Release(piBitmap);
    piBitmap = NULL;
    IWICImagingFactory_Release(piFactory);
    piFactory = NULL;
    return EXIT_FAILURE;
  }
  hr = IWICStream_InitializeFromFilename(piStream, pPathName, GENERIC_WRITE);
  if (FAILED(hr)) {
    IWICStream_Release(piStream);
    piStream = NULL;
    IWICBitmap_Release(piBitmap);
    piBitmap = NULL;
    IWICImagingFactory_Release(piFactory);
    piFactory = NULL;
    return EXIT_FAILURE;
  }
  
  // (5) Create an IWICBitmapEncoder instance, and associate it with the stream.
  IWICBitmapEncoder* piEncoder = NULL;
  hr = IWICImagingFactory_CreateEncoder(piFactory, &GUID_ContainerFormatBmp, NULL, &piEncoder);
  if (FAILED(hr)) {
    IWICStream_Release(piStream);
    piStream = NULL;
    IWICBitmap_Release(piBitmap);
    piBitmap = NULL;
    IWICImagingFactory_Release(piFactory);
    piFactory = NULL;
    return EXIT_FAILURE;
  }
  hr = IWICBitmapEncoder_Initialize(piEncoder, (IStream*)piStream, WICBitmapEncoderNoCache);
  if (FAILED(hr)) {
    IWICStream_Release(piStream);
    piStream = NULL;
    IWICBitmap_Release(piBitmap);
    piBitmap = NULL;
    IWICImagingFactory_Release(piFactory);
    piFactory = NULL;
    return EXIT_FAILURE;
  }

  // (6) Create an IWICBitmapFrameEncode instance, and initialize it in compliance with the source HBITMAP.
  IWICBitmapFrameEncode* piFrame = NULL;
  hr = IWICBitmapEncoder_CreateNewFrame(piEncoder, &piFrame, NULL);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(piEncoder);
    piEncoder = NULL;
    IWICStream_Release(piStream);
    piStream = NULL;
    IWICBitmap_Release(piBitmap);
    piBitmap = NULL;
    IWICImagingFactory_Release(piFactory);
    piFactory = NULL;
    return EXIT_FAILURE;
  }
  hr = IWICBitmapFrameEncode_Initialize(piFrame, NULL);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(piEncoder);
    piEncoder = NULL;
    IWICStream_Release(piStream);
    piStream = NULL;
    IWICBitmap_Release(piBitmap);
    piBitmap = NULL;
    IWICImagingFactory_Release(piFactory);
    piFactory = NULL;
    return EXIT_FAILURE;
  }
  if (SUCCEEDED(hr))
    hr = IWICBitmapFrameEncode_SetSize(frame, bm_info.bmWidth, bm_info.bmHeight);
  if (SUCCEEDED(hr)) {
    GUID pixel_format = GUID_WICPixelFormat24bppBGR;
    hr = IWICBitmapFrameEncode_SetPixelFormat(frame, &pixel_format);
  }

  // (7) Write bitmap data to the frame.
  if (SUCCEEDED(hr))
    hr = IWICBitmapFrameEncode_WriteSource(frame, (IWICBitmapSource*)wic_bitmap,
      NULL);

// (8) Commit frame and data to stream.
  if (SUCCEEDED(hr))
    hr = IWICBitmapFrameEncode_Commit(frame);
  if (SUCCEEDED(hr))
    hr = IWICBitmapEncoder_Commit(encoder);

// Cleanup
  if (frame)
    IWICBitmapFrameEncode_Release(frame);
  if (encoder)
    IWICBitmapEncoder_Release(encoder);
  if (stream)
    IWICStream_Release(stream);
  if (wic_bitmap)
    IWICBitmap_Release(wic_bitmap);
  if (factory)
    IWICImagingFactory_Release(factory);

  return hr;
}

static int f(HBITMAP* result, int w, int h) {
  // Create display device context.
  HDC hDisplayDC = CreateDC("DISPLAY", NULL, NULL, NULL);
  if (!hDisplayDC) {
    return EXIT_FAILURE;
  }

  // Create memory device context.
  HDC hMemoryDC = CreateCompatibleDC(hDisplayDC);
  if (!hMemoryDC) {
    DeleteDC(hDisplayDC);
    hDisplayDC = NULL;
    return EXIT_FAILURE;
  }

  // Create DIB section.
  BITMAPINFO bitmapInfo;
  bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bitmapInfo.bmiHeader.biWidth = w;
  bitmapInfo.bmiHeader.biHeight = h;
  bitmapInfo.bmiHeader.biPlanes = 1;
  bitmapInfo.bmiHeader.biBitCount = 24;
  bitmapInfo.bmiHeader.biCompression = BI_RGB;
  bitmapInfo.bmiHeader.biSizeImage = (w * h) * 3;
  VOID *pvBits = NULL;
  HBITMAP hBitmap = CreateDIBSection(hMemoryDC, &bitmapInfo, DIB_RGB_COLORS, &pvBits, NULL, 0);
  if (!hBitmap) {
    DeleteDC(hMemoryDC);
    hMemoryDC = NULL;
    DeleteDC(hDisplayDC);
    hDisplayDC = NULL;
    return EXIT_FAILURE;
  }

  HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
  if (!hBrush) {
    DeleteObject(hBitmap);
    hBitmap = NULL;
    DeleteDC(hMemoryDC);
    hMemoryDC = NULL;
    DeleteDC(hDisplayDC);
    hDisplayDC = NULL;
    return EXIT_FAILURE;
  }

  SelectObject(hMemoryDC, hBrush);
  Rectangle(hMemoryDC, 0, 0, w, h);

  DeleteObject(hBrush);
  hBrush = NULL;

  DeleteDC(hMemoryDC);
  hMemoryDC = NULL;
  DeleteDC(hDisplayDC);
  hDisplayDC = NULL;

  *result = hBitmap;

  return EXIT_SUCCESS;
}

int bitmap_create(struct bitmap_t** result, int width, int height) {
  struct bitmap_t* self = NULL;
  if (os_allocate(&self, sizeof(struct bitmap_t))) {
    return EXIT_FAILURE;
  }
  self->width = width;
  self->height = height;
  self->pixels = NULL;
  if (os_allocate(&self->pixels, sizeof(uint32_t) * width * height)) {
    os_deallocate(self); 
    self = NULL;
    return EXIT_FAILURE;
  }
  self->reference_count = 1;
  *result = self;
  return EXIT_SUCCESS;
}

int bitmap_ref(struct bitmap_t* self) {
  if (self->reference_count < REFERENCE_COUNT_MAXIMUM) {
    self->reference_count++;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

int bitmap_unref(struct bitmap_t* self) {
  if (self->reference_count <= 0) {
    return EXIT_FAILURE;
  }
  if (0 == --self->reference_count) {
    os_deallocate(self->pixels);
    self->pixels = NULL;
    os_deallocate(self);
    self = NULL;
  }
  return EXIT_SUCCESS;
}

