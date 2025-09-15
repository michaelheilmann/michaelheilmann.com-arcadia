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

#include "Arcadia/Imaging/IcoImageWriter.h"

#include "Arcadia/Imaging/ImageWriterParameters.h"
#include "Arcadia/Imaging/ImageManager.h"

static void
IcoImageWriter_constructImpl
  ( 
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
IcoImageWriter_visit
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  );

static Arcadia_ImmutableList*
IcoImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  );

static void
IcoImageWriter_writeToPathImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
IcoImageWriter_writeToByteBufferImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static Arcadia_Imaging_ImageWriter*
IcoImageWriter_getPngImageWriter
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  );

static void
IcoImageWriter_writeIcoToPathImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
IcoImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static void
IcoImageWriter_writeImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* source,
    Arcadia_Imaging_ImageWriterParameters* target
  );

static Arcadia_ImmutableList*
IcoImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  )
{ return self->supportedTypes; }

static void
IcoImageWriter_writeToPathImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{ 
  Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(extension);
  Arcadia_Value b[] = {
    Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"ico", sizeof(u8"ico") - 1)))),
  };

  if (Arcadia_Value_isEqualTo(thread, &a, &b[0])) {
    if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers) < 1) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    IcoImageWriter_writeIcoToPathImpl(thread, self, sourcePixelBuffers, targetPath);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
IcoImageWriter_writeToByteBufferImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(extension);
  Arcadia_Value b[] = {
    Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"ico", sizeof(u8"ico") - 1)))),
  };
  if (Arcadia_Value_isEqualTo(thread, &a, &b[0])) {
    if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers) < 1) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    IcoImageWriter_writeIcoToByteBufferImpl(thread, self, sourcePixelBuffers, targetByteBuffer);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static Arcadia_Imaging_ImageWriter*
IcoImageWriter_getPngImageWriter
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  )
{
  Arcadia_Imaging_ImageManager* imageManager = Arcadia_Imaging_ImageManager_getOrCreate(thread);
  Arcadia_String* extension = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"png", sizeof(u8"png") - 1)));
  Arcadia_List* writers = Arcadia_Imaging_ImageManager_getWriters(thread, imageManager, extension);
  if (!Arcadia_Collection_getSize(thread, (Arcadia_Collection*)writers)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
    Arcadia_Thread_popJumpTarget(thread);
  }
  Arcadia_Imaging_ImageWriter* writer = (Arcadia_Imaging_ImageWriter*)Arcadia_List_getObjectReferenceValueAt(thread, writers, 0);
  return writer;
}

static void
IcoImageWriter_writeIcoToPathImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(thread);
  IcoImageWriter_writeIcoToByteBufferImpl(thread, self, sourcePixelBuffers, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_getOrCreate(thread), Arcadia_FilePath_parseUnix(thread, targetPath), targetByteBuffer);
}

static void
IcoImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
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
    .numberOfImages = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers)
  };
  Arcadia_List* pixelBuffers = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, &iconDir, sizeof(ICONDIR));
  
  Arcadia_Imaging_ImageWriter* pngImageWriter =  IcoImageWriter_getPngImageWriter(thread, self);
  Arcadia_String* pngExtension = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"png", sizeof(u8"png") - 1)));
  Arcadia_ByteBuffer* temporary = Arcadia_ByteBuffer_create(thread);
  Arcadia_Imaging_ImageWriterParameters* pngParameters = Arcadia_Imaging_ImageWriterParameters_createByteBuffer(thread, temporary, pngExtension);
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers); i < n; ++i) {
    Arcadia_Imaging_PixelBuffer* pixelBuffer = (Arcadia_Imaging_PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(thread, temporary);
    Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBuffers);
    Arcadia_List_insertBackObjectReferenceValue(thread, pixelBuffers, pixelBuffer);
    Arcadia_Imaging_ImageWriter_write(thread, pngImageWriter, pixelBuffers, pngParameters);
    if (Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8 != Arcadia_Imaging_PixelBuffer_getPixelFormat(thread, pixelBuffer)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    size_t width = Arcadia_Imaging_PixelBuffer_getNumberOfColumns(thread, pixelBuffer),
           height = Arcadia_Imaging_PixelBuffer_getNumberOfRows(thread, pixelBuffer);
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
                                  .offset = sizeof(ICONDIR) + Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers) * sizeof(ICONDIRENTRY) + offset };
    Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, &iconDirEntry, sizeof(ICONDIRENTRY));
    offset += Arcadia_ByteBuffer_getSize(thread, temporary);
  }
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers); i < n; ++i) {
    Arcadia_Imaging_PixelBuffer* pixelBuffer = (Arcadia_Imaging_PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(thread, temporary);
    Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBuffers);
    Arcadia_List_insertBackObjectReferenceValue(thread, pixelBuffers, pixelBuffer);
    Arcadia_Imaging_ImageWriter_write(thread, pngImageWriter, pixelBuffers, pngParameters);
    Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, temporary->p, temporary->sz);
    offset += Arcadia_ByteBuffer_getSize(thread, temporary);
  }
}

static void
IcoImageWriter_writeImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* source,
    Arcadia_Imaging_ImageWriterParameters* target
  )
{
  Arcadia_Value requestedExtension = Arcadia_Value_makeObjectReferenceValue(Arcadia_Imaging_ImageWriterParameters_getFormat(thread, target));
  if (!Arcadia_List_contains(thread, (Arcadia_List*)self->supportedTypes, requestedExtension)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (Arcadia_Imaging_ImageWriterParameters_hasByteBuffer(thread, target)) {
    IcoImageWriter_writeIcoToByteBufferImpl(thread, self, source, Arcadia_Imaging_ImageWriterParameters_getByteBuffer(thread, target));
  } else if (Arcadia_Imaging_ImageWriterParameters_hasPath(thread, target)) {
    IcoImageWriter_writeIcoToPathImpl(thread, self, source, Arcadia_Imaging_ImageWriterParameters_getPath(thread, target));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &IcoImageWriter_constructImpl,
  .destruct = NULL,
  .visit = &IcoImageWriter_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.IcoImageWriter", IcoImageWriter,
                         u8"Arcadia.Imaging.ImageWriter", Arcadia_Imaging_ImageWriter,
                         &_typeOperations);

static void
IcoImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  IcoImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_Type* _type = _IcoImageWriter_getType(thread);
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
  Arcadia_List_insertBackObjectReferenceValue(thread, supportedTypes, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"ico", sizeof(u8"ico") - 1))));
  _self->supportedTypes = Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(supportedTypes));
  ((Arcadia_Imaging_ImageWriter*)_self)->getSupportedTypes = (Arcadia_ImmutableList*(*)(Arcadia_Thread*, Arcadia_Imaging_ImageWriter*))&IcoImageWriter_getSupportedTypesImpl;
  ((Arcadia_Imaging_ImageWriter*)_self)->write = (void (*)(Arcadia_Thread*, Arcadia_Imaging_ImageWriter*, Arcadia_List*, Arcadia_Imaging_ImageWriterParameters*)) & IcoImageWriter_writeImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
IcoImageWriter_visit
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  )
{
  if (self->supportedTypes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->supportedTypes);
  }
}

IcoImageWriter*
IcoImageWriter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(IcoImageWriter);
}
