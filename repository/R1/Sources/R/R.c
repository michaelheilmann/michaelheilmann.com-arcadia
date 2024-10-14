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

// Last modified: 2024-10-07

#include "R/R.h"

#include "R/Atoms.h"
#include "R/Object.internal.h"
// For registering the types.
#include "R/TypeNames.h"

#include "R/ArmsIntegration.h"

typedef uint32_t ReferenceCount;
#define ReferenceCount_Minimum (UINT32_C(0))
#define ReferenceCount_Maximum (UINT32_MAX)

static ReferenceCount g_referenceCount = 0;

#define On(Category, cilName, cName) \
    static R_Type* g_##cName##_type = NULL; \
    static void \
    _##cName##_typeDestructing \
      ( \
        void* context \
      ) \
    { \
      g_##cName##_type = NULL; \
    }

On(Boolean, "R.Boolean", R_BooleanValue);
On(Integer, "R.Integer8", R_Integer8Value);
On(Integer, "R.Integer16", R_Integer16Value);
On(Integer, "R.Integer32", R_Integer32Value);
On(Integer, "R.Integer64", R_Integer64Value);
On(Natural, "R.Natural8", R_Natural8Value);
On(Natural, "R.Natural16", R_Natural16Value);
On(Natural, "R.Natural32", R_Natural32Value);
On(Natural, "R.Natural64", R_Natural64Value);
On(Size, "R.Size", R_SizeValue);
On(Void, "R.Void", R_VoidValue);

#undef On

static void
registerTypes
  (
  )
{ 
  #define On(Category, cilName, cName) \
    R_register##Category##Type(cilName, sizeof(cilName) - 1, _##cName##_typeDestructing);

  On(Boolean, "R.Boolean", R_BooleanValue);
  On(Integer, "R.Integer8", R_Integer8Value);
  On(Integer, "R.Integer16", R_Integer16Value);
  On(Integer, "R.Integer32", R_Integer32Value);
  On(Integer, "R.Integer64", R_Integer64Value);
  On(Natural, "R.Natural8", R_Natural8Value);
  On(Natural, "R.Natural16", R_Natural16Value);
  On(Natural, "R.Natural32", R_Natural32Value);
  On(Natural, "R.Natural64", R_Natural64Value);
  On(Size, "R.Size", R_SizeValue);
  On(Void, "R.Void", R_VoidValue);

#undef On
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
    R_Status status = R_Arms_startup();
    if (status) {
      return status;
    }
    R_JumpTarget jumpTarget;

    R_pushJumpTarget(&jumpTarget);
    if (R_JumpTarget_save(&jumpTarget)) {
      R_TypeNames_startup();
      R_popJumpTarget();
    } else {
      R_popJumpTarget();
      R_Arms_run();
      R_Arms_shutdown();
      return R_getStatus();
    }

    R_pushJumpTarget(&jumpTarget);
    if (R_JumpTarget_save(&jumpTarget)) {
      _R_startupTypes();
      R_popJumpTarget();
    } else {
      R_popJumpTarget();
      R_TypeNames_onPreMark();
      R_Arms_run();
      R_TypeNames_onPostFinalize(true);
      R_TypeNames_shutdown();
      R_Arms_shutdown();
      return R_getStatus();
    }

    R_pushJumpTarget(&jumpTarget);
    if (R_JumpTarget_save(&jumpTarget)) {
      registerTypes();
      _R_Object_getType();
      R_popJumpTarget();
    } else {
      R_popJumpTarget();

      _R_shutdownTypes();

      R_TypeNames_onPreMark();
      R_Arms_run();
      R_TypeNames_onPostFinalize(true);
      R_TypeNames_shutdown();

      R_Arms_run();

      R_Arms_shutdown();

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
    _R_shutdownTypes();

    R_TypeNames_onPreMark();
    R_Arms_run();
    R_TypeNames_onPostFinalize(true);
    R_TypeNames_shutdown();

    R_Arms_run();

    R_Arms_shutdown();
  }
  g_referenceCount--;
  return R_Status_Success;
}
