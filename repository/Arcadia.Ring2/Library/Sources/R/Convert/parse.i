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

// Last modified: 2024-09-26

#include "R/Convert/Include.h"

#if 0
#include "R/Utf8.h"
#endif
#include <assert.h>

#define CodePoint_Start (Arcadia_Utf8CodePoint_Last + 1)
#define CodePoint_End (Arcadia_Utf8CodePoint_Last + 2)
#define CodePoint_Error (Arcadia_Utf8CodePoint_Last + 3)

typedef struct State {
  uint32_t symbol;
  char const* start;
  char const* end;
  char const* current;
} State;

static void
next
  (
    State* state
  )
{
  if (state->symbol == CodePoint_End || state->symbol == CodePoint_Error) {
    return;
  }
  if (state->current == state->end) {
    state->symbol = CodePoint_End;
  } else {
    assert(state->current != state->end);
    state->symbol = *state->current;
    state->current++;
  }
}

static Arcadia_BooleanValue
isEnd
  (
    State* state
  )
{ return (CodePoint_End == state->symbol); }

static Arcadia_BooleanValue
isZero
  (
    State* state
  )
{ 
  return ('0' == state->symbol);
}

static Arcadia_BooleanValue
isDigit
  (
    State* state
  )
{
  return ('0' <= state->symbol)
      && (state->symbol <= '9');
}

static Arcadia_BooleanValue
isSign
  (
    State* state
  )
{
  return ('+' == state->symbol)
      || ('-' == state->symbol);
}

static Arcadia_BooleanValue
isPlus
  (
    State* state
  )
{
  return ('+' == state->symbol);
}

static Arcadia_BooleanValue
isMinus
  (
    State* state
  )
{
  return ('-' == state->symbol);
}

static Arcadia_BooleanValue
isPeriod
  (
    State* state
  )
{ return ('.' == state->symbol); }

static Arcadia_BooleanValue
isExponentPrefix
  (
    State* state
  )
{
  return ('e' == state->symbol)
      || ('E' == state->symbol);
}

static Arcadia_BooleanValue
is
  (
    State* state,
    uint32_t x
  )
{ return x == state->symbol; }
