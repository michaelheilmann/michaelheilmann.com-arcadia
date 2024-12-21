#include "R/BigInteger/Include.h"

#include "Arms.h"
#include "R/DynamicArrayUtilities.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Value.h"
#include "R/cstdlib.h"

#define Operation_Create (1)
#define Operation_Add (2)
#define Operation_Subtract (3)
#define Operation_Negate (4)

static void
R_BigInteger_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_BigInteger_destruct
  (
    R_BigInteger* self
  );

static void
R_BigInteger_equalToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
R_BigInteger_greaterThanImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
R_BigInteger_greaterThanOrEqualToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
R_BigInteger_lowerThanImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
R_BigInteger_lowerThanOrEqualToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
R_BigInteger_notEqualToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_BigInteger_constructImpl,
  .destruct = &R_BigInteger_destruct,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("R.BigInteger", R_BigInteger, "R.Object", R_Object, &_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static R_DynamicArrayUtilities_Result
Digits_allocate
  (
    R_BigInteger_DigitType** array,
    R_SizeValue capacity
  );

static void
Digits_deallocate
  (
    R_BigInteger_DigitType* array
  );

static R_DynamicArrayUtilities_Result
Digits_reallocate
  (
    R_BigInteger_DigitType** array,
    R_SizeValue capacity
  );

static R_DynamicArrayUtilities_Result
Digits_ensureFreeCapacity
  (
    R_BigInteger_DigitType** array,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  );

#include "R/BigInteger/from.h.i"
#include "R/BigInteger/add.h.i"

static R_DynamicArrayUtilities_Result
Digits_allocate
  (
    R_BigInteger_DigitType** array,
    R_SizeValue capacity
  )
{
  if (Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), array, sizeof(R_BigInteger_DigitType) * (capacity))) {
    return R_DynamicArrayUtilities_Result_AllocationFailed;
  }
  return R_DynamicArrayUtilities_Result_Success;
}

static void
Digits_deallocate
  (
    R_BigInteger_DigitType* array
  )
{
  Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), array);
}

static R_DynamicArrayUtilities_Result
Digits_reallocate
  (
    R_BigInteger_DigitType** array,
    R_SizeValue capacity
  )
{
  if (Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), array, sizeof(R_BigInteger_DigitType) * (capacity))) {
    return R_DynamicArrayUtilities_Result_AllocationFailed;
  }
  return R_DynamicArrayUtilities_Result_Success;
}

static R_DynamicArrayUtilities_Result
Digits_ensureFreeCapacity
  (
    R_BigInteger_DigitType** array,
    R_SizeValue size,
    R_SizeValue* capacity,
    R_SizeValue requiredFreeCapacity
  ) 
{
  return R_DynamicArrayUtilities_ensureFreeCapacity(array, sizeof(R_BigInteger_DigitType), size, capacity, requiredFreeCapacity, R_DynamicArrayUtilities_GrowthStrategy4);
}

#include "R/BigInteger/from.c.i"
#include "R/BigInteger/add.c.i"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "R/ArgumentsValidation.h"

static void
R_BigInteger_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_BigInteger* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_BigInteger_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (numberOfArgumentValues < 1) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Value_isInteger32Value(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  switch (R_Value_getInteger32Value(&argumentValues[0])) {
    case Operation_Create: {
      if (numberOfArgumentValues != 2) {
        R_setStatus(R_Status_NumberOfArgumentsInvalid);
        R_jump();
      }
             if (R_Value_isInteger16Value(&argumentValues[1])) {
        Digits_fromInteger64(&_self->digits, &_self->size, &_self->capacity, &_self->sign, R_Value_getInteger16Value(&argumentValues[1]));
      } else if (R_Value_isInteger32Value(&argumentValues[1])) {
        Digits_fromInteger64(&_self->digits, &_self->size, &_self->capacity, &_self->sign, R_Value_getInteger32Value(&argumentValues[1]));
      } else if (R_Value_isInteger64Value(&argumentValues[1])) {
        Digits_fromInteger64(&_self->digits, &_self->size, &_self->capacity, &_self->sign, R_Value_getInteger64Value(&argumentValues[1]));
      } else if (R_Value_isInteger8Value(&argumentValues[1])) {
        Digits_fromInteger64(&_self->digits, &_self->size, &_self->capacity, &_self->sign, R_Value_getInteger8Value(&argumentValues[1]));
      } else if (R_Value_isNatural16Value(&argumentValues[1])) {
        Digits_fromNatural64(&_self->digits, &_self->size, &_self->capacity, &_self->sign, R_Value_getNatural16Value(&argumentValues[1]));
      } else if (R_Value_isNatural32Value(&argumentValues[1])) {
        Digits_fromNatural64(&_self->digits, &_self->size, &_self->capacity, &_self->sign, R_Value_getNatural32Value(&argumentValues[1]));
      } else if (R_Value_isNatural64Value(&argumentValues[1])) {
        Digits_fromNatural64(&_self->digits, &_self->size, &_self->capacity, &_self->sign, R_Value_getNatural64Value(&argumentValues[1]));
      } else if (R_Value_isNatural8Value(&argumentValues[1])) {
        Digits_fromNatural64(&_self->digits, &_self->size, &_self->capacity, &_self->sign, R_Value_getNatural8Value(&argumentValues[1]));
      } else {
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      }
    } break;
    case Operation_Add: {
      if (numberOfArgumentValues != 3) {
        R_setStatus(R_Status_NumberOfArgumentsInvalid);
        R_jump();
      }
      R_BigInteger* a = R_Argument_getObjectReferenceValue(&(argumentValues[1]), _R_BigInteger_getType());
      R_BigInteger* b = R_Argument_getObjectReferenceValue(&(argumentValues[2]), _R_BigInteger_getType());
      Digits_add(&_self->digits, &_self->size, &_self->capacity, &_self->sign, a, b);
    } break;
    case Operation_Subtract: {
      if (numberOfArgumentValues != 3) {
        R_setStatus(R_Status_NumberOfArgumentsInvalid);
        R_jump();
      }
      R_BigInteger* a = R_Argument_getObjectReferenceValue(&(argumentValues[1]), _R_BigInteger_getType());
      R_BigInteger* b = R_Argument_getObjectReferenceValue(&(argumentValues[2]), _R_BigInteger_getType());
      Digits_subtract(&_self->digits, &_self->size, &_self->capacity, &_self->sign, a, b);
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  };

  R_Object_setType((R_Object*)_self, _type);
}

static void
R_BigInteger_destruct
  (
    R_BigInteger* self
  )
{ 
  Digits_deallocate(self->digits);
  self->digits = NULL;
}

static void
R_BigInteger_equalToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Type_isSubType(R_Value_getType(other), _R_BigInteger_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();  
  }
  R_Value_setBooleanValue(target, R_Integer8Value_Literal(0) == R_BigInteger_compare((R_BigInteger*)R_Value_getObjectReferenceValue(self), (R_BigInteger*)R_Value_getObjectReferenceValue(other)));
}

static void
R_BigInteger_greaterThanImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Type_isSubType(R_Value_getType(other), _R_BigInteger_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();  
  }
  R_Value_setBooleanValue(target, R_Integer8Value_Literal(0) < R_BigInteger_compare((R_BigInteger*)R_Value_getObjectReferenceValue(self), (R_BigInteger*)R_Value_getObjectReferenceValue(other)));
}

static void
R_BigInteger_greaterThanOrEqualToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Type_isSubType(R_Value_getType(other), _R_BigInteger_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();  
  }
  R_Value_setBooleanValue(target, R_Integer8Value_Literal(0) <= R_BigInteger_compare((R_BigInteger*)R_Value_getObjectReferenceValue(self), (R_BigInteger*)R_Value_getObjectReferenceValue(other)));
}

static void
R_BigInteger_lowerThanImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Type_isSubType(R_Value_getType(other), _R_BigInteger_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();  
  }
  R_Value_setBooleanValue(target, R_Integer8Value_Literal(0) > R_BigInteger_compare((R_BigInteger*)R_Value_getObjectReferenceValue(self), (R_BigInteger*)R_Value_getObjectReferenceValue(other)));
}

static void
R_BigInteger_lowerThanOrEqualToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Type_isSubType(R_Value_getType(other), _R_BigInteger_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();  
  }
  R_Value_setBooleanValue(target, R_Integer8Value_Literal(0) >= R_BigInteger_compare((R_BigInteger*)R_Value_getObjectReferenceValue(self), (R_BigInteger*)R_Value_getObjectReferenceValue(other)));
}

static void
R_BigInteger_notEqualToImpl
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!R_Type_isSubType(R_Value_getType(other), _R_BigInteger_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();  
  }
  R_Value_setBooleanValue(target, R_Integer8Value_Literal(0) != R_BigInteger_compare((R_BigInteger*)R_Value_getObjectReferenceValue(self), (R_BigInteger*)R_Value_getObjectReferenceValue(other)));
}

R_BigInteger*
R_BigInteger_create
  (
    R_Value value
  )
{
  R_Value argumentValues[] = { { .tag = R_ValueTag_Integer32, .integer32Value = Operation_Create, }, value };
  R_BigInteger* self = R_allocateObject(_R_BigInteger_getType(), 2, &argumentValues[0]);
  return self;
}

R_BigInteger*
R_BigInteger_add
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Integer32, .integer32Value = Operation_Add, }, { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = a }, { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = b } };
  R_BigInteger* self = R_allocateObject(_R_BigInteger_getType(), 3, &argumentValues[0]);
  return self;
}

R_BigInteger*
R_BigInteger_subtract
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Integer32, .integer32Value = Operation_Subtract, }, {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = a }, {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = b } };
  R_BigInteger* self = R_allocateObject(_R_BigInteger_getType(), 3, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// The following functions are for convenience when writing C code.

R_Integer8Value
R_BigInteger_compareMagnitudes
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  if (a->size < b->size) {
    return R_Integer8Value_Literal(-1);
  } else if (a->size > b->size) {
    return R_Integer8Value_Literal(+1);
  } else {
    for (R_SizeValue i = a->size; i > 0; --i) {
      if (a->digits[i - 1] < b->digits[i - 1]) {
        return R_Integer8Value_Literal(-1);
      } else if (a->digits[i - 1] > b->digits[i - 1]) {
        return R_Integer8Value_Literal(+1);
      }
    }
  }
  return R_Integer8Value_Literal(0);
}

R_Integer8Value
R_BigInteger_compare
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{ 
  if (a->sign == R_BooleanValue_False && b->sign == R_BooleanValue_True) {
    // a is negative, b is non-negative
    return R_Integer8Value_Literal(-1);
  } else if (a->sign == R_BooleanValue_True && b->sign == R_BooleanValue_False) {
    // a is non-negative, b is negative
    return R_Integer8Value_Literal(+1);
  }
  // either both are non-negative or both are negative
  R_Integer8Value c = R_BigInteger_compareMagnitudes(a, b);
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

void
R_BigInteger_assign
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  if (a == b) {
    return;
  }
  if (Digits_reallocate(&a->digits, b->size)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  a->capacity = b->capacity;
  c_memcpy(a->digits, b->digits, sizeof(R_BigInteger_DigitType) * b->size);
  a->sign = b->sign;
  a->size = b->size;
}

void
R_BigInteger_addInPlace
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  R_BigInteger_assign(a, R_BigInteger_add(a, b));
}

void
R_BigInteger_subtractInPlace
  (
    R_BigInteger* a,
    R_BigInteger* b
  )
{
  R_BigInteger_assign(a, R_BigInteger_subtract(a, b));
}

R_BigInteger*
R_BigInteger_fromInteger16
  (
    R_Integer16Value v
  )
{
  R_Value w = { .tag = R_ValueTag_Integer16, .integer16Value = v };
  return R_BigInteger_create(w); }

R_BigInteger*
R_BigInteger_fromInteger32
  (
    R_Integer32Value v
  )
{
  R_Value w = { .tag = R_ValueTag_Integer32, .integer32Value = v };
  return R_BigInteger_create(w);
}

R_BigInteger*
R_BigInteger_fromInteger64
  (
    R_Integer64Value v
  )
{
  R_Value w = { .tag = R_ValueTag_Integer64, .integer64Value = v };
  return R_BigInteger_create(w);
}

R_BigInteger*
R_BigInteger_fromInteger8
  (
    R_Integer8Value v
  )
{
  R_Value w = { .tag = R_ValueTag_Integer8, .integer8Value = v };
  return R_BigInteger_create(w);
}

R_BigInteger*
R_BigInteger_fromNatural16
  (
    R_Natural16Value v
  )
{
  R_Value w = { .tag = R_ValueTag_Natural16, .natural16Value = v };
  return R_BigInteger_create(w);
}

R_BigInteger*
R_BigInteger_fromNatural32
  (
    R_Natural32Value v
  )
{
  R_Value w = { .tag = R_ValueTag_Natural32, .natural32Value = v };
  return R_BigInteger_create(w);
}

R_BigInteger*
R_BigInteger_fromNatural64
  (
    R_Natural64Value v
  )
{
  R_Value w = { .tag = R_ValueTag_Natural64, .natural64Value = v };
  return R_BigInteger_create(w);
}

R_BigInteger*
R_BigInteger_fromNatural8
  (
    R_Natural8Value v
  )
{
  R_Value w = { .tag = R_ValueTag_Natural8, .natural8Value = v };
  return R_BigInteger_create(w);
}
