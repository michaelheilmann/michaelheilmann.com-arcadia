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

#include "R/Atoms.h"
#include "R/Object.internal.h"
// For registering the types.
#include "R/TypeNames.h"
#include "R/ArmsIntegration.h"


typedef uint32_t ReferenceCount;
#define ReferenceCount_Minimum (UINT32_C(0))
#define ReferenceCount_Maximum (UINT32_MAX)

static ReferenceCount g_referenceCount = 0;

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
      _R_StringBuffer_registerType();
      _R_Utf8Reader_registerType();
      _R_Utf8Writer_registerType();
      _R_Utf8ByteBufferReader_registerType();
      _R_Utf8ByteBufferWriter_registerType();
      _R_Utf8StringReader_registerType();
      _R_String_registerType();
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
