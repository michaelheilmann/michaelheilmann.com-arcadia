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

// Last modified: 2025-01-20

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Implementation/BigInteger.h"

#include "R/ArgumentsValidation.h"

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Create (1)

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Add (2)

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Subtract (3)

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Negate (4)

// Symbolic constant denoting the operation to be executed by the constructor.
#define Operation_Magnitude (5)

static void
Arcadia_BigInteger_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
Arcadia_BigInteger_destruct
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* self
  );

static void
Arcadia_BigInteger_equalToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
Arcadia_BigInteger_greaterThanImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
Arcadia_BigInteger_greaterThanOrEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
Arcadia_BigInteger_lowerThanImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
Arcadia_BigInteger_lowerThanOrEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
Arcadia_BigInteger_notEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_BigInteger_constructImpl,
  .destruct = &Arcadia_BigInteger_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &Arcadia_BigInteger_equalToImpl,
  .greaterThan = &Arcadia_BigInteger_greaterThanImpl,
  .greaterThanOrEqualTo = &Arcadia_BigInteger_greaterThanOrEqualToImpl,
  .hash = NULL,
  .lowerThan = &Arcadia_BigInteger_lowerThanImpl,
  .lowerThanOrEqualTo = &Arcadia_BigInteger_lowerThanOrEqualToImpl,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = &Arcadia_BigInteger_notEqualToImpl,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"R.BigInteger", Arcadia_BigInteger, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_BigInteger_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  Arcadia_BigInteger* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_BigInteger_getType(process);
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
  if (apint10_initialize(&_self->_apint10)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  switch (Arcadia_Value_getInteger32Value(&arguments[0])) {
    case Operation_Create: {
      if (numberOfArguments != 2) {
        Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
        Arcadia_Process_jump(process);
      }
      if (false) {
      }
#define On(Suffix1, Suffix2) \
      else if (Arcadia_Value_is##Suffix1##Value(&arguments[1])) { \
        if (apint10_from_##Suffix2(&_self->_apint10, Arcadia_Value_get##Suffix1##Value(&arguments[1]))) { \
          Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed); \
          Arcadia_Process_jump(process); \
        } \
      }
      On(Integer16, int16)
      On(Integer32, int32)
      On(Integer64, int64)
      On(Integer8,  int8)
      On(Natural16, uint16)
      On(Natural32, uint32)
      On(Natural64, uint64)
      On(Natural8,  uint8)
      else {
        Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Process_jump(process);
      }
#undef On
    } break;
    case Operation_Add: {
      if (numberOfArguments != 3) {
        Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
        Arcadia_Process_jump(process);
      }
      Arcadia_BigInteger* a = R_Argument_getObjectReferenceValue(process, &(arguments[1]), _Arcadia_BigInteger_getType(process));
      Arcadia_BigInteger* b = R_Argument_getObjectReferenceValue(process, &(arguments[2]), _Arcadia_BigInteger_getType(process));
      if (apint10_copy(&_self->_apint10, &a->_apint10)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
      }
      if (apint10_add(&_self->_apint10, &b->_apint10)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
      }
    } break;
    case Operation_Subtract: {
      if (numberOfArguments != 3) {
        Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
        Arcadia_Process_jump(process);
      }
      Arcadia_BigInteger* a = R_Argument_getObjectReferenceValue(process, &(arguments[1]), _Arcadia_BigInteger_getType(process));
      Arcadia_BigInteger* b = R_Argument_getObjectReferenceValue(process, &(arguments[2]), _Arcadia_BigInteger_getType(process));
      if (apint10_copy(&_self->_apint10, &a->_apint10)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
      }
     if (apint10_subtract(&_self->_apint10, &b->_apint10)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
      }
    } break;
    case Operation_Magnitude: {
      if (numberOfArguments != 1) {
        Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
        Arcadia_Process_jump(process);
      }
      Arcadia_BigInteger* a = R_Argument_getObjectReferenceValue(process, &(arguments[1]), _Arcadia_BigInteger_getType(process));
      if (apint10_copy(&_self->_apint10, &a->_apint10)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
      }
      if (apint10_magnitude(&_self->_apint10)) {
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
      }
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    } break;
  };
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_BigInteger_destruct
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* self
  )
{
  apint10_uninitialize(&self->_apint10);
}

static void
Arcadia_BigInteger_equalToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _Arcadia_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) == Arcadia_BigInteger_compare(process, (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
Arcadia_BigInteger_greaterThanImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _Arcadia_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) < Arcadia_BigInteger_compare(process, (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
Arcadia_BigInteger_greaterThanOrEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _Arcadia_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) <= Arcadia_BigInteger_compare(process, (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
Arcadia_BigInteger_lowerThanImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _Arcadia_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) > Arcadia_BigInteger_compare(process, (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
Arcadia_BigInteger_lowerThanOrEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _Arcadia_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) >= Arcadia_BigInteger_compare(process, (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

static void
Arcadia_BigInteger_notEqualToImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, A2), _Arcadia_BigInteger_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Value_setBooleanValue(target, Arcadia_Integer8Value_Literal(0) != Arcadia_BigInteger_compare(process, (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A1), (Arcadia_BigInteger*)Arcadia_Value_getObjectReferenceValue(A2)));
#undef A2
#undef A1
}

Arcadia_BigInteger*
Arcadia_BigInteger_create
  (
    Arcadia_Process* process,
    Arcadia_Value value
  )
{
  Arcadia_Value argumentValues[] = { { .tag = Arcadia_ValueTag_Integer32, .integer32Value = Operation_Create, }, value };
  Arcadia_BigInteger* self = R_allocateObject(process, _Arcadia_BigInteger_getType(process), 2, &argumentValues[0]);
  return self;
}

Arcadia_BigInteger*
Arcadia_BigInteger_add
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = Operation_Add, }, { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = a }, { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = b }, };
  Arcadia_BigInteger* self = R_allocateObject(process, _Arcadia_BigInteger_getType(process), 3, &argumentValues[0]);
  return self;
}

Arcadia_BigInteger*
Arcadia_BigInteger_subtract
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = Operation_Subtract, }, {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = a }, {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = b }, };
  Arcadia_BigInteger* self = R_allocateObject(process, _Arcadia_BigInteger_getType(process), 3, &argumentValues[0]);
  return self;
}

Arcadia_BigInteger*
Arcadia_BigInteger_magnitude
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = Operation_Magnitude, }, {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = a }, };
  Arcadia_BigInteger* self = R_allocateObject(process, _Arcadia_BigInteger_getType(process), 2, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// The following functions are for convenience when writing C code.

Arcadia_Integer8Value
Arcadia_BigInteger_compareMagnitudes
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  int result;
  if (apint10_compare_magnitudes(&result, &a->_apint10, &b->_apint10)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  return result;
}

Arcadia_Integer8Value
Arcadia_BigInteger_compare
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{ 
  int result;
  if (apint10_compare(&result, &a->_apint10, &b->_apint10)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  return result;
}

Arcadia_BooleanValue
Arcadia_BigInteger_isZero
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a
  )
{
  bool result;
  if (apint10_is_zero(&result, &a->_apint10)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  return result;
}

Arcadia_BooleanValue
Arcadia_BigInteger_isNegative
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a
  )
{
  bool result;
  if (apint10_is_negative(&result, &a->_apint10)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  return result;
}

Arcadia_BooleanValue
Arcadia_BigInteger_isPositive
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a
  )
{
  bool result;
  if (apint10_is_positive(&result, &a->_apint10)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  return result;
}

void
Arcadia_BigInteger_assign
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  if (a == b) {
    return;
  }
  if (apint10_copy(&a->_apint10, &b->_apint10)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
}

void
Arcadia_BigInteger_addInPlace
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  Arcadia_BigInteger_assign(process, a, Arcadia_BigInteger_add(process, a, b));
}

void
Arcadia_BigInteger_subtractInPlace
  (
    Arcadia_Process* process,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  Arcadia_BigInteger_assign(process, a, Arcadia_BigInteger_subtract(process, a, b));
}

Arcadia_BigInteger*
Arcadia_BigInteger_fromInteger16
  (
    Arcadia_Process* process,
    Arcadia_Integer16Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Integer16, .integer16Value = v };
  return Arcadia_BigInteger_create(process, w); }

Arcadia_BigInteger*
Arcadia_BigInteger_fromInteger32
  (
    Arcadia_Process* process,
    Arcadia_Integer32Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Integer32, .integer32Value = v };
  return Arcadia_BigInteger_create(process, w);
}

Arcadia_BigInteger*
Arcadia_BigInteger_fromInteger64
  (
    Arcadia_Process* process,
    Arcadia_Integer64Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Integer64, .integer64Value = v };
  return Arcadia_BigInteger_create(process, w);
}

Arcadia_BigInteger*
Arcadia_BigInteger_fromInteger8
  (
    Arcadia_Process* process,
    Arcadia_Integer8Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Integer8, .integer8Value = v };
  return Arcadia_BigInteger_create(process, w);
}

Arcadia_BigInteger*
Arcadia_BigInteger_fromNatural16
  (
    Arcadia_Process* process,
    Arcadia_Natural16Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Natural16, .natural16Value = v };
  return Arcadia_BigInteger_create(process, w);
}

Arcadia_BigInteger*
Arcadia_BigInteger_fromNatural32
  (
    Arcadia_Process* process,
    Arcadia_Natural32Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Natural32, .natural32Value = v };
  return Arcadia_BigInteger_create(process, w);
}

Arcadia_BigInteger*
Arcadia_BigInteger_fromNatural64
  (
    Arcadia_Process* process,
    Arcadia_Natural64Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Natural64, .natural64Value = v };
  return Arcadia_BigInteger_create(process, w);
}

Arcadia_BigInteger*
Arcadia_BigInteger_fromNatural8
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value v
  )
{
  Arcadia_Value w = { .tag = Arcadia_ValueTag_Natural8, .natural8Value = v };
  return Arcadia_BigInteger_create(process, w);
}
