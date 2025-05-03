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

// Warning: This function does not validate parameters.
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

Arcadia_defineObjectType(u8"Arcadia.StringBuffer", Arcadia_StringBuffer, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

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
  Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &_self->elements, 0);
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
    Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), self->elements);
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
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  Arcadia_SizeValue availableFreeCapacity = self->capacity - self->size;
  if (availableFreeCapacity < requiredFreeCapacity) {
    Arcadia_SizeValue additionalCapacity = requiredFreeCapacity - availableFreeCapacity;
    Arcadia_SizeValue oldCapacity = self->capacity;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_SizeValue newCapacity = oldCapacity + additionalCapacity;
    Arcadia_Process_reallocateUnmanaged(process, &self->elements, newCapacity);
    self->capacity = newCapacity;
  }
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
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  ensureFreeCapacityBytes(thread, self, numberOfBytes);
  Arcadia_Process_copyMemory(process, self->elements + self->size, bytes, numberOfBytes);
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
  return !Arcadia_Process_compareMemory(Arcadia_Thread_getProcess(thread), self->elements + d, bytes, numberOfBytes);
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
  return !Arcadia_Process_compareMemory(Arcadia_Thread_getProcess(thread), self->elements, bytes, numberOfBytes);
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
  if (!Arcadia_isUtf8(thread, bytes, numberOfBytes, NULL)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
    Arcadia_Thread_jump(thread);
  }
  ensureFreeCapacityBytes(thread, self, numberOfBytes);
  Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), self->elements + self->size, bytes, numberOfBytes);
  self->size += numberOfBytes;
}

void
Arcadia_StringBuffer_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Value value
  )
{
  if (!Arcadia_Value_isObjectReferenceValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue referenceValue = Arcadia_Value_getObjectReferenceValue(&value);
  if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, referenceValue), _Arcadia_ByteBuffer_getType(thread))) {
    Arcadia_ByteBuffer* object = (Arcadia_ByteBuffer*)referenceValue;
    if (!Arcadia_isUtf8(thread, Arcadia_ByteBuffer_getBytes(thread, object), Arcadia_ByteBuffer_getNumberOfBytes(thread, object), NULL)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(thread);
    }
    ensureFreeCapacityBytes(thread, self, Arcadia_ByteBuffer_getNumberOfBytes(thread, object));
    Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), self->elements + self->size, Arcadia_ByteBuffer_getBytes(thread, object), Arcadia_ByteBuffer_getNumberOfBytes(thread, object));
    self->size += Arcadia_ByteBuffer_getNumberOfBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, referenceValue), _Arcadia_String_getType(thread))) {
    Arcadia_String* object = (Arcadia_String*)referenceValue;
    // The Byte sequence of Arcadia.String is guaranteed to be an UTF8 Byte sequence.
    ensureFreeCapacityBytes(thread, self, Arcadia_String_getNumberOfBytes(thread, object));
    Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), self->elements + self->size, Arcadia_String_getBytes(thread, object), Arcadia_String_getNumberOfBytes(thread, object));
    self->size += Arcadia_String_getNumberOfBytes(thread, object);
  } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, referenceValue), _Arcadia_StringBuffer_getType(thread))) {
    Arcadia_StringBuffer* object = (Arcadia_StringBuffer*)referenceValue;
    // The Byte sequence of Arcadia.StringBuffer is guaranteed to be an UTF8 Byte sequence.
    ensureFreeCapacityBytes(thread, self, Arcadia_StringBuffer_getNumberOfBytes(thread, object));
    Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), self->elements + self->size, Arcadia_StringBuffer_getBytes(thread, object), Arcadia_StringBuffer_getNumberOfBytes(thread, object));
    self->size += Arcadia_StringBuffer_getNumberOfBytes(thread, object);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_StringBuffer_appendCodePoints
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  Arcadia_Utf8_encodeCodePoints(Arcadia_Thread_getProcess(thread), codePoints, numberOfCodePoints, self, (void (*)(Arcadia_Process*, void*, Arcadia_Natural8Value const*, Arcadia_SizeValue))&appendBytesInternal);
}

Arcadia_BooleanValue
Arcadia_StringBuffer_isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_StringBuffer* other
  )
{
  if (self == other) {
    return Arcadia_BooleanValue_True;
  }
  if (self->size == other->size) {
    return !Arcadia_Process_compareMemory(Arcadia_Thread_getProcess(thread), self->elements, other->elements, self->size);
  } else {
    return Arcadia_BooleanValue_False;
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
