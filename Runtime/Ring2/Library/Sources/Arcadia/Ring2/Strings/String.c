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
#include "Arcadia/Ring2/Strings/String.h"

#include <assert.h>
#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/Strings/StringBuffer.h"

static void
Arcadia_String_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_String* self
  );

static Arcadia_SizeValue
hash
  (
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
isEqualToImpl
  (
    Arcadia_Thread* thread
  );

static void
hashImpl
  (
    Arcadia_Thread* thread
  );

static void
isNotEqualToImpl
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_String_visit
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
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

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_String_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_String_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
  .equalTo = &isEqualToImpl,
  .hash = &hashImpl,
  .notEqualTo = &isNotEqualToImpl,
};

#define BINARY_OPERATION() \
  if (Arcadia_ValueStack_getSize(thread) < 3) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  if (2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 2); \
  Arcadia_Value y = Arcadia_ValueStack_getValue(thread, 1); \
  Arcadia_ValueStack_popValues(thread, 3);

#define UNARY_OPERATION() \
  if (Arcadia_ValueStack_getSize(thread) < 2) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  if (1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 1); \
  Arcadia_ValueStack_popValues(thread, 2);

Arcadia_defineObjectType(u8"Arcadia.String", Arcadia_String,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

#define On(Type, Suffix) \
  static void \
  from##Suffix \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_ImmutableUtf8String** pImmutableUtf8String, \
      Type##Value value \
    ) \
  { \
    *pImmutableUtf8String = Arcadia_ImmutableUtf8String_createFrom##Suffix(thread, value); \
  }

On(Arcadia_Boolean, Boolean)

On(Arcadia_Integer16, Integer16)
On(Arcadia_Integer32, Integer32)
On(Arcadia_Integer64, Integer64)
On(Arcadia_Integer8, Integer8)

On(Arcadia_Natural16, Natural16)
On(Arcadia_Natural32, Natural32)
On(Arcadia_Natural64, Natural64)
On(Arcadia_Natural8, Natural8)

On(Arcadia_Void, Void)

static void
fromImmutableByteArray
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String** pImmutableUtf8String,
    Arcadia_ImmutableByteArray* value
  )
{
  *pImmutableUtf8String =
    Arcadia_ImmutableUtf8String_create
      (
        thread,
        Arcadia_ImmutableByteArray_getBytes(thread, value),
        Arcadia_ImmutableByteArray_getNumberOfBytes(thread, value)
      );
}

static void
fromImmutableUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String** pImmutableUtf8String,
    Arcadia_ImmutableUtf8String* value
  )
{
  *pImmutableUtf8String = value;
}

static void
Arcadia_String_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_String* self
  )
{
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_TypeValue _type = _Arcadia_String_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 1);
  if (Arcadia_Value_isBooleanValue(&x)) {
    fromBoolean(thread, &self->immutableUtf8String, Arcadia_Value_getBooleanValue(&x));
  } else if (Arcadia_Value_isInteger16Value(&x)) {
    fromInteger16(thread, &self->immutableUtf8String, Arcadia_Value_getInteger16Value(&x));
  } else if (Arcadia_Value_isInteger32Value(&x)) {
    fromInteger32(thread, &self->immutableUtf8String, Arcadia_Value_getInteger32Value(&x));
  } else if (Arcadia_Value_isInteger64Value(&x)) {
    fromInteger64(thread, &self->immutableUtf8String, Arcadia_Value_getInteger64Value(&x));
  } else if (Arcadia_Value_isInteger8Value(&x)) {
    fromInteger8(thread, &self->immutableUtf8String, Arcadia_Value_getInteger8Value(&x));
  } else if (Arcadia_Value_isNatural16Value(&x)) {
    fromNatural16(thread, &self->immutableUtf8String, Arcadia_Value_getNatural16Value(&x));
  } else if (Arcadia_Value_isNatural32Value(&x)) {
    fromNatural32(thread, &self->immutableUtf8String, Arcadia_Value_getNatural32Value(&x));
  } else if (Arcadia_Value_isNatural64Value(&x)) {
    fromNatural64(thread, &self->immutableUtf8String, Arcadia_Value_getNatural64Value(&x));
  } else if (Arcadia_Value_isNatural8Value(&x)) {
    fromNatural8(thread, &self->immutableUtf8String, Arcadia_Value_getNatural8Value(&x));
  } if (Arcadia_Value_isImmutableByteArrayValue(&x)) {
    fromImmutableByteArray(thread, &self->immutableUtf8String, Arcadia_Value_getImmutableByteArrayValue(&x));
  } else if (Arcadia_Value_isImmutableUtf8StringValue(&x)) {
    fromImmutableUtf8String(thread, &self->immutableUtf8String, Arcadia_Value_getImmutableUtf8StringValue(&x));
  } else if (Arcadia_Value_isObjectReferenceValue(&x)) {
    Arcadia_ObjectReferenceValue referenceValue = Arcadia_Value_getObjectReferenceValue(&x);
    if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, referenceValue), _Arcadia_ByteBuffer_getType(thread))) {
      Arcadia_ByteBuffer* object = (Arcadia_ByteBuffer*)referenceValue;
      self->immutableUtf8String =
        Arcadia_ImmutableUtf8String_create
          (
            thread,
            Arcadia_ByteBuffer_getBytes(thread, object),
            Arcadia_ByteBuffer_getNumberOfBytes(thread, object)
          );
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, referenceValue), _Arcadia_String_getType(thread))) {
      Arcadia_String* object = (Arcadia_String*)referenceValue;
      self->immutableUtf8String = object->immutableUtf8String;
    } else if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, referenceValue), _Arcadia_StringBuffer_getType(thread))) {
      Arcadia_StringBuffer* object = (Arcadia_StringBuffer*)referenceValue;
      self->immutableUtf8String = Arcadia_ImmutableUtf8String_create(thread, Arcadia_StringBuffer_getBytes(thread, object), Arcadia_StringBuffer_getNumberOfBytes(thread, object));
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  } else if (Arcadia_Value_isVoidValue(&x)) {
    fromVoid(thread, &self->immutableUtf8String, Arcadia_Value_getVoidValue(&x));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
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
isEqualToImpl
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  Arcadia_Object* a0 = Arcadia_Value_getObjectReferenceValue(&x);
  if (!Arcadia_Value_isObjectReferenceValue(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
    return;
  }
  Arcadia_Object* b0 = Arcadia_Value_getObjectReferenceValue(&y);
  if (a0 == b0) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
    return;
  }
  assert(NULL != b0);
  assert(Arcadia_Object_isInstanceOf(thread, b0, _Arcadia_Object_getType(thread)));
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, b0), _Arcadia_String_getType(thread))) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
    return;
  }
  Arcadia_String* a1 = (Arcadia_String*)a0;
  Arcadia_String* b1 = (Arcadia_String*)b0;
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, a1->immutableUtf8String) ==
      Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, b1->immutableUtf8String) &&
      Arcadia_ImmutableUtf8String_getHash(thread, a1->immutableUtf8String) ==
      Arcadia_ImmutableUtf8String_getHash(thread, b1->immutableUtf8String)) {
    Arcadia_ValueStack_pushBooleanValue
      (
        thread,
        !Arcadia_Memory_compare
          (
            thread,
            Arcadia_ImmutableUtf8String_getBytes(thread, a1->immutableUtf8String),
            Arcadia_ImmutableUtf8String_getBytes(thread, b1->immutableUtf8String),
            Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, a1->immutableUtf8String)
          )
      );
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  }
}

static void
hashImpl
  (
    Arcadia_Thread* thread
  )
{
  UNARY_OPERATION();
  Arcadia_String* self1 = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&x);
  Arcadia_ValueStack_pushSizeValue(thread, Arcadia_ImmutableUtf8String_getHash(thread, self1->immutableUtf8String));
}

static void
isNotEqualToImpl
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  Arcadia_Object* a0 = Arcadia_Value_getObjectReferenceValue(&x);
  if (!Arcadia_Value_isObjectReferenceValue(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
    return;
  }
  Arcadia_Object* b0 = Arcadia_Value_getObjectReferenceValue(&y);
  if (a0 == b0) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
    return;
  }
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, b0), _Arcadia_String_getType(thread))) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
    return;
  }
  Arcadia_String* a1 = (Arcadia_String*)a0;
  Arcadia_String* b1 = (Arcadia_String*)b0;
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, a1->immutableUtf8String) !=
      Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, b1->immutableUtf8String) ||
      Arcadia_ImmutableUtf8String_getHash(thread, a1->immutableUtf8String) !=
      Arcadia_ImmutableUtf8String_getHash(thread, b1->immutableUtf8String)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
    return;
  }
  Arcadia_ValueStack_pushBooleanValue
    (
      thread,
      Arcadia_Memory_compare
        (
          thread,
          Arcadia_ImmutableUtf8String_getBytes(thread, a1->immutableUtf8String),
          Arcadia_ImmutableUtf8String_getBytes(thread, b1->immutableUtf8String),
          Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, a1->immutableUtf8String)
        )
    );
}

static void
Arcadia_String_visit
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  )
{
  Arcadia_ImmutableUtf8String_visit(thread, string->immutableUtf8String);
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
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      for (Arcadia_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      for (Arcadia_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      for (Arcadia_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(Arcadia_Process_getThread(process));
    }
  }
  if (!currentByteIndex) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      for (Arcadia_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      for (Arcadia_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      for (Arcadia_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
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
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(Arcadia_Process_getThread(process));
    }
  }
  if (!currentByteLength) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  *byteIndex = currentByteIndex - start;
  *byteLength = currentByteLength - start;
}

Arcadia_String*
Arcadia_String_create_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArray* immutableByteArray
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushImmutableByteArrayValue(thread, immutableByteArray);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_String);
}

Arcadia_String*
Arcadia_String_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushValue(thread, &value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_String);
}

Arcadia_BooleanValue
Arcadia_String_endsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, self->immutableUtf8String) < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, self->immutableUtf8String) - numberOfBytes;
  return !Arcadia_Memory_compare(thread,
                                 Arcadia_ImmutableUtf8String_getBytes(thread, self->immutableUtf8String) + d,
                                 bytes, numberOfBytes);
}

Arcadia_BooleanValue
Arcadia_String_startsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, self->immutableUtf8String) < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !Arcadia_Memory_compare(thread,
                                 Arcadia_ImmutableUtf8String_getBytes(thread, self->immutableUtf8String),
                                 bytes, numberOfBytes);
}

Arcadia_SizeValue
Arcadia_String_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{
  return Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, self->immutableUtf8String);
}

Arcadia_Natural8Value const*
Arcadia_String_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{
  return Arcadia_ImmutableUtf8String_getBytes(thread, self->immutableUtf8String);
}

Arcadia_Natural8Value
Arcadia_String_getByteAt
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    Arcadia_SizeValue index
  )
{
  if (index >= Arcadia_String_getNumberOfBytes(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return *(Arcadia_String_getBytes(thread, self) + index);
}

Arcadia_SizeValue
Arcadia_String_getNumberOfCodePoints
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{
  return Arcadia_ImmutableUtf8String_getNumberOfCodePoints(thread, self->immutableUtf8String);
}

#if 0
Arcadia_String*
Arcadia_String_getSubString
  (
    Arcadia_String const* self,
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
Arcadia_String_isEqualTo_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, self->immutableUtf8String) == numberOfBytes) {
    return !Arcadia_Memory_compare(thread, Arcadia_ImmutableUtf8String_getBytes(thread, self->immutableUtf8String),
                                   bytes, numberOfBytes);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

Arcadia_BooleanValue
Arcadia_String_toBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toBoolean(thread, self->immutableUtf8String); }

Arcadia_Integer16Value
Arcadia_String_toInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toInteger16(thread, self->immutableUtf8String); }

Arcadia_Integer32Value
Arcadia_String_toInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toInteger32(thread, self->immutableUtf8String); }

Arcadia_Integer64Value
Arcadia_String_toInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toInteger64(thread, self->immutableUtf8String); }

Arcadia_Integer8Value
Arcadia_String_toInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toInteger8(thread, self->immutableUtf8String); }

Arcadia_Natural16Value
Arcadia_String_toNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toNatural16(thread, self->immutableUtf8String); }

Arcadia_Natural32Value
Arcadia_String_toNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toNatural32(thread, self->immutableUtf8String); }

Arcadia_Natural64Value
Arcadia_String_toNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toNatural64(thread, self->immutableUtf8String); }

Arcadia_Natural8Value
Arcadia_String_toNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toNatural8(thread, self->immutableUtf8String); }

Arcadia_Real32Value
Arcadia_String_toReal32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_toReal32(thread, Arcadia_String_getBytes(thread, self), Arcadia_String_getNumberOfBytes(thread, self)); }

Arcadia_Real64Value
Arcadia_String_toReal64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_toReal64(thread, Arcadia_String_getBytes(thread, self), Arcadia_String_getNumberOfBytes(thread, self)); }

Arcadia_VoidValue
Arcadia_String_toVoid
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toVoid(thread, self->immutableUtf8String); }

Arcadia_String*
Arcadia_String_createFromBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue booleanValue
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromBoolean(thread, booleanValue))); }

Arcadia_String*
Arcadia_String_createFromInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromInteger16(thread, integer16Value))); }

Arcadia_String*
Arcadia_String_createFromInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromInteger32(thread, integer32Value))); }

Arcadia_String*
Arcadia_String_createFromInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromInteger64(thread, integer64Value))); }

Arcadia_String*
Arcadia_String_createFromInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromInteger8(thread, integer8Value))); }

Arcadia_String*
Arcadia_String_createFromNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromNatural16(thread, natural16Value))); }

Arcadia_String*
Arcadia_String_createFromNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromNatural32(thread, natural32Value))); }


Arcadia_String*
Arcadia_String_createFromNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromNatural64(thread, natural64Value))); }

Arcadia_String*
Arcadia_String_createFromNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromNatural8(thread, natural8Value))); }

Arcadia_String*
Arcadia_String_createFromReal32
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value real32Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromReal32(thread, real32Value))); }

Arcadia_String*
Arcadia_String_createFromReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value real64Value
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromReal64(thread, real64Value))); }

Arcadia_String*
Arcadia_String_createFromSize
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue sizeValue
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromSize(thread, sizeValue))); }

Arcadia_String*
Arcadia_String_createFromVoid
  (
    Arcadia_Thread* thread,
    Arcadia_VoidValue voidValue
  )
{ return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromVoid(thread, voidValue))); }
