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

#include "R/Value.h"

#include "Arcadia/Ring1/Implementation/hash.h"
#include "R/Object.h"
// exit, EXIT_FAILURE
#include <stdlib.h>
// fprintf, stderr
#include <stdio.h>


void
R_Value_visit
  (
    R_Value* self
  )
{
  switch (self->tag) {
    case R_ValueTag_Atom: {
      Arcadia_Atom_visit(self->atomValue);
    } break;
    case R_ValueTag_Boolean: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_ForeignProcedure: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_ImmutableByteArray: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Integer16: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Integer32: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Integer64: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Integer8: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Natural16: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Natural32: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Natural64: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Natural8: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_ObjectReference: {
      R_Object_visit(self->objectReferenceValue);
    } break;
    case R_ValueTag_Real32: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Real64: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Size: {
      /* Intentionally empty. */
    } break;
    case R_ValueTag_Type: {
      Arcadia_Type_visit(self->typeValue);
    } break;
    case R_ValueTag_Void: {
      /* Intentionally empty. */
    } break;
    default: {
      fprintf(stderr, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_TypeValue
R_Value_getType
  (
    Arcadia_Process* process,
    R_Value const* self
  )
{ 
  switch (self->tag) {
    case R_ValueTag_Atom: {
      return _R_Atom_getType(process);
    } break;
    case R_ValueTag_Boolean: {
      return _Arcadia_BooleanValue_getType(process);
    } break;
    case R_ValueTag_ForeignProcedure: {
      return _Arcadia_ForeignProcedureValue_getType(process);
    } break;
    case R_ValueTag_ImmutableByteArray: {
      return _Arcadia_ImmutableByteArray_getType(process);
    } break;
    case R_ValueTag_Integer16: {
      return _Arcadia_Integer16Value_getType(process);
    } break;
    case R_ValueTag_Integer32: {
      return _Arcadia_Integer32Value_getType(process);
    } break;
    case R_ValueTag_Integer64: {
      return _Arcadia_Integer64Value_getType(process);
    } break;
    case R_ValueTag_Integer8: {
      return _Arcadia_Integer8Value_getType(process);
    } break;
    case R_ValueTag_Natural16: {
      return _Arcadia_Natural16Value_getType(process);
    } break;
    case R_ValueTag_Natural32: {
      return _Arcadia_Natural32Value_getType(process);
    } break;
    case R_ValueTag_Natural64: {
      return _Arcadia_Natural64Value_getType(process);
    } break;
    case R_ValueTag_Natural8: {
      return _Arcadia_Natural8Value_getType(process);
    } break;
    case R_ValueTag_ObjectReference: {
      return R_Object_getType(self->objectReferenceValue);
    } break;
    case R_ValueTag_Real32: {
      return _Arcadia_Real32Value_getType(process);
    } break;
    case R_ValueTag_Real64: {
      return _Arcadia_Real64Value_getType(process);
    } break;
    case R_ValueTag_Size: {
      return _Arcadia_SizeValue_getType(process);
    } break;
    case R_ValueTag_Type: {
      return _Arcadia_Type_getType(process);
    } break;
    case R_ValueTag_Void: {
      return _Arcadia_VoidValue_getType(process);
    } break;
    default: {
      fprintf(stderr, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_BooleanValue
R_Value_isEqualTo
  (
    Arcadia_Process* process,
    R_Value const* self,
    R_Value const* other 
  )
{
  switch (self->tag) {
    case R_ValueTag_Atom: {
      if (!R_Value_isAtomValue(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->atomValue == other->atomValue;
    } break;
    case R_ValueTag_Boolean: {
      if (!R_Value_isBooleanValue(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->booleanValue == other->booleanValue;
    } break;
    case R_ValueTag_ForeignProcedure: {
      if (!R_Value_isForeignProcedureValue(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->foreignProcedureValue == other->foreignProcedureValue;
    } break;
    case R_ValueTag_Integer16: {
      if (!R_Value_isInteger16Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->integer16Value == other->integer16Value;
    } break;
    case R_ValueTag_Integer32: {
      if (!R_Value_isInteger32Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->integer32Value == other->integer32Value;
    } break;
    case R_ValueTag_Integer64: {
      if (!R_Value_isInteger64Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->integer64Value == other->integer64Value;
    } break;
    case R_ValueTag_Integer8: {
      if (!R_Value_isInteger8Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->natural8Value == other->natural8Value;
    } break;
    case R_ValueTag_Natural16: {
      if (!R_Value_isNatural16Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->natural16Value == other->natural16Value;
    } break;
    case R_ValueTag_Natural32: {
      if (!R_Value_isNatural32Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->natural32Value == other->natural32Value;
    } break;
    case R_ValueTag_Natural64: {
      if (!R_Value_isNatural64Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->natural64Value == other->natural64Value;
    } break;
    case R_ValueTag_Natural8: 
      if (!R_Value_isNatural8Value(other)) {
        return Arcadia_BooleanValue_False;
      } {
        return self->natural8Value == other->natural8Value;
    } break;
    case R_ValueTag_ObjectReference: {
      return R_Object_equalTo(process, self->objectReferenceValue, other);
    } break;
    case R_ValueTag_Real32: {
      if (!R_Value_isReal32Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->real32Value == other->real32Value;
    } break;
    case R_ValueTag_Real64: {
      if (!R_Value_isReal64Value(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->real64Value == other->real64Value;
    } break;
    case R_ValueTag_Size: {
      if (!R_Value_isSizeValue(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->sizeValue == other->sizeValue;
    } break;
    case R_ValueTag_Type: {
      if (!R_Value_isTypeValue(other)) {
        return Arcadia_BooleanValue_False;
      }
      return self->typeValue == other->typeValue;
    } break;
    case R_ValueTag_Void: {
      return R_Value_isVoidValue(other);
    } break;
    default: {
      fprintf(stderr, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}

Arcadia_SizeValue
R_Value_hash
  (
    Arcadia_Process* process,
    R_Value const* self
  )
{
  switch (self->tag) {
    case R_ValueTag_Atom: {
      return Arcadia_hashAtomValue(self->typeValue);
    } break;
    case R_ValueTag_Boolean: {
      return Arcadia_hashBooleanValue(self->booleanValue);
    } break;
    case R_ValueTag_ForeignProcedure: {
      return Arcadia_hashForeignProcedureValue(self->foreignProcedureValue);
    } break;
    case R_ValueTag_Integer16: {
      return Arcadia_hashInteger16Value(self->integer16Value);
    } break;
    case R_ValueTag_Integer32: {
      return Arcadia_hashInteger32Value(self->integer32Value);
    } break;
    case R_ValueTag_Integer64: {
      return Arcadia_hashInteger64Value(self->integer64Value);
    } break;
    case R_ValueTag_Integer8: {
      return Arcadia_hashInteger8Value(self->integer8Value);
    } break;
    case R_ValueTag_Natural16: {
      return Arcadia_hashNatural16Value(self->natural16Value);
    } break;
    case R_ValueTag_Natural32: {
      return Arcadia_hashNatural32Value(self->natural32Value);
    } break;
    case R_ValueTag_Natural64: {
      return Arcadia_hashNatural64Value(self->natural64Value);
    } break;
    case R_ValueTag_Natural8: {
      return Arcadia_hashNatural8Value(self->natural8Value);
    } break;
    case R_ValueTag_ObjectReference: {
      return R_Object_hash(process, self->objectReferenceValue);
    } break;
    case R_ValueTag_Real32: {
      return Arcadia_hashReal32Value(self->real32Value);
    } break;
    case R_ValueTag_Real64: {
      return Arcadia_hashReal64Value(self->real64Value);
    } break;
    case R_ValueTag_Size: {
      return Arcadia_hashSizeValue(self->sizeValue);
    } break;
    case R_ValueTag_Type: {
      return Arcadia_hashTypeValue(self->typeValue);
    } break;
    case R_ValueTag_Void: {
      return Arcadia_hashVoidValue(self->voidValue);
    } break;
    default: {
      fprintf(stderr, "%s:%d: unreachable code reached\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
    } break;
  };
}
