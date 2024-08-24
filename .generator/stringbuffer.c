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

#include "stringbuffer.h"

#include <string.h>

#include "arcadia/arms1.h"
#include "arcadia/r1.h"

static void registerType(char const* name, size_t nameLength, Arms_VisitCallbackFunction* visit, Arms_FinalizeCallbackFunction* finalize);

static void StringBuffer_finalize(StringBuffer* w);

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

static void StringBuffer_finalize(StringBuffer* w) {
  if (w->p) {
    Arms_deallocateUnmanaged(w->p);
    w->p = NULL;
  }
}

void _StringBuffer_registerType() {
  registerType("StringBuffer", sizeof("StringBuffer") - 1, NULL, (Arms_FinalizeCallbackFunction*)&StringBuffer_finalize);
}

StringBuffer*
StringBuffer_create
  (
  )
{
  StringBuffer* w = NULL;
  Arms_Status armsResult = Arms_allocate(&w, "StringBuffer", sizeof("StringBuffer") - 1, sizeof(StringBuffer));
  if (Arms_Status_Success != armsResult) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  w->p = NULL;
  w->sz = 0;
  w->cp = 0;
  if (Arms_allocateUnmanaged(&w->p, 1)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  return w;
}

R_BooleanValue
StringBuffer_endsWith_pn
  (
    StringBuffer* w,
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (w->sz < numberOfBytes) {
    return R_BooleanValue_False;
  }
  size_t d = w->sz - numberOfBytes;
  return !memcmp(w->p + d, bytes, numberOfBytes);
}

R_BooleanValue
StringBuffer_startsWith_pn
  (
    StringBuffer* w,
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (w->sz < numberOfBytes) {
    return R_BooleanValue_False;
  }
  return !memcmp(w->p, bytes, numberOfBytes);
}

void
StringBuffer_append_pn
  (
    StringBuffer* w,
    char const* bytes,
    size_t numberOfBytes
  )
{
  size_t freeCp = w->cp - w->sz;
  if (freeCp < numberOfBytes) {
    size_t additionalCp = numberOfBytes - freeCp;
    size_t oldCp = w->cp;
    if (SIZE_MAX - oldCp < additionalCp) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    size_t newCp = oldCp + additionalCp;
    if (Arms_reallocateUnmanaged(&w->p, newCp)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    w->cp = newCp;
  }
  memcpy(w->p + w->sz, bytes, numberOfBytes);
  w->sz += numberOfBytes;
}

R_BooleanValue
StringBuffer_areEqual
  (
    StringBuffer* v,
    StringBuffer* w
  )
{
  if (v == w) {
    return R_BooleanValue_True;
  }
  if (v->sz == w->sz) {
    return !memcmp(v->p, w->p, v->sz);
  } else {
    return R_BooleanValue_False;
  }
}

void
StringBuffer_clear
  (
    StringBuffer* w
  )
{
  w->sz = 0;
}
