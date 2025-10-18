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
#include "Arcadia/Ring1/Implementation/Void.h"

#include "Arcadia/Ring1/Implementation/_defineScalarType.h"
#include "Arcadia/Ring1/Include.h"

static void
isEqualTo
  (
    Arcadia_Thread* thread
  );

static void
hash
  (
    Arcadia_Thread* thread
  );

static void
identical
  (
    Arcadia_Thread* thread
  );

static void
isNotEqualTo
  (
    Arcadia_Thread* thread
  );

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .equalTo = &isEqualTo,
  .hash = &hash,
  .identical = &identical,
  .notEqualTo = &isNotEqualTo,
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

static void
isEqualTo
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isVoidValue(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getVoidValue(&x) == Arcadia_Value_getVoidValue(&y));
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  }
}

static void
hash
  (
    Arcadia_Thread* thread
  )
{
  UNARY_OPERATION();
  Arcadia_ValueStack_pushSizeValue(thread, (Arcadia_SizeValue)71);
}

static void
identical
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isVoidValue(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  }
}

static void
isNotEqualTo
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (Arcadia_Value_isVoidValue(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getVoidValue(&x) != Arcadia_Value_getVoidValue(&y));
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
  }
}

Arcadia_defineScalarType(Arcadia_Void, u8"Arcadia.Void", &_typeOperations);
