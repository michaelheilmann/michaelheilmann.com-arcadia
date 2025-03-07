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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/TypeNameParser.h"

#include "Arcadia/Ring1/Include.h"

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
    Arcadia_Thread* thread,
    char const** current,
    char const* start,
    char const* end
  )
{
  if (!isAlphabetic(*current, start, end) && !isUnderscore(*current, start, end)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  (*current)++;
  while (isAlphabetic(*current, start, end) || isUnderscore(*current, start, end) || isAlphanumeric(*current, start, end)) {
    (*current)++;
  }
}

static void
parseQualifiedName
  (
    Arcadia_Thread* thread,
    char const** current,
    char const* start,
    char const* end
  )
{
  parseName(thread, current, start, end);
  while (isPeriod(*current, start, end)) {
    (*current)++;
    parseName(thread, current, start, end);
  }
}

void
Arcadia_Names_parseTypeName
  (
    Arcadia_Thread* thread,
    const char *bytes,
    size_t numberOfBytes
  )
{
  char const* current = bytes,
            * start = bytes,
            * end = ((uint8_t const*)bytes) + numberOfBytes;
  parseQualifiedName(thread, &current, start, end);
  if (!isEnd(current, start, end)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}
