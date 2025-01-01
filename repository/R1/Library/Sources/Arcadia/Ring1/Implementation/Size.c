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

// Last modified: 2024-10-27

#include "Arcadia/Ring1/Implementation/Size.h"

#include "Arcadia/Ring1/Include.h"
#include "R/Value.h"

static void
add
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
divide
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
equalTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
greaterThan
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
hash
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  );

static void
lowerThan
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
multiply
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
negate
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  );

static void
notEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
subtract
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = NULL,
  .add = &add,
  .and = NULL,
  .concatenate = NULL,
  .divide = &divide,
  .equalTo = &equalTo,
  .greaterThan = &greaterThan,
  .greaterThanOrEqualTo = &greaterThanOrEqualTo,
  .hash = &hash,
  .lowerThan = &lowerThan,
  .lowerThanOrEqualTo = &lowerThanOrEqualTo,
  .multiply = &multiply,
  .negate = &negate,
  .not = NULL,
  .notEqualTo = &notEqualTo,
  .or = NULL,
  .subtract = &subtract,
};

static void
add
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  c_static_assert(Arcadia_SizeValue_Minimum >= Arcadia_SizeValue_Literal(0), "environment not (yet) supported");
  if (R_Value_isSizeValue(other)) {
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) + R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) + (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) + (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) + (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setNatural64Value(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) + R_Value_getNatural64Value(other));
  #else
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) + (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
divide
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  c_static_assert(Arcadia_SizeValue_Minimum >= Arcadia_SizeValue_Literal(0), "environment not (yet) supported");
  if (R_Value_isSizeValue(other)) {
    Arcadia_SizeValue x = R_Value_getSizeValue(other);
    if (Arcadia_SizeValue_Literal(0) == x) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) / x);
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Natural8Value x = R_Value_getNatural8Value(other);
    if (Arcadia_Natural8Value_Literal(0) == x) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) / (Arcadia_SizeValue)x);
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Natural16Value x = R_Value_getNatural16Value(other);
    if (Arcadia_Natural16Value_Literal(0) == x) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) / (Arcadia_SizeValue)x);
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Natural32Value x = R_Value_getNatural32Value(other);
    if (Arcadia_Natural32Value_Literal(0) == x) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) / (Arcadia_SizeValue)x);
  } else if (R_Value_isNatural64Value(other)) {
    Arcadia_Natural64Value x = R_Value_getNatural64Value(other);
    if (Arcadia_Natural64Value_Literal(0) == x) {
      Arcadia_Process_setStatus(process, Arcadia_Status_DivisionByZero);
      Arcadia_Process_jump(process);
    }
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setNatural64Value(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) / x);
  #else
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) / (Arcadia_SizeValue)x);
  #endif
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
equalTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) == R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
}

static void
greaterThan
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) > R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) >= R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
hash
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setSizeValue(target, (Arcadia_SizeValue)R_Value_getNatural64Value(self));
}

static void
lowerThan
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) < R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) <= R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
multiply
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  c_static_assert(Arcadia_SizeValue_Minimum >= Arcadia_SizeValue_Literal(0), "environment not (yet) supported");
  if (R_Value_isSizeValue(other)) {
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) * R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) * (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) * (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) * (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setNatural64Value(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) * R_Value_getNatural64Value(other));
  #else
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) * (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

static void
negate
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setSizeValue(target, -R_Value_getSizeValue(self));
}

static void
notEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) != R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
}

static void
subtract
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  c_static_assert(Arcadia_SizeValue_Minimum >= Arcadia_SizeValue_Literal(0), "environment not (yet) supported");
  if (R_Value_isSizeValue(other)) {
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) - R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) - (Arcadia_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) - (Arcadia_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) - (Arcadia_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    R_Value_setNatural64Value(target, (Arcadia_Natural64Value)R_Value_getSizeValue(self) * R_Value_getNatural64Value(other));
  #else
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) - (Arcadia_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
}

Rex_defineScalarType(Arcadia_Size, u8"Arcadia.Size", &_typeOperations);
