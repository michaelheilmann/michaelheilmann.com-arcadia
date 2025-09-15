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

#include "Arcadia/Imaging/Windows/TifImageWriter.h"

#include "Arcadia/Imaging/Windows/MultiByteToWideCharZeroTerminated.h"

// WIC library
#pragma comment (lib, "Windowscodecs.lib")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Arcadia/Imaging/ImageWriterParameters.h"

static Arcadia_ImmutableList*
Arcadia_Imaging_Windows_TifImageWriter_getSupportedTypes
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self
  );

static void
Arcadia_Imaging_Windows_TifImageWriter_writeToPathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
Arcadia_Imaging_Windows_TifImageWriter_writeToByteBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static void
configure
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  )
{
  HRESULT hr;
  // https://learn.microsoft.com/en-us/windows/win32/wic/tiff-format-overview
  PROPBAG2 option = { 0 };
  option.pstrName = L"TiffCompressionMethod";
  VARIANT varValue;
  VariantInit(&varValue);
  varValue.vt = VT_UI1;
  varValue.bVal = WICTiffCompressionZIP;
  hr = IPropertyBag2_Write(((Arcadia_Imaging_Windows_WicImageWriterBase*)self)->pPropertyBag, 1, &option, &varValue);
  if (FAILED(hr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
getFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters,
    GUID const** guid
  )
{
  *guid = &GUID_ContainerFormatTiff;
}

static Arcadia_ImmutableList*
Arcadia_Imaging_Windows_TifImageWriter_getSupportedTypes
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self
  )
{
  return self->supportedTypes;
}

static void
Arcadia_Imaging_Windows_TifImageWriter_writeToPathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{
  Arcadia_Imaging_ImageWriterParameters* parameters = Arcadia_Imaging_ImageWriterParameters_createFile(thread, targetPath, extension);
  if (1 != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue sourceObject = Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, 0);
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, sourceObject), _Arcadia_Imaging_PixelBuffer_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Imaging_PixelBuffer* sourcePixelBuffer = (Arcadia_Imaging_PixelBuffer*)sourceObject;
  Arcadia_Imaging_Windows_WicImageWriterBase_doWrite(thread, (Arcadia_Imaging_Windows_WicImageWriterBase*)self, sourcePixelBuffer, parameters);
}

static void
Arcadia_Imaging_Windows_TifImageWriter_writeToByteBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  Arcadia_Imaging_ImageWriterParameters* parameters = Arcadia_Imaging_ImageWriterParameters_createByteBuffer(thread, targetByteBuffer, extension);
  if (1 != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue sourceObject = Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, 0);
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, sourceObject), _Arcadia_Imaging_PixelBuffer_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Imaging_PixelBuffer* sourcePixelBuffer = (Arcadia_Imaging_PixelBuffer*)sourceObject;
  Arcadia_Imaging_Windows_WicImageWriterBase_doWrite(thread, (Arcadia_Imaging_Windows_WicImageWriterBase*)self, sourcePixelBuffer, parameters);
}

static void
Arcadia_Imaging_Windows_TifImageWriter_write
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_TifImageWriter* self,
    Arcadia_List* source,
    Arcadia_Imaging_ImageWriterParameters* target
  )
{
  Arcadia_Value requestedExtension = Arcadia_Value_makeObjectReferenceValue(Arcadia_Imaging_ImageWriterParameters_getFormat(thread, target));
  if (!Arcadia_List_contains(thread, (Arcadia_List*)self->supportedTypes, requestedExtension)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue sourceObject = Arcadia_List_getObjectReferenceValueAt(thread, source, 0);
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, sourceObject), _Arcadia_Imaging_PixelBuffer_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Imaging_PixelBuffer* sourcePixelBuffer = (Arcadia_Imaging_PixelBuffer*)sourceObject;
  Arcadia_Imaging_Windows_WicImageWriterBase_doWrite(thread, (Arcadia_Imaging_Windows_WicImageWriterBase*)self, sourcePixelBuffer, target);
}

static void
Arcadia_Imaging_Windows_TifImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Imaging_Windows_TifImageWriter_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.Windows.TifImageWriter", Arcadia_Imaging_Windows_TifImageWriter,
                         u8"Arcadia.Imaging.Windows.WicImagerWriterBase", Arcadia_Imaging_Windows_WicImageWriterBase,
                         &_typeOperations);

static void
Arcadia_Imaging_Windows_TifImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Imaging_Windows_TifImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Imaging_Windows_TifImageWriter_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  _self->supportedTypes = NULL;
  Arcadia_List* supportedTypes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, supportedTypes, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"tif", sizeof(u8"tif") - 1))));
  _self->supportedTypes = Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(supportedTypes));
  
  ((Arcadia_Imaging_ImageWriter*)_self)->getSupportedTypes = (Arcadia_ImmutableList * (*)(Arcadia_Thread*, Arcadia_Imaging_ImageWriter*))& Arcadia_Imaging_Windows_TifImageWriter_getSupportedTypes;
  ((Arcadia_Imaging_ImageWriter*)_self)->write = (void (*)(Arcadia_Thread*, Arcadia_Imaging_ImageWriter*, Arcadia_List*, Arcadia_Imaging_ImageWriterParameters*)) & Arcadia_Imaging_Windows_TifImageWriter_write;

  ((Arcadia_Imaging_Windows_WicImageWriterBase*)_self)->getFormat = (void (*)(Arcadia_Thread*, Arcadia_Imaging_Windows_WicImageWriterBase*, Arcadia_Imaging_PixelBuffer*, Arcadia_Imaging_ImageWriterParameters*, GUID const**)) & getFormat;
  ((Arcadia_Imaging_Windows_WicImageWriterBase*)_self)->configure = (void (*)(Arcadia_Thread*, Arcadia_Imaging_Windows_WicImageWriterBase*, Arcadia_Imaging_PixelBuffer*, Arcadia_Imaging_ImageWriterParameters*)) & configure;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

Arcadia_Imaging_Windows_TifImageWriter*
Arcadia_Imaging_Windows_TifImageWriter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Imaging_Windows_TifImageWriter);
}
