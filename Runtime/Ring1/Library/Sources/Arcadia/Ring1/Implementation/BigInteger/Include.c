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
#include "Arcadia/Ring1/Implementation/BigInteger/Include.h"

#include "Arcadia/Ring1/Include.h"

#define TypeName u8"Arcadia.BigInteger"

static Arcadia_BooleanValue g_registered = Arcadia_BooleanValue_False;

static void
onFinalize
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  if (self->limps) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->limps);
    self->limps = NULL;
  }
}

static void
onTypeRemoved
  (
    Arcadia_Thread* thread,
    const uint8_t* bytes,
    size_t numberOfBytes
  )
{
  g_registered = Arcadia_BooleanValue_False;
}

Arcadia_BigInteger*
Arcadia_BigInteger_create
  (
    Arcadia_Thread* thread
  )
{
  if (!g_registered) {
    Arcadia_Process_registerType(Arcadia_Thread_getProcess(thread), TypeName, sizeof(TypeName) - 1, thread, &onTypeRemoved, NULL, &onFinalize);
    g_registered = Arcadia_BooleanValue_True;
  }
  Arcadia_BigInteger* self = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &self, TypeName, sizeof(TypeName) - 1, sizeof(Arcadia_BigInteger));
  self->numberOfLimps = 0;
  self->limps = NULL;
  self->sign = 0;
  self->limps = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_BigInteger_Limp) * 0);
  return self;
}

void
Arcadia_BigInteger_swap
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  if (self != other) {
    Arcadia_swapPointer(thread, &self->limps, &other->limps);
    Arcadia_swapSize(thread, &self->numberOfLimps, &other->numberOfLimps);
    Arcadia_swapInteger8(thread, &self->sign, &other->sign);
  }
}

void
Arcadia_BigInteger_copy
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  if (self != other) {
    if (self->numberOfLimps < other->numberOfLimps) {
      Arcadia_Memory_reallocateUnmanaged(thread, &self->limps, sizeof(Arcadia_BigInteger_Limp) * other->numberOfLimps);
    }
    Arcadia_Memory_copy(thread, self->limps, other->limps, sizeof(Arcadia_BigInteger_Limp) * other->numberOfLimps);
    self->numberOfLimps = other->numberOfLimps;
    self->sign = other->sign;
  }
}

void
Arcadia_BigInteger_setZero
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  self->sign = 0;
  self->numberOfLimps = 0;
}

Arcadia_BooleanValue
Arcadia_BigInteger_isZero
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{ return 0 == self->sign; }

Arcadia_BooleanValue
Arcadia_BigInteger_isPositive
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{ return +1 == self->sign; }

Arcadia_BooleanValue
Arcadia_BigInteger_isNegative
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{ return -1 == self->sign; }

void
Arcadia_BigInteger_visit
  (
    Arcadia_Thread* thread,
    Arcadia_BigIntegerValue self
  )
{
  Arcadia_Process_visitObject(Arcadia_Thread_getProcess(thread), self);
}

static void
isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isGreaterThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isGreaterThanOrEqualTo
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
isLowerThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isLowerThanOrEqualTo
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
  Arcadia_Type_Operations_Initializer,
  .equalTo = &isEqualTo,
  .greaterThan = &isGreaterThan,
  .greaterThanOrEqualTo = &isGreaterThanOrEqualTo,
  .hash = &hash,
  .lowerThan = &isLowerThan,
  .lowerThanOrEqualTo = &isLowerThanOrEqualTo,
  .notEqualTo = &isNotEqualTo,
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
  if (Arcadia_Value_isBigIntegerValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BigInteger_equalTo(thread, Arcadia_Value_getBigIntegerValue(A1),  Arcadia_Value_getBigIntegerValue(A2)));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
isGreaterThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isBigIntegerValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BigInteger_greaterThan(thread, Arcadia_Value_getBigIntegerValue(A1), Arcadia_Value_getBigIntegerValue(A2)));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
isGreaterThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isBigIntegerValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BigInteger_greaterThanOrEqualTo(thread, Arcadia_Value_getBigIntegerValue(A1), Arcadia_Value_getBigIntegerValue(A2)));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
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
  Arcadia_Value_setSizeValue(target, (Arcadia_SizeValue)(uintptr_t)Arcadia_Value_getBigIntegerValue(A1));
#undef A1
}

static void
isLowerThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isBigIntegerValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BigInteger_lowerThan(thread, Arcadia_Value_getBigIntegerValue(A1), Arcadia_Value_getBigIntegerValue(A2)));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
isLowerThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isBigIntegerValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BigInteger_lowerThanOrEqualTo(thread, Arcadia_Value_getBigIntegerValue(A1), Arcadia_Value_getBigIntegerValue(A2)));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
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
  if (Arcadia_Value_isBigIntegerValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_BigInteger_notEqualTo(thread, Arcadia_Value_getBigIntegerValue(A1), Arcadia_Value_getBigIntegerValue(A2)));
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
_Arcadia_BigIntegerValue_getType
  (
    Arcadia_Thread* thread
  )
{
  if (!g_type) {
    g_type = Arcadia_registerInternalType(thread, TypeName, sizeof(TypeName) - 1, &_typeOperations, &typeDestructing);
  }
  return g_type;
}

#include <stdio.h>

void
Arcadia_BigInteger_toStdoutDebug
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  if (Arcadia_BigInteger_isZero(thread, self)) {
    fprintf(stdout, "%s\n", "0");
  } else {
    Arcadia_BigInteger* ten = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_setInteger16(thread, ten, 10);
    Arcadia_BigInteger* quotient = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_copy(thread, quotient, self);
    Arcadia_BigInteger* remainder = Arcadia_BigInteger_create(thread);
    if (Arcadia_BigInteger_isNegative(thread, self)) {
      fprintf(stdout, "-");
    }
    Arcadia_SizeValue i = 0, n = 1024;
    char* p = Arcadia_Memory_allocateUnmanaged(thread, 1024);
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      do {
        Arcadia_BigInteger_divide3(thread, quotient, ten, quotient, remainder);
        Arcadia_Natural8Value digit = Arcadia_BigInteger_toNatural8(thread, remainder);
        if (i == n) {
          Arcadia_SizeValue m = 2 * n;
          if (m < n) {
            Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
            Arcadia_Thread_jump(thread);
          }
          Arcadia_Memory_reallocateUnmanaged(thread, &p, m);
          n = m;
        }
        p[i++] = (char)(digit + '0');

      } while (!Arcadia_BigInteger_isZero(thread, quotient));
      for (Arcadia_SizeValue j = 0; j < i / 2; ++j) {
        char t = p[j];
        p[j] = p[i - j - 1];
        p[i - j - 1] = t;
      }
      p[i] = '\0';
      fprintf(stdout, "%s\n", p);
    }
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Memory_deallocateUnmanaged(thread, p);
    p = NULL;
  }
}

void
_Arcadia_BigInteger_stripLeadingZeroes
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger_Limp** limps,
    Arcadia_SizeValue* numberOfLimps
  )
{
  while ((*numberOfLimps)> 0 && !(*limps)[(*numberOfLimps) - 1]) {
    (*numberOfLimps)--;
  }
}
