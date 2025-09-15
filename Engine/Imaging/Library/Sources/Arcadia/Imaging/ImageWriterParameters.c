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

#include "Arcadia/Imaging/ImageWriterParameters.h"

struct Arcadia_Imaging_ImageWriterParameters {
  Arcadia_Object _parent;
  // The format string.
  Arcadia_String* format;
  // "object" either refers to a "Arcadia.ByteBuffer" object or a "Arcadia.Path" object.
  Arcadia_ObjectReferenceValue object;
};

static void
Arcadia_Imaging_ImageWriterParameters_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Imaging_ImageWriterParameters_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  );

static void
Arcadia_Imaging_ImageWriterParameters_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Imaging_ImageWriterParameters_constructImpl,
  .destruct = &Arcadia_Imaging_ImageWriterParameters_destruct,
  .visit = &Arcadia_Imaging_ImageWriterParameters_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.ImageWriterParameters", Arcadia_Imaging_ImageWriterParameters,
                         u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Imaging_ImageWriterParameters_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Imaging_ImageWriterParameters* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Imaging_ImageWriterParameters_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object* object = Arcadia_ValueStack_getObjectReferenceValue(thread, 2);
  if (Arcadia_Object_isInstanceOf(thread, object, _Arcadia_String_getType(thread))) {
    _self->object = (Arcadia_ObjectReferenceValue)object;
  } else if (Arcadia_Object_isInstanceOf(thread, object, _Arcadia_ByteBuffer_getType(thread))) {
    _self->object = (Arcadia_ObjectReferenceValue)object;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->format = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_Imaging_ImageWriterParameters_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  )
{
  if (self->format) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->format);
  }
  if (self->object) {
    Arcadia_Object_visit(thread, self->object);
  }
}

static void
Arcadia_Imaging_ImageWriterParameters_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  )
{/*Intentionally empty.*/}

Arcadia_Imaging_ImageWriterParameters*
Arcadia_Imaging_ImageWriterParameters_createFile
  (
    Arcadia_Thread* thread,
    Arcadia_String* path,
    Arcadia_String* format
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (path) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, path);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (format) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, format);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Imaging_ImageWriterParameters);
}

Arcadia_Imaging_ImageWriterParameters*
Arcadia_Imaging_ImageWriterParameters_createByteBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* byteBuffer,
    Arcadia_String* format
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (byteBuffer) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, byteBuffer);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (format) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, format);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Imaging_ImageWriterParameters);
}

Arcadia_BooleanValue
Arcadia_Imaging_ImageWriterParameters_hasPath
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(thread, self->object);
  return Arcadia_Type_isSubType(thread, type, _Arcadia_String_getType(thread));
}

Arcadia_String*
Arcadia_Imaging_ImageWriterParameters_getPath
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  )
{
  if (!Arcadia_Imaging_ImageWriterParameters_hasPath(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_String*)self->object;
}

Arcadia_BooleanValue
Arcadia_Imaging_ImageWriterParameters_hasByteBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(thread, self->object);
  return Arcadia_Type_isSubType(thread, type, _Arcadia_ByteBuffer_getType(thread));
}

Arcadia_ByteBuffer*
Arcadia_Imaging_ImageWriterParameters_getByteBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  )
{
  if (!Arcadia_Imaging_ImageWriterParameters_hasByteBuffer(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return (Arcadia_ByteBuffer*)self->object;
}

Arcadia_String*
Arcadia_Imaging_ImageWriterParameters_getFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  )
{
  return self->format;
}
