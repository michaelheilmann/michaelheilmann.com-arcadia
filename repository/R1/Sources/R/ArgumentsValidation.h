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

// Last modified: 2024-12-10

#if !defined (R_ARGUMENTSVALIDATION_H_INCLUDED)
#define R_ARGUMENTSVALIDATION_H_INCLUDED

#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/Value.h"

static inline R_ObjectReferenceValue
R_Argument_getObjectReferenceValue
  (
    R_Value const* value,
    R_Type *type
  )
{
  if (!R_Value_isObjectReferenceValue(value)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_ObjectReferenceValue objectReferenceValue = R_Value_getObjectReferenceValue(value);
  if (!R_Type_isSubType(R_Object_getType(objectReferenceValue), type)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  return objectReferenceValue;
}

static inline R_ObjectReferenceValue
R_Argument_getObjectReferenceValueOrNull
  (
    R_Value const* value,
    R_Type* type
  ) 
{
  if (R_Value_isVoidValue(value)) {
    return NULL;
  }
  if (!R_Value_isObjectReferenceValue(value)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_ObjectReferenceValue objectReferenceValue = R_Value_getObjectReferenceValue(value);
  if (!R_Type_isSubType(R_Object_getType(objectReferenceValue), type)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  return objectReferenceValue;
}

#endif // R_ARGUMENTSVALIDATION_H_INCLUDED
