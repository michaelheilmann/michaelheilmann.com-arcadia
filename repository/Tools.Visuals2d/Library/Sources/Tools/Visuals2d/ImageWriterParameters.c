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

#include "Tools/Visuals2d/ImageWriterParameters.h"

struct ImageWriterParameters {
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
ImageWriterParameters_finalize
  (
    ImageWriterParameters* self
  )
{/*Intentionally empty.*/}

void
_ImageWriterParameters_registerType
  (
  )
{
  R_registerObjectType("ImageWriterParameters", sizeof("ImageWriterParameters") - 1, sizeof(ImageWriterParameters), NULL, &ImageWriterParameters_visit, &ImageWriterParameters_finalize);
}

ImageWriterParameters*
ImageWriterParameters_createFile
  (
    R_String* path,
    ImageWriterFormat format
  )
{
  ImageWriterParameters* self = R_allocateObject(R_getObjectType("ImageWriterParameters", sizeof("ImageWriterParameters") - 1));
  self->object = (R_ObjectReferenceValue)path;
  self->format = format;
  return self;
}

ImageWriterParameters*
ImageWriterParameters_createByteBuffer
  (
    R_ByteBuffer* byteBuffer,
    ImageWriterFormat format
  )
{
  ImageWriterParameters* self = R_allocateObject(R_getObjectType("ImageWriterParameters", sizeof("ImageWriterParameters") - 1));
  self->object = (R_ObjectReferenceValue)byteBuffer;
  self->format = format;
  return self;
}

R_BooleanValue
ImageWriterParameters_hasPath
  (
    ImageWriterParameters* self
  )
{
  R_Type* type = R_Object_getType(self->object);
  return R_Type_isSubType(type, R_getObjectType("R.String", sizeof("R.String") - 1));
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
  return R_Type_isSubType(type, R_getObjectType("R.ByteBuffer", sizeof("R.ByteBuffer") - 1));
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
