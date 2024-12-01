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

// Last modified: 2024-09-01

#include "R/String.h"

#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/StringBuffer.h"
#include "R/UnmanagedMemory.h"
#include "R/Utf8.h"
#include "R/ToNumber/Include.h"
#include "R/cstdlib.h"

static void
R_String_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static R_SizeValue
hash
  (
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  );

static void
equalToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
hashImpl
  (
    R_Value* target,
    R_Value const* self
  );

static void
notEqualToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
R_String_visit
  (
    R_String* string 
  );

static void
getByteRange
  (
    R_SizeValue symbolIndex,
    R_SizeValue symbolLength,
    R_SizeValue* byteIndex,
    R_SizeValue* byteLength,
    uint8_t const* p,
    R_SizeValue l
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_String_constructImpl,
  .destruct = NULL,
  .visit = &R_String_visit,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &equalToImpl,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = &hashImpl,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = &notEqualToImpl,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.String", R_String, "R.Object", R_Object, &_typeOperations);

static void
R_String_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  R_String* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_String_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (R_Value_isImmutableByteArrayValue(&argumentValues[0])) {
    R_SizeValue numberOfSymbols;
    R_ImmutableByteArray* immutableByteArray = R_Value_getImmutableByteArrayValue(&argumentValues[0]);
    if (!R_isUtf8(R_ImmutableByteArray_getBytes(immutableByteArray), R_ImmutableByteArray_getNumberOfBytes(immutableByteArray), &numberOfSymbols)) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(R_ImmutableByteArray_getBytes(immutableByteArray), R_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_ObjectReferenceValue referenceValue = R_Value_getObjectReferenceValue(&argumentValues[0]);
    if (R_Type_isSubType(R_Object_getType(referenceValue), _R_ByteBuffer_getType())) {
      R_ByteBuffer* object = (R_ByteBuffer*)referenceValue;
      if (!R_isUtf8(R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object), NULL)) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      _self->immutableByteArray = R_ImmutableByteArray_create(R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object));
      _self->hash = hash(R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object));
    } else if (R_Type_isSubType(R_Object_getType(referenceValue), _R_String_getType())) {
      R_String* object = (R_String*)referenceValue;
      _self->immutableByteArray = object->immutableByteArray;
      _self->hash = object->hash;
    } else if (R_Type_isSubType(R_Object_getType(referenceValue), _R_StringBuffer_getType())) {
      R_StringBuffer* object = (R_StringBuffer*)referenceValue;
      _self->immutableByteArray = R_ImmutableByteArray_create(R_StringBuffer_getBytes(object), R_StringBuffer_getNumberOfBytes(object));
      _self->hash = hash(R_StringBuffer_getBytes(object), R_StringBuffer_getNumberOfBytes(object));
    } else {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object_setType((R_Object*)_self, _type);
}

static R_SizeValue
hash
  (
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_SizeValue hash = numberOfBytes;
  for (R_SizeValue i = 0, n = numberOfBytes; i < n; ++i) {
    hash = hash * 37 + bytes[i];
  }
  return hash;
}

static void
equalToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  R_String* self1 = (R_String*)R_Value_getObjectReferenceValue(self);
  if (!R_Value_isObjectReferenceValue(other)) {
    R_Value_setBooleanValue(target, R_BooleanValue_False);
    return;
  }
  R_Object* other1 = R_Value_getObjectReferenceValue(other);
  if ((R_Object*)self1 == other1) {
    R_Value_setBooleanValue(target, R_BooleanValue_True);
    return;
  }
  if (!R_Type_isSubType(R_Object_getType(other1), _R_String_getType())) {
    R_Value_setBooleanValue(target, R_BooleanValue_False);
    return;
  }
  R_String* otherString1 = (R_String*)other1;
  if (R_ImmutableByteArray_getNumberOfBytes(self1->immutableByteArray) == R_ImmutableByteArray_getNumberOfBytes(otherString1->immutableByteArray)) {
    R_Value_setBooleanValue(target, !c_memcmp(R_ImmutableByteArray_getBytes(self1->immutableByteArray), 
                                              R_ImmutableByteArray_getBytes(otherString1->immutableByteArray), 
                                              R_ImmutableByteArray_getNumberOfBytes(self1->immutableByteArray)));
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_False);
  }
}

static void
hashImpl
  (
    R_Value* target,
    R_Value const* self
  )
{
  R_String* self1 = (R_String*)R_Value_getObjectReferenceValue(self);
  R_Value_setSizeValue(target, self1->hash);
}

static void
notEqualToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  equalToImpl(target, self, other);
}

static void
R_String_visit
  (
    R_String* string
  )
{ 
  R_ImmutableByteArray_visit(string->immutableByteArray);
}

static void
getByteRange
  (
    R_SizeValue symbolIndex,
    R_SizeValue symbolLength,
    R_SizeValue* byteIndex,
    R_SizeValue* byteLength,
    uint8_t const* p,
    R_SizeValue l
  )
{
  uint8_t const* start = p;
  uint8_t const* end = p + l;
  uint8_t const* current = start;

  uint8_t const* currentByteIndex = NULL;
  R_SizeValue currentSymbolIndex = 0;

  uint8_t const* currentByteLength = NULL;
  R_SizeValue currentSymbolLength = 0;

  while (current != end) {
    uint8_t x = (*current);
    if (x <= 0x7f) {
      uint8_t const* last = current;
      current += 1;
      if (currentSymbolIndex == symbolIndex) {
        currentByteIndex = last;
        break;
      } else {
        currentSymbolIndex++;
      }
    } else if (x <= 0x7ff) {
      uint8_t const* last = current;
      if (end - current < 2) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      for (R_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
      }
      current++;
      if (currentSymbolIndex == symbolIndex) {
        currentByteIndex = last;
        break;
      } else {
        currentSymbolIndex++;
      }
    } else if (x <= 0xffff) {
      uint8_t const* last = current;
      if (end - current < 3) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      for (R_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
      }
      current++;
      if (currentSymbolIndex == symbolIndex) {
        currentByteIndex = last;
        break;
      } else {
        currentSymbolIndex++;
      }
    } else if (x <= 0x10ffff) {
      uint8_t const* last = current;
      if (end - current < 4) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      for (R_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
      }
      current++;
      if (currentSymbolIndex == symbolIndex) {
        currentByteIndex = last;
        break;
      } else {
        currentSymbolIndex++;
      }
    } else {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
  }
  if (!currentByteIndex) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }

  while (current != end) {
    uint8_t x = (*current);
    if (x <= 0x7f) {
      current += 1;
      if (currentSymbolLength == symbolLength) {
        currentByteLength = current;
        break;
      } else {
        currentSymbolLength++;
      }
    } else if (x <= 0x7ff) {
      if (end - current < 2) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      for (R_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
      }
      current++;
      if (currentSymbolLength == symbolLength) {
        currentByteLength = current;
        break;
      } else {
        currentSymbolLength++;
      }
    } else if (x <= 0xffff) {
      if (end - current < 3) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      for (R_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
      }
      current++;
      if (currentSymbolLength == symbolLength) {
        currentByteLength = current;
        break;
      } else {
        currentSymbolLength++;
      }
    } else if (x <= 0x10ffff) {
      if (end - current < 4) {
        R_setStatus(R_Status_EncodingInvalid);
        R_jump();
      }
      for (R_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          R_setStatus(R_Status_EncodingInvalid);
          R_jump();
        }
      }
      current++;
      if (currentSymbolLength == symbolLength) {
        currentByteLength = current;
        break;
      } else {
        currentSymbolLength++;
      }
    } else {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
  }
  if (!currentByteLength) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  *byteIndex = currentByteIndex - start;
  *byteLength = currentByteLength - start;
}

R_String*
R_String_create_pn
  (
    R_ImmutableByteArray* immutableByteArray
  )
{
  R_Value argumentValues[] = { { .tag = R_ValueTag_ImmutableByteArray, .immutableByteArrayValue = immutableByteArray } };
  R_String* self = R_allocateObject(_R_String_getType(), 1, &argumentValues[0]);
  return self;
}

R_String*
R_String_create
  (
    R_Value value
  )
{ 
  R_Value argumentValues[] = { value };
  R_String* self = R_allocateObject(_R_String_getType(), 1, &argumentValues[0]);
  return self;
}

R_BooleanValue
R_String_endsWith_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (R_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray) < numberOfBytes) {
    return R_BooleanValue_False;
  }
  R_SizeValue d = R_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray) - numberOfBytes;
  return !c_memcmp(R_ImmutableByteArray_getBytes(self->immutableByteArray) + d, bytes, numberOfBytes);
}

R_BooleanValue
R_String_startsWith_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (R_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray) < numberOfBytes) {
    return R_BooleanValue_False;
  }
  return !c_memcmp(R_ImmutableByteArray_getBytes(self->immutableByteArray), bytes, numberOfBytes);
}

R_SizeValue
R_String_getNumberOfBytes
  (
    R_String const* self
  )
{
  return R_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray);
}

R_Natural8Value const*
R_String_getBytes
  (
    R_String const* self
  )
{
  return R_ImmutableByteArray_getBytes(self->immutableByteArray);
}

R_Natural8Value
R_String_getByteAt
  (
    R_String const* self,
    R_SizeValue index
  )
{
  if (index >= R_String_getNumberOfBytes(self)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return *(R_String_getBytes(self) + index);
}

R_SizeValue
R_String_getNumberOfSymbols
  (
    R_String const* self
  )
{
  R_SizeValue numberOfSymbols;
  R_isUtf8(R_String_getBytes(self), R_String_getNumberOfBytes(self), &numberOfSymbols);
  return numberOfSymbols;
}

R_String*
R_String_getSubString
  (
    R_String const* self,
    R_SizeValue index,
    R_SizeValue length
  )
{
  R_SizeValue byteIndex, byteLength;
  getByteRange(index, length, &byteIndex, &byteLength, R_ImmutableByteArray_getBytes(self->immutableByteArray), R_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray));
  return NULL;
}

R_BooleanValue
R_String_isEqualTo_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (R_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray) == numberOfBytes) {
    return !c_memcmp(R_ImmutableByteArray_getBytes(self->immutableByteArray), bytes, numberOfBytes);
  } else {
    return R_BooleanValue_False;
  }
}

R_Integer8Value
R_String_toInteger8
  (
    R_String const* self
  )
{ return R_toInteger8(R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

R_Integer16Value
R_String_toInteger16
  (
    R_String const* self
  )
{ return R_toInteger16(R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

R_Integer32Value
R_String_toInteger32
  (
    R_String const* self
  )
{ return R_toInteger32(R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

R_Integer64Value
R_String_toInteger64
  (
    R_String const* self
  )
{ return R_toInteger64(R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

R_Integer8Value
R_String_toNatural8
  (
    R_String const* self
  )
{ return R_toNatural8(R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

R_Natural16Value
R_String_toNatural16
  (
    R_String const* self
  )
{ return R_toNatural16(R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

R_Natural32Value
R_String_toNatural32
  (
    R_String const* self
  )
{ return R_toNatural32(R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

R_Natural64Value
R_String_toNatural64
  (
    R_String const* self
  )
{ return R_toNatural64(R_String_getBytes(self), R_String_getNumberOfBytes(self)); }
