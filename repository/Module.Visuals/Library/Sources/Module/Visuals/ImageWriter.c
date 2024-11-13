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

// Last modified: 2024-09-19

#include "Module/Visuals/ImageWriter.h"

// WIC header
#define COBJMACROS (1)
#include <wincodec.h>
// WIC library
#pragma comment (lib, "Windowscodecs.lib")

#include "Module/Visuals/ImageWriterParameters.h"

static IWICImagingFactory* g_piFactory = NULL;
static HGLOBAL g_hMemory = NULL;
static IStream *g_piMemoryStream = NULL; // NULL if there is no memory stream
static IWICStream* g_piStream = NULL;
static IWICBitmapEncoder* g_piEncoder = NULL;

static IWICBitmapFrameEncode* g_piBitmapFrame = NULL;
static IPropertyBag2* g_pPropertyBag = NULL;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static HRESULT createMemoryStream(IStream** pStream, size_t initialSize) {
  g_hMemory = GlobalAlloc(GMEM_MOVEABLE, initialSize);
  if (!g_hMemory) {
    return E_OUTOFMEMORY;
  }
  LPVOID pImage = GlobalLock(g_hMemory);
  GlobalUnlock(g_hMemory);

  IStream* pStream1 = NULL;
  HRESULT hr = CreateStreamOnHGlobal(g_hMemory, FALSE, &pStream1);
  if (FAILED(hr)) {
    return hr;
  }
  *pStream = pStream1;
  return S_OK;
}

static wchar_t*
multiByteToWideChar
  (
    const char* source
  )
{
  int result;
  result = MultiByteToWideChar(CP_ACP, 0, source, -1, NULL, 0);
  if (!result) {
    return NULL;
  }
  wchar_t* target = malloc(sizeof(wchar_t) * result);
  if (!target) {
    return NULL;
  }
  result = MultiByteToWideChar(CP_ACP, 0, source, -1, target, result);
  if (!result) {
    free(target);
    target = NULL;
    return NULL;
  }
  return target;
}

static void
startupFactory
  (
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  hr = CoInitialize(NULL);
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  //
  hr = CoCreateInstance(&CLSID_WICImagingFactory,
    NULL,
    CLSCTX_INPROC_SERVER,
    &IID_IWICImagingFactory,
    (LPVOID*)&g_piFactory);
  if (FAILED(hr)) {
    CoUninitialize();
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  //
  hr = IWICImagingFactory_CreateStream(g_piFactory, &g_piStream);
  if (FAILED(hr)) {
    IWICImagingFactory_Release(g_piFactory);
    g_piFactory = NULL;
    CoUninitialize();
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
}

static void
shutdownFactory
  (
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  IWICStream_Release(g_piStream);
  g_piStream = NULL;
  //
  IWICImagingFactory_Release(g_piFactory);
  g_piFactory = NULL;
  //
  CoUninitialize();
}

static void
startup1
  (
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  if (ImageWriterParameters_hasPath(parameters)) {
    R_ByteBuffer* b = R_ByteBuffer_create();
    R_ByteBuffer_append_pn(b, ImageWriterParameters_getPath(parameters)->p, ImageWriterParameters_getPath(parameters)->numberOfBytes);
    R_ByteBuffer_append_pn(b, "", 1);
    wchar_t* targetPathW = multiByteToWideChar(b->p);
    if (!targetPathW) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    hr = IWICStream_InitializeFromFilename(g_piStream, targetPathW, GENERIC_WRITE);
    free(targetPathW);
    if (FAILED(hr)) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
  } else {
    hr = createMemoryStream(&g_piMemoryStream, 8);
    if (FAILED(hr)) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    hr = IWICStream_InitializeFromIStream(g_piStream, g_piMemoryStream);
    if (FAILED(hr)) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
  }
}

static void
shutdown1
  (
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  if (g_piMemoryStream) {
    IStream_Release(g_piMemoryStream);
    g_piMemoryStream = NULL;
  }
  if (g_hMemory) {
    GlobalFree(g_hMemory);
    g_hMemory = NULL;
  }
}

static void
startupEncoder
  (
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  GUID const* pFormat = NULL;
  switch (ImageWriterParameters_getFormat(parameters)) {
    case ImageWriterFormat_Tiff:
      pFormat = &GUID_ContainerFormatTiff;
      break;
    case ImageWriterFormat_Png:
      pFormat = &GUID_ContainerFormatPng;
      break;
    case ImageWriterFormat_Bmp:
      pFormat = &GUID_ContainerFormatBmp;
      break;
    default:
    case ImageWriterFormat_Undefined: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
  }
  hr = IWICImagingFactory_CreateEncoder(g_piFactory, pFormat, NULL, &g_piEncoder);
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  hr = IWICBitmapEncoder_Initialize(g_piEncoder, (IStream*)g_piStream, WICBitmapEncoderNoCache);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(g_piEncoder);
    g_piEncoder = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  //
  hr = IWICBitmapEncoder_CreateNewFrame(g_piEncoder, &g_piBitmapFrame, &g_pPropertyBag);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(g_piEncoder);
    g_piEncoder = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  switch (ImageWriterParameters_getFormat(parameters)) {
    // https://learn.microsoft.com/en-us/windows/win32/wic/tiff-format-overview
    case ImageWriterFormat_Tiff: {
      PROPBAG2 option = { 0 };
      option.pstrName = L"TiffCompressionMethod";
      VARIANT varValue;
      VariantInit(&varValue);
      varValue.vt = VT_UI1;
      varValue.bVal = WICTiffCompressionZIP;
      hr = IPropertyBag2_Write(g_pPropertyBag, 1, &option, &varValue);
      if (FAILED(hr)) {
        IPropertyBag2_Release(g_pPropertyBag);
        g_pPropertyBag = NULL;
        IWICBitmapFrameEncode_Release(g_piBitmapFrame);
        g_piBitmapFrame = NULL;
        IWICBitmapEncoder_Release(g_piEncoder);
        g_piEncoder = NULL;
        R_setStatus(R_Status_EnvironmentFailed);
        R_jump();
      }
    } break;
    // https://learn.microsoft.com/en-us/windows/win32/wic/png-format-overview
    case ImageWriterFormat_Png: {
      /*Nothing to do here.*/
    } break;
    // https://learn.microsoft.com/en-us/windows/win32/wic/bmp-format-overview
    case ImageWriterFormat_Bmp: {
      PROPBAG2 option = { 0 };
      option.pstrName = L"EnableV5Header32bppBGRA";
      VARIANT varValue;
      VariantInit(&varValue);
      varValue.vt = VT_BOOL;
      varValue.boolVal = VARIANT_TRUE;
      hr = IPropertyBag2_Write(g_pPropertyBag, 1, &option, &varValue);
      if (FAILED(hr)) {
        IPropertyBag2_Release(g_pPropertyBag);
        g_pPropertyBag = NULL;
        IWICBitmapFrameEncode_Release(g_piBitmapFrame);
        g_piBitmapFrame = NULL;
        IWICBitmapEncoder_Release(g_piEncoder);
        g_piEncoder = NULL;
        R_setStatus(R_Status_EnvironmentFailed);
        R_jump();
      }
    } break;
    case ImageWriterFormat_Undefined:
    default: {
      IPropertyBag2_Release(g_pPropertyBag);
      g_pPropertyBag = NULL;
      IWICBitmapFrameEncode_Release(g_piBitmapFrame);
      g_piBitmapFrame = NULL;
      IWICBitmapEncoder_Release(g_piEncoder);
      g_piEncoder = NULL;
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
  };
  hr = IWICBitmapFrameEncode_Initialize(g_piBitmapFrame, g_pPropertyBag);
  if (FAILED(hr)) {
    IPropertyBag2_Release(g_pPropertyBag);
    g_pPropertyBag = NULL;
    IWICBitmapFrameEncode_Release(g_piBitmapFrame);
    g_piBitmapFrame = NULL;
    IWICBitmapEncoder_Release(g_piEncoder);
    g_piEncoder = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
}

static void
shutdownEncoder
  (
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  IPropertyBag2_Release(g_pPropertyBag);
  g_pPropertyBag = NULL;
  IWICBitmapFrameEncode_Release(g_piBitmapFrame);
  g_piBitmapFrame = NULL;
  IWICBitmapEncoder_Release(g_piEncoder);
  g_piEncoder = NULL;
}

static void
startup3
  (
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //

  size_t sourceWidth = PixelBuffer_getNumberOfColumns(sourcePixelBuffer);
  size_t sourceHeight = PixelBuffer_getNumberOfRows(sourcePixelBuffer);
  hr = IWICBitmapFrameEncode_SetSize(g_piBitmapFrame, (UINT)sourceWidth, (UINT)sourceHeight);
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  //
  WICPixelFormatGUID formatGUID = GUID_WICPixelFormatUndefined;
  switch (sourcePixelBuffer->pixelFormat) {
    case PixelFormat_Rn8Gn8Bn8: {
      formatGUID = GUID_WICPixelFormat24bppBGR;
    } break;
    case PixelFormat_An8Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(sourcePixelBuffer);
      PixelBuffer_setPixelFormat(pixelBuffer, PixelFormat_Bn8Gn8Rn8An8);
      sourcePixelBuffer = pixelBuffer;
      formatGUID = GUID_WICPixelFormat32bppBGRA;
    } break;
    default: {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    } break;
  };
  hr = IWICBitmapFrameEncode_SetPixelFormat(g_piBitmapFrame, &formatGUID);
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  size_t sourceLineStride = PixelBuffer_getLineStride(sourcePixelBuffer);
  size_t sourceSizeInPixels = sourceLineStride * sourceHeight;
  hr = IWICBitmapFrameEncode_WritePixels(g_piBitmapFrame, (UINT)sourceHeight, (UINT)sourceLineStride, (UINT)sourceSizeInPixels, (void*)sourcePixelBuffer->bytes);
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  hr = IWICBitmapFrameEncode_Commit(g_piBitmapFrame);
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  hr = IWICBitmapEncoder_Commit(g_piEncoder);
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  if (ImageWriterParameters_hasByteBuffer(parameters)) {
    STATSTG statstg;
    hr = IStream_Stat(g_piStream, &statstg, STATFLAG_NONAME);
    if (FAILED(hr)) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    if (statstg.cbSize.QuadPart > SIZE_MAX) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    size_t n = (size_t)statstg.cbSize.QuadPart;
    LPVOID p = GlobalLock(g_hMemory);
    R_JumpTarget jumpTarget;
    R_pushJumpTarget(&jumpTarget);
    if (R_JumpTarget_save(&jumpTarget)) {
      R_ByteBuffer_append_pn(ImageWriterParameters_getByteBuffer(parameters), p, n);
      GlobalUnlock(g_hMemory);
      R_popJumpTarget();
    } else {
      GlobalUnlock(g_hMemory);
      R_popJumpTarget();
      R_jump();
    }
  }
}

static void
shutdown3
  (
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{ }

typedef struct Module {
  void (*startup)(PixelBuffer* sourcePixelBuffer, ImageWriterParameters* parameters);
  void (*shutdown)(PixelBuffer* sourcePixelBuffer, ImageWriterParameters* parameters);
} Module;

static write(PixelBuffer* sourcePixelBuffer, ImageWriterParameters* parameters) {
  const Module modules[] = {
   { &startupFactory, &shutdownFactory },
   { &startup1, &shutdown1 },
   { &startupEncoder, &shutdownEncoder },
   { &startup3, &shutdown3 },
  };
  const size_t numberOfModules = sizeof(modules) / sizeof(Module);
  size_t currentModule = 0;

  while (currentModule < numberOfModules) {
    R_JumpTarget jumpTarget;
    R_pushJumpTarget(&jumpTarget);
    if (R_JumpTarget_save(&jumpTarget)) {
      modules[currentModule++].startup(sourcePixelBuffer, parameters);
      R_popJumpTarget();
    } else {
      R_popJumpTarget();
      while (currentModule > 0) {
        modules[--currentModule].shutdown(sourcePixelBuffer, parameters);
      }
      R_jump();
    }
  }

  while (currentModule > 0) {
    modules[--currentModule].shutdown(sourcePixelBuffer, parameters);
  }
}

void writePngToPath(PixelBuffer* sourcePixelBuffer, R_String* targetPath) {
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createFile(targetPath, ImageWriterFormat_Png);
  write(sourcePixelBuffer, imageWriterParameters);
}

void writePngToByteBuffer(PixelBuffer* sourcePixelBuffer, R_ByteBuffer* targetByteBuffer) {
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createByteBuffer(targetByteBuffer, ImageWriterFormat_Png);
  write(sourcePixelBuffer, imageWriterParameters);
}

void writeBmpToPath(PixelBuffer* sourcePixelBuffer, R_String* targetPath) {
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createFile(targetPath, ImageWriterFormat_Bmp);
  write(sourcePixelBuffer, imageWriterParameters);
}

void writeBmpToByteBuffer(PixelBuffer* sourcePixelBuffer, R_ByteBuffer* targetByteBuffer) {
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createByteBuffer(targetByteBuffer, ImageWriterFormat_Bmp);
  write(sourcePixelBuffer, imageWriterParameters);
}

typedef struct ICONDIR {
  uint16_t reserved1;
  uint16_t type;
  uint16_t numberOfImages;
} ICONDIR;

typedef struct ICONDIRENTRY {
  uint8_t width;
  uint8_t height;
  uint8_t numberOfColors;
  uint8_t reserved1;
  uint16_t numberOfColorPlanes;
  uint16_t numberOfBitsPerPixel;
  uint32_t imageSize;
  uint32_t offset;
} ICONDIRENTRY;

void writeIconToPath(R_List* sourcePixelBuffers, R_String* targetPath) {
  R_ByteBuffer* targetByteBuffer = R_ByteBuffer_create();
  writeIconToByteBuffer(sourcePixelBuffers, targetByteBuffer);
  R_FileSystem_setFileContents(R_FileSystem_create(), R_FilePath_parseUnixFilePath(targetPath->p, targetPath->numberOfBytes), targetByteBuffer);
}

void writeIconToByteBuffer(R_List* sourcePixelBuffers, R_ByteBuffer* targetByteBuffer) {
  ICONDIR iconDir = {
    .reserved1 = 0,
    .type = 1,
    .numberOfImages = R_List_getSize(sourcePixelBuffers)
  };
  R_ByteBuffer_append_pn(targetByteBuffer, &iconDir, sizeof(ICONDIR));

  R_ByteBuffer* temporary = R_ByteBuffer_create();
  for (R_SizeValue i = 0, offset = 0, n = R_List_getSize(sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)R_List_getObjectReferenceValueAt(sourcePixelBuffers, i);
    R_ByteBuffer_clear(temporary);
    writePngToByteBuffer(pixelBuffer, temporary);
    if (PixelFormat_An8Rn8Gn8Bn8 != PixelBuffer_getPixelFormat(pixelBuffer)) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    size_t width = PixelBuffer_getNumberOfColumns(pixelBuffer),
           height = PixelBuffer_getNumberOfRows(pixelBuffer);
    if (width > 256) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    if (height > 256) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    if (width == 256) {
      width = 0;
    }
    if (height == 256) {
      height = 256;
    }

    ICONDIRENTRY iconDirEntry = { .width = width,
                                  .height = height,
                                  .numberOfColors = 0,
                                  .reserved1 = 0,
                                  .numberOfColorPlanes = 1,
                                  .numberOfBitsPerPixel = 32,
                                  .imageSize = R_ByteBuffer_getSize(temporary),
                                  .offset = sizeof(ICONDIR) + R_List_getSize(sourcePixelBuffers) * sizeof(ICONDIRENTRY) + offset };
    R_ByteBuffer_append_pn(targetByteBuffer, &iconDirEntry, sizeof(ICONDIRENTRY));
    offset += R_ByteBuffer_getSize(temporary);
  }
  for (R_SizeValue i = 0, offset = 0, n = R_List_getSize(sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)R_List_getObjectReferenceValueAt(sourcePixelBuffers, i);
    R_ByteBuffer_clear(temporary);
    writePngToByteBuffer(pixelBuffer, temporary);
    R_ByteBuffer_append_pn(targetByteBuffer, temporary->p, temporary->sz);
    offset += R_ByteBuffer_getSize(temporary);
  }
}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
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

Rex_defineObjectType("NativeWindowsImageWriter", NativeWindowsImageWriter, "R.Object", R_Object, &_typeOperations);

void
NativeWindowsImageWriter_construct
  (
    NativeWindowsImageWriter* self
  )
{
  R_Type* _type = _NativeWindowsImageWriter_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType((R_Object*)self, _type);
}
