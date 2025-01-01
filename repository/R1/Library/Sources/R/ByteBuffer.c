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

// Last modified: 2024-10-07

#include "ByteBuffer.h"

#include "R/ArmsIntegration.h"
#include "R/Object.h"
#include "R/DynamicArrayUtilities.h"
#include "R/Value.h"
#include "R/cstdlib.h"

static void
R_ByteBuffer_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_ByteBuffer_destruct
  (
    Arcadia_Process* process,
    R_ByteBuffer* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_ByteBuffer_constructImpl,
  .destruct = &R_ByteBuffer_destruct,
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

Rex_defineObjectType(u8"R.ByteBuffer", R_ByteBuffer, u8"R.Object", R_Object, &_typeOperations);

static void
R_ByteBuffer_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_ByteBuffer* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_ByteBuffer_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  if (!R_allocateUnmanaged_nojump(process, &_self->p, 0)) {
    Arcadia_Process_jump(process);
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_ByteBuffer_destruct
  (
    Arcadia_Process* process,
    R_ByteBuffer* self
  )
{
  if (self->p) {
    R_deallocateUnmanaged_nojump(process, self->p);
    self->p = NULL;
  }
}

R_ByteBuffer*
R_ByteBuffer_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_ByteBuffer* self = R_allocateObject(process, _R_ByteBuffer_getType(process), 0, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
R_ByteBuffer_endsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = self->sz - numberOfBytes;
  return !c_memcmp(self->p + d, bytes, numberOfBytes);
}

Arcadia_BooleanValue
R_ByteBuffer_startsWith_pn
  (
    R_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !c_memcmp(self->p, bytes, numberOfBytes);
}

void
R_ByteBuffer_append_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  R_ByteBuffer_insert_pn(process, self, self->sz, bytes, numberOfBytes);
}

void
R_ByteBuffer_prepend_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  R_ByteBuffer_insert_pn(process, self, Arcadia_SizeValue_Literal(0), bytes, numberOfBytes);
}

void
R_ByteBuffer_insert_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer* self,
    Arcadia_SizeValue index,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self || !bytes || index > self->sz) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (!numberOfBytes) {
    return;
  }
  Arcadia_SizeValue freeCapacity = self->cp - self->sz;
  if (freeCapacity < numberOfBytes) {
    Arcadia_SizeValue additionalCapacity = numberOfBytes - freeCapacity;
    Arcadia_SizeValue oldCapacity = self->cp;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
      Arcadia_Process_jump(process);
    }
    Arcadia_SizeValue newCapacity = oldCapacity + additionalCapacity;
    if (!R_reallocateUnmanaged_nojump(process, &self->p, newCapacity)) {
      Arcadia_Process_jump(process);
    }
    self->cp = newCapacity;
  }
  if (index < self->sz) {
    c_memmove(self->p + index, self->p + index + numberOfBytes, self->sz - index);
  }
  c_memcpy(self->p + index, bytes, numberOfBytes);
  self->sz += numberOfBytes;
}

Arcadia_BooleanValue
R_ByteBuffer_isEqualTo
  (
    R_ByteBuffer const* self,
    R_ByteBuffer const* other
  )
{
  if (self == other) {
    return Arcadia_BooleanValue_True;
  }
  if (self->sz == other->sz) {
    return !c_memcmp(self->p, other->p, self->sz);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

Arcadia_BooleanValue
R_ByteBuffer_isEqualTo_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self || !bytes) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (self->sz == numberOfBytes) {
    return !c_memcmp(self->p, bytes, numberOfBytes);
  } else {
    return Arcadia_BooleanValue_False;
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

Arcadia_SizeValue
R_ByteBuffer_getSize
  (
    R_ByteBuffer const* self
  )
{
  return self->sz;
}

Arcadia_SizeValue
R_ByteBuffer_getNumberOfBytes
  (
    R_ByteBuffer const* self
  )
{ return self->sz; }

Arcadia_Natural8Value const*
R_ByteBuffer_getBytes
  (
    R_ByteBuffer const* self
  )
{ return self->p; }

Arcadia_Natural8Value
R_ByteBuffer_getAt
  (
    Arcadia_Process* process,
    R_ByteBuffer const* self,
    Arcadia_SizeValue index
  )
{
  if (index >= self->sz) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return *(self->p + index);
}
