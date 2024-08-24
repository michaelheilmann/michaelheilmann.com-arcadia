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

#include "file.h"

#include "arcadia/arms1.h"
#include "arcadia/r1.h"

static void registerType(char const* name, size_t nameLength, Arms_VisitCallbackFunction* visit, Arms_FinalizeCallbackFunction* finalize);

static void File_finalize(File* a);

static void registerType(char const* name, size_t nameLength, Arms_VisitCallbackFunction* visit, Arms_FinalizeCallbackFunction* finalize) {
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

static void File_finalize(File* a) {
  if (a->fd) {
    if (a->fd != stdin && a->fd != stderr && a->fd != stdout) {
      fclose(a->fd);
    }
    a->fd = NULL;
  }
}

void _File_registerType() {
  registerType("File", sizeof("File") - 1, NULL, (Arms_FinalizeCallbackFunction*)&File_finalize);
}

File* File_create() {
  File* a = NULL;
  Arms_Status armsResult = Arms_allocate(&a, "File", sizeof("File") - 1, sizeof(File));
  if (Arms_Status_Success != armsResult) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  a->fd = NULL;
  return a;
}

