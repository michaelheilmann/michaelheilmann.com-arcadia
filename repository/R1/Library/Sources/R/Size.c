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

// Last modified: 2024-10-27

#include "R/Size.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Value.h"

static void
add
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
divide
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
equalTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
greaterThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
greaterThanOrEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
hash
  (
    R_Value* target,
    R_Value const* self
  );

static void
lowerThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
lowerThanOrEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
multiply
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
negate
  (
    R_Value* target,
    R_Value const* self
  );

static void
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
subtract
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const R_Type_Operations typeOperations = {
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
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  c_static_assert(R_SizeValue_Minimum >= R_SizeValue_Literal(0), "environment not (yet) supported");
  if (R_Value_isSizeValue(other)) {
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) + R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) + (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) + (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) + (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setNatural64Value(target, (R_Natural64Value)R_Value_getSizeValue(self) + R_Value_getNatural64Value(other));
  #else
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) + (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
divide
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  c_static_assert(R_SizeValue_Minimum >= R_SizeValue_Literal(0), "environment not (yet) supported");
  if (R_Value_isSizeValue(other)) {
    R_SizeValue x = R_Value_getSizeValue(other);
    if (R_SizeValue_Literal(0) == x) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) / x);
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Natural8Value x = R_Value_getNatural8Value(other);
    if (R_Natural8Value_Literal(0) == x) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) / (R_SizeValue)x);
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Natural16Value x = R_Value_getNatural16Value(other);
    if (R_Natural16Value_Literal(0) == x) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) / (R_SizeValue)x);
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Natural32Value x = R_Value_getNatural32Value(other);
    if (R_Natural32Value_Literal(0) == x) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) / (R_SizeValue)x);
  } else if (R_Value_isNatural64Value(other)) {
    R_Natural64Value x = R_Value_getNatural64Value(other);
    if (R_Natural64Value_Literal(0) == x) {
      R_setStatus(R_Status_DivisionByZero);
      R_jump();
    }
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setNatural64Value(target, (R_Natural64Value)R_Value_getSizeValue(self) / x);
  #else
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) / (R_SizeValue)x);
  #endif
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
equalTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (R_Natural64Value)R_Value_getSizeValue(self) == R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) == (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_False);
  }
}

static void
greaterThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (R_Natural64Value)R_Value_getSizeValue(self) > R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) > (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
greaterThanOrEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (R_Natural64Value)R_Value_getSizeValue(self) >= R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) >= (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
hash
  (
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setSizeValue(target, (R_SizeValue)R_Value_getNatural64Value(self));
}

static void
lowerThan
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (R_Natural64Value)R_Value_getSizeValue(self) < R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) < (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
lowerThanOrEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (R_Natural64Value)R_Value_getSizeValue(self) <= R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) <= (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
multiply
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  c_static_assert(R_SizeValue_Minimum >= R_SizeValue_Literal(0), "environment not (yet) supported");
  if (R_Value_isSizeValue(other)) {
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) * R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) * (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) * (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) * (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setNatural64Value(target, (R_Natural64Value)R_Value_getSizeValue(self) * R_Value_getNatural64Value(other));
  #else
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) * (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static void
negate
  (
    R_Value* target,
    R_Value const* self
  )
{
  R_Value_setSizeValue(target, -R_Value_getSizeValue(self));
}

static void
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isSizeValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setBooleanValue(target, (R_Natural64Value)R_Value_getSizeValue(self) != R_Value_getNatural64Value(other));
  #else
    R_Value_setBooleanValue(target, R_Value_getSizeValue(self) != (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_True);
  }
}

static void
subtract
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  c_static_assert(R_SizeValue_Minimum >= R_SizeValue_Literal(0), "environment not (yet) supported");
  if (R_Value_isSizeValue(other)) {
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) - R_Value_getSizeValue(other));
  } else if (R_Value_isNatural8Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural8Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) - (R_SizeValue)R_Value_getNatural8Value(other));
  } else if (R_Value_isNatural16Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural16Value_Maximum, "environment not (yet) supported");
    R_Value_setNatural64Value(target, R_Value_getSizeValue(self) - (R_SizeValue)R_Value_getNatural16Value(other));
  } else if (R_Value_isNatural32Value(other)) {
    c_static_assert(R_SizeValue_Maximum >= R_Natural32Value_Maximum, "environment not (yet) supported");
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) - (R_SizeValue)R_Value_getNatural32Value(other));
  } else if (R_Value_isNatural64Value(other)) {
  #if R_SizeValue_Maximum < R_Natural64Value_Maximum
    R_Value_setNatural64Value(target, (R_Natural64Value)R_Value_getSizeValue(self) * R_Value_getNatural64Value(other));
  #else
    R_Value_setSizeValue(target, R_Value_getSizeValue(self) - (R_SizeValue)R_Value_getNatural64Value(other));
  #endif
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
}

static R_Type* g_type = NULL;

static void
typeDestructing
  (
    void* context
  )
{
  g_type = NULL;
}

R_Type*
_R_SizeValue_getType
  (
  )
{
  if (!g_type) {
    R_registerRealType(u8"R.Size", sizeof("R.Size") - 1, &typeOperations, &typeDestructing);
    g_type = R_getType(u8"R.Size", sizeof("R.Size") - 1);
  }
  return g_type;
}
