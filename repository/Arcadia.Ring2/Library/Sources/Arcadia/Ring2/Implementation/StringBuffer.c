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

// Last modified: 2024-09-22

#include "Arcadia/Ring2/Implementation/StringBuffer.h"

#include "R/Utf8/EncodeCodePoints.h"
#include "Arcadia/Ring2/Include.h"

static void
Arcadia_StringBuffer_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_StringBuffer_destruct
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self
  );

static void
ensureFreeCapacityBytes
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

// Warning: This function does not validate parameters.
static void
appendBytesInternal
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_StringBuffer_constructImpl,
  .destruct = &Arcadia_StringBuffer_destruct,
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

Rex_defineObjectType(u8"Arcadia.StringBuffer", Arcadia_StringBuffer, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_StringBuffer_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_StringBuffer* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_StringBuffer_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->elements = NULL;
  _self->size = 0;
  _self->capacity = 0;
  Arcadia_Process_allocateUnmanaged(process, &_self->elements, 0);
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_StringBuffer_destruct
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self
  )
{
  if (self->elements) {
    Arcadia_Process_deallocateUnmanaged(process, self->elements);
    self->elements = NULL;
  }
}

static void
ensureFreeCapacityBytes
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue requiredFreeCapacity
  )
{
  Arcadia_SizeValue availableFreeCapacity = self->capacity - self->size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    Arcadia_SizeValue additionalCapacity = requiredFreeCapacity - availableFreeCapacity;
    Arcadia_SizeValue oldCapacity = self->capacity;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
      Arcadia_Process_jump(process);
    }
    Arcadia_SizeValue newCapacity = oldCapacity + additionalCapacity;
    Arcadia_Process_reallocateUnmanaged(process, &self->elements, newCapacity);
    self->capacity = newCapacity;
  }
}

static void
appendBytesInternal
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  ensureFreeCapacityBytes(process, self, numberOfBytes);
  Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

Arcadia_StringBuffer*
Arcadia_StringBuffer_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_StringBuffer* self = R_allocateObject(process, _Arcadia_StringBuffer_getType(process), 0, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
Arcadia_StringBuffer_endsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->size < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = self->size - numberOfBytes;
  return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), self->elements + d, bytes, numberOfBytes);
}

Arcadia_BooleanValue
Arcadia_StringBuffer_startsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->size < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), self->elements, bytes, numberOfBytes);
}

void
Arcadia_StringBuffer_append_pn
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!bytes) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_isUtf8(process, bytes, numberOfBytes, NULL)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
    Arcadia_Process_jump(process);
  }
  ensureFreeCapacityBytes(process, self, numberOfBytes);
  Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

void
Arcadia_StringBuffer_append
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    Arcadia_Value value
  )
{
  if (!Arcadia_Value_isObjectReferenceValue(&value)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_ObjectReferenceValue referenceValue = Arcadia_Value_getObjectReferenceValue(&value);
  if (Arcadia_Type_isSubType(Arcadia_Object_getType(referenceValue), _Arcadia_ByteBuffer_getType(process))) {
    Arcadia_ByteBuffer* object = (Arcadia_ByteBuffer*)referenceValue;
    if (!Arcadia_isUtf8(process, Arcadia_ByteBuffer_getBytes(process, object), Arcadia_ByteBuffer_getNumberOfBytes(process, object), NULL)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
    ensureFreeCapacityBytes(process, self, Arcadia_ByteBuffer_getNumberOfBytes(process, object));
    Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), self->elements + self->size, Arcadia_ByteBuffer_getBytes(process, object), Arcadia_ByteBuffer_getNumberOfBytes(process, object));
    self->size += Arcadia_ByteBuffer_getNumberOfBytes(process, object);
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(referenceValue), _Arcadia_String_getType(process))) {
    Arcadia_String* object = (Arcadia_String*)referenceValue;
    // The Byte sequence of Arcadia.String is guaranteed to be an UTF8 Byte sequence.
    ensureFreeCapacityBytes(process, self, Arcadia_String_getNumberOfBytes(process, object));
    Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), self->elements + self->size, Arcadia_String_getBytes(process, object), Arcadia_String_getNumberOfBytes(process, object));
    self->size += Arcadia_String_getNumberOfBytes(process, object);
  } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(referenceValue), _Arcadia_StringBuffer_getType(process))) {
    Arcadia_StringBuffer* object = (Arcadia_StringBuffer*)referenceValue;
    // The Byte sequence of Arcadia.StringBuffer is guaranteed to be an UTF8 Byte sequence.
    ensureFreeCapacityBytes(process, self, Arcadia_StringBuffer_getNumberOfBytes(object));
    Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), self->elements + self->size, Arcadia_StringBuffer_getBytes(object), Arcadia_StringBuffer_getNumberOfBytes(object));
    self->size += Arcadia_StringBuffer_getNumberOfBytes(object);
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

void
Arcadia_StringBuffer_appendCodePoints
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  R_Utf8_encodeCodePoints(process, codePoints, numberOfCodePoints, self, (void (*)(Arcadia_Process*, void*, Arcadia_Natural8Value const*, Arcadia_SizeValue))&appendBytesInternal);
}

Arcadia_BooleanValue
Arcadia_StringBuffer_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    Arcadia_StringBuffer* other
  )
{
  if (self == other) {
    return Arcadia_BooleanValue_True;
  }
  if (self->size == other->size) {
    return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), self->elements, other->elements, self->size);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

void
Arcadia_StringBuffer_clear
  (
    Arcadia_StringBuffer* self
  )
{ self->size = 0; }

Arcadia_SizeValue
Arcadia_StringBuffer_getNumberOfBytes
  (
    Arcadia_StringBuffer const* self
  )
{ return self->size; }

Arcadia_Natural8Value const*
Arcadia_StringBuffer_getBytes
  (
    Arcadia_StringBuffer const* self
  )
{ return self->elements; }
