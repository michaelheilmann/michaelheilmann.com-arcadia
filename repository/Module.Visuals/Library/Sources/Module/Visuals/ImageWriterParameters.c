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

// Last modified: 2024-09-16

#include "Module/Visuals/ImageWriterParameters.h"

struct ImageWriterParameters {
  Arcadia_Object _parent;
  ImageWriterFormat format;
  // "object" either refers to a "R.ByteBuffer" object (if target is ImageWriter_Target_Memory) or a "Arcadia.String" object (if target is ImageWriter_Target_File).
  Arcadia_ObjectReferenceValue object;
};

static void
ImageWriterParameters_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
ImageWriterParameters_visit
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  );

static void
ImageWriterParameters_destruct
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &ImageWriterParameters_constructImpl,
  .destruct = &ImageWriterParameters_destruct,
  .visit = &ImageWriterParameters_visit,
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

Rex_defineObjectType(u8"ImageWriterParameters", ImageWriterParameters, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
ImageWriterParameters_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  ImageWriterParameters* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _ImageWriterParameters_getType(process);
  if (2 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_Type_isSubType(Arcadia_Value_getType(process, &argumentValues[0]), _Arcadia_String_getType(process))) {
    _self->object = (Arcadia_ObjectReferenceValue)Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
    _self->format = Arcadia_Value_getInteger32Value(&argumentValues[1]);
  } else if (Arcadia_Type_isSubType(Arcadia_Value_getType(process, &argumentValues[0]), _R_ByteBuffer_getType(process))) {
    _self->object = (Arcadia_ObjectReferenceValue)Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
    _self->format = Arcadia_Value_getInteger32Value(&argumentValues[1]);
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Object_setType(process, _self, _type);
}

static void
ImageWriterParameters_visit
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  )
{ Arcadia_Object_visit(process, self->object); }

static void
ImageWriterParameters_destruct
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  )
{/*Intentionally empty.*/}

ImageWriterParameters*
ImageWriterParameters_createFile
  (
    Arcadia_Process* process,
    Arcadia_String* path,
    ImageWriterFormat format
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = path },
                               {.tag = Arcadia_ValueTag_Integer32, .integer32Value = format }, };
  ImageWriterParameters* self = R_allocateObject(process, _ImageWriterParameters_getType(process), 2, &argumentValues[0]);
  return self;
}

ImageWriterParameters*
ImageWriterParameters_createByteBuffer
  (
    Arcadia_Process* process,
    R_ByteBuffer* byteBuffer,
    ImageWriterFormat format
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = byteBuffer },
                               {.tag = Arcadia_ValueTag_Integer32, .integer32Value = format }, };
  ImageWriterParameters* self = R_allocateObject(process, _ImageWriterParameters_getType(process), 2, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
ImageWriterParameters_hasPath
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(self->object);
  return Arcadia_Type_isSubType(type, _Arcadia_String_getType(process));
}

Arcadia_String*
ImageWriterParameters_getPath
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  )
{
  if (!ImageWriterParameters_hasPath(process, self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  return (Arcadia_String*)self->object;
}

Arcadia_BooleanValue
ImageWriterParameters_hasByteBuffer
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(self->object);
  return Arcadia_Type_isSubType(type, _R_ByteBuffer_getType(process));
}

R_ByteBuffer*
ImageWriterParameters_getByteBuffer
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  )
{
  if (!ImageWriterParameters_hasByteBuffer(process, self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
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
