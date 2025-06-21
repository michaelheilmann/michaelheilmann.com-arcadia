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
#include "Arcadia/Ring1/Implementation/ImmutableByteArray.h"

#include "Arcadia/Ring1/Include.h"

#define TypeName u8"Arcadia.ImmutableByteArray"

static Arcadia_BooleanValue g_registered = Arcadia_BooleanValue_False;

static void
onTypeRemoved
  (
    Arcadia_Thread* thread,
    const uint8_t* bytes,
    size_t numberOfBytes
  )
{ g_registered = Arcadia_BooleanValue_False; }

Arcadia_ImmutableByteArray*
Arcadia_ImmutableByteArray_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!bytes) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (SIZE_MAX - sizeof(Arcadia_ImmutableByteArray) < numberOfBytes) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!g_registered) {
    Arcadia_Process_registerType(Arcadia_Thread_getProcess(thread), TypeName, sizeof(TypeName) - 1, thread, &onTypeRemoved, NULL, NULL);
    g_registered = Arcadia_BooleanValue_True;
  }
  Arcadia_ImmutableByteArray*array = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &array, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_ImmutableByteArray) + numberOfBytes);
  Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), array->bytes, bytes, numberOfBytes);
  array->numberOfBytes = numberOfBytes;
  return array;
}

void
Arcadia_ImmutableByteArray_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArrayValue self
  )
{ Arcadia_Process_visitObject(Arcadia_Thread_getProcess(thread), self); }

Arcadia_Natural8Value const*
Arcadia_ImmutableByteArray_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArrayValue self
  )
{ return self->bytes; }

Arcadia_SizeValue
Arcadia_ImmutableByteArray_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArrayValue self
  )
{ return self->numberOfBytes; }

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
  .identical = NULL,
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
  if (Arcadia_Value_isImmutableByteArrayValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getImmutableByteArrayValue(A1) == Arcadia_Value_getImmutableByteArrayValue(A2));
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
  Arcadia_Value_setSizeValue(target, (Arcadia_SizeValue)(uintptr_t)Arcadia_Value_getImmutableByteArrayValue(A1));
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
  if (Arcadia_Value_isImmutableByteArrayValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getImmutableByteArrayValue(A1) != Arcadia_Value_getImmutableByteArrayValue(A2));
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
_Arcadia_ImmutableByteArrayValue_getType
  (
    Arcadia_Thread* thread
  )
{
  if (!g_type) {
    g_type = Arcadia_registerInternalType(thread, TypeName, sizeof(TypeName) - 1, &_typeOperations, &typeDestructing);
  }
  return g_type;
}
