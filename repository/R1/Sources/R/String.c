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
// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

static void
R_String_destruct
  (
    R_String* self
  );

static R_SizeValue
hash
  (
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  );

static void
R_String_destruct
  (
    R_String* self
  )
{
  if (self->p) {
    R_deallocateUnmanaged_nojump(self->p);
    self->p = NULL;
  }
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

Rex_defineObjectType("R.String", R_String, "R.Object", R_Object, NULL, &R_String_destruct);

void
R_String_construct_pn
  (
    R_String* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_Type* _type = _R_String_getType();
  if (!bytes) {
    R_setStatus(R_Status_EncodingInvalid);
    R_jump();
  }
  R_SizeValue numberOfSymbols;
  if (!R_isUtf8(bytes, numberOfBytes, &numberOfSymbols)) {
    R_setStatus(R_Status_EncodingInvalid);
    R_jump();
  }
  R_Object_construct((R_Object*)self);
  self->p = NULL;
  self->hash = 0;
  self->numberOfBytes = 0;
  if (!R_allocateUnmanaged_nojump(&self->p, numberOfBytes)) {
    R_jump();
  }
  memcpy(self->p, bytes, numberOfBytes);
  self->numberOfBytes = numberOfBytes;
  self->hash = hash(self->p, self->numberOfBytes);
  R_Object_setType((R_Object*)self, _type);
}

R_String*
R_String_create_pn
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_String* self = R_allocateObject(_R_String_getType());
  R_String_construct_pn(self, bytes, numberOfBytes);
  return self;
}

void
R_String_construct
  (
    R_String* self,
    R_Value value
  )
{
  if (!R_Value_isObjectReferenceValue(&value)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Type* _type = _R_String_getType();
  R_Object_construct((R_Object*)self);
  R_ObjectReferenceValue referenceValue = R_Value_getObjectReferenceValue(&value);
  if (R_Type_isSubType(R_Object_getType(referenceValue), _R_ByteBuffer_getType())) {
    R_ByteBuffer* object = (R_ByteBuffer*)referenceValue;
    if (!R_isUtf8(R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object), NULL)) {
      R_setStatus(R_Status_EncodingInvalid);
      R_jump();
    }
    self->p = NULL;
    self->hash = 0;
    self->numberOfBytes = 0;
    if (!R_allocateUnmanaged_nojump(&self->p, R_ByteBuffer_getNumberOfBytes(object))) {
      R_jump();
    }
    memcpy(self->p, R_ByteBuffer_getBytes(object), R_ByteBuffer_getNumberOfBytes(object));
    self->numberOfBytes = R_ByteBuffer_getNumberOfBytes(object);
    self->hash = hash(self->p, self->numberOfBytes);
  } else if (R_Type_isSubType(R_Object_getType(referenceValue), _R_String_getType())) {
    R_String* object = (R_String*)referenceValue;
    self->p = NULL;
    self->hash = 0;
    self->numberOfBytes = 0;
    if (!R_allocateUnmanaged_nojump(&self->p, R_String_getNumberOfBytes(object))) {
      R_jump();
    }
    memcpy(self->p, R_String_getBytes(object), R_String_getNumberOfBytes(object));
    self->numberOfBytes = object->numberOfBytes;
    self->hash = object->hash;
  } else if (R_Type_isSubType(R_Object_getType(referenceValue), _R_StringBuffer_getType())) {
    R_StringBuffer* object = (R_StringBuffer*)referenceValue;
    self->p = NULL;
    self->hash = 0;
    self->numberOfBytes = 0;
    if (!R_allocateUnmanaged_nojump(&self->p, R_StringBuffer_getNumberOfBytes(object))) {
      R_jump();
    }
    memcpy(self->p, R_StringBuffer_getBytes(object), R_StringBuffer_getNumberOfBytes(object));
    self->numberOfBytes = R_StringBuffer_getNumberOfBytes(object);
    self->hash = hash(self->p, self->numberOfBytes);
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object_setType((R_Object*)self, _type);
}

R_String*
R_String_create
  (
    R_Value value
  )
{
  R_String* self = R_allocateObject(_R_String_getType());
  R_String_construct(self, value);
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
  if (self->numberOfBytes < numberOfBytes) {
    return R_BooleanValue_False;
  }
  R_SizeValue d = self->numberOfBytes - numberOfBytes;
  return !memcmp(self->p + d, bytes, numberOfBytes);
}

R_BooleanValue
R_String_startsWith_pn
  (
    R_String const* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (self->numberOfBytes < numberOfBytes) {
    return R_BooleanValue_False;
  }
  return !memcmp(self->p, bytes, numberOfBytes);
}

R_BooleanValue
R_String_isEqualTo
  (
    R_String const* self,
    R_String const* other
  )
{
  if (self == other) {
    return R_BooleanValue_True;
  }
  if (self->numberOfBytes == other->numberOfBytes) {
    return !memcmp(self->p, other->p, self->numberOfBytes);
  } else {
    return R_BooleanValue_False;
  }
}

R_SizeValue
R_String_getNumberOfBytes
  (
    R_String const* self
  )
{
  return self->numberOfBytes;
}

R_Natural8Value const*
R_String_getBytes
  (
    R_String const* self
  )
{
  return self->p;
}

R_Natural8Value
R_String_getByteAt
  (
    R_String const* self,
    R_SizeValue index
  )
{
  if (index >= self->numberOfBytes) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return *(self->p + index);
}

R_SizeValue
R_String_getHash
  (
    R_String const* self
  )
{
  return self->hash;
}

R_SizeValue
R_String_getNumberOfSymbols
  (
    R_String const* self
  )
{
  R_SizeValue numberOfSymbols;
  R_isUtf8(self->p, self->numberOfBytes, &numberOfSymbols);
  return numberOfSymbols;
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
        if (0x80 != x & 0xc0) {
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
        if (0x80 != x & 0xc0) {
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
        if (0x80 != x & 0xc0) {
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
        if (0x80 != x & 0xc0) {
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
        if (0x80 != x & 0xc0) {
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
        if (0x80 != x & 0xc0) {
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
R_String_getSubString
  (
    R_String const* self,
    R_SizeValue index,
    R_SizeValue length
  )
{
  R_SizeValue byteIndex, byteLength;
  getByteRange(index, length, &byteIndex, &byteLength, self->p, self->numberOfBytes);
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
  if (self->numberOfBytes == numberOfBytes) {
    return !memcmp(self->p, bytes, numberOfBytes);
  } else {
    return R_BooleanValue_False;
  }
}

#include "R/ToNumber/Include.h"

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
