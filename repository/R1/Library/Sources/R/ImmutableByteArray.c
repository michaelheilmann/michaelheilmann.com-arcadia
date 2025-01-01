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

// Last modified: 2024-09-20

#include "R/ImmutableByteArray.h"

#include "R/cstdlib.h"
#include "R/ArmsIntegration.h"
#include "Arcadia/Ring1/Include.h"
#include "R/Value.h"

#define Name u8"R.ImmutableByteArray"

static Arcadia_BooleanValue g_registered = Arcadia_BooleanValue_False;

static void
onTypeRemoved
  (
    Arcadia_Process* process,
    const uint8_t* bytes,
    size_t numberOfBytes
  )
{ g_registered = Arcadia_BooleanValue_False; }

Arcadia_ImmutableByteArray*
Arcadia_ImmutableByteArray_create
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!bytes) {
     Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);   
  }
  if (SIZE_MAX - sizeof(Arcadia_ImmutableByteArray) < numberOfBytes) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (!g_registered) {
    if (!R_Arms_registerType_nojump(process, Name, sizeof(Name) - 1, process, &onTypeRemoved, NULL, NULL)) {
      Arcadia_Process_jump(process);
    }
    g_registered = Arcadia_BooleanValue_True;
  }
  Arcadia_ImmutableByteArray*array = NULL;
  if (!R_allocate_nojump(process, &array, Name, sizeof(Name) - 1, sizeof(Arcadia_ImmutableByteArray) + numberOfBytes)) {
    Arcadia_Process_jump(process);
  }
  c_memcpy(array->bytes, bytes, numberOfBytes);
  array->numberOfBytes = numberOfBytes;
  return array;
}

void
Arcadia_ImmutableByteArray_visit
  (
    Arcadia_ImmutableByteArray* immutableByteArray
  )
{ R_Arms_visit(immutableByteArray); }

Arcadia_Natural8Value const*
Arcadia_ImmutableByteArray_getBytes
  (
    Arcadia_ImmutableByteArray const* immutableByteArray
  )
{ return immutableByteArray->bytes; }

Arcadia_SizeValue
Arcadia_ImmutableByteArray_getNumberOfBytes
  (
    Arcadia_ImmutableByteArray const* immutableByteArray
  )
{ return immutableByteArray->numberOfBytes; }

static void
equalTo
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
notEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const Arcadia_Type_Operations _typeOperations = {
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
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isImmutableByteArrayValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getImmutableByteArrayValue(self) == R_Value_getImmutableByteArrayValue(other));
  } else {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
}

static void
hash
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  )
{ R_Value_setSizeValue(target, (Arcadia_SizeValue)(uintptr_t)R_Value_getImmutableByteArrayValue(self)); }

static void
notEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (R_Value_isImmutableByteArrayValue(other)) {
    R_Value_setBooleanValue(target, R_Value_getImmutableByteArrayValue(self) != R_Value_getImmutableByteArrayValue(other));
  } else {
    R_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
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
_Arcadia_ImmutableByteArray_getType
  (
    Arcadia_Process* process
  )
{
  if (!g_type) {
    g_type = R_registerInternalType(process, Name, sizeof(Name) - 1, &_typeOperations, &typeDestructing);
  }
  return g_type;
}
