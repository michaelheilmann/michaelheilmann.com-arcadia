#include "R/BigInteger/Include.h"

#include "R/ArgumentsValidation.h"
#include "R/BigInteger/add.h"
#include "R/BigInteger/digits.h"
#include "R/BigInteger/from.h"

static void
R_BigInteger_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
R_BigInteger_destruct
  (
    Arcadia_Process* process,
    R_BigInteger* self
  );

static void
R_BigInteger_equalToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
R_BigInteger_greaterThanImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
R_BigInteger_greaterThanOrEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
R_BigInteger_lowerThanImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
R_BigInteger_lowerThanOrEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
R_BigInteger_notEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_BigInteger_constructImpl,
  .destruct = &R_BigInteger_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &R_BigInteger_equalToImpl,
  .greaterThan = &R_BigInteger_greaterThanImpl,
  .greaterThanOrEqualTo = &R_BigInteger_greaterThanOrEqualToImpl,
  .hash = NULL,
  .lowerThan = &R_BigInteger_lowerThanImpl,
  .lowerThanOrEqualTo = &R_BigInteger_lowerThanOrEqualToImpl,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = &R_BigInteger_notEqualToImpl,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"R.BigInteger", R_BigInteger, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_BigInteger_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  R_BigInteger* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_BigInteger_getType(process);
  {
    Arcadia_Value arguments[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &arguments[0]);
  }
  if (numberOfArguments < 1) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Value_isInteger32Value(&arguments[0])) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  switch (Arcadia_Value_getInteger32Value(&arguments[0])) {
    case Operation_Create: {
      if (numberOfArguments != 2) {
        Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
        Arcadia_Process_jump(process);
      }
             if (Arcadia_Value_isInteger16Value(&arguments[1])) {
        Digits_fromInteger64(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, Arcadia_Value_getInteger16Value(&arguments[1]));
      } else if (Arcadia_Value_isInteger32Value(&arguments[1])) {
        Digits_fromInteger64(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, Arcadia_Value_getInteger32Value(&arguments[1]));
      } else if (Arcadia_Value_isInteger64Value(&arguments[1])) {
        Digits_fromInteger64(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, Arcadia_Value_getInteger64Value(&arguments[1]));
      } else if (Arcadia_Value_isInteger8Value(&arguments[1])) {
        Digits_fromInteger64(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, Arcadia_Value_getInteger8Value(&arguments[1]));
      } else if (Arcadia_Value_isNatural16Value(&arguments[1])) {
        Digits_fromNatural64(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, Arcadia_Value_getNatural16Value(&arguments[1]));
      } else if (Arcadia_Value_isNatural32Value(&arguments[1])) {
        Digits_fromNatural64(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, Arcadia_Value_getNatural32Value(&arguments[1]));
      } else if (Arcadia_Value_isNatural64Value(&arguments[1])) {
        Digits_fromNatural64(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, Arcadia_Value_getNatural64Value(&arguments[1]));
      } else if (Arcadia_Value_isNatural8Value(&arguments[1])) {
        Digits_fromNatural64(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, Arcadia_Value_getNatural8Value(&arguments[1]));
      } else {
        Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Process_jump(process);
      }
    } break;
    case Operation_Add: {
      if (numberOfArguments != 3) {
        Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
        Arcadia_Process_jump(process);
      }
      R_BigInteger* a = R_Argument_getObjectReferenceValue(process, &(arguments[1]), _R_BigInteger_getType(process));
      R_BigInteger* b = R_Argument_getObjectReferenceValue(process, &(arguments[2]), _R_BigInteger_getType(process));
      Digits_add(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, a, b);
    } break;
    case Operation_Subtract: {
      if (numberOfArguments != 3) {
        Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
        Arcadia_Process_jump(process);
      }
      R_BigInteger* a = R_Argument_getObjectReferenceValue(process, &(arguments[1]), _R_BigInteger_getType(process));
      R_BigInteger* b = R_Argument_getObjectReferenceValue(process, &(arguments[2]), _R_BigInteger_getType(process));
      Digits_subtract(process, &_self->digits, &_self->size, &_self->capacity, &_self->sign, a, b);
    } break;
    case Operation_Magnitude: {
      if (numberOfArguments != 1) {
        Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
        Arcadia_Process_jump(process);
      }
      R_BigInteger* a = R_Argument_getObjectReferenceValue(process, &(arguments[1]), _R_BigInteger_getType(process));
      Digits_allocate(process, &_self->digits, a->size);
      Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), _self->digits, a->digits, sizeof(R_BigInteger_Digit) * a->size);
      _self->size = a->size;
      _self->capacity = a->capacity;
      _self->sign = Arcadia_BooleanValue_True;
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    } break;
  };
  Arcadia_Object_setType(process, _self, _type);
}

static void
R_BigInteger_destruct
  (
    Arcadia_Process* process,
    R_BigInteger* self
  )
{ 
  Digits_deallocate(self->digits);
  self->digits = NULL;
}

static void
R_BigInteger_equalToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _R_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);  
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) == R_BigInteger_compare((R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
R_BigInteger_greaterThanImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _R_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);  
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) < R_BigInteger_compare((R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
R_BigInteger_greaterThanOrEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _R_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);  
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) <= R_BigInteger_compare((R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
R_BigInteger_lowerThanImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _R_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);  
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) > R_BigInteger_compare((R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
R_BigInteger_lowerThanOrEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _R_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);  
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) >= R_BigInteger_compare((R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
R_BigInteger_notEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _R_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);  
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) != R_BigInteger_compare((R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (R_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

R_BigInteger*
R_BigInteger_create
  (
    Arcadia_Process* process,
    Arcadia_Value value
  )
{
  Arcadia_Value argumentValues[] = { { .tag = Arcadia_ValueTag_Integer32, .integer32Value = Operation_Create, }, value };
  R_BigInteger* self = R_allocateObject(process, _R_BigInteger_getType(process), 2, &argumentValues[0]);
  return self;
}

R_BigInteger*
R_BigInteger_add
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = Operation_Add, }, { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = a }, { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = b }, };
  R_BigInteger* self = R_allocateObject(process, _R_BigInteger_getType(process), 3, &argumentValues[0]);
  return self;
}

R_BigInteger*
R_BigInteger_subtract
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = Operation_Subtract, }, {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = a }, {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = b }, };
  R_BigInteger* self = R_allocateObject(process, _R_BigInteger_getType(process), 3, &argumentValues[0]);
  return self;
}

R_BigInteger*
R_BigInteger_magnitude
  (
    Arcadia_Process* process,
    R_BigInteger* a
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = Operation_Magnitude, }, {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = a }, };
  R_BigInteger* self = R_allocateObject(process, _R_BigInteger_getType(process), 2, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// The following functions are for convenience when writing C code.

Arcadia_Integer8Value
R_BigInteger_compareMagnitudes
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  if (a->size < b->size) {
    return Arcadia_Integer8Value_Literal(-1);
  } else if (a->size > b->size) {
    return Arcadia_Integer8Value_Literal(+1);
  } else {
    for (Arcadia_SizeValue i = a->size; i > 0; --i) {
      if (a->digits[i - 1] < b->digits[i - 1]) {
        return Arcadia_Integer8Value_Literal(-1);
      } else if (a->digits[i - 1] > b->digits[i - 1]) {
        return Arcadia_Integer8Value_Literal(+1);
      }
    }
  }
  return Arcadia_Integer8Value_Literal(0);
}

Arcadia_Integer8Value
R_BigInteger_compare
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{ 
  if (a->sign == Arcadia_BooleanValue_False && b->sign == Arcadia_BooleanValue_True) {
    // a is negative, b is non-negative
    return Arcadia_Integer8Value_Literal(-1);
  } else if (a->sign == Arcadia_BooleanValue_True && b->sign == Arcadia_BooleanValue_False) {
    // a is non-negative, b is negative
    return Arcadia_Integer8Value_Literal(+1);
  }
  // either both are non-negative or both are negative
  Arcadia_Integer8Value c = R_BigInteger_compareMagnitudes(a, b);
  // Why is this correct?
  // Case 1: Both are negative (hence false = sign).
  // Case 1.1: Assume |a| < |b| holds (that is, -1 = c) then consequently b < a. Hence c must be negated to return -1.
  // Case 1.2: Assume |a| > |b| holds (that is, +1 = c) then consequently a < b. Hence c must be negated to return -1.
  // Case 1.3: Assume |a| = |b| holds (that is,  0 = c) then consequently a = b. Hence c can be negated or retained, however, the correct result is always 0.
  // Case 2: Both are non-negative (hence true = sign).
  // Case 2.1: Assume |a| < |b| holds (that is, -1 = c) then consequently a < b. Hence c must be retained to return -1.
  // Case 2.2: Assume |a| > |b| holds (that is, +1 = c) then consequently a > b. Hence c must be retained to return +1.
  // Case 2.3: Assume |a| = |b| holds (that is,  0 = c) then consequently a = b. Hence c can be negated or retained, however, the correct result is always 0.
  return a->sign ? +c : -c;
}

Arcadia_BooleanValue
R_BigInteger_isZero
  (
    R_BigInteger* a
  )
{ return a->size == 1 && a->digits[0] == R_BigInteger_Digit_Literal(0); }

Arcadia_BooleanValue
R_BigInteger_isNegative
  (
    R_BigInteger* a
  )
{ return a->digits[0] != R_BigInteger_Digit_Literal(0) && Arcadia_BooleanValue_False == a->sign; }

Arcadia_BooleanValue
R_BigInteger_isPositive
  (
    R_BigInteger* a
  )
{ return a->digits[0] != R_BigInteger_Digit_Literal(0) && Arcadia_BooleanValue_True == a->sign; }

void
R_BigInteger_assign
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  if (a == b) {
    return;
  }
  Digits_reallocate(process, &a->digits, b->size);
  a->capacity = b->capacity;
  Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), a->digits, b->digits, sizeof(R_BigInteger_Digit) * b->size);
  a->sign = b->sign;
  a->size = b->size;
}

void
R_BigInteger_addInPlace
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  R_BigInteger_assign(process, a, R_BigInteger_add(process, a, b));
}

void
R_BigInteger_subtractInPlace
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  R_BigInteger_assign(process, a, R_BigInteger_subtract(process, a, b));
}

R_BigInteger*
R_BigInteger_fromInteger16
  (
    Arcadia_Process* process,
    Arcadia_Integer16Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Integer16, .integer16Value = v };
  return R_BigInteger_create(process, w); }

R_BigInteger*
R_BigInteger_fromInteger32
  (
    Arcadia_Process* process,
    Arcadia_Integer32Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Integer32, .integer32Value = v };
  return R_BigInteger_create(process, w);
}

R_BigInteger*
R_BigInteger_fromInteger64
  (
    Arcadia_Process* process,
    Arcadia_Integer64Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Integer64, .integer64Value = v };
  return R_BigInteger_create(process, w);
}

R_BigInteger*
R_BigInteger_fromInteger8
  (
    Arcadia_Process* process,
    Arcadia_Integer8Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Integer8, .integer8Value = v };
  return R_BigInteger_create(process, w);
}

R_BigInteger*
R_BigInteger_fromNatural16
  (
    Arcadia_Process* process,
    Arcadia_Natural16Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Natural16, .natural16Value = v };
  return R_BigInteger_create(process, w);
}

R_BigInteger*
R_BigInteger_fromNatural32
  (
    Arcadia_Process* process,
    Arcadia_Natural32Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Natural32, .natural32Value = v };
  return R_BigInteger_create(process, w);
}

R_BigInteger*
R_BigInteger_fromNatural64
  (
    Arcadia_Process* process,
    Arcadia_Natural64Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Natural64, .natural64Value = v };
  return R_BigInteger_create(process, w);
}

R_BigInteger*
R_BigInteger_fromNatural8
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Natural8, .natural8Value = v };
  return R_BigInteger_create(process, w);
}
