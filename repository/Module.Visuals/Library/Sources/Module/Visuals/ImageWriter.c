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

#include "Module/Visuals/ImageWriter.h"

void
ImageWriter_writePngToPath
  (
    Arcadia_Process* process,
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{ self->writePngToPath(process, self, sourcePixelBuffer, targetPath); }

void
ImageWriter_writePngToByteBuffer
  (
    Arcadia_Process* process,
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{ self->writePngToByteBuffer(process, self, sourcePixelBuffer, targetByteBuffer); }

void
ImageWriter_writeBmpToPath
  (
    Arcadia_Process* process,
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{ self->writeBmpToPath(process, self, sourcePixelBuffer, targetPath); }

void
ImageWriter_writeBmpToByteBuffer
  (
    Arcadia_Process* process,
    ImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{ self->writeBmpToByteBuffer(process, self, sourcePixelBuffer, targetByteBuffer); }

void
ImageWriter_writeIcoToPath
  (
    Arcadia_Process* process,
    ImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{ self->writeIcoToPath(process, self, sourcePixelBuffers, targetPath); }

void
ImageWriter_writeIcoToByteBuffer
  (
    Arcadia_Process* process,
    ImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{ self->writeIcoToByteBuffer(process, self, sourcePixelBuffers, targetByteBuffer); }

static void
ImageWriter_constructImpl
  (
    Arcadia_Process* process,
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

Rex_defineObjectType(u8"ImageWriter", ImageWriter, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
ImageWriter_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  ImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _ImageWriter_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->writeBmpToByteBuffer = NULL;
  _self->writeBmpToPath = NULL;
  _self->writeIcoToByteBuffer = NULL;
  _self->writeIcoToPath = NULL;
  _self->writePngToByteBuffer = NULL;
  _self->writePngToPath = NULL;
  Arcadia_Object_setType(process, _self, _type);
}
