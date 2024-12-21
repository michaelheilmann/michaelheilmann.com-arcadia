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

// Last modified: 2024-10-07

#include "ByteBuffer.h"

#include "R/ArmsIntegration.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/DynamicArrayUtilities.h"
#include "R/Value.h"
#include "R/cstdlib.h"

static void
R_ByteBuffer_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_ByteBuffer_destruct
  (
    R_ByteBuffer* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_ByteBuffer_constructImpl,
  .destruct = &R_ByteBuffer_destruct,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("R.ByteBuffer", R_ByteBuffer, "R.Object", R_Object, &_typeOperations);

static void
R_ByteBuffer_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_ByteBuffer* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_ByteBuffer_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  if (!R_allocateUnmanaged_nojump(&_self->p, 0)) {
    R_jump();
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_ByteBuffer_destruct
  (
    R_ByteBuffer* self
  )
{
  if (self->p) {
    R_deallocateUnmanaged_nojump(self->p);
    self->p = NULL;
  }
}

R_ByteBuffer*
R_ByteBuffer_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_ByteBuffer* self = R_allocateObject(_R_ByteBuffer_getType(), 0, &argumentValues[0]);
  R_Value selfValue = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = self };
  R_ByteBuffer_constructImpl(&selfValue, 0, &argumentValues[0]);
  return self;
}

R_BooleanValue
R_ByteBuffer_endsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return R_BooleanValue_False;
  }
  R_SizeValue d = self->sz - numberOfBytes;
  return !c_memcmp(self->p + d, bytes, numberOfBytes);
}

R_BooleanValue
R_ByteBuffer_startsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return R_BooleanValue_False;
  }
  return !c_memcmp(self->p, bytes, numberOfBytes);
}

void
R_ByteBuffer_append_pn
  (
    R_ByteBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_ByteBuffer_insert_pn(self, self->sz, bytes, numberOfBytes);
}

void
R_ByteBuffer_prepend_pn
  (
    R_ByteBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_ByteBuffer_insert_pn(self, R_SizeValue_Literal(0), bytes, numberOfBytes);
}

void
R_ByteBuffer_insert_pn
  (
    R_ByteBuffer* self,
    R_SizeValue index,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!self || !bytes || index > self->sz) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!numberOfBytes) {
    return;
  }
  R_SizeValue freeCapacity = self->cp - self->sz;
  if (freeCapacity < numberOfBytes) {
    R_SizeValue additionalCapacity = numberOfBytes - freeCapacity;
    R_SizeValue oldCapacity = self->cp;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    R_SizeValue newCapacity = oldCapacity + additionalCapacity;
    if (!R_reallocateUnmanaged_nojump(&self->p, newCapacity)) {
      R_jump();
    }
    self->cp = newCapacity;
  }
  if (index < self->sz) {
    c_memmove(self->p + index, self->p + index + numberOfBytes, self->sz - index);
  }
  c_memcpy(self->p + index, bytes, numberOfBytes);
  self->sz += numberOfBytes;
}

R_BooleanValue
R_ByteBuffer_isEqualTo
  (
    R_ByteBuffer const* self,
    R_ByteBuffer const* other
  )
{
  if (self == other) {
    return R_BooleanValue_True;
  }
  if (self->sz == other->sz) {
    return !c_memcmp(self->p, other->p, self->sz);
  } else {
    return R_BooleanValue_False;
  }
}

R_BooleanValue
R_ByteBuffer_isEqualTo_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!self || !bytes) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (self->sz == numberOfBytes) {
    return !c_memcmp(self->p, bytes, numberOfBytes);
  } else {
    return R_BooleanValue_False;
  }
}

void
R_ByteBuffer_clear
  (
    R_ByteBuffer* self
  )
{
  self->sz = 0;
}

R_SizeValue
R_ByteBuffer_getSize
  (
    R_ByteBuffer const* self
  )
{
  return self->sz;
}

R_SizeValue
R_ByteBuffer_getNumberOfBytes
  (
    R_ByteBuffer const* self
  )
{ return self->sz; }

R_Natural8Value const*
R_ByteBuffer_getBytes
  (
    R_ByteBuffer const* self
  )
{ return self->p; }

R_Natural8Value
R_ByteBuffer_getAt
  (
    R_ByteBuffer const* self,
    R_SizeValue index
  )
{
  if (index >= self->sz) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return *(self->p + index);
}
