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

#include "R/Convert/StringToBoolean.h"

#include "R/Convert/parse.i"

static R_BooleanValue
toBoolean
  (
    State* state
  );

static R_BooleanValue
toBoolean
  (
    State* state
  )
{
#if 0
 // Precondition prevents that.
  if (CodePoint_Start != state->symbol) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
#endif
#define check(x) \
  if (!is(state, (x))) { \
    R_setStatus(R_Status_ConversionFailed); \
    R_jump(); \
  } \
  next(state);

  next(state);
  if (is(state, 't')) {
    next(state);
    check('r');
    check('u');
    check('e');
    check(CodePoint_End);
    return R_BooleanValue_True;
  } else if (is(state, 'f')) {
    next(state);
    check('a');
    check('l');
    check('s');
    check('e');
    check(CodePoint_End);
    return R_BooleanValue_False;
  } else {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
#undef check
}

R_BooleanValue
R_toBoolean
  (
    char const* p,
    R_SizeValue n
  )
{ 
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toBoolean(&state);
}
