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

#include "Module/Visuals/ImageWriter.h"

void
ImageWriter_writePngToPath
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{ self->writePngToPath(thread, self, sourcePixelBuffer, targetPath); }

void
ImageWriter_writePngToByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{ self->writePngToByteBuffer(thread, self, sourcePixelBuffer, targetByteBuffer); }

void
ImageWriter_writeBmpToPath
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{ self->writeBmpToPath(thread, self, sourcePixelBuffer, targetPath); }

void
ImageWriter_writeBmpToByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{ self->writeBmpToByteBuffer(thread, self, sourcePixelBuffer, targetByteBuffer); }

void
ImageWriter_writeIcoToPath
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{ self->writeIcoToPath(thread, self, sourcePixelBuffers, targetPath); }

void
ImageWriter_writeIcoToByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{ self->writeIcoToByteBuffer(thread, self, sourcePixelBuffers, targetByteBuffer); }

static void
ImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &ImageWriter_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"ImageWriter", ImageWriter, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
ImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  ImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _ImageWriter_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->writeBmpToByteBuffer = NULL;
  _self->writeBmpToPath = NULL;
  _self->writeIcoToByteBuffer = NULL;
  _self->writeIcoToPath = NULL;
  _self->writePngToByteBuffer = NULL;
  _self->writePngToPath = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}
