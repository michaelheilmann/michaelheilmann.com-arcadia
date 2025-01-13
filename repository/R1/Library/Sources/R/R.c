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

#include "R/R.h"

#include "Arcadia/Ring1/Include.h"

static Arcadia_Process* g_process = NULL;

typedef uint32_t ReferenceCount;
#define ReferenceCount_Minimum (UINT32_C(0))
#define ReferenceCount_Maximum (UINT32_MAX)

static ReferenceCount g_referenceCount = 0;

Arcadia_Status
R_startup
  (
  )
{
  if (g_referenceCount == ReferenceCount_Maximum) {
    return Arcadia_Status_OperationInvalid;
  }
  if (!g_referenceCount) {
    if (Arcadia_Process_get(&g_process)) {
      return Arcadia_Status_EnvironmentFailed;
    }
  }
  g_referenceCount++;
  return Arcadia_Status_Success;
}

Arcadia_Status
R_shutdown
  (
  )
{
  if (g_referenceCount == ReferenceCount_Minimum) {
    return Arcadia_Status_OperationInvalid;
  }
  if (1 == g_referenceCount) {
    Arcadia_Process_relinquish(g_process);
    g_process = NULL;
  }
  g_referenceCount--;
  return Arcadia_Status_Success;
}
