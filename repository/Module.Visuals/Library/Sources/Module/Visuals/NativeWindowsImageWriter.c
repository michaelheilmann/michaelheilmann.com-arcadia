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
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
NativeWindowsImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  );

static void
NativeWindowsImageWriter_writeBmpToPathImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
NativeWindowsImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
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
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    R_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
NativeWindowsImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    R_List* sourcePixelBuffers,
    R_ByteBuffer* targetByteBuffer
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
    Arcadia_Process* process,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  hr = CoInitialize(NULL);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  //
  hr = CoCreateInstance(&CLSID_WICImagingFactory,
                        NULL,
                        CLSCTX_INPROC_SERVER,
                        &IID_IWICImagingFactory,
                        (LPVOID*)&g_piFactory);
  if (FAILED(hr)) {
    CoUninitialize();
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  //
  hr = IWICImagingFactory_CreateStream(g_piFactory, &g_piStream);
  if (FAILED(hr)) {
    IWICImagingFactory_Release(g_piFactory);
    g_piFactory = NULL;
    CoUninitialize();
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
}

static void
shutdownFactory
  (
    Arcadia_Process* process,
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
    Arcadia_Process* process,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  if (ImageWriterParameters_hasPath(process, parameters)) {
    R_ByteBuffer* b = R_ByteBuffer_create(process);
    R_ByteBuffer_append_pn(process, b, Arcadia_String_getBytes(process, ImageWriterParameters_getPath(process, parameters)), Arcadia_String_getNumberOfBytes(process, ImageWriterParameters_getPath(process, parameters)));
    R_ByteBuffer_append_pn(process, b, u8"", 1);
    wchar_t* targetPathW = multiByteToWideChar(b->p);
    if (!targetPathW) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    hr = IWICStream_InitializeFromFilename(g_piStream, targetPathW, GENERIC_WRITE);
    free(targetPathW);
    if (FAILED(hr)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
  } else {
    hr = createMemoryStream(&g_piMemoryStream, 8);
    if (FAILED(hr)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    hr = IWICStream_InitializeFromIStream(g_piStream, g_piMemoryStream);
    if (FAILED(hr)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
  }
}

static void
shutdown1
  (
    Arcadia_Process* process,
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
    Arcadia_Process* process,
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
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
  }
  hr = IWICImagingFactory_CreateEncoder(g_piFactory, pFormat, NULL, &g_piEncoder);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  hr = IWICBitmapEncoder_Initialize(g_piEncoder, (IStream*)g_piStream, WICBitmapEncoderNoCache);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(g_piEncoder);
    g_piEncoder = NULL;
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  //
  hr = IWICBitmapEncoder_CreateNewFrame(g_piEncoder, &g_piBitmapFrame, &g_pPropertyBag);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(g_piEncoder);
    g_piEncoder = NULL;
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
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
        Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
        Arcadia_Process_jump(process);
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
        Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
        Arcadia_Process_jump(process);
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
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
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
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
}

static void
shutdownEncoder
  (
    Arcadia_Process* process,
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
    Arcadia_Process* process,
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
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  //
  WICPixelFormatGUID formatGUID = GUID_WICPixelFormatUndefined;
  switch (sourcePixelBuffer->pixelFormat) {
    case PixelFormat_Rn8Gn8Bn8: {
      formatGUID = GUID_WICPixelFormat24bppBGR;
    } break;
    case PixelFormat_An8Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(process, sourcePixelBuffer);
      PixelBuffer_setPixelFormat(process, pixelBuffer, PixelFormat_Bn8Gn8Rn8An8);
      sourcePixelBuffer = pixelBuffer;
      formatGUID = GUID_WICPixelFormat32bppBGRA;
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    } break;
  };
  hr = IWICBitmapFrameEncode_SetPixelFormat(g_piBitmapFrame, &formatGUID);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  size_t sourceLineStride = PixelBuffer_getLineStride(process, sourcePixelBuffer);
  size_t sourceSizeInPixels = sourceLineStride * sourceHeight;
  hr = IWICBitmapFrameEncode_WritePixels(g_piBitmapFrame, (UINT)sourceHeight, (UINT)sourceLineStride, (UINT)sourceSizeInPixels, (void*)sourcePixelBuffer->bytes);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }

  hr = IWICBitmapFrameEncode_Commit(g_piBitmapFrame);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }

  hr = IWICBitmapEncoder_Commit(g_piEncoder);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  if (ImageWriterParameters_hasByteBuffer(process, parameters)) {
    STATSTG statstg;
    hr = IStream_Stat(g_piStream, &statstg, STATFLAG_NONAME);
    if (FAILED(hr)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    if (statstg.cbSize.QuadPart > SIZE_MAX) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    size_t n = (size_t)statstg.cbSize.QuadPart;
    LPVOID p = GlobalLock(g_hMemory);
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Process_pushJumpTarget(process, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      R_ByteBuffer_append_pn(process, ImageWriterParameters_getByteBuffer(process, parameters), p, n);
      GlobalUnlock(g_hMemory);
      Arcadia_Process_popJumpTarget(process);
    } else {
      GlobalUnlock(g_hMemory);
      Arcadia_Process_popJumpTarget(process);
      Arcadia_Process_jump(process);
    }
  }
}

static void
shutdown3
  (
    Arcadia_Process* process,
    PixelBuffer* sourcePixelBuffer,
    ImageWriterParameters* parameters
  )
{ }

typedef struct Module {
  void (*startup)(Arcadia_Process* process, PixelBuffer* sourcePixelBuffer, ImageWriterParameters* parameters);
  void (*shutdown)(Arcadia_Process* process, PixelBuffer* sourcePixelBuffer, ImageWriterParameters* parameters);
} Module;

static
write
  (
    Arcadia_Process* process,
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
    Arcadia_Process_pushJumpTarget(process, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      modules[currentModule++].startup(process, sourcePixelBuffer, parameters);
      Arcadia_Process_popJumpTarget(process);
    } else {
      Arcadia_Process_popJumpTarget(process);
      while (currentModule > 0) {
        modules[--currentModule].shutdown(process, sourcePixelBuffer, parameters);
      }
      Arcadia_Process_jump(process);
    }
  }

  while (currentModule > 0) {
    modules[--currentModule].shutdown(process, sourcePixelBuffer, parameters);
  }
}

static void
NativeWindowsImageWriter_writePngToPathImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createFile(process, targetPath, ImageWriterFormat_Png);
  write(process, sourcePixelBuffer, imageWriterParameters);
}

static void
NativeWindowsImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  )
{
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createByteBuffer(process, targetByteBuffer, ImageWriterFormat_Png);
  write(process, sourcePixelBuffer, imageWriterParameters);
}

static void
NativeWindowsImageWriter_writeBmpToPathImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createFile(process, targetPath, ImageWriterFormat_Bmp);
  write(process, sourcePixelBuffer, imageWriterParameters);
}

static void
NativeWindowsImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  )
{
  ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createByteBuffer(process, targetByteBuffer, ImageWriterFormat_Bmp);
  write(process, sourcePixelBuffer, imageWriterParameters);
}

static void
NativeWindowsImageWriter_writeIcoToPathImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    R_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{
  R_ByteBuffer* targetByteBuffer = R_ByteBuffer_create(process);
  ImageWriter_writeIcoToByteBuffer(process, (ImageWriter*)self, sourcePixelBuffers, targetByteBuffer);
  R_FileSystem_setFileContents(process, R_FileSystem_create(process), R_FilePath_parseNative(process, Arcadia_String_getBytes(process, targetPath), Arcadia_String_getNumberOfBytes(process, targetPath)), targetByteBuffer);
}

static void
NativeWindowsImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeWindowsImageWriter* self,
    R_List* sourcePixelBuffers,
    R_ByteBuffer* targetByteBuffer
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
    .numberOfImages = R_List_getSize(sourcePixelBuffers)
  };
  R_ByteBuffer_append_pn(process, targetByteBuffer, &iconDir, sizeof(ICONDIR));

  R_ByteBuffer* temporary = R_ByteBuffer_create(process);
  for (Arcadia_SizeValue i = 0, offset = 0, n = R_List_getSize(sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)R_List_getObjectReferenceValueAt(process, sourcePixelBuffers, i);
    R_ByteBuffer_clear(temporary);
    ImageWriter_writePngToByteBuffer(process, (ImageWriter*)self, pixelBuffer, temporary);
    if (PixelFormat_An8Rn8Gn8Bn8 != PixelBuffer_getPixelFormat(pixelBuffer)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    size_t width = PixelBuffer_getNumberOfColumns(pixelBuffer),
           height = PixelBuffer_getNumberOfRows(pixelBuffer);
    if (width > 256) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    if (height > 256) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
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
    R_ByteBuffer_append_pn(process, targetByteBuffer, &iconDirEntry, sizeof(ICONDIRENTRY));
    offset += R_ByteBuffer_getSize(temporary);
  }
  for (Arcadia_SizeValue i = 0, offset = 0, n = R_List_getSize(sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)R_List_getObjectReferenceValueAt(process, sourcePixelBuffers, i);
    R_ByteBuffer_clear(temporary);
    ImageWriter_writePngToByteBuffer(process, (ImageWriter*)self, pixelBuffer, temporary);
    R_ByteBuffer_append_pn(process, targetByteBuffer, temporary->p, temporary->sz);
    offset += R_ByteBuffer_getSize(temporary);
  }
}

static void
NativeWindowsImageWriter_constructImpl
  (
    Arcadia_Process* process,
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

Rex_defineObjectType(u8"NativeWindowsImageWriter", NativeWindowsImageWriter, u8"ImageWriter", ImageWriter, &_typeOperations);

static void
NativeWindowsImageWriter_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  NativeWindowsImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _NativeWindowsImageWriter_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  ((ImageWriter*)_self)->writeBmpToByteBuffer = (void (*)(Arcadia_Process*, ImageWriter*, PixelBuffer*,R_ByteBuffer*))NativeWindowsImageWriter_writeBmpToByteBufferImpl;
  ((ImageWriter*)_self)->writeBmpToPath = (void (*)(Arcadia_Process*, ImageWriter*, PixelBuffer*, Arcadia_String*))NativeWindowsImageWriter_writeBmpToPathImpl;
  ((ImageWriter*)_self)->writeIcoToByteBuffer = (void (*)(Arcadia_Process*,ImageWriter*, R_List*, R_ByteBuffer*))NativeWindowsImageWriter_writeIcoToByteBufferImpl;
  ((ImageWriter*)_self)->writeIcoToPath = (void (*)(Arcadia_Process*,ImageWriter*, R_List*, Arcadia_String*))NativeWindowsImageWriter_writeIcoToPathImpl;
  ((ImageWriter*)_self)->writePngToByteBuffer = (void (*)(Arcadia_Process*,ImageWriter*, PixelBuffer*, R_ByteBuffer*))NativeWindowsImageWriter_writePngToByteBufferImpl;
  ((ImageWriter*)_self)->writePngToPath = (void (*)(Arcadia_Process*,ImageWriter*, PixelBuffer*, Arcadia_String*))NativeWindowsImageWriter_writePngToPathImpl;
  Arcadia_Object_setType(process, _self, _type);
}

NativeWindowsImageWriter*
NativeWindowsImageWriter_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  NativeWindowsImageWriter* self = R_allocateObject(process, _NativeWindowsImageWriter_getType(process), 0, &argumentValues[0]);
  return self;
}
