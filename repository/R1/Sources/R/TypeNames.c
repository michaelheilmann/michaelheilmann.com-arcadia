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

#include "R/TypeNames.h"

#include "R.h"
#include <string.h>

static inline R_SizeValue
mix
  (
    R_SizeValue h,
    R_SizeValue a
  )
{ return h * 37 + a; }

static bool
isAlphabetic
  (
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    return false;
  }
  return ('a' <= *current && *current <= 'z')
      || ('A' <= *current && *current <= 'Z');
}

static bool
isAlphanumeric
  (
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    return false;
  }
  return '0' <= *current && *current <= '9';
}

static bool
isUnderscore
  (
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    return false;
  }
  return '_' == *current;
}

static bool
isPeriod
  (
    char const* current,
    char const* start,
    char const* end
  )
{
  if (current == end) {
    return false;
  }
  return '.' == *current;
}

static bool
isEnd
  (
    char const* current,
    char const* start,
    char const* end
  )
{ return current == end; }

static void
parseName
  (
    char const** current,
    char const* start,
    char const* end,
    R_SizeValue* hash
  )
{
  if (!isAlphabetic(*current, start, end) && !isUnderscore(*current, start, end)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  *hash = mix(*hash, (R_SizeValue)(**current));
  (*current)++;
  while (isAlphabetic(*current, start, end) || isUnderscore(*current, start, end) || isAlphanumeric(*current, start, end)) {
    *hash = mix(*hash, (R_SizeValue)(**current));
    (*current)++;
  }
}

_TypeName* _TypeNames_createTypeName(void const* bytes, R_SizeValue numberOfBytes) {
  R_SizeValue hash = numberOfBytes;
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    char const* current = bytes,
              * start = bytes,
              * end = ((uint8_t const*)bytes) + numberOfBytes;
    parseName(&current, start, end, &hash);
    while (isPeriod(current, start, end)) {
      hash = mix(hash, (R_SizeValue)(*current));
      current++;
      parseName(&current, start, end, &hash);
    }
    if (!isEnd(current, start, end)) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_jump();
  }
  _TypeName* typeName = NULL;
  if (Arms_allocateUnmanaged(&typeName, sizeof(_TypeName))) {
    R_setStatus(Arms_Status_AllocationFailed);
    R_jump();
  }
  if (Arms_allocateUnmanaged(&typeName->bytes, numberOfBytes)) {
    Arms_deallocateUnmanaged(typeName);
    typeName = NULL;
    R_popJumpTarget();
    R_jump();   
  }
  memcpy(typeName->bytes, bytes, numberOfBytes);
  typeName->numberOfBytes = numberOfBytes;
  typeName->hash = hash;
  return typeName;
}

void _TypeNames_destroyTypeName(_TypeName* typeName) {
  Arms_deallocateUnmanaged(typeName->bytes);
  typeName->bytes = NULL;
  Arms_deallocateUnmanaged(typeName);
  typeName = NULL;
}

R_BooleanValue
TypeNames_areTypeNamesEqual
  (
    _TypeName const* x,
    _TypeName const* y
  )
{
  if (x == y) {
    return true;
  }
  if (x->hash == y->hash && x->numberOfBytes == y->numberOfBytes) {
    return !memcmp(x->bytes, y->bytes, x->numberOfBytes);
  } else {
    return false;
  }
}

void
_R_TypeNames_startup
  (
  )
{/*Intentionally empty.*/}

void
_R_TypeNames_shutdown
  (
  )
{/*Intentionally empty.*/}
