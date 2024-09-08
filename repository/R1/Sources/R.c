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

// Last modified: 2024-09-01

#include "R.h"

#include "Arms.h"
#include "R/Object.internal.h"
// For registering the types.
#include "R/ByteBuffer.h"
#include "R/FileHandle.h"
#include "R/List.h"
#include "R/Stack.h"
#include "R/String.h"
#include "R/Utf8.h"

typedef uint32_t ReferenceCount;
#define ReferenceCount_Minimum (UINT32_C(0))
#define ReferenceCount_Maximum (UINT32_MAX)

static ReferenceCount g_referenceCount = 0;

static R_Status
startupArms
  (
  );

static R_Status
shutdownArms
  (
  );

static R_Status
runArms
  (
  );

static R_Status
startupArms
  (
  )
{
  Arms_Status status = Arms_startup();
  switch (status) {
    case Arms_Status_Success: {
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return R_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is R_Status_EnvironmentInvalid.
      return R_Status_OperationInvalid;
    } break;
  };
}

static R_Status
shutdownArms
  (
  )
{
  Arms_Status status = Arms_shutdown();
  switch (status) {
    case Arms_Status_Success: {
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return R_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is R_Status_EnvironmentInvalid.
      return R_Status_OperationInvalid;
    } break;
  };
}

static R_Status
runArms
  ( 
  )
{
  Arms_Status status = Arms_run();
  switch (status) {
    case Arms_Status_Success: {
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed:
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is R_Status_EnvironmentInvalid.
      return R_Status_OperationInvalid;
    } break;
  };
}

R_Status
R_startup
  (
  )
{
  if (g_referenceCount == ReferenceCount_Maximum) {
    return R_Status_OperationInvalid;
  }
  if (!g_referenceCount) {
    R_Status status = startupArms();
    if (status) {
      return status;
    }
    R_JumpTarget jumpTarget;
    R_pushJumpTarget(&jumpTarget);
    if (R_JumpTarget_save(&jumpTarget)) {
      _R_startupTypes();
      R_popJumpTarget();
    } else {
      R_popJumpTarget();
      Arms_run();
      Arms_shutdown();
      return R_getStatus();
    }

    R_pushJumpTarget(&jumpTarget);
    if (R_JumpTarget_save(&jumpTarget)) {
      R_registerBooleanType("R.Boolean", sizeof("R.Boolean") - 1);
      R_registerIntegerType("R.Integer8", sizeof("R.Integer8") - 1);
      R_registerIntegerType("R.Integer16", sizeof("R.Integer16") - 1);
      R_registerIntegerType("R.Integer32", sizeof("R.Integer32") - 1);
      R_registerIntegerType("R.Integer64", sizeof("R.Integer64") - 1);
      R_registerNaturalType("R.Natural8", sizeof("R.Natural8") - 1);
      R_registerNaturalType("R.Natural16", sizeof("R.Natural16") - 1);
      R_registerNaturalType("R.Natural32", sizeof("R.Natural32") - 1);
      R_registerNaturalType("R.Natural64", sizeof("R.Natural64") - 1);
      R_registerSizeType("R.Size", sizeof("R.Size") - 1);
      R_registerVoidType("R.Void", sizeof("R.Void") - 1);

      _R_ByteBuffer_registerType();
      _R_FileHandle_registerType();
      _R_FilePath_registerType();
      _R_FileSystem_registerType();
      _R_List_registerType();
      _R_Stack_registerType();
      _R_Utf8Reader_registerType();
      _R_Utf8Writer_registerType();
      _R_String_registerType();
      R_popJumpTarget();
    } else {
      R_popJumpTarget();
      Arms_run();
      _R_shutdownTypes();
      Arms_shutdown();
      return R_getStatus();
    }
  }
  g_referenceCount++;
  return R_Status_Success;
}

R_Status
R_shutdown
  (
  )
{
  if (g_referenceCount == ReferenceCount_Minimum) {
    return R_Status_OperationInvalid;
  }
  if (1 == g_referenceCount) {
    R_Status status;
    status = runArms();
    if (status) {
      return status;
    }
    _R_shutdownTypes();
    status = runArms();
    if (status) {
      return status;
    }
    status = shutdownArms();
    if (status) {
      return status;
    }
  }
  g_referenceCount--;
  return R_Status_Success;
}
