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
#include "Arcadia/Ring2/Implementation/ByteBuffer.h"

static void
Arcadia_ByteBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_ByteBuffer_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_ByteBuffer_constructImpl,
  .destruct = &Arcadia_ByteBuffer_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ByteBuffer", Arcadia_ByteBuffer, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_ByteBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_ByteBuffer* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_ByteBuffer_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  _self->p = Arcadia_Memory_allocateUnmanaged(thread, 0);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_ByteBuffer_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self
  )
{
  if (self->p) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->p);
    self->p = NULL;
  }
}

Arcadia_ByteBuffer*
Arcadia_ByteBuffer_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_ByteBuffer* self = Arcadia_allocateObject(thread, _Arcadia_ByteBuffer_getType(thread), 0, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
Arcadia_ByteBuffer_endsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = self->sz - numberOfBytes;
  return !Arcadia_Memory_compare(thread, self->p + d, bytes, numberOfBytes);
}

Arcadia_BooleanValue
Arcadia_ByteBuffer_startsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !Arcadia_Memory_compare(thread, self->p, bytes, numberOfBytes);
}

void
Arcadia_ByteBuffer_append_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ByteBuffer_insert_pn(thread, self, self->sz, bytes, numberOfBytes);
}

void
Arcadia_ByteBuffer_prepend_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ByteBuffer_insert_pn(thread, self, Arcadia_SizeValue_Literal(0), bytes, numberOfBytes);
}

void
Arcadia_ByteBuffer_insert_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self,
    Arcadia_SizeValue index,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self || !bytes || index > self->sz) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!numberOfBytes) {
    return;
  }
  // TODO: Use Arcadia_Arrays_* maybe?
  Arcadia_SizeValue freeCapacity = self->cp - self->sz;
  if (freeCapacity < numberOfBytes) {
    Arcadia_SizeValue additionalCapacity = numberOfBytes - freeCapacity;
    Arcadia_SizeValue oldCapacity = self->cp;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_SizeValue newCapacity = oldCapacity + additionalCapacity;
    Arcadia_Memory_reallocateUnmanaged(thread, &self->p, newCapacity);
    self->cp = newCapacity;
  }
  if (index < self->sz) {
    Arcadia_Memory_copy(thread, self->p + index, self->p + index + numberOfBytes, self->sz - index);
  }
  Arcadia_Memory_copy(thread, self->p + index, bytes, numberOfBytes);
  self->sz += numberOfBytes;
}

Arcadia_BooleanValue
Arcadia_ByteBuffer_isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    Arcadia_ByteBuffer const* other
  )
{
  if (self == other) {
    return Arcadia_BooleanValue_True;
  }
  if (self->sz == other->sz) {
    return !Arcadia_Memory_compare(thread, self->p, other->p, self->sz);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

Arcadia_BooleanValue
Arcadia_ByteBuffer_isEqualTo_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self || !bytes) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (self->sz == numberOfBytes) {
    return !Arcadia_Memory_compare(thread, self->p, bytes, numberOfBytes);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

void
Arcadia_ByteBuffer_clear
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* self
  )
{
  self->sz = 0;
}

Arcadia_SizeValue
Arcadia_ByteBuffer_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self
  )
{
  return self->sz;
}

Arcadia_SizeValue
Arcadia_ByteBuffer_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self
  )
{ return self->sz; }

Arcadia_Natural8Value const*
Arcadia_ByteBuffer_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self
  )
{ return self->p; }

Arcadia_Natural8Value
Arcadia_ByteBuffer_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer const* self,
    Arcadia_SizeValue index
  )
{
  if (index >= self->sz) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return *(self->p + index);
}
