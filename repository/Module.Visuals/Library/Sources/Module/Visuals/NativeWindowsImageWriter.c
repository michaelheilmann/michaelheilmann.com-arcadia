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

// Last modified: 2024-09-19

#include "Module/Visuals/NativeWindowsImageWriter.h"

// WIC header
#define COBJMACROS (1)
#include <wincodec.h>
// WIC library
#pragma comment (lib, "Windowscodecs.lib")

#include "Module/Visuals/ImageWriterParameters.h"

static void
NativeWindowsImageWriter_writePngToPathImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
NativeWindowsImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static void
NativeWindowsImageWriter_writeBmpToPathImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
NativeWindowsImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

// The "Windows Imaging Component" ("WIC") does not provide an encoder for "ico" files.
// See https://learn.microsoft.com/en-us/windows/win32/wic/ico-format-overview?redirectedfrom=MSDN for more information.
//
// The "ico" file format is described on Wikipedia.
// See https://en.wikipedia.org/wiki/ICO_(file_format) for more information.
//
// From the description of the file format:
// - The width and height of any image in an "ico" files may not exceed 256.
// - all source pixel buffers must be of format PixelBuffer_An8Rn8Gn8Bn8.
static void
NativeWindowsImageWriter_writeIcoToPathImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
NativeWindowsImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static IWICImagingFactory* g_piFactory = NULL;
static HGLOBAL g_hMemory = NULL;
static IStream *g_piMemoryStream = NULL; // NULL if there is no memory stream
static IWICStream* g_piStream = NULL;
static IWICBitmapEncoder* g_piEncoder = NULL;

static IWICBitmapFrameEncode* g_piBitmapFrame = NULL;
static IPropertyBag2* g_pPropertyBag = NULL;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static HRESULT
createMemoryStream
  (
    IStream** pStream,
    size_t initialSize
  )
{
  g_hMemory = GlobalAlloc(GMEM_MOVEABLE, initialSize);
  if (!g_hMemory) {
    return E_OUTOFMEMORY;
  }
  IStream* pStream1 = NULL;
  HRESULT hr = CreateStreamOnHGlobal(g_hMemory, FALSE, &pStream1);
  if (FAILED(hr)) {
    GlobalFree(g_hMemory);
    g_hMemory = NULL;
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
    Arcadia_Thread* thread,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  hr = CoInitialize(NULL);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  //
  hr = CoCreateInstance(&CLSID_WICImagingFactory,
                        NULL,
                        CLSCTX_INPROC_SERVER,
                        &IID_IWICImagingFactory,
                        (LPVOID*)&g_piFactory);
  if (FAILED(hr)) {
    CoUninitialize();
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  //
  hr = IWICImagingFactory_CreateStream(g_piFactory, &g_piStream);
  if (FAILED(hr)) {
    IWICImagingFactory_Release(g_piFactory);
    g_piFactory = NULL;
    CoUninitialize();
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
shutdownFactory
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  if (ImageWriterParameters_hasPath(thread, parameters)) {
    Arcadia_ByteBuffer* b = Arcadia_ByteBuffer_create(thread);
    Arcadia_ByteBuffer_append_pn(thread, b, Arcadia_String_getBytes(thread, ImageWriterParameters_getPath(thread, parameters)), Arcadia_String_getNumberOfBytes(thread, ImageWriterParameters_getPath(thread, parameters)));
    Arcadia_ByteBuffer_append_pn(thread, b, u8"", 1);
    wchar_t* targetPathW = multiByteToWideChar(b->p);
    if (!targetPathW) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    hr = IWICStream_InitializeFromFilename(g_piStream, targetPathW, GENERIC_WRITE);
    free(targetPathW);
    if (FAILED(hr)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  } else {
    hr = createMemoryStream(&g_piMemoryStream, 8);
    if (FAILED(hr)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    hr = IWICStream_InitializeFromIStream(g_piStream, g_piMemoryStream);
    if (FAILED(hr)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
shutdown1
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  GUID const* pFormat = NULL;
  switch (ImageWriterParameters_getFormat(thread, parameters)) {
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
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
  hr = IWICImagingFactory_CreateEncoder(g_piFactory, pFormat, NULL, &g_piEncoder);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  hr = IWICBitmapEncoder_Initialize(g_piEncoder, (IStream*)g_piStream, WICBitmapEncoderNoCache);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(g_piEncoder);
    g_piEncoder = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  //
  hr = IWICBitmapEncoder_CreateNewFrame(g_piEncoder, &g_piBitmapFrame, &g_pPropertyBag);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(g_piEncoder);
    g_piEncoder = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  switch (ImageWriterParameters_getFormat(thread, parameters)) {
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
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
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
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
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
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
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
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
shutdownEncoder
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  size_t sourceWidth = PixelBuffer_getNumberOfColumns(thread, sourcePixelBuffer);
  size_t sourceHeight = PixelBuffer_getNumberOfRows(thread, sourcePixelBuffer);
  hr = IWICBitmapFrameEncode_SetSize(g_piBitmapFrame, (UINT)sourceWidth, (UINT)sourceHeight);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  //
  WICPixelFormatGUID formatGUID = GUID_WICPixelFormatUndefined;
  switch (sourcePixelBuffer->pixelFormat) {
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
      formatGUID = GUID_WICPixelFormat24bppBGR;
    } break;
    case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(thread, sourcePixelBuffer);
      PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8);
      sourcePixelBuffer = pixelBuffer;
      formatGUID = GUID_WICPixelFormat32bppBGRA;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };
  hr = IWICBitmapFrameEncode_SetPixelFormat(g_piBitmapFrame, &formatGUID);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  size_t sourceLineStride = PixelBuffer_getLineStride(thread, sourcePixelBuffer);
  size_t sourceSizeInPixels = sourceLineStride * sourceHeight;
  hr = IWICBitmapFrameEncode_WritePixels(g_piBitmapFrame, (UINT)sourceHeight, (UINT)sourceLineStride, (UINT)sourceSizeInPixels, (void*)sourcePixelBuffer->bytes);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  hr = IWICBitmapFrameEncode_Commit(g_piBitmapFrame);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  hr = IWICBitmapEncoder_Commit(g_piEncoder);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (ImageWriterParameters_hasByteBuffer(thread, parameters)) {
    STATSTG statstg;
    hr = IStream_Stat(g_piStream, &statstg, STATFLAG_NONAME);
    if (FAILED(hr)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (statstg.cbSize.QuadPart > SIZE_MAX) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    size_t n = (size_t)statstg.cbSize.QuadPart;
    LPVOID p = GlobalLock(g_hMemory);
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_ByteBuffer_append_pn(thread, ImageWriterParameters_getByteBuffer(thread, parameters), p, n);
      GlobalUnlock(g_hMemory);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      GlobalUnlock(g_hMemory);
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
shutdown3
  (
    Arcadia_Thread* thread,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{ }

typedef struct Module {
  void (*startup)(Arcadia_Thread* thread, PixelBuffer* sourcePixelBuffer, ImageWriterParameters* parameters);
  void (*shutdown)(Arcadia_Thread* thread, PixelBuffer* sourcePixelBuffer, ImageWriterParameters* parameters);
} Module;

static
write
  (
    Arcadia_Thread* thread,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  const Module modules[] = {
   { &startupFactory, &shutdownFactory },
   { &startup1, &shutdown1 },
   { &startupEncoder, &shutdownEncoder },
   { &startup3, &shutdown3 },
  };
  const size_t numberOfModules = sizeof(modules) / sizeof(Module);
  size_t currentModule = 0;

  while (currentModule < numberOfModules) {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      modules[currentModule++].startup(thread, sourcePixelBuffer, parameters);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      while (currentModule > 0) {
        modules[--currentModule].shutdown(thread, sourcePixelBuffer, parameters);
      }
      Arcadia_Thread_jump(thread);
    }
  }

  while (currentModule > 0) {
    modules[--currentModule].shutdown(thread, sourcePixelBuffer, parameters);
  }
}

static void
NativeWindowsImageWriter_writePngToPathImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createFile(thread, targetPath, ImageWriterFormat_Png);
  write(thread, sourcePixelBuffer, imageWriterParameters);
}

static void
NativeWindowsImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createByteBuffer(thread, targetByteBuffer, ImageWriterFormat_Png);
  write(thread, sourcePixelBuffer, imageWriterParameters);
}

static void
NativeWindowsImageWriter_writeBmpToPathImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createFile(thread, targetPath, ImageWriterFormat_Bmp);
  write(thread, sourcePixelBuffer, imageWriterParameters);
}

static void
NativeWindowsImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createByteBuffer(thread, targetByteBuffer, ImageWriterFormat_Bmp);
  write(thread, sourcePixelBuffer, imageWriterParameters);
}

static void
NativeWindowsImageWriter_writeIcoToPathImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(thread);
  ImageWriter_writeIcoToByteBuffer(thread, (ImageWriter*)self, sourcePixelBuffers, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_create(thread), Arcadia_FilePath_parseNative(thread, Arcadia_String_getBytes(thread, targetPath), Arcadia_String_getNumberOfBytes(thread, targetPath)), targetByteBuffer);
}

static void
NativeWindowsImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
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

  ICONDIR iconDir = {
    .reserved1 = 0,
    .type = 1,
    .numberOfImages = Arcadia_List_getSize(thread, sourcePixelBuffers)
  };
  Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, &iconDir, sizeof(ICONDIR));

  Arcadia_ByteBuffer* temporary = Arcadia_ByteBuffer_create(thread);
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_List_getSize(thread, sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(thread, temporary);
    ImageWriter_writePngToByteBuffer(thread, (ImageWriter*)self, pixelBuffer, temporary);
    if (Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8 != PixelBuffer_getPixelFormat(thread, pixelBuffer)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    size_t width = PixelBuffer_getNumberOfColumns(thread, pixelBuffer),
           height = PixelBuffer_getNumberOfRows(thread, pixelBuffer);
    if (width > 256) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (height > 256) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
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
                                  .imageSize = Arcadia_ByteBuffer_getSize(thread, temporary),
                                  .offset = sizeof(ICONDIR) + Arcadia_List_getSize(thread, sourcePixelBuffers) * sizeof(ICONDIRENTRY) + offset };
    Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, &iconDirEntry, sizeof(ICONDIRENTRY));
    offset += Arcadia_ByteBuffer_getSize(thread, temporary);
  }
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_List_getSize(thread, sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(thread, temporary);
    ImageWriter_writePngToByteBuffer(thread, (ImageWriter*)self, pixelBuffer, temporary);
    Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, temporary->p, temporary->sz);
    offset += Arcadia_ByteBuffer_getSize(thread, temporary);
  }
}

static void
NativeWindowsImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &NativeWindowsImageWriter_constructImpl,
  .destruct = NULL,
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

Arcadia_defineObjectType(u8"NativeWindowsImageWriter", NativeWindowsImageWriter, u8"ImageWriter", ImageWriter, &_typeOperations);

static void
NativeWindowsImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  NativeWindowsImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _NativeWindowsImageWriter_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  ((ImageWriter*)_self)->writeBmpToByteBuffer = (void (*)(Arcadia_Thread*, ImageWriter*, PixelBuffer*,Arcadia_ByteBuffer*))NativeWindowsImageWriter_writeBmpToByteBufferImpl;
  ((ImageWriter*)_self)->writeBmpToPath = (void (*)(Arcadia_Thread*, ImageWriter*, PixelBuffer*, Arcadia_String*))NativeWindowsImageWriter_writeBmpToPathImpl;
  ((ImageWriter*)_self)->writeIcoToByteBuffer = (void (*)(Arcadia_Thread*,ImageWriter*, Arcadia_List*, Arcadia_ByteBuffer*))NativeWindowsImageWriter_writeIcoToByteBufferImpl;
  ((ImageWriter*)_self)->writeIcoToPath = (void (*)(Arcadia_Thread*,ImageWriter*, Arcadia_List*, Arcadia_String*))NativeWindowsImageWriter_writeIcoToPathImpl;
  ((ImageWriter*)_self)->writePngToByteBuffer = (void (*)(Arcadia_Thread*,ImageWriter*, PixelBuffer*, Arcadia_ByteBuffer*))NativeWindowsImageWriter_writePngToByteBufferImpl;
  ((ImageWriter*)_self)->writePngToPath = (void (*)(Arcadia_Thread*,ImageWriter*, PixelBuffer*, Arcadia_String*))NativeWindowsImageWriter_writePngToPathImpl;
  Arcadia_Object_setType(thread, _self, _type);
}

NativeWindowsImageWriter*
NativeWindowsImageWriter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  NativeWindowsImageWriter* self = Arcadia_allocateObject(thread, _NativeWindowsImageWriter_getType(thread), 0, &argumentValues[0]);
  return self;
}
