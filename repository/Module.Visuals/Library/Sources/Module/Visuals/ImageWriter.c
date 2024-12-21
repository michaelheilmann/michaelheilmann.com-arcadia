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

void
ImageWriter_writePngToPath
  (
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_String* targetPath
  )
{ self->writePngToPath(self, sourcePixelBuffer, targetPath); }

void
ImageWriter_writePngToByteBuffer
  (
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  )
{ self->writePngToByteBuffer(self, sourcePixelBuffer, targetByteBuffer); }

void
ImageWriter_writeBmpToPath
  (
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_String* targetPath
  )
{ self->writeBmpToPath(self, sourcePixelBuffer, targetPath); }

void
ImageWriter_writeBmpToByteBuffer
  (
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  )
{ self->writeBmpToByteBuffer(self, sourcePixelBuffer, targetByteBuffer); }

void
ImageWriter_writeIcoToPath
  (
    ImageWriter* self,
    R_List* sourcePixelBuffers,
    R_String* targetPath
  )
{ self->writeIcoToPath(self, sourcePixelBuffers, targetPath); }

void
ImageWriter_writeIcoToByteBuffer
  (
    ImageWriter* self,
    R_List* sourcePixelBuffers,
    R_ByteBuffer* targetByteBuffer
  )
{ self->writeIcoToByteBuffer(self, sourcePixelBuffers, targetByteBuffer); }

static void
ImageWriter_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  ); 

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &ImageWriter_constructImpl,
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

Rex_defineObjectType("ImageWriter", ImageWriter, "R.Object", R_Object, &_typeOperations);

static void
ImageWriter_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  ImageWriter* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _ImageWriter_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->writeBmpToByteBuffer = NULL;
  _self->writeBmpToPath = NULL;
  _self->writeIcoToByteBuffer = NULL;
  _self->writeIcoToPath = NULL;
  _self->writePngToByteBuffer = NULL;
  _self->writePngToPath = NULL;
  R_Object_setType((R_Object*)_self, _type);
}
