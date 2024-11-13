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

// Last modified: 2024-09-16

#include "Module/Visuals/ImageWriterParameters.h"

struct ImageWriterParameters {
  R_Object _parent;
  ImageWriterFormat format;
  // "object" either refers to a "R.ByteBuffer" object (if target is ImageWriter_Target_Memory) or a "R.String" object (if target is ImageWriter_Target_File).
  R_ObjectReferenceValue object;
};

static void
ImageWriterParameters_visit
  (
    ImageWriterParameters* self
  )
{
  R_Object_visit(self->object);
}

static void
ImageWriterParameters_destruct
  (
    ImageWriterParameters* self
  )
{/*Intentionally empty.*/}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = &ImageWriterParameters_destruct,
  .visit = &ImageWriterParameters_visit,
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

Rex_defineObjectType("ImageWriterParameters", ImageWriterParameters, "R.Object", R_Object, &_typeOperations);

void
ImageWriterParameters_constructFile
  (
    ImageWriterParameters* self,
    R_String* path,
    ImageWriterFormat format
  )
{
  R_Type* _type = _ImageWriterParameters_getType();
  R_Object_construct((R_Object*)self);
  self->object = (R_ObjectReferenceValue)path;
  self->format = format;
  R_Object_setType((R_Object*)self, _type);
}

ImageWriterParameters*
ImageWriterParameters_createFile
  (
    R_String* path,
    ImageWriterFormat format
  )
{
  ImageWriterParameters* self = R_allocateObject(_ImageWriterParameters_getType());
  ImageWriterParameters_constructFile(self, path, format);
  return self;
}

void
ImageWriterParameters_constructByteBuffer
  (
    ImageWriterParameters* self,
    R_ByteBuffer* byteBuffer,
    ImageWriterFormat format
  )
{
  R_Type* _type = _ImageWriterParameters_getType();
  R_Object_construct((R_Object*)self);
  self->object = (R_ObjectReferenceValue)byteBuffer;
  self->format = format;
  R_Object_setType((R_Object*)self, _type);
}

ImageWriterParameters*
ImageWriterParameters_createByteBuffer
  (
    R_ByteBuffer* byteBuffer,
    ImageWriterFormat format
  )
{
  ImageWriterParameters* self = R_allocateObject(_ImageWriterParameters_getType());
  ImageWriterParameters_constructByteBuffer(self, byteBuffer, format);
  return self;
}

R_BooleanValue
ImageWriterParameters_hasPath
  (
    ImageWriterParameters* self
  )
{
  R_Type* type = R_Object_getType(self->object);
  return R_Type_isSubType(type, _R_String_getType());
}

R_String*
ImageWriterParameters_getPath
  (
    ImageWriterParameters* self
  )
{
  if (!ImageWriterParameters_hasPath(self)) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  return (R_String*)self->object;
}

R_BooleanValue
ImageWriterParameters_hasByteBuffer
  (
    ImageWriterParameters* self
  )
{
  R_Type* type = R_Object_getType(self->object);
  return R_Type_isSubType(type, _R_ByteBuffer_getType());
}

R_ByteBuffer*
ImageWriterParameters_getByteBuffer
  (
    ImageWriterParameters* self
  )
{
  if (!ImageWriterParameters_hasByteBuffer(self)) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  return (R_ByteBuffer*)self->object;
}

ImageWriterFormat
ImageWriterParameters_getFormat
  (
    ImageWriterParameters* self
  )
{
  return self->format;
}
