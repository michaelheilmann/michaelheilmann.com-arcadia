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

// Last modified: 2024-08-27

#include "r.h"

#include "arms1.h"

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
    status = shutdownArms();
    if (status) {
      return status;
    }
  }
  g_referenceCount--;
  return R_Status_Success;
}
