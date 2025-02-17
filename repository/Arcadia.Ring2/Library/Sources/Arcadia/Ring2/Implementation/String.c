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

#include "Arcadia/Ring2/Implementation/String.h"

#include "R/Convert/Include.h"
#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/Implementation/StringBuffer.h"

static void
Arcadia_String_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
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
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
hashImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
notEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
Arcadia_String_visit
  (
    Arcadia_Process* process,
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
  .construct = &Arcadia_String_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_String_visit,
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

Rex_defineObjectType(u8"Arcadia.String", Arcadia_String, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

#define On(Type, Suffix) \
  static void \
  from##Suffix \
    ( \
      Arcadia_Process* process, \
      Arcadia_ImmutableUtf8String** pImmutableUtf8String, \
      Type##Value value \
    ) \
  { \
    *pImmutableUtf8String = Arcadia_ImmutableUtf8String_createFrom##Suffix(Arcadia_Process_getProcess1(process), value); \
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
    Arcadia_Process* process,
    Arcadia_ImmutableUtf8String** pImmutableUtf8String,
    Arcadia_ImmutableByteArray* value
  ) 
{
  *pImmutableUtf8String =
    Arcadia_ImmutableUtf8String_create
      (
        Arcadia_Process_getProcess1(process),
        Arcadia_ImmutableByteArray_getBytes(Arcadia_Process_getProcess1(process), value),
        Arcadia_ImmutableByteArray_getNumberOfBytes(Arcadia_Process_getProcess1(process), value)
      );
}

static void
fromImmutableUtf8String
  (
    Arcadia_Process* process,
    Arcadia_ImmutableUtf8String** pImmutableUtf8String,
    Arcadia_ImmutableUtf8String* value
  )
{
  *pImmutableUtf8String = value;
}

static void
Arcadia_String_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  if (1 != numberOfArguments) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_String* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_String_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_Value_isBooleanValue(&arguments[0])) {
    fromBoolean(process, &_self->immutableUtf8String, Arcadia_Value_getBooleanValue(&arguments[0]));
  } else if (Arcadia_Value_isInteger16Value(&arguments[0])) {
    fromInteger16(process, &_self->immutableUtf8String, Arcadia_Value_getInteger16Value(&arguments[0]));
  } else if (Arcadia_Value_isInteger32Value(&arguments[0])) {
    fromInteger32(process, &_self->immutableUtf8String, Arcadia_Value_getInteger32Value(&arguments[0]));
  } else if (Arcadia_Value_isInteger64Value(&arguments[0])) {
    fromInteger64(process, &_self->immutableUtf8String, Arcadia_Value_getInteger64Value(&arguments[0]));
  } else if (Arcadia_Value_isInteger8Value(&arguments[0])) {
    fromInteger8(process, &_self->immutableUtf8String, Arcadia_Value_getInteger8Value(&arguments[0]));
  } else if (Arcadia_Value_isNatural16Value(&arguments[0])) {
    fromNatural16(process, &_self->immutableUtf8String, Arcadia_Value_getNatural16Value(&arguments[0]));
  } else if (Arcadia_Value_isNatural32Value(&arguments[0])) {
    fromNatural32(process, &_self->immutableUtf8String, Arcadia_Value_getNatural32Value(&arguments[0]));
  } else if (Arcadia_Value_isNatural64Value(&arguments[0])) {
    fromNatural64(process, &_self->immutableUtf8String, Arcadia_Value_getNatural64Value(&arguments[0]));
  } else if (Arcadia_Value_isNatural8Value(&arguments[0])) {
    fromNatural8(process, &_self->immutableUtf8String, Arcadia_Value_getNatural8Value(&arguments[0]));
  } if (Arcadia_Value_isImmutableByteArrayValue(&arguments[0])) {
    fromImmutableByteArray(process, &_self->immutableUtf8String, Arcadia_Value_getImmutableByteArrayValue(&arguments[0]));
  } else if (Arcadia_Value_isImmutableUtf8StringValue(&arguments[0])) {
    fromImmutableUtf8String(process, &_self->immutableUtf8String, Arcadia_Value_getImmutableUtf8StringValue(&arguments[0]));
  } else if (Arcadia_Value_isObjectReferenceValue(&arguments[0])) {
    Arcadia_ObjectReferenceValue referenceValue = Arcadia_Value_getObjectReferenceValue(&arguments[0]);
    if (Arcadia_Type_isSubType(Arcadia_Object_getType(referenceValue), _Arcadia_ByteBuffer_getType(process))) {
      Arcadia_ByteBuffer* object = (Arcadia_ByteBuffer*)referenceValue;
      _self->immutableUtf8String =
        Arcadia_ImmutableUtf8String_create
          (
            Arcadia_Process_getProcess1(process),
            Arcadia_ByteBuffer_getBytes(process, object),
            Arcadia_ByteBuffer_getNumberOfBytes(process, object)
          );
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(referenceValue), _Arcadia_String_getType(process))) {
      Arcadia_String* object = (Arcadia_String*)referenceValue;
      _self->immutableUtf8String = object->immutableUtf8String;
    } else if (Arcadia_Type_isSubType(Arcadia_Object_getType(referenceValue), _Arcadia_StringBuffer_getType(process))) {
      Arcadia_StringBuffer* object = (Arcadia_StringBuffer*)referenceValue;
      _self->immutableUtf8String = Arcadia_ImmutableUtf8String_create(Arcadia_Process_getProcess1(process), Arcadia_StringBuffer_getBytes(object), Arcadia_StringBuffer_getNumberOfBytes(object));
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Process_jump(process);
    }

  } else if (Arcadia_Value_isVoidValue(&arguments[0])) {
    fromVoid(process, &_self->immutableUtf8String, Arcadia_Value_getVoidValue(&arguments[0]));
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Object_setType(process, _self, _type);
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
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  Arcadia_String* self1 = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(A1);
  if (!Arcadia_Value_isObjectReferenceValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
    return;
  }
  Arcadia_Object* other1 = Arcadia_Value_getObjectReferenceValue(A2);
  if ((Arcadia_Object*)self1 == other1) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
    return;
  }
  if (!Arcadia_Type_isSubType(Arcadia_Object_getType(other1), _Arcadia_String_getType(process))) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
    return;
  }
  Arcadia_String* otherString1 = (Arcadia_String*)other1;
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self1->immutableUtf8String) == Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), otherString1->immutableUtf8String)) {
    Arcadia_Value_setBooleanValue(target, !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), Arcadia_ImmutableUtf8String_getBytes(Arcadia_Process_getProcess1(process), self1->immutableUtf8String),
                                          Arcadia_ImmutableUtf8String_getBytes(Arcadia_Process_getProcess1(process), otherString1->immutableUtf8String),
                                          Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self1->immutableUtf8String)));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
hashImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_String* self1 = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(A1);
  Arcadia_Value_setSizeValue(target, Arcadia_ImmutableUtf8String_getHash(Arcadia_Process_getProcess1(process), self1->immutableUtf8String));
#undef A1
}

static void
notEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  Arcadia_String* self1 = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(A1);
  if (!Arcadia_Value_isObjectReferenceValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
    return;
  }
  Arcadia_Object* other1 = Arcadia_Value_getObjectReferenceValue(A2);
  if ((Arcadia_Object*)self1 != other1) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
    return;
  }
  if (!Arcadia_Type_isSubType(Arcadia_Object_getType(other1), _Arcadia_String_getType(process))) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
    return;
  }
  Arcadia_String* otherString1 = (Arcadia_String*)other1;
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self1->immutableUtf8String) != Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), otherString1->immutableUtf8String)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
    return;
  }
  Arcadia_Value_setBooleanValue(target,
                                Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process),
                                                               Arcadia_ImmutableUtf8String_getBytes(Arcadia_Process_getProcess1(process), self1->immutableUtf8String),
                                                               Arcadia_ImmutableUtf8String_getBytes(Arcadia_Process_getProcess1(process), otherString1->immutableUtf8String),
                                                               Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self1->immutableUtf8String)));
#undef A2
#undef A1
}

static void
Arcadia_String_visit
  (
    Arcadia_Process* process,
    Arcadia_String* string
  )
{ 
  Arcadia_ImmutableUtf8String_visit(Arcadia_Process_getProcess1(process), string->immutableUtf8String);
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

Arcadia_String*
Arcadia_String_create_pn
  (
    Arcadia_Process* process,
    Arcadia_ImmutableByteArray* immutableByteArray
  )
{
  Arcadia_Value argumentValues[] = { { .tag = Arcadia_ValueTag_ImmutableByteArray, .immutableByteArrayValue = immutableByteArray } };
  Arcadia_String* self = R_allocateObject(process, _Arcadia_String_getType(process), 1, &argumentValues[0]);
  return self;
}

Arcadia_String*
Arcadia_String_create
  (
    Arcadia_Process* process,
    Arcadia_Value value
  )
{ 
  Arcadia_Value argumentValues[] = { value };
  Arcadia_String* self = R_allocateObject(process, _Arcadia_String_getType(process), 1, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
Arcadia_String_endsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String) < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String) - numberOfBytes;
  return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process),
                                         Arcadia_ImmutableUtf8String_getBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String) + d,
                                         bytes, numberOfBytes);
}

Arcadia_BooleanValue
Arcadia_String_startsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String) < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process),
                                         Arcadia_ImmutableUtf8String_getBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String),
                                         bytes, numberOfBytes);
}

Arcadia_SizeValue
Arcadia_String_getNumberOfBytes
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{
  return Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String);
}

Arcadia_Natural8Value const*
Arcadia_String_getBytes
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{
  return Arcadia_ImmutableUtf8String_getBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String);
}

Arcadia_Natural8Value
Arcadia_String_getByteAt
  (
    Arcadia_Process* process,
    Arcadia_String const* self,
    Arcadia_SizeValue index
  )
{
  if (index >= Arcadia_String_getNumberOfBytes(process, self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return *(Arcadia_String_getBytes(process, self) + index);
}

Arcadia_SizeValue
Arcadia_String_getNumberOfSymbols
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{
  Arcadia_SizeValue numberOfSymbols;
  Arcadia_isUtf8(process, Arcadia_String_getBytes(process, self), Arcadia_String_getNumberOfBytes(process, self), &numberOfSymbols);
  return numberOfSymbols;
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
    Arcadia_Process* process,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (Arcadia_ImmutableUtf8String_getNumberOfBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String) == numberOfBytes) {
    return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), Arcadia_ImmutableUtf8String_getBytes(Arcadia_Process_getProcess1(process), self->immutableUtf8String),
                                           bytes, numberOfBytes);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

Arcadia_BooleanValue
Arcadia_String_toBoolean
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toBoolean(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Integer16Value
Arcadia_String_toInteger16
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toInteger16(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Integer32Value
Arcadia_String_toInteger32
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toInteger32(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Integer64Value
Arcadia_String_toInteger64
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toInteger64(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Integer8Value
Arcadia_String_toInteger8
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toInteger8(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Natural16Value
Arcadia_String_toNatural16
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toNatural16(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Natural32Value
Arcadia_String_toNatural32
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toNatural32(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Natural64Value
Arcadia_String_toNatural64
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toNatural64(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Natural8Value
Arcadia_String_toNatural8
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toNatural8(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }

Arcadia_Real32Value
Arcadia_String_toReal32
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return R_toReal32(process, Arcadia_String_getBytes(process, self), Arcadia_String_getNumberOfBytes(process, self)); }

Arcadia_Real64Value
Arcadia_String_toReal64
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return R_toReal64(process, Arcadia_String_getBytes(process, self), Arcadia_String_getNumberOfBytes(process, self)); }

Arcadia_VoidValue
Arcadia_String_toVoid
  (
    Arcadia_Process* process,
    Arcadia_String const* self
  )
{ return Arcadia_ImmutableUtf8String_toVoid(Arcadia_Process_getProcess1(process), self->immutableUtf8String); }
