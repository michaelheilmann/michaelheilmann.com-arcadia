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

#include "r/object.h"

#include "r/jumptarget.h"
#include "r/status.h"
#include <string.h>

void R_registerObjectType(char const* name, size_t nameLength, Arms_VisitCallbackFunction* visit, Arms_FinalizeCallbackFunction* finalize) {
  Arms_Status status;
  status = Arms_registerType(name, nameLength, visit, finalize);
  switch (status) {
    case Arms_Status_Success: {
      return;
    } break;
    case Arms_Status_AllocationFailed: {
      R_setStatus(R_Status_AllocationFailed);
    } break;
    case Arms_Status_ArgumentValueInvalid: {
      R_setStatus(R_Status_ArgumentValueInvalid);
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_TypeExists: {
      R_setStatus(Arms_Status_OperationInvalid);
    } break;
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      R_setStatus(Arms_Status_OperationInvalid);
    } break;
  };
}

void* R_allocateObject(char const* name, size_t nameLength, size_t size) {
  void* p = NULL;
  Arms_Status status = Arms_allocate(&p, name, nameLength, size);
  switch (status) {
    case Arms_Status_Success: {
      return p;
    } break;
    case Arms_Status_AllocationFailed: {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    } break;
    case Arms_Status_TypeNotExists: {
      // @todo Add and use R_Status_TypeNotExists.
      R_setStatus(Arms_Status_OperationInvalid);
      R_jump();
    } break;
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_OperationInvalid:
    case Arms_Status_TypeExists:
    default: {
      // This should not happen.
      R_setStatus(Arms_Status_OperationInvalid);
      R_jump();
    } break;
  };
}
