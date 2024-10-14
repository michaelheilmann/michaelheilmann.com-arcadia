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

// Last modified: 2024-09-22

#include "R/StringBuffer.h"

#include "R/Utf8/EncodeCodePoints.h"
#include <string.h>
#include "R/ArmsIntegration.h"
#include "R.h"

static void
R_StringBuffer_destruct
  (
    R_StringBuffer* self
  );

static void
ensureFreeCapacityBytes
  (
    R_StringBuffer* self,
    R_SizeValue requiredFreeCapacity
  );

// Warning: This function does not validate parameters.
static void
appendBytesInternal
  (
    R_StringBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

static void
R_StringBuffer_destruct
  (
    R_StringBuffer* self
  )
{
  if (self->elements) {
    R_Arms_deallocateUnmanaged_nojump(self->elements);
    self->elements = NULL;
  }
}

static void
ensureFreeCapacityBytes
  (
    R_StringBuffer* self,
    R_SizeValue requiredFreeCapacity
  )
{
  R_SizeValue availableFreeCapacity = self->capacity - self->size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    R_SizeValue additionalCapacity = requiredFreeCapacity - availableFreeCapacity;
    R_SizeValue oldCapacity = self->capacity;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    R_SizeValue newCapacity = oldCapacity + additionalCapacity;
    if (!R_Arms_reallocateUnmanaged_nojump(&self->elements, newCapacity)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    self->capacity = newCapacity;
  }
}

static void
appendBytesInternal
  (
    R_StringBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  ensureFreeCapacityBytes(self, numberOfBytes);
  memcpy(self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

Rex_defineObjectType("R.StringBuffer", R_StringBuffer, "R.Object", R_Object, NULL, &R_StringBuffer_destruct);

void
R_StringBuffer_construct
  (
    R_StringBuffer* self
  )
{
  R_Type* _type = _R_StringBuffer_getType();
  R_Object_construct((R_Object*)self);
  self->elements = NULL;
  self->size = 0;
  self->capacity = 0;
  if (!R_Arms_allocateUnmanaged_nojump(&self->elements, 0)) {
    R_jump();
  }
  R_Object_setType((R_Object*)self, _type);
}

R_StringBuffer*
R_StringBuffer_create
  (
  )
{
  R_Type* _type = _R_StringBuffer_getType();
  R_StringBuffer* self = R_allocateObject(_type);
  R_StringBuffer_construct(self);
  return self;
}

R_BooleanValue
R_StringBuffer_endsWith_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->size < numberOfBytes) {
    return R_BooleanValue_False;
  }
  R_SizeValue d = self->size - numberOfBytes;
  return !memcmp(self->elements + d, bytes, numberOfBytes);
}

R_BooleanValue
R_StringBuffer_startsWith_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->size < numberOfBytes) {
    return R_BooleanValue_False;
  }
  return !memcmp(self->elements, bytes, numberOfBytes);
}

void
R_StringBuffer_append_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!bytes) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!R_isUtf8(bytes, numberOfBytes, NULL)) {
    R_setStatus(R_Status_EncodingInvalid);
    R_jump();
  }
  ensureFreeCapacityBytes(self, numberOfBytes);
  memcpy(self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

void
R_StringBuffer_append
  (
    R_StringBuffer* self,
    R_Value value
  )
{
  if (!R_Value_isObjectReferenceValue(&value)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_ObjectReferenceValue referenceValue = R_Value_getObjectReferenceValue(&value);
  if (R_Type_isSubType(R_Object_getType(referenceValue), _R_ByteBuffer_getType())) {
    R_ByteBuffer* object = (R_ByteBuffer*)referenceValue;
    if (!R_isUtf8(R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object), NULL)) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
    ensureFreeCapacityBytes(self, R_ByteBuffer_getNumberOfBytes(object));
    memcpy(self->elements + self->size, R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object));
    self->size += R_ByteBuffer_getNumberOfBytes(object);
  } else if (R_Type_isSubType(R_Object_getType(referenceValue), _R_String_getType())) {
    R_String* object = (R_String*)referenceValue;
    // The Byte sequence of R.String is guaranteed to be an UTF8 Byte sequence.
    ensureFreeCapacityBytes(self, R_String_getNumberOfBytes(object));
    memcpy(self->elements + self->size, R_String_getBytes(object), R_String_getNumberOfBytes(object));
    self->size += R_String_getNumberOfBytes(object);
  } else if (R_Type_isSubType(R_Object_getType(referenceValue), _R_StringBuffer_getType())) {
    R_StringBuffer* object = (R_StringBuffer*)referenceValue;
    // The Byte sequence of R.StringBuffer is guaranteed to be an UTF8 Byte sequence.
    ensureFreeCapacityBytes(self, R_StringBuffer_getNumberOfBytes(object));
    memcpy(self->elements + self->size, R_StringBuffer_getBytes(object), R_StringBuffer_getNumberOfBytes(object));
    self->size += R_StringBuffer_getNumberOfBytes(object);
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

void
R_StringBuffer_appendCodePoints
  (
    R_StringBuffer* self,
    R_Natural32Value const* codePoints,
    R_SizeValue numberOfCodePoints
  )
{
  R_Utf8_encodeCodePoints(codePoints, numberOfCodePoints, self, (void (*)(void*, R_Natural8Value const*, R_SizeValue))&appendBytesInternal);
}

R_BooleanValue
R_StringBuffer_isEqualTo
  (
    R_StringBuffer* self,
    R_StringBuffer* other
  )
{
  if (self == other) {
    return R_BooleanValue_True;
  }
  if (self->size == other->size) {
    return !memcmp(self->elements, other->elements, self->size);
  } else {
    return R_BooleanValue_False;
  }
}

void
R_StringBuffer_clear
  (
    R_StringBuffer* self
  )
{
  self->size = 0;
}

R_SizeValue
R_StringBuffer_getNumberOfBytes
  (
    R_StringBuffer const* self
  )
{ return self->size; }

R_Natural8Value const*
R_StringBuffer_getBytes
  (
    R_StringBuffer const* self
  )
{ return self->elements; }