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

#include "R/StringBuffer.h"

#include "R/Utf8/EncodeCodePoints.h"
#include "R/cstdlib.h"
#include "R/ArmsIntegration.h"
#include "R.h"

static void
R_StringBuffer_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_StringBuffer_destruct
  (
    Arcadia_Process* process,
    R_StringBuffer* self
  );

static void
ensureFreeCapacityBytes
  (
    Arcadia_Process* process,
    R_StringBuffer* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

// Warning: This function does not validate parameters.
static void
appendBytesInternal
  (
    Arcadia_Process* process,
    R_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_StringBuffer_constructImpl,
  .destruct = &R_StringBuffer_destruct,
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

Rex_defineObjectType(u8"R.StringBuffer", R_StringBuffer, u8"R.Object", R_Object, &_typeOperations);

static void
R_StringBuffer_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_StringBuffer* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_StringBuffer_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->elements = NULL;
  _self->size = 0;
  _self->capacity = 0;
  if (!R_allocateUnmanaged_nojump(process, &_self->elements, 0)) {
    Arcadia_Process_jump(process);
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_StringBuffer_destruct
  (
    Arcadia_Process* process,
    R_StringBuffer* self
  )
{
  if (self->elements) {
    R_deallocateUnmanaged_nojump(process, self->elements);
    self->elements = NULL;
  }
}

static void
ensureFreeCapacityBytes
  (
    Arcadia_Process* process,
    R_StringBuffer* self,
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
    if (!R_reallocateUnmanaged_nojump(process, &self->elements, newCapacity)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
      Arcadia_Process_jump(process);
    }
    self->capacity = newCapacity;
  }
}

static void
appendBytesInternal
  (
    Arcadia_Process* process,
    R_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  ensureFreeCapacityBytes(process, self, numberOfBytes);
  c_memcpy(self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

R_StringBuffer*
R_StringBuffer_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_StringBuffer* self = R_allocateObject(process, _R_StringBuffer_getType(process), 0, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
R_StringBuffer_endsWith_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->size < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = self->size - numberOfBytes;
  return !c_memcmp(self->elements + d, bytes, numberOfBytes);
}

Arcadia_BooleanValue
R_StringBuffer_startsWith_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->size < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !c_memcmp(self->elements, bytes, numberOfBytes);
}

void
R_StringBuffer_append_pn
  (
    Arcadia_Process* process,
    R_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!bytes) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (!R_isUtf8(bytes, numberOfBytes, NULL)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
    Arcadia_Process_jump(process);
  }
  ensureFreeCapacityBytes(process, self, numberOfBytes);
  c_memcpy(self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

void
R_StringBuffer_append
  (
    Arcadia_Process* process,
    R_StringBuffer* self,
    R_Value value
  )
{
  if (!R_Value_isObjectReferenceValue(&value)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  R_ObjectReferenceValue referenceValue = R_Value_getObjectReferenceValue(&value);
  if (Arcadia_Type_isSubType(R_Object_getType(referenceValue), _R_ByteBuffer_getType(process))) {
    R_ByteBuffer* object = (R_ByteBuffer*)referenceValue;
    if (!R_isUtf8(R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object), NULL)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
    ensureFreeCapacityBytes(process, self, R_ByteBuffer_getNumberOfBytes(object));
    c_memcpy(self->elements + self->size, R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object));
    self->size += R_ByteBuffer_getNumberOfBytes(object);
  } else if (Arcadia_Type_isSubType(R_Object_getType(referenceValue), _R_String_getType(process))) {
    R_String* object = (R_String*)referenceValue;
    // The Byte sequence of R.String is guaranteed to be an UTF8 Byte sequence.
    ensureFreeCapacityBytes(process, self, R_String_getNumberOfBytes(object));
    c_memcpy(self->elements + self->size, R_String_getBytes(object), R_String_getNumberOfBytes(object));
    self->size += R_String_getNumberOfBytes(object);
  } else if (Arcadia_Type_isSubType(R_Object_getType(referenceValue), _R_StringBuffer_getType(process))) {
    R_StringBuffer* object = (R_StringBuffer*)referenceValue;
    // The Byte sequence of R.StringBuffer is guaranteed to be an UTF8 Byte sequence.
    ensureFreeCapacityBytes(process, self, R_StringBuffer_getNumberOfBytes(object));
    c_memcpy(self->elements + self->size, R_StringBuffer_getBytes(object), R_StringBuffer_getNumberOfBytes(object));
    self->size += R_StringBuffer_getNumberOfBytes(object);
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

void
R_StringBuffer_appendCodePoints
  (
    Arcadia_Process* process,
    R_StringBuffer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  R_Utf8_encodeCodePoints(process, codePoints, numberOfCodePoints, self, (void (*)(Arcadia_Process*, void*, Arcadia_Natural8Value const*, Arcadia_SizeValue))&appendBytesInternal);
}

Arcadia_BooleanValue
R_StringBuffer_isEqualTo
  (
    R_StringBuffer* self,
    R_StringBuffer* other
  )
{
  if (self == other) {
    return Arcadia_BooleanValue_True;
  }
  if (self->size == other->size) {
    return !c_memcmp(self->elements, other->elements, self->size);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

void
R_StringBuffer_clear
  (
    R_StringBuffer* self
  )
{ self->size = 0; }

Arcadia_SizeValue
R_StringBuffer_getNumberOfBytes
  (
    R_StringBuffer const* self
  )
{ return self->size; }

Arcadia_Natural8Value const*
R_StringBuffer_getBytes
  (
    R_StringBuffer const* self
  )
{ return self->elements; }
