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

// Last modified: 2024-10-07

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Value.h"

#include "Arcadia/Ring1/Implementation/Diagnostics.h"
#include "Arcadia/Ring1/Implementation/hash.h"
#include "Arcadia/Ring1/Implementation/Object.h"
// exit, EXIT_FAILURE
#include <stdlib.h>

static Arcadia_SizeValue
Arcadia_Object_hash
  (
    Arcadia_Process* process,
    Arcadia_Object* self
  );

static Arcadia_BooleanValue
Arcadia_Object_isNotEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Object* self,
    Arcadia_Value const* other
  );

static Arcadia_BooleanValue
Arcadia_Object_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Object* self,
    Arcadia_Value const* other
  );

static Arcadia_SizeValue
Arcadia_Object_hash
  (
    Arcadia_Process* process,
    Arcadia_Object* self
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  Arcadia_Value resultValue;
  Arcadia_Value args[1] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = self }, };
  operations->hash(process, &resultValue, 1, &args[0]);
  return Arcadia_Value_getSizeValue(&resultValue);
}

static Arcadia_BooleanValue
Arcadia_Object_isNotEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Object* self,
    Arcadia_Value const* other
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  Arcadia_Value resultValue;
  Arcadia_Value args[2] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = self }, *other };
  operations->notEqualTo(process, &resultValue, 2, &args[0]);
  return Arcadia_Value_getBooleanValue(&resultValue);
}

static Arcadia_BooleanValue
Arcadia_Object_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Object* self,
    Arcadia_Value const* other
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  Arcadia_Value resultValue;
  Arcadia_Value args[2] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = self }, *other };
  operations->equalTo(process, &resultValue, 2, &args[0]);
  return Arcadia_Value_getBooleanValue(&resultValue);
}

void
Arcadia_Value_visit
  (
    Arcadia_Process* process,
    Arcadia_Value* self
  )
{
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      Arcadia_Atom_visit(process, self->atomValue);
    } break;
    case Arcadia_ValueTag_Boolean: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_ForeignProcedure: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_ImmutableByteArray: {
      Arcadia_ImmutableByteArray_visit(Arcadia_Process_getBackendNoLock(process), self->immutableByteArrayValue);
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Integer16: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Integer32: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Integer64: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Integer8: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Natural16: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Natural32: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Natural64: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Natural8: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_ObjectReference: {
      Arcadia_Object_visit(process, self->objectReferenceValue);
    } break;
    case Arcadia_ValueTag_Real32: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Real64: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Size: {
      /* Intentionally empty. */
    } break;
    case Arcadia_ValueTag_Type: {
      Arcadia_Type_visit(self->typeValue);
    } break;
    case Arcadia_ValueTag_Void: {
      /* Intentionally empty. */
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_TypeValue
Arcadia_Value_getType
  (
    Arcadia_Process* process,
    Arcadia_Value const* self
  )
{ 
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      return _Arcadia_Atom_getType(process);
    } break;
    case Arcadia_ValueTag_Boolean: {
      return _Arcadia_BooleanValue_getType(process);
    } break;
    case Arcadia_ValueTag_ForeignProcedure: {
      return _Arcadia_ForeignProcedureValue_getType(process);
    } break;
    case Arcadia_ValueTag_ImmutableByteArray: {
      return _Arcadia_ImmutableByteArray_getType(process);
    } break;
    case Arcadia_ValueTag_Integer16: {
      return _Arcadia_Integer16Value_getType(process);
    } break;
    case Arcadia_ValueTag_Integer32: {
      return _Arcadia_Integer32Value_getType(process);
    } break;
    case Arcadia_ValueTag_Integer64: {
      return _Arcadia_Integer64Value_getType(process);
    } break;
    case Arcadia_ValueTag_Integer8: {
      return _Arcadia_Integer8Value_getType(process);
    } break;
    case Arcadia_ValueTag_Natural16: {
      return _Arcadia_Natural16Value_getType(process);
    } break;
    case Arcadia_ValueTag_Natural32: {
      return _Arcadia_Natural32Value_getType(process);
    } break;
    case Arcadia_ValueTag_Natural64: {
      return _Arcadia_Natural64Value_getType(process);
    } break;
    case Arcadia_ValueTag_Natural8: {
      return _Arcadia_Natural8Value_getType(process);
    } break;
    case Arcadia_ValueTag_ObjectReference: {
      return Arcadia_Object_getType(self->objectReferenceValue);
    } break;
    case Arcadia_ValueTag_Real32: {
      return _Arcadia_Real32Value_getType(process);
    } break;
    case Arcadia_ValueTag_Real64: {
      return _Arcadia_Real64Value_getType(process);
    } break;
    case Arcadia_ValueTag_Size: {
      return _Arcadia_SizeValue_getType(process);
    } break;
    case Arcadia_ValueTag_Type: {
      return _Arcadia_Type_getType(process);
    } break;
    case Arcadia_ValueTag_Void: {
      return _Arcadia_VoidValue_getType(process);
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

#define OnRelational(Type, Operation) \
  case Arcadia_ValueTag_##Type: { \
      Arcadia_TypeValue type = _Arcadia_##Type##Value_getType(process); \
      Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type); \
      Arcadia_Value result; \
      Arcadia_Value arguments[] = { *self, *other }; \
      operations->Operation(process, &result, 2, &arguments[0]); \
      return Arcadia_Value_getBooleanValue(&result); \
  } break;
  
Arcadia_BooleanValue
Arcadia_Value_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value const* self,
    Arcadia_Value const* other 
  )
{
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      if (!Arcadia_Value_isAtomValue(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->atomValue == other->atomValue;
    } break;
    OnRelational(Boolean, equalTo);
    OnRelational(ForeignProcedure, equalTo);
    OnRelational(Integer16, equalTo);
    OnRelational(Integer32, equalTo);
    OnRelational(Integer64, equalTo);
    OnRelational(Integer8, equalTo);
    OnRelational(Natural16, equalTo);
    OnRelational(Natural32, equalTo);
    OnRelational(Natural64, equalTo);
    OnRelational(Natural8, equalTo);
    OnRelational(Real32, equalTo);
    OnRelational(Real64, equalTo);
    OnRelational(Size, equalTo);
    OnRelational(Void, equalTo);
    case Arcadia_ValueTag_ObjectReference: {
      return Arcadia_Object_isEqualTo(process, self->objectReferenceValue, other);
    } break;
    case Arcadia_ValueTag_Type: {
      if (!Arcadia_Value_isTypeValue(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->typeValue == other->typeValue;
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_BooleanValue
Arcadia_Value_isNotEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value const* self,
    Arcadia_Value const* other
  )
{
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      if (!Arcadia_Value_isAtomValue(other)) {
        return Arcadia_BooleanValue_True;
      }
      return self->atomValue != other->atomValue;
    } break;
    OnRelational(Boolean, notEqualTo);
    OnRelational(ForeignProcedure, notEqualTo);
    OnRelational(Integer16, notEqualTo);
    OnRelational(Integer32, notEqualTo);
    OnRelational(Integer64, notEqualTo);
    OnRelational(Integer8, notEqualTo);
    OnRelational(Natural16, notEqualTo);
    OnRelational(Natural32, notEqualTo);
    OnRelational(Natural64, notEqualTo);
    OnRelational(Natural8, notEqualTo);
    OnRelational(Real32, notEqualTo);
    OnRelational(Real64, notEqualTo);
    OnRelational(Size, notEqualTo);
    OnRelational(Void, notEqualTo);
    case Arcadia_ValueTag_ObjectReference: {
      return Arcadia_Object_isNotEqualTo(process, self->objectReferenceValue, other);
    } break;
    case Arcadia_ValueTag_Type: {
      if (!Arcadia_Value_isTypeValue(other)) {
        return Arcadia_BooleanValue_True;
      }
      return self->typeValue != other->typeValue;
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_BooleanValue
Arcadia_Value_isLowerThan
  (
    Arcadia_Process* process,
    Arcadia_Value const* self,
    Arcadia_Value const* other
  )
{
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    } break;
    OnRelational(Boolean, lowerThan);
    OnRelational(ForeignProcedure, lowerThan);
    OnRelational(Integer16, lowerThan);
    OnRelational(Integer32, lowerThan);
    OnRelational(Integer64, lowerThan);
    OnRelational(Integer8, lowerThan);
    OnRelational(Natural16, lowerThan);
    OnRelational(Natural32, lowerThan);
    OnRelational(Natural64, lowerThan);
    OnRelational(Natural8, lowerThan);
    OnRelational(Real32, lowerThan);
    OnRelational(Real64, lowerThan);
    OnRelational(Size, lowerThan);
    OnRelational(Void, lowerThan);
    case Arcadia_ValueTag_ObjectReference: {
      Arcadia_TypeValue type = Arcadia_Object_getType(self->objectReferenceValue);
      Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
      Arcadia_Value resultValue;
      Arcadia_Value args[2] = { *self, *other };
      operations->lowerThan(process, &resultValue, 2, &args[0]);
      return Arcadia_Value_getBooleanValue(&resultValue);
    } break;
    case Arcadia_ValueTag_Type: {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_BooleanValue
Arcadia_Value_isLowerThanOrEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value const* self,
    Arcadia_Value const* other
  )
{
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    } break;
    OnRelational(Boolean, lowerThanOrEqualTo);
    OnRelational(ForeignProcedure, lowerThanOrEqualTo);
    OnRelational(Integer16, lowerThanOrEqualTo);
    OnRelational(Integer32, lowerThanOrEqualTo);
    OnRelational(Integer64, lowerThanOrEqualTo);
    OnRelational(Integer8, lowerThanOrEqualTo);
    OnRelational(Natural16, lowerThanOrEqualTo);
    OnRelational(Natural32, lowerThanOrEqualTo);
    OnRelational(Natural64, lowerThanOrEqualTo);
    OnRelational(Natural8, lowerThanOrEqualTo);
    OnRelational(Real32, lowerThanOrEqualTo);
    OnRelational(Real64, lowerThanOrEqualTo);
    OnRelational(Size, lowerThanOrEqualTo);
    OnRelational(Void, lowerThanOrEqualTo);
    case Arcadia_ValueTag_ObjectReference: {
      Arcadia_TypeValue type = Arcadia_Object_getType(self->objectReferenceValue);
      Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
      Arcadia_Value resultValue;
      Arcadia_Value args[2] = { *self, *other };
      operations->lowerThanOrEqualTo(process, &resultValue, 2, &args[0]);
      return Arcadia_Value_getBooleanValue(&resultValue);
    } break;
    case Arcadia_ValueTag_Type: {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_BooleanValue
Arcadia_Value_isGreaterThan
  (
    Arcadia_Process* process,
    Arcadia_Value const* self,
    Arcadia_Value const* other
  )
{
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    } break;
    OnRelational(Boolean, greaterThan);
    OnRelational(ForeignProcedure, greaterThan);
    OnRelational(Integer16, greaterThan);
    OnRelational(Integer32, greaterThan);
    OnRelational(Integer64, greaterThan);
    OnRelational(Integer8, greaterThan);
    OnRelational(Natural16, greaterThan);
    OnRelational(Natural32, greaterThan);
    OnRelational(Natural64, greaterThan);
    OnRelational(Natural8, greaterThan);
    OnRelational(Real32, greaterThan);
    OnRelational(Real64, greaterThan);
    OnRelational(Size, greaterThan);
    OnRelational(Void, greaterThan);
    case Arcadia_ValueTag_ObjectReference: {
      Arcadia_TypeValue type = Arcadia_Object_getType(self->objectReferenceValue);
      Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
      Arcadia_Value resultValue;
      Arcadia_Value args[2] = { *self, *other };
      operations->greaterThan(process, &resultValue, 2, &args[0]);
      return Arcadia_Value_getBooleanValue(&resultValue);
    } break;
    case Arcadia_ValueTag_Type: {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_BooleanValue
Arcadia_Value_isGreaterThanOrEqualTo
  (
    Arcadia_Process* process,
    Arcadia_Value const* self,
    Arcadia_Value const* other
  )
{
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    } break;
    OnRelational(Boolean, greaterThanOrEqualTo);
    OnRelational(ForeignProcedure, greaterThanOrEqualTo);
    OnRelational(Integer16, greaterThanOrEqualTo);
    OnRelational(Integer32, greaterThanOrEqualTo);
    OnRelational(Integer64, greaterThanOrEqualTo);
    OnRelational(Integer8, greaterThanOrEqualTo);
    OnRelational(Natural16, greaterThanOrEqualTo);
    OnRelational(Natural32, greaterThanOrEqualTo);
    OnRelational(Natural64, greaterThanOrEqualTo);
    OnRelational(Natural8, greaterThanOrEqualTo);
    OnRelational(Real32, greaterThanOrEqualTo);
    OnRelational(Real64, greaterThanOrEqualTo);
    OnRelational(Size, greaterThanOrEqualTo);
    OnRelational(Void, greaterThanOrEqualTo);
    case Arcadia_ValueTag_ObjectReference: {
      Arcadia_TypeValue type = Arcadia_Object_getType(self->objectReferenceValue);
      Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
      Arcadia_Value resultValue;
      Arcadia_Value args[2] = { *self, *other };
      operations->greaterThanOrEqualTo(process, &resultValue, 2, &args[0]);
      return Arcadia_Value_getBooleanValue(&resultValue);
    } break;
    case Arcadia_ValueTag_Type: {
      Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
      Arcadia_Process_jump(process);
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

#undef OnRelational

#define OnHash(Type) \
  case Arcadia_ValueTag_##Type: { \
    Arcadia_TypeValue type = _Arcadia_##Type##Value_getType(process); \
    Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type); \
    Arcadia_Value result; \
    Arcadia_Value arguments[] = { *self }; \
    operations->hash(process, &result, 1, &arguments[0]); \
    return Arcadia_Value_getSizeValue(&result); \
  } break;

Arcadia_SizeValue
Arcadia_Value_getHash
  (
    Arcadia_Process* process,
    Arcadia_Value* self
  )
{
  switch (self->tag) {
    case Arcadia_ValueTag_Atom: {
      return Arcadia_hashAtomValue(self->typeValue);
    } break;
    OnHash(Boolean);
    OnHash(ForeignProcedure);
    OnHash(Integer16);
    OnHash(Integer32);
    OnHash(Integer64);
    OnHash(Integer8);
    OnHash(Natural16);
    OnHash(Natural32);
    OnHash(Natural64);
    OnHash(Natural8);
    OnHash(Real32);
    OnHash(Real64);
    OnHash(Size);
    OnHash(Void);
    case Arcadia_ValueTag_ObjectReference: {
      Arcadia_TypeValue type = Arcadia_Object_getType(self->objectReferenceValue);
      Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
      Arcadia_Value resultValue;
      Arcadia_Value args[1] = { *self };
      operations->hash(process, &resultValue, 1, &args[0]);
      return Arcadia_Value_getSizeValue(&resultValue);
    } break;
    default: {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

#undef OnHash
