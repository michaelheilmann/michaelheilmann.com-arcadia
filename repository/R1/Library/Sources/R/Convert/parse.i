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

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Utf8.h"
#include "R/cstdlib.h"

#define CodePoint_Start (R_Utf8CodePoint_Last + 1)
#define CodePoint_End (R_Utf8CodePoint_Last + 2)
#define CodePoint_Error (R_Utf8CodePoint_Last + 3)

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

static R_BooleanValue
isEnd
  (
    State* state
  )
{ return (CodePoint_End == state->symbol); }

static R_BooleanValue
isZero
  (
    State* state
  )
{ 
  return ('0' == state->symbol);
}

static R_BooleanValue
isDigit
  (
    State* state
  )
{
  return ('0' <= state->symbol)
      && (state->symbol <= '9');
}

static R_BooleanValue
isSign
  (
    State* state
  )
{
  return ('+' == state->symbol)
      || ('-' == state->symbol);
}

static R_BooleanValue
isPlus
  (
    State* state
  )
{
  return ('+' == state->symbol);
}

static R_BooleanValue
isMinus
  (
    State* state
  )
{
  return ('-' == state->symbol);
}

static R_BooleanValue
isPeriod
  (
    State* state
  )
{ return ('.' == state->symbol); }

static R_BooleanValue
isExponentPrefix
  (
    State* state
  )
{
  return ('e' == state->symbol)
      || ('E' == state->symbol);
}

static R_BooleanValue
is
  (
    State* state,
    uint32_t x
  )
{ return x == state->symbol; }
