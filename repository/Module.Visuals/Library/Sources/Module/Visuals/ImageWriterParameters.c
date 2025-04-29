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
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
ImageWriterParameters_visit
  (
    Arcadia_Thread* thread,
    ImageWriterParameters* self
  );

static void
ImageWriterParameters_destruct
  (
    Arcadia_Thread* thread,
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

Arcadia_defineObjectType(u8"ImageWriterParameters", ImageWriterParameters, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
ImageWriterParameters_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  ImageWriterParameters* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _ImageWriterParameters_getType(thread);
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_Type_isSubType(thread, Arcadia_Value_getType(thread, &argumentValues[0]), _Arcadia_String_getType(thread))) {
    _self->object = (Arcadia_ObjectReferenceValue)Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
    _self->format = Arcadia_Value_getInteger32Value(&argumentValues[1]);
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Value_getType(thread, &argumentValues[0]), _Arcadia_ByteBuffer_getType(thread))) {
    _self->object = (Arcadia_ObjectReferenceValue)Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
    _self->format = Arcadia_Value_getInteger32Value(&argumentValues[1]);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, _self, _type);
}

static void
ImageWriterParameters_visit
  (
    Arcadia_Thread* thread,
    ImageWriterParameters* self
  )
{ Arcadia_Object_visit(thread, self->object); }

static void
ImageWriterParameters_destruct
  (
    Arcadia_Thread* thread,
    ImageWriterParameters* self
  )
{/*Intentionally empty.*/}

ImageWriterParameters*
ImageWriterParameters_createFile
  (
    Arcadia_Thread* thread,
    Arcadia_String* path,
    ImageWriterFormat format
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = path },
                               {.tag = Arcadia_ValueTag_Integer32, .integer32Value = format }, };
  ImageWriterParameters* self = Arcadia_allocateObject(thread, _ImageWriterParameters_getType(thread), 2, &argumentValues[0]);
  return self;
}

ImageWriterParameters*
ImageWriterParameters_createByteBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* byteBuffer,
    ImageWriterFormat format
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = byteBuffer },
                               {.tag = Arcadia_ValueTag_Integer32, .integer32Value = format }, };
  ImageWriterParameters* self = Arcadia_allocateObject(thread, _ImageWriterParameters_getType(thread), 2, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
ImageWriterParameters_hasPath
  (
    Arcadia_Thread* thread,
    ImageWriterParameters* self
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(self->object);
  return Arcadia_Type_isSubType(thread, type, _Arcadia_String_getType(thread));
}

Arcadia_String*
ImageWriterParameters_getPath
  (
    Arcadia_Thread* thread,
    ImageWriterParameters* self
  )
{
  if (!ImageWriterParameters_hasPath(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_String*)self->object;
}

Arcadia_BooleanValue
ImageWriterParameters_hasByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriterParameters* self
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(self->object);
  return Arcadia_Type_isSubType(thread, type, _Arcadia_ByteBuffer_getType(thread));
}

Arcadia_ByteBuffer*
ImageWriterParameters_getByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriterParameters* self
  )
{
  if (!ImageWriterParameters_hasByteBuffer(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_ByteBuffer*)self->object;
}

ImageWriterFormat
ImageWriterParameters_getFormat
  (
    Arcadia_Thread* thread,
    ImageWriterParameters* self
  )
{
  return self->format;
}
