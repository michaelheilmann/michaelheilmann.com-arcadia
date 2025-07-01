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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toBoolean.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toReal.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toSize.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h"

#include "Arcadia/Ring1/Implementation/BooleanToString/Include.h"
#include "Arcadia/Ring1/Implementation/IntegerToString/Include.h"
#include "Arcadia/Ring1/Implementation/NaturalToString/Include.h"
#include "Arcadia/Ring1/Implementation/SizeToString/Include.h"
#include "Arcadia/Ring1/Implementation/VoidToString/Include.h"

typedef struct Context {
  Arcadia_ImmutableUtf8String* string;
} Context;

static void
Callback
  (
    Arcadia_Thread* thread,
    Context* context,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n
  )
{
  if (Arcadia_SizeValue_Maximum - sizeof(Arcadia_ImmutableUtf8String) < n) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  _ensureTypeRegistered(thread);
  Arcadia_ImmutableUtf8String* string = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &string, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableUtf8String) + n);
  Arcadia_Memory_copy(thread, string->bytes, p, n);
  string->numberOfBytes = n;
  string->hash = _hashUtf8(thread, p, n);

  context->string = string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  return _createFromBytes(thread, bytes, numberOfBytes);
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue booleanValue
  )
{ 
  Context context;
  Arcadia_BooleanValue_toUtf8String(thread, booleanValue, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  )
{
  Context context;
  Arcadia_Integer16Value_toUtf8String(thread, integer16Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  )
{
  Context context;
  Arcadia_Integer32Value_toUtf8String(thread, integer32Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  )
{
  Context context;
  Arcadia_Integer64Value_toUtf8String(thread, integer64Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  )
{
  Context context;
  Arcadia_Integer8Value_toUtf8String(thread, integer8Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  )
{
  Context context;
  Arcadia_Natural16Value_toUtf8String(thread, natural16Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  )
{
  Context context;
  Arcadia_Natural32Value_toUtf8String(thread, natural32Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  )
{
  Context context;
  Arcadia_Natural64Value_toUtf8String(thread, natural64Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  )
{
  Context context;
  Arcadia_Natural8Value_toUtf8String(thread, natural8Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromReal32
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value real32Value
  )
{
  Context context;
  Arcadia_Real32Value_toUtf8String(thread, real32Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value real64Value
  )
{
  Context context;
  Arcadia_Real64Value_toUtf8String(thread, real64Value, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromSize
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue sizeValue
  )
{
  Context context;
  Arcadia_SizeValue_toUtf8String(thread, sizeValue, &context, &Callback);
  return context.string;
}

Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromVoid
  (
    Arcadia_Thread* thread,
    Arcadia_VoidValue voidValue
  )
{
  Context context;
  Arcadia_VoidValue_toUtf8String(thread, voidValue, &context, &Callback);
  return context.string;
}

void
Arcadia_ImmutableUtf8String_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ Arcadia_Process_visitObject(Arcadia_Thread_getProcess(thread), self); }

Arcadia_Natural8Value const*
Arcadia_ImmutableUtf8String_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return self->bytes; }

Arcadia_SizeValue
Arcadia_ImmutableUtf8String_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return self->numberOfBytes; }

Arcadia_SizeValue
Arcadia_ImmutableUtf8String_getHash
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return self->hash; }

Arcadia_SizeValue
Arcadia_ImmutableUtf8String_getNumberOfCodePoints
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{
  Arcadia_SizeValue numberOfCodePoints;
  Arcadia_Unicode_isUtf8(thread, Arcadia_ImmutableUtf8String_getBytes(thread, self), Arcadia_ImmutableUtf8String_getNumberOfBytes(thread, self), &numberOfCodePoints);
  return numberOfCodePoints;
}

Arcadia_BooleanValue
Arcadia_ImmutableUtf8String_toBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toBoolean(thread, self); }

Arcadia_Integer16Value
Arcadia_ImmutableUtf8String_toInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toInteger16(thread, self); }

Arcadia_Integer32Value
Arcadia_ImmutableUtf8String_toInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toInteger32(thread, self); }

Arcadia_Integer64Value
Arcadia_ImmutableUtf8String_toInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toInteger64(thread, self); }

Arcadia_Integer8Value
Arcadia_ImmutableUtf8String_toInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toInteger8(thread, self); }

Arcadia_Natural16Value
Arcadia_ImmutableUtf8String_toNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toNatural16(thread, self); }

Arcadia_Natural32Value
Arcadia_ImmutableUtf8String_toNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toNatural32(thread, self); }

Arcadia_Natural64Value
Arcadia_ImmutableUtf8String_toNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toNatural64(thread, self); }

Arcadia_Natural8Value
Arcadia_ImmutableUtf8String_toNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toNatural8(thread, self); }

Arcadia_Real32Value
Arcadia_ImmutableUtf8String_toReal32
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toReal32(thread, self); }

Arcadia_Real64Value
Arcadia_ImmutableUtf8String_toReal64
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toReal64(thread, self); }

Arcadia_SizeValue
Arcadia_ImmutableUtf8String_toSize
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toSize(thread, self); }

Arcadia_VoidValue
Arcadia_ImmutableUtf8String_toVoid
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  )
{ return _toVoid(thread, self); }

static void
isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
hash
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isNotEqualTo
  (
    Arcadia_Thread* thread,
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
  .equalTo = &isEqualTo,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = &hash,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = &isNotEqualTo,
  .or = NULL,
  .subtract = NULL,
};

static void
isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isImmutableUtf8StringValue(A2)) {
    Arcadia_ImmutableUtf8String* a1 = Arcadia_Value_getImmutableUtf8StringValue(A1);
    Arcadia_ImmutableUtf8String* a2 = Arcadia_Value_getImmutableUtf8StringValue(A2);
    if (a1 == a2) {
      Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
    } else {
      if (a1->numberOfBytes != a2->numberOfBytes) {
        Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
      } else {
        Arcadia_Value_setBooleanValue(target, Arcadia_Memory_compare(thread, a1->bytes, a2->bytes, a1->numberOfBytes) == 0);
      }
    }
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
hash
  (
    Arcadia_Thread* thread,
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
isNotEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isImmutableUtf8StringValue(A2)) {
    Arcadia_ImmutableUtf8String* a1 = Arcadia_Value_getImmutableUtf8StringValue(A1);
    Arcadia_ImmutableUtf8String* a2 = Arcadia_Value_getImmutableUtf8StringValue(A2);
    if (a1 == a2) {
      Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
    } else {
      if (a1->numberOfBytes != a2->numberOfBytes) {
        Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
      } else {
        Arcadia_Value_setBooleanValue(target, Arcadia_Memory_compare(thread, a1->bytes, a2->bytes, a1->numberOfBytes) != 0);
      }
    }
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
    Arcadia_Thread* thread
  )
{
  if (!g_type) {
    g_type = Arcadia_registerInternalType(thread, TypeName, sizeof(TypeName) - 1, &_typeOperations, &typeDestructing);
  }
  return g_type;
}
