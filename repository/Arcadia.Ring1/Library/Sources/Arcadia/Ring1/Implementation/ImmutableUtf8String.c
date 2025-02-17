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

// Last modified: 2025-02-16

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBoolean.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromInteger.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromNatural.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromVoid.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toBoolean.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h"

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_create
  (
    Arcadia_Process1* process,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  return _createFromBytes(process, bytes, numberOfBytes);
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromBoolean
  (
    Arcadia_Process1* process,
    Arcadia_BooleanValue booleanValue
  )
{ return _createFromBoolean(process, booleanValue); }


Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger16
  (
    Arcadia_Process1* process,
    Arcadia_Integer16Value integer16Value
  )
{ return _createFromInteger16(process, integer16Value); }

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger32
  (
    Arcadia_Process1* process,
    Arcadia_Integer32Value integer32Value
  )
{ return _createFromInteger32(process, integer32Value); }

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger64
  (
    Arcadia_Process1* process,
    Arcadia_Integer64Value integer64Value
  )
{ return _createFromInteger64(process, integer64Value); }

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger8
  (
    Arcadia_Process1* process,
    Arcadia_Integer8Value integer8Value
  )
{ return _createFromInteger8(process, integer8Value); }

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural16
  (
    Arcadia_Process1* process,
    Arcadia_Natural16Value natural16Value
  )
{ return _createFromNatural16(process, natural16Value); }

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural32
  (
    Arcadia_Process1* process,
    Arcadia_Natural32Value natural32Value
  )
{ return _createFromNatural32(process, natural32Value); }

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural64
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value natural64Value
  )
{ return _createFromNatural64(process, natural64Value); }

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural8
  (
    Arcadia_Process1* process,
    Arcadia_Natural8Value natural8Value
  )
{ return _createFromNatural8(process, natural8Value); }

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromVoid
  (
    Arcadia_Process1* process,
    Arcadia_VoidValue voidValue
  )
{ return _createFromVoid(process, voidValue); }

void
Arcadia_ImmutableUtf8String_visit
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ Arcadia_Process1_visitObject(process, self); }

Arcadia_Natural8Value const*
Arcadia_ImmutableUtf8String_getBytes
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return self->bytes; }

Arcadia_SizeValue
Arcadia_ImmutableUtf8String_getNumberOfBytes
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return self->numberOfBytes; }

Arcadia_SizeValue
Arcadia_ImmutableUtf8String_getHash
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return self->hash; }

Arcadia_BooleanValue
Arcadia_ImmutableUtf8String_toBoolean
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toBoolean(process, self); }

Arcadia_Integer16Value
Arcadia_ImmutableUtf8String_toInteger16
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toInteger16(process, self); }

Arcadia_Integer32Value
Arcadia_ImmutableUtf8String_toInteger32
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toInteger32(process, self); }

Arcadia_Integer64Value
Arcadia_ImmutableUtf8String_toInteger64
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toInteger64(process, self); }

Arcadia_Integer8Value
Arcadia_ImmutableUtf8String_toInteger8
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toInteger8(process, self); }

Arcadia_Natural16Value
Arcadia_ImmutableUtf8String_toNatural16
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toNatural16(process, self); }

Arcadia_Natural32Value
Arcadia_ImmutableUtf8String_toNatural32
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toNatural32(process, self); }

Arcadia_Natural64Value
Arcadia_ImmutableUtf8String_toNatural64
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toNatural64(process, self); }

Arcadia_Natural8Value
Arcadia_ImmutableUtf8String_toNatural8
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toNatural8(process, self); }

Arcadia_VoidValue
Arcadia_ImmutableUtf8String_toVoid
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toVoid(process, self); }

static void
equalTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
hash
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
notEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = NULL,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &equalTo,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = &hash,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = &notEqualTo,
  .or = NULL,
  .subtract = NULL,
};

static void
equalTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isImmutableUtf8StringValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getImmutableUtf8StringValue(A1) == Arcadia_Value_getImmutableUtf8StringValue(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
hash
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setSizeValue(target, (Arcadia_SizeValue)(uintptr_t)Arcadia_Value_getImmutableUtf8StringValue(A1));
#undef A1
}

static void
notEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isImmutableUtf8StringValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getImmutableUtf8StringValue(A1) != Arcadia_Value_getImmutableUtf8StringValue(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
#undef A2
#undef A1
}

static Arcadia_TypeValue g_type = NULL;

static void
typeDestructing
  (
    void* context
  )
{
  g_type = NULL;
}

Arcadia_TypeValue
_Arcadia_ImmutableUtf8StringValue_getType
  (
    Arcadia_Process* process
  )
{
  if (!g_type) {
    g_type = Arcadia_registerInternalType(process, TypeName, sizeof(TypeName) - 1, &_typeOperations, &typeDestructing);
  }
  return g_type;
}
