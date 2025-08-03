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

#include "Arcadia/Imaging/Windows/WicImageWriterBase.h"

#include "Arcadia/Imaging/Windows/MultiByteToWideCharZeroTerminated.h"

// WIC library
#pragma comment (lib, "Windowscodecs.lib")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Arcadia/Imaging/ImageWriterParameters.h"

static HRESULT
createMemoryStream
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    IStream** pStream,
    size_t initialSize
  )
{
  self->hMemory = GlobalAlloc(GMEM_MOVEABLE, initialSize);
  if (!self->hMemory) {
    return E_OUTOFMEMORY;
  }
  IStream* pStream1 = NULL;
  HRESULT hr = CreateStreamOnHGlobal(self->hMemory, FALSE, &pStream1);
  if (FAILED(hr)) {
    GlobalFree(self->hMemory);
    self->hMemory = NULL;
    return hr;
  }
  *pStream = pStream1;
  return S_OK;
}

static void
startupFactory
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
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
                        (LPVOID*)&self->piFactory);
  if (FAILED(hr)) {
    CoUninitialize();
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  //
  hr = IWICImagingFactory_CreateStream(self->piFactory, &self->piStream);
  if (FAILED(hr)) {
    IWICImagingFactory_Release(self->piFactory);
    self->piFactory = NULL;
    CoUninitialize();
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
shutdownFactory
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  )
{
  IWICStream_Release(self->piStream);
  self->piStream = NULL;
  //
  IWICImagingFactory_Release(self->piFactory);
  self->piFactory = NULL;
  //
  CoUninitialize();
}

static void
startup1
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  if (Arcadia_Imaging_ImageWriterParameters_hasPath(thread, parameters)) {
    Arcadia_ByteBuffer* b = Arcadia_ByteBuffer_create(thread);
    Arcadia_ByteBuffer_append_pn(thread, b, Arcadia_String_getBytes(thread, Arcadia_Imaging_ImageWriterParameters_getPath(thread, parameters)),
                                            Arcadia_String_getNumberOfBytes(thread, Arcadia_Imaging_ImageWriterParameters_getPath(thread, parameters)));
    Arcadia_ByteBuffer_append_pn(thread, b, u8"", 1);
    wchar_t* targetPathW = Arcadia_Windows_multiByteToWideCharZeroTerminated(b->p);
    if (!targetPathW) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    hr = IWICStream_InitializeFromFilename(self->piStream, targetPathW, GENERIC_WRITE);
    free(targetPathW);
    if (FAILED(hr)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  } else {
    hr = createMemoryStream(thread, self, &self->piMemoryStream, 8);
    if (FAILED(hr)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    hr = IWICStream_InitializeFromIStream(self->piStream, self->piMemoryStream);
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
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  )
{
  if (self->piMemoryStream) {
    IStream_Release(self->piMemoryStream);
    self->piMemoryStream = NULL;
  }
  if (self->hMemory) {
    GlobalFree(self->hMemory);
    self->hMemory = NULL;
  }
}

static void
startupEncoder
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  GUID const* pFormat = NULL;
  self->getFormat(thread, self, sourcePixelBuffer, parameters, &pFormat);
  if (NULL == pFormat) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  hr = IWICImagingFactory_CreateEncoder(self->piFactory, pFormat, NULL, &self->piEncoder);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  hr = IWICBitmapEncoder_Initialize(self->piEncoder, (IStream*)self->piStream, WICBitmapEncoderNoCache);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(self->piEncoder);
    self->piEncoder = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  //
  hr = IWICBitmapEncoder_CreateNewFrame(self->piEncoder, &self->piBitmapFrame, &self->pPropertyBag);
  if (FAILED(hr)) {
    IWICBitmapEncoder_Release(self->piEncoder);
    self->piEncoder = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      self->configure(thread, self, sourcePixelBuffer, parameters);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      IPropertyBag2_Release(self->pPropertyBag);
      self->pPropertyBag = NULL;
      IWICBitmapFrameEncode_Release(self->piBitmapFrame);
      self->piBitmapFrame = NULL;
      IWICBitmapEncoder_Release(self->piEncoder);
      self->piEncoder = NULL;
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
  hr = IWICBitmapFrameEncode_Initialize(self->piBitmapFrame, self->pPropertyBag);
  if (FAILED(hr)) {
    IPropertyBag2_Release(self->pPropertyBag);
    self->pPropertyBag = NULL;
    IWICBitmapFrameEncode_Release(self->piBitmapFrame);
    self->piBitmapFrame = NULL;
    IWICBitmapEncoder_Release(self->piEncoder);
    self->piEncoder = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
shutdownEncoder
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  )
{
  IPropertyBag2_Release(self->pPropertyBag);
  self->pPropertyBag = NULL;
  IWICBitmapFrameEncode_Release(self->piBitmapFrame);
  self->piBitmapFrame = NULL;
  IWICBitmapEncoder_Release(self->piEncoder);
  self->piEncoder = NULL;
}

static void
startup3
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  //
  size_t sourceWidth = Arcadia_Imaging_PixelBuffer_getNumberOfColumns(thread, sourcePixelBuffer);
  size_t sourceHeight = Arcadia_Imaging_PixelBuffer_getNumberOfRows(thread, sourcePixelBuffer);
  hr = IWICBitmapFrameEncode_SetSize(self->piBitmapFrame, (UINT)sourceWidth, (UINT)sourceHeight);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  //
  WICPixelFormatGUID formatGUID = GUID_WICPixelFormatUndefined;
  switch (sourcePixelBuffer->pixelFormat) {
    case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8: {
      Arcadia_Imaging_PixelBuffer* pixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8);
      sourcePixelBuffer = pixelBuffer;
      formatGUID = GUID_WICPixelFormat32bppBGRA;
    } break;
    case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8: {
      Arcadia_Imaging_PixelBuffer* pixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8);
      sourcePixelBuffer = pixelBuffer;
      formatGUID = GUID_WICPixelFormat32bppBGRA;
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8: {
      formatGUID = GUID_WICPixelFormat24bppBGR;
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8: {
      formatGUID = GUID_WICPixelFormat32bppBGRA;
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
      formatGUID = GUID_WICPixelFormat24bppBGR;
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
      formatGUID = GUID_WICPixelFormat32bppRGBA;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };
  hr = IWICBitmapFrameEncode_SetPixelFormat(self->piBitmapFrame, &formatGUID);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  size_t sourceLineStride = Arcadia_Imaging_PixelBuffer_getLineStride(thread, sourcePixelBuffer);
  size_t sourceSizeInPixels = sourceLineStride * sourceHeight;
  hr = IWICBitmapFrameEncode_WritePixels(self->piBitmapFrame, (UINT)sourceHeight, (UINT)sourceLineStride, (UINT)sourceSizeInPixels, (void*)sourcePixelBuffer->bytes);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  hr = IWICBitmapFrameEncode_Commit(self->piBitmapFrame);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  hr = IWICBitmapEncoder_Commit(self->piEncoder);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (Arcadia_Imaging_ImageWriterParameters_hasByteBuffer(thread, parameters)) {
    STATSTG statstg;
    hr = IStream_Stat(self->piStream, &statstg, STATFLAG_NONAME);
    if (FAILED(hr)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (statstg.cbSize.QuadPart > SIZE_MAX) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    size_t n = (size_t)statstg.cbSize.QuadPart;
    LPVOID p = GlobalLock(self->hMemory);
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_ByteBuffer_append_pn(thread, Arcadia_Imaging_ImageWriterParameters_getByteBuffer(thread, parameters), p, n);
      GlobalUnlock(self->hMemory);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      GlobalUnlock(self->hMemory);
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
shutdown3
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  )
{ }

typedef struct Module {
  void (*startup)(Arcadia_Thread* thread, Arcadia_Imaging_Windows_WicImageWriterBase*, Arcadia_Imaging_PixelBuffer* sourcePixelBuffer, Arcadia_Imaging_ImageWriterParameters* parameters);
  void (*shutdown)(Arcadia_Thread* thread, Arcadia_Imaging_Windows_WicImageWriterBase*, Arcadia_Imaging_PixelBuffer* sourcePixelBuffer, Arcadia_Imaging_ImageWriterParameters* parameters);
} Module;

static void
Arcadia_Imaging_Windows_WicImageWriterBase_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Imaging_Windows_WicImageWriterBase_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.Windows.WicImageWriterBase", Arcadia_Imaging_Windows_WicImageWriterBase,
                         u8"Arcadia.Imaging.ImageWriter", Arcadia_Imaging_ImageWriter,
                         &_typeOperations);

static void
Arcadia_Imaging_Windows_WicImageWriterBase_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Imaging_Windows_WicImageWriterBase* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Imaging_Windows_WicImageWriterBase_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }

  _self->piFactory = NULL;
  _self->hMemory = NULL;
  _self->piMemoryStream = NULL;
  _self->piStream = NULL;
  _self->piEncoder = NULL;
  _self->piBitmapFrame = NULL;
  _self->pPropertyBag = NULL;
  
  _self->configure = NULL;
  _self->getFormat = NULL;
  
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

void
Arcadia_Imaging_Windows_WicImageWriterBase_doWrite
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
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
      modules[currentModule++].startup(thread, self, sourcePixelBuffer, parameters);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      while (currentModule > 0) {
        modules[--currentModule].shutdown(thread, self, sourcePixelBuffer, parameters);
      }
      Arcadia_Thread_jump(thread);
    }
  }

  while (currentModule > 0) {
    modules[--currentModule].shutdown(thread, self, sourcePixelBuffer, parameters);
  }  
}
