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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Implementation/StringBuffer.h"

#include "Arcadia/Ring2/Include.h"

/// @param offset [out] Pointer to an Arcadia_SizeValue variable.
/// That variable is assigned
/// - the offset of the first Byte of the code point at the code point index if that code point index is within bounds.
/// - @a n otherwise where @a n is the number of Bytes in the buffer.
/// @return #Arcadia_BooleanValue_True if the code point index is within bounds. #Arcadia_BooleanValue_False otherwise.
static Arcadia_BooleanValue
getOffsetFromFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue codePointIndex,
    Arcadia_SizeValue* offset
  );

/// @param offset [out] Pointer to an Arcadia_SizeValue variable.
/// That variable is assigned
/// - the offset of the first Byte behind the Bytes of the code point at the code point index if that code point index is within bounds.
/// - @a 0 otherwise.
/// @return #Arcadia_BooleanValue_True if the code point index is within bounds. #Arcadia_BooleanValue_False otherwise.
static Arcadia_BooleanValue
getOffsetFromBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue codePointIndex,
    Arcadia_SizeValue* offset
  );

static void
Arcadia_StringBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_StringBuffer_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self
  );

static void
ensureFreeCapacityBytes
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

// Warning: This function does not check if the Bytes are UTF-8 Bytes.
static void
prependBytesInternal
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// Warning: This function does not check if the Bytes are UTF-8 Bytes.
static void
appendBytesInternal
  (
    Arcadia_Thread* thread,
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
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.StringBuffer", Arcadia_StringBuffer, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static Arcadia_BooleanValue
getOffsetFromFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue codePointIndex,
    Arcadia_SizeValue* offset
  )
{
  // Warning: This assumes valid UTF-8 Byte sequences. However: Arcadia_StringBuffer only holds valid UTF-8 Byte sequences.
  const Arcadia_Natural8Value* start = self->elements;
  const Arcadia_Natural8Value* end = self->elements + self->size;
  const Arcadia_Natural8Value* current = self->elements;
  Arcadia_SizeValue currentCodePointIndex = 0;
  while (currentCodePointIndex != codePointIndex && current != end) {
    const Arcadia_Natural8Value x = *current;
    if ((x & 0x80) == 0x00) {
      current += 1;
    } else if ((x & 0xE0) == 0xC0) {
      current += 2;
    } else if ((x & 0xF0) == 0xE0) {
      current += 3;
    } else /*if ((x & 0xF8) == 0xF0)*/ {
      current += 4;
    }
    currentCodePointIndex++;
  }
  *offset = current - start;
  return currentCodePointIndex == codePointIndex;
}

static Arcadia_BooleanValue
getOffsetFromBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue codePointIndex,
    Arcadia_SizeValue* offset
  )
{
  // Warning: This assumes valid UTF-8 Byte sequences. However: Arcadia_StringBuffer only holds valid UTF-8 Byte sequences.
  const Arcadia_Natural8Value* end = self->elements;
  const Arcadia_Natural8Value* start = self->elements + self->size;
  const Arcadia_Natural8Value* current = start;

  Arcadia_SizeValue currentCodePointIndex = 0;
  while (currentCodePointIndex != codePointIndex && current != end) {
    current--;
    while (((*current) & 0xC0) == 0x80) {
      current--;
    }
    currentCodePointIndex++;
  }
  *offset = start - current;
  return currentCodePointIndex == codePointIndex;
}

static void
Arcadia_StringBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_StringBuffer* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_StringBuffer_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->elements = NULL;
  _self->size = 0;
  _self->capacity = 0;
  _self->elements = Arcadia_Memory_allocateUnmanaged(thread, 0);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_StringBuffer_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self
  )
{
  if (self->elements) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->elements);
    self->elements = NULL;
  }
}

static void
ensureFreeCapacityBytes
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue requiredFreeCapacity
  )
{
  Arcadia_SizeValue availableFreeCapacity = self->capacity - self->size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    Arcadia_SizeValue additionalCapacity = requiredFreeCapacity - availableFreeCapacity;
    Arcadia_SizeValue oldCapacity = self->capacity;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_SizeValue newCapacity = oldCapacity + additionalCapacity;
    Arcadia_Memory_reallocateUnmanaged(thread, &self->elements, newCapacity);
    self->capacity = newCapacity;
  }
}

static void
prependBytesInternal
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  ensureFreeCapacityBytes(thread, self, numberOfBytes);
  Arcadia_Memory_copy(thread, self->elements + numberOfBytes, self->elements, self->size);
  Arcadia_Memory_copy(thread, self->elements, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

static void
appendBytesInternal
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  ensureFreeCapacityBytes(thread, self, numberOfBytes);
  Arcadia_Memory_copy(thread, self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

Arcadia_StringBuffer*
Arcadia_StringBuffer_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_StringBuffer* self = Arcadia_allocateObject(thread, _Arcadia_StringBuffer_getType(thread), 0, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
Arcadia_StringBuffer_endsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->size < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = self->size - numberOfBytes;
  return !Arcadia_Memory_compare(thread, self->elements + d, bytes, numberOfBytes);
}

Arcadia_BooleanValue
Arcadia_StringBuffer_startsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->size < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !Arcadia_Memory_compare(thread, self->elements, bytes, numberOfBytes);
}

void
Arcadia_StringBuffer_append_pn
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!bytes) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Unicode_isUtf8(thread, bytes, numberOfBytes, NULL)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
    Arcadia_Thread_jump(thread);
  }
  ensureFreeCapacityBytes(thread, self, numberOfBytes);
  Arcadia_Memory_copy(thread, self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

void
Arcadia_StringBuffer_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue codePointIndex,
    Arcadia_Value value
  )
{
  Arcadia_SizeValue byteIndex = 0;
  if (!getOffsetFromFront(thread, self, codePointIndex, &byteIndex)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // byteIndex is the index at which to insert the elements
  Arcadia_Type* type = Arcadia_Value_getType(thread, &value);
  Arcadia_Natural8Value const* p = NULL;
  Arcadia_SizeValue n = 0;
  if (Arcadia_Type_isSubType(thread, type, _Arcadia_ImmutableUtf8StringValue_getType(thread))) {
    // The Byte sequence of Arcadia.ImmutableUtf8String is guaranteed to be an UTF8 Byte sequence.
    Arcadia_ImmutableUtf8String* object = (Arcadia_ImmutableUtf8String*)Arcadia_Value_getImmutableUtf8StringValue(&value);
    n = Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, object);
    p = Arcadia_ImmutableUtf8String_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_ImmutableByteArrayValue_getType(thread))) {
    Arcadia_ImmutableByteArray* object = (Arcadia_ImmutableByteArray*)Arcadia_Value_getImmutableByteArrayValue(&value);
    if (!Arcadia_Unicode_isUtf8(thread, p, n, NULL)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(thread);
    }
    n = Arcadia_ImmutableByteArray_getNumberOfBytes(thread, object);
    p = Arcadia_ImmutableByteArray_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_ByteBuffer_getType(thread))) {
    Arcadia_ByteBuffer* object = (Arcadia_ByteBuffer*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_ByteBuffer_getNumberOfBytes(thread, object);
    p = Arcadia_ByteBuffer_getBytes(thread, object);
    if (!Arcadia_Unicode_isUtf8(thread, p, n, NULL)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(thread);
    }
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_String_getType(thread))) {
    // The Byte sequence of Arcadia.String is guaranteed to be an UTF8 Byte sequence.
    Arcadia_String* object = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_String_getNumberOfBytes(thread, object);
    p = Arcadia_String_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_StringBuffer_getType(thread))) {
    // The Byte sequence of Arcadia.StringBuffer is guaranteed to be an UTF8 Byte sequence.
    Arcadia_StringBuffer* object = (Arcadia_StringBuffer*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_StringBuffer_getNumberOfBytes(thread, object);
    p = Arcadia_StringBuffer_getBytes(thread, object);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  ensureFreeCapacityBytes(thread, self, n);
  if (byteIndex < self->size) {
    Arcadia_Memory_copy(thread, self->elements + byteIndex, self->elements + byteIndex + n, self->size - byteIndex);
  }
  Arcadia_Memory_copy(thread, self->elements + byteIndex, p, n);
  self->size += n;
}

void
Arcadia_StringBuffer_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Value value
  )
{
  Arcadia_Type* type = Arcadia_Value_getType(thread, &value);
  Arcadia_Natural8Value const* p = NULL;
  Arcadia_SizeValue n = 0;
  if (Arcadia_Type_isSubType(thread, type, _Arcadia_ImmutableUtf8StringValue_getType(thread))) {
    // The Byte sequence of Arcadia.ImmutableUtf8String is guaranteed to be an UTF8 Byte sequence.
    Arcadia_ImmutableUtf8String* object = (Arcadia_ImmutableUtf8String*)Arcadia_Value_getImmutableUtf8StringValue(&value);
    n = Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, object);
    p = Arcadia_ImmutableUtf8String_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_ImmutableByteArrayValue_getType(thread))) {
    Arcadia_ImmutableByteArray* object = (Arcadia_ImmutableByteArray*)Arcadia_Value_getImmutableByteArrayValue(&value);
    n = Arcadia_ImmutableByteArray_getNumberOfBytes(thread, object);
    p = Arcadia_ImmutableByteArray_getBytes(thread, object);
    if (!Arcadia_Unicode_isUtf8(thread, p, n, NULL)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(thread);
    }
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_ByteBuffer_getType(thread))) {
    Arcadia_ByteBuffer* object = (Arcadia_ByteBuffer*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_ByteBuffer_getNumberOfBytes(thread, object);
    p = Arcadia_ByteBuffer_getBytes(thread, object);
    if (!Arcadia_Unicode_isUtf8(thread, p, n, NULL)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(thread);
    }
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_String_getType(thread))) {
    // The Byte sequence of Arcadia.String is guaranteed to be an UTF8 Byte sequence.
    Arcadia_String* object = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_String_getNumberOfBytes(thread, object);
    p = Arcadia_String_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_StringBuffer_getType(thread))) {
    // The Byte sequence of Arcadia.StringBuffer is guaranteed to be an UTF8 Byte sequence.
    Arcadia_StringBuffer* object = (Arcadia_StringBuffer*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_StringBuffer_getNumberOfBytes(thread, object);
    p = Arcadia_StringBuffer_getBytes(thread, object);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  ensureFreeCapacityBytes(thread, self, n);
  Arcadia_Memory_copy(thread, self->elements + self->size, p, n);
  self->size += n;
}

void
Arcadia_StringBuffer_insertFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Value value
  )
{
  Arcadia_Type* type = Arcadia_Value_getType(thread, &value);
  Arcadia_Natural8Value const* p = NULL;
  Arcadia_SizeValue n = 0;
  if (Arcadia_Type_isSubType(thread, type, _Arcadia_ImmutableUtf8StringValue_getType(thread))) {
    // The Byte sequence of Arcadia.ImmutableUtf8String is guaranteed to be an UTF8 Byte sequence.
    Arcadia_ImmutableUtf8String* object = (Arcadia_ImmutableUtf8String*)Arcadia_Value_getImmutableUtf8StringValue(&value);
    n = Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, object);
    p = Arcadia_ImmutableUtf8String_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_ImmutableByteArrayValue_getType(thread))) {
    Arcadia_ImmutableByteArray* object = (Arcadia_ImmutableByteArray*)Arcadia_Value_getImmutableByteArrayValue(&value);
    if (!Arcadia_Unicode_isUtf8(thread, p, n, NULL)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(thread);
    }
    n = Arcadia_ImmutableByteArray_getNumberOfBytes(thread, object);
    p = Arcadia_ImmutableByteArray_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_ByteBuffer_getType(thread))) {
    Arcadia_ByteBuffer* object = (Arcadia_ByteBuffer*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_ByteBuffer_getNumberOfBytes(thread, object);
    p = Arcadia_ByteBuffer_getBytes(thread, object);
    if (!Arcadia_Unicode_isUtf8(thread, p, n, NULL)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(thread);
    }
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_String_getType(thread))) {
    // The Byte sequence of Arcadia.String is guaranteed to be an UTF8 Byte sequence.
    Arcadia_String* object = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_String_getNumberOfBytes(thread, object);
    p = Arcadia_String_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_StringBuffer_getType(thread))) {
    // The Byte sequence of Arcadia.StringBuffer is guaranteed to be an UTF8 Byte sequence.
    Arcadia_StringBuffer* object = (Arcadia_StringBuffer*)Arcadia_Value_getObjectReferenceValue(&value);
    n = Arcadia_StringBuffer_getNumberOfBytes(thread, object);
    p = Arcadia_StringBuffer_getBytes(thread, object);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  ensureFreeCapacityBytes(thread, self, n);
  Arcadia_Memory_copy(thread, self->elements + n, self->elements, self->size);
  Arcadia_Memory_copy(thread, self->elements, p, n);
  self->size += n;
}

void
Arcadia_StringBuffer_insertCodePointsBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  Arcadia_Unicode_encodeCodePointsUtf8(thread, codePoints, numberOfCodePoints, self, (Arcadia_Unicode_EncodeCodePointCallbackFunction*)&appendBytesInternal);
}

void
Arcadia_StringBuffer_insertCodePointsFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  Arcadia_StringBuffer* temporary = Arcadia_StringBuffer_create(thread);
  Arcadia_Unicode_encodeCodePointsUtf8(thread, codePoints, numberOfCodePoints, temporary, (Arcadia_Unicode_EncodeCodePointCallbackFunction*)&appendBytesInternal);
  prependBytesInternal(thread, self, Arcadia_StringBuffer_getBytes(thread, temporary), Arcadia_StringBuffer_getNumberOfBytes(thread, temporary));
}

Arcadia_Integer32Value
Arcadia_StringBuffer_compareTo
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Value other
  )
{
  Arcadia_Type* type = Arcadia_Value_getType(thread, &other);
  Arcadia_Natural8Value const* p = NULL;
  Arcadia_SizeValue n = 0;
  if (Arcadia_Type_isSubType(thread, type, _Arcadia_ImmutableUtf8StringValue_getType(thread))) {
    // The Byte sequence of Arcadia.ImmutableUtf8String is guaranteed to be an UTF8 Byte sequence.
    Arcadia_ImmutableUtf8String* object = (Arcadia_ImmutableUtf8String*)Arcadia_Value_getImmutableUtf8StringValue(&other);
    n = Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, object);
    p = Arcadia_ImmutableUtf8String_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_String_getType(thread))) {
    // The Byte sequence of Arcadia.String is guaranteed to be an UTF8 Byte sequence.
    Arcadia_String* object = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&other);
    n = Arcadia_String_getNumberOfBytes(thread, object);
    p = Arcadia_String_getBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, type, _Arcadia_StringBuffer_getType(thread))) {
    // The Byte sequence of Arcadia.StringBuffer is guaranteed to be an UTF8 Byte sequence.
    Arcadia_StringBuffer* object = (Arcadia_StringBuffer*)Arcadia_Value_getObjectReferenceValue(&other);
    n = Arcadia_StringBuffer_getNumberOfBytes(thread, object);
    p = Arcadia_StringBuffer_getBytes(thread, object);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue k = n <= self->size ? n : self->size;
  Arcadia_Integer32Value result = Arcadia_Memory_compare(thread, self->elements, p, k);
  if (result) {
    return result;
  }
  if (n < self->size) {
    return -1;
  } else if (n > self->size) {
    return +1;
  } else {
    return 0;
  }
}

void
Arcadia_StringBuffer_clear
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self
  )
{ self->size = 0; }

Arcadia_SizeValue
Arcadia_StringBuffer_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer const* self
  )
{ return self->size; }

Arcadia_Natural8Value const*
Arcadia_StringBuffer_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer const* self
  )
{ return self->elements; }

void
Arcadia_StringBuffer_removeCodePointsFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  Arcadia_SizeValue offset;
  if (!getOffsetFromFront(thread, self, numberOfCodePoints, &offset)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (offset < self->size) {
    Arcadia_Memory_copy(thread, self->elements, self->elements + offset, self->size - offset);
  }
  self->size -= offset;
}

void
Arcadia_StringBuffer_removeCodePointsBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  Arcadia_SizeValue offset;
  if (!getOffsetFromBack(thread, self, numberOfCodePoints, &offset)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->size -= offset;
}
