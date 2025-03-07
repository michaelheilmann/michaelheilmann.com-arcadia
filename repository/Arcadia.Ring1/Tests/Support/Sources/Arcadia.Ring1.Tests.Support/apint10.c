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

// Last modified: 2025-02-17

#include "Arcadia.Ring1.Tests.Support/apint10.h"

#include <stdlib.h>
#include "Arcadia/Ring1/Support/apint10.h"

// test
// - initialize and
// - set i64
static void
testFromI64
  (
    Arcadia_Thread* thread
  )
{
  size_t k = 0;
  apint10 v[2];
  for (; k < 2; ++k) {
    if (apint10_initialize(&v[k])) {
      goto Error;
    }
  }
  for (size_t i = 0; i < 63; ++i) {
    int64_t u = INT64_C(1) << i;
    if (apint10_from_int64(&v[0], u)) {
      goto Error;
    }
  }

  while (k > 0) {
    apint10_uninitialize(&v[--k]);
  }
  return;
Error:
  while (k > 0) {
    apint10_uninitialize(&v[--k]);
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
}


// test
// - initialize and
// - set u64
static void
testFromU64
  (
    Arcadia_Thread* thread
  )
{
  size_t k = 0;
  apint10 v[2];
  for (; k < 2; ++k) {
    if (apint10_initialize(&v[k])) {
      goto Error;
    }
  }
  for (size_t i = 0; i < 63; ++i) {
    uint64_t u = UINT64_C(1) << i;
    if (apint10_from_uint64(&v[0], u)) {
      goto Error;
    }
  }

  while (k > 0) {
    apint10_uninitialize(&v[--k]);
  }
  return;
Error:
  while (k > 0) {
    apint10_uninitialize(&v[--k]);
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  Arcadia_Thread_jump(thread);
}

void
Arcadia_Ring1_Tests_Support_apint10
  (
    Arcadia_Thread* thread
  )
{
  testFromI64(thread);
  testFromU64(thread);
}
