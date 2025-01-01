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

// Last modified: 2024-09-01

#include "R/String.h"

#include "R/Convert/Include.h"
#include "R/Object.h"
#include "R/StringBuffer.h"
#include "R/Utf8.h"
#include "R/cstdlib.h"
#include "Arms.h"

static void
R_String_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static Arcadia_SizeValue
hash
  (
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
equalToImpl
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
hashImpl
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  );

static void
notEqualToImpl
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
R_String_visit
  (
    Arcadia_Process* process,
    R_String* string 
  );

static void
getByteRange
  (
    Arcadia_Process* process,
    Arcadia_SizeValue symbolIndex,
    Arcadia_SizeValue symbolLength,
    Arcadia_SizeValue* byteIndex,
    Arcadia_SizeValue* byteLength,
    uint8_t const* p,
    Arcadia_SizeValue l
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_String_constructImpl,
  .destruct = NULL,
  .visit = &R_String_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Rex_defineObjectType(u8"R.String", R_String, u8"R.Object", R_Object, &_typeOperations);

#define On(Type, Suffix) \
  static Arcadia_ImmutableByteArray* \
  from##Suffix \
    ( \
      Arcadia_Process* process, \
      Type##Value value \
    ) \
  { \
    Arms_MemoryManager* memoryManager = Arms_getSlabMemoryManager(); \
    char* p; size_t n; \
    Type##_toString(process, memoryManager, value, &p, &n); \
    R_JumpTarget jumpTarget; \
    Arcadia_Process_pushJumpTarget(process, &jumpTarget); \
    if (R_JumpTarget_save(&jumpTarget)) { \
      Arcadia_ImmutableByteArray* result = Arcadia_ImmutableByteArray_create(process, p, n); \
      Arms_MemoryManager_deallocate(memoryManager, p); \
      p = NULL; \
      Arcadia_Process_popJumpTarget(process); \
      return result; \
    } else { \
      Arcadia_Process_popJumpTarget(process); \
      Arms_MemoryManager_deallocate(memoryManager, p); \
      p = NULL; \
      Arcadia_Process_jump(process); \
    } \
  }

On(Arcadia_Integer16, Integer16)
On(Arcadia_Integer32, Integer32)
On(Arcadia_Integer64, Integer64)
On(Arcadia_Integer8, Integer8)

On(Arcadia_Natural16, Natural16)
On(Arcadia_Natural32, Natural32)
On(Arcadia_Natural64, Natural64)
On(Arcadia_Natural8, Natural8)

static void
R_String_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  R_String* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_String_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (R_Value_isInteger16Value(&argumentValues[0])) {
    Arcadia_ImmutableByteArray* immutableByteArray = fromInteger16(process, R_Value_getInteger16Value(&argumentValues[0]));
    /* The functions assert the Bytes are UTF-8. */
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isInteger32Value(&argumentValues[0])) {
    Arcadia_ImmutableByteArray* immutableByteArray = fromInteger32(process, R_Value_getInteger16Value(&argumentValues[0]));
    /* The functions assert the Bytes are UTF-8. */
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isInteger64Value(&argumentValues[0])) {
    Arcadia_ImmutableByteArray* immutableByteArray = fromInteger64(process, R_Value_getInteger16Value(&argumentValues[0]));
    /* The functions assert the Bytes are UTF-8. */
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isInteger8Value(&argumentValues[0])) {
    Arcadia_ImmutableByteArray* immutableByteArray = fromInteger8(process, R_Value_getInteger16Value(&argumentValues[0]));
    /* The functions assert the Bytes are UTF-8. */
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isNatural16Value(&argumentValues[0])) {
    Arcadia_ImmutableByteArray* immutableByteArray = fromNatural16(process, R_Value_getInteger16Value(&argumentValues[0]));
    /* The functions assert the Bytes are UTF-8. */
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isNatural32Value(&argumentValues[0])) {
    Arcadia_ImmutableByteArray* immutableByteArray = fromNatural32(process, R_Value_getInteger16Value(&argumentValues[0]));
    /* The functions assert the Bytes are UTF-8. */
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isNatural64Value(&argumentValues[0])) {
    Arcadia_ImmutableByteArray* immutableByteArray = fromNatural64(process, R_Value_getInteger16Value(&argumentValues[0]));
    /* The functions assert the Bytes are UTF-8. */
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isNatural8Value(&argumentValues[0])) {
    Arcadia_ImmutableByteArray* immutableByteArray = fromNatural8(process, R_Value_getInteger16Value(&argumentValues[0]));
    /* The functions assert the Bytes are UTF-8. */
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } if (R_Value_isImmutableByteArrayValue(&argumentValues[0])) {
    Arcadia_SizeValue numberOfSymbols;
    Arcadia_ImmutableByteArray* immutableByteArray = R_Value_getImmutableByteArrayValue(&argumentValues[0]);
    if (!R_isUtf8(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray), &numberOfSymbols)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
    _self->immutableByteArray = immutableByteArray;
    _self->hash = hash(Arcadia_ImmutableByteArray_getBytes(immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(immutableByteArray));
  } else if (R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_ObjectReferenceValue referenceValue = R_Value_getObjectReferenceValue(&argumentValues[0]);
    if (Arcadia_Type_isSubType(R_Object_getType(referenceValue), _R_ByteBuffer_getType(process))) {
      R_ByteBuffer* object = (R_ByteBuffer*)referenceValue;
      if (!R_isUtf8(R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object), NULL)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      _self->immutableByteArray = Arcadia_ImmutableByteArray_create(process, R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object));
      _self->hash = hash(R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object));
    } else if (Arcadia_Type_isSubType(R_Object_getType(referenceValue), _R_String_getType(process))) {
      R_String* object = (R_String*)referenceValue;
      _self->immutableByteArray = object->immutableByteArray;
      _self->hash = object->hash;
    } else if (Arcadia_Type_isSubType(R_Object_getType(referenceValue), _R_StringBuffer_getType(process))) {
      R_StringBuffer* object = (R_StringBuffer*)referenceValue;
      _self->immutableByteArray = Arcadia_ImmutableByteArray_create(process, R_StringBuffer_getBytes(object), R_StringBuffer_getNumberOfBytes(object));
      _self->hash = hash(R_StringBuffer_getBytes(object), R_StringBuffer_getNumberOfBytes(object));
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Process_jump(process);
    }
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  R_Object_setType((R_Object*)_self, _type);
}

static Arcadia_SizeValue
hash
  (
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_SizeValue hash = numberOfBytes;
  for (Arcadia_SizeValue i = 0, n = numberOfBytes; i < n; ++i) {
    hash = hash * 37 + bytes[i];
  }
  return hash;
}

static void
equalToImpl
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  R_String* self1 = (R_String*)R_Value_getObjectReferenceValue(self);
  if (!R_Value_isObjectReferenceValue(other)) {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
    return;
  }
  R_Object* other1 = R_Value_getObjectReferenceValue(other);
  if ((R_Object*)self1 == other1) {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
    return;
  }
  if (!Arcadia_Type_isSubType(R_Object_getType(other1), _R_String_getType(process))) {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
    return;
  }
  R_String* otherString1 = (R_String*)other1;
  if (Arcadia_ImmutableByteArray_getNumberOfBytes(self1->immutableByteArray) == Arcadia_ImmutableByteArray_getNumberOfBytes(otherString1->immutableByteArray)) {
    R_Value_setBooleanValue(target, !c_memcmp(Arcadia_ImmutableByteArray_getBytes(self1->immutableByteArray), 
                                              Arcadia_ImmutableByteArray_getBytes(otherString1->immutableByteArray), 
                                              Arcadia_ImmutableByteArray_getNumberOfBytes(self1->immutableByteArray)));
  } else {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
}

static void
hashImpl
  (
    Arcadia_Process* process,
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
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  equalToImpl(process, target, self, other);
}

static void
R_String_visit
  (
    Arcadia_Process* process,
    R_String* string
  )
{ 
  Arcadia_ImmutableByteArray_visit(string->immutableByteArray);
}

static void
getByteRange
  (
    Arcadia_Process* process,
    Arcadia_SizeValue symbolIndex,
    Arcadia_SizeValue symbolLength,
    Arcadia_SizeValue* byteIndex,
    Arcadia_SizeValue* byteLength,
    uint8_t const* p,
    Arcadia_SizeValue l
  )
{
  uint8_t const* start = p;
  uint8_t const* end = p + l;
  uint8_t const* current = start;

  uint8_t const* currentByteIndex = NULL;
  Arcadia_SizeValue currentSymbolIndex = 0;

  uint8_t const* currentByteLength = NULL;
  Arcadia_SizeValue currentSymbolLength = 0;

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
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      for (Arcadia_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
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
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      for (Arcadia_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
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
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      for (Arcadia_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
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
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
  }
  if (!currentByteIndex) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
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
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      for (Arcadia_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
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
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      for (Arcadia_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
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
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      for (Arcadia_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
          Arcadia_Process_jump(process);
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
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
  }
  if (!currentByteLength) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  *byteIndex = currentByteIndex - start;
  *byteLength = currentByteLength - start;
}

R_String*
R_String_create_pn
  (
    Arcadia_Process* process,
    Arcadia_ImmutableByteArray* immutableByteArray
  )
{
  R_Value argumentValues[] = { { .tag = R_ValueTag_ImmutableByteArray, .immutableByteArrayValue = immutableByteArray } };
  R_String* self = R_allocateObject(process, _R_String_getType(process), 1, &argumentValues[0]);
  return self;
}

R_String*
R_String_create
  (
    Arcadia_Process* process,
    R_Value value
  )
{ 
  R_Value argumentValues[] = { value };
  R_String* self = R_allocateObject(process, _R_String_getType(process), 1, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
R_String_endsWith_pn
  (
    R_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray) < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = Arcadia_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray) - numberOfBytes;
  return !c_memcmp(Arcadia_ImmutableByteArray_getBytes(self->immutableByteArray) + d, bytes, numberOfBytes);
}

Arcadia_BooleanValue
R_String_startsWith_pn
  (
    R_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray) < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !c_memcmp(Arcadia_ImmutableByteArray_getBytes(self->immutableByteArray), bytes, numberOfBytes);
}

Arcadia_SizeValue
R_String_getNumberOfBytes
  (
    R_String const* self
  )
{
  return Arcadia_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray);
}

Arcadia_Natural8Value const*
R_String_getBytes
  (
    R_String const* self
  )
{
  return Arcadia_ImmutableByteArray_getBytes(self->immutableByteArray);
}

Arcadia_Natural8Value
R_String_getByteAt
  (
    Arcadia_Process* process,
    R_String const* self,
    Arcadia_SizeValue index
  )
{
  if (index >= R_String_getNumberOfBytes(self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return *(R_String_getBytes(self) + index);
}

Arcadia_SizeValue
R_String_getNumberOfSymbols
  (
    R_String const* self
  )
{
  Arcadia_SizeValue numberOfSymbols;
  R_isUtf8(R_String_getBytes(self), R_String_getNumberOfBytes(self), &numberOfSymbols);
  return numberOfSymbols;
}

#if 0
R_String*
R_String_getSubString
  (
    R_String const* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue length
  )
{
  Arcadia_SizeValue byteIndex, byteLength;
  getByteRange(index, length, &byteIndex, &byteLength, Arcadia_ImmutableByteArray_getBytes(self->immutableByteArray), Arcadia_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray));
  return NULL;
}
#endif

Arcadia_BooleanValue
R_String_isEqualTo_pn
  (
    R_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableByteArray_getNumberOfBytes(self->immutableByteArray) == numberOfBytes) {
    return !c_memcmp(Arcadia_ImmutableByteArray_getBytes(self->immutableByteArray), bytes, numberOfBytes);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

Arcadia_BooleanValue
R_String_toBoolean
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toBoolean(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Integer16Value
R_String_toInteger16
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toInteger16(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Integer32Value
R_String_toInteger32
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toInteger32(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Integer64Value
R_String_toInteger64
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toInteger64(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Integer8Value
R_String_toInteger8
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toInteger8(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Natural16Value
R_String_toNatural16
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toNatural16(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Natural32Value
R_String_toNatural32
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toNatural32(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Natural64Value
R_String_toNatural64
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toNatural64(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Natural8Value
R_String_toNatural8
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toNatural8(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Real32Value
R_String_toReal32
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toReal32(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_Real64Value
R_String_toReal64
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toReal64(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }

Arcadia_VoidValue
R_String_toVoid
  (
    Arcadia_Process* process,
    R_String const* self
  )
{ return R_toVoid(process, R_String_getBytes(self), R_String_getNumberOfBytes(self)); }
