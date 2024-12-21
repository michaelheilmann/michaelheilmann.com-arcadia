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

// Last modified: 2024-09-20

#include "R/ImmutableByteArray.h"

#include "R/cstdlib.h"
#include "R/ArmsIntegration.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Value.h"

#define Name u8"R.ImmutableByteArray"

static R_BooleanValue g_registered = R_BooleanValue_False;

static void
onTypeRemoved
  (
    uint8_t const* bytes,
    size_t numberOfBytes
  )
{ g_registered = R_BooleanValue_False; }

R_ImmutableByteArray*
R_ImmutableByteArray_create
  (
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  )
{
  if (!bytes) {
     R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();   
  }
  if (SIZE_MAX - sizeof(R_ImmutableByteArray) < numberOfBytes) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!g_registered) {
    if (!R_Arms_registerType_nojump(Name, sizeof(Name) - 1, &onTypeRemoved, NULL, NULL)) {
      R_jump();
    }
    g_registered = R_BooleanValue_True;
  }
  R_ImmutableByteArray *array = NULL;
  if (!R_allocate_nojump(&array, Name, sizeof(Name) - 1, sizeof(R_ImmutableByteArray) + numberOfBytes)) {
    R_jump();
  }
  c_memcpy(array->bytes, bytes, numberOfBytes);
  array->numberOfBytes = numberOfBytes;
  return array;
}

void
R_ImmutableByteArray_visit
  (
    R_ImmutableByteArray* immutableByteArray
  )
{ R_Arms_visit(immutableByteArray); }

R_Natural8Value const*
R_ImmutableByteArray_getBytes
  (
    R_ImmutableByteArray const* immutableByteArray
  )
{ return immutableByteArray->bytes; }

R_SizeValue
R_ImmutableByteArray_getNumberOfBytes
  (
    R_ImmutableByteArray const* immutableByteArray
  )
{ return immutableByteArray->numberOfBytes; }

static void
equalTo
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
notEqualTo
(
  R_Value* target,
  R_Value const* self,
  R_Value const* other
);

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = NULL,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &equalTo,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = &hash,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = &notEqualTo,
  .or = NULL,
  .subtract = NULL,
};

static void
equalTo
(
  R_Value* target,
  R_Value const* self,
  R_Value const* other
) {
  if (R_Value_isForeignProcedureValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getForeignProcedureValue(self) == R_Value_getForeignProcedureValue(other));
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_False);
  }
}

static void
hash
  (
    R_Value* target,
    R_Value const* self
  )
{ R_Value_setSizeValue(target, (R_SizeValue)(uintptr_t)R_Value_getForeignProcedureValue(self)); }

static void
notEqualTo
  (
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isForeignProcedureValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getForeignProcedureValue(self) != R_Value_getForeignProcedureValue(other));
  } else {
    R_Value_setBooleanValue(target, R_BooleanValue_True);
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
_R_ImmutableByteArray_getType
  (
  )
{
  if (!g_type) {
    R_registerForeignValueType(Name, sizeof(Name) - 1, &_typeOperations, &typeDestructing);
    g_type = R_getType(Name, sizeof(Name) - 1);
  }
  return g_type;
}
