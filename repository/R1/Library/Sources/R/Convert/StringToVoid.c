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

// Last modified: 2024-09-26

#include "R/Convert/Include.h"

#include "R/Convert/parse.i"

static Arcadia_VoidValue
toVoid
  (
    Arcadia_Process* process,
    State* state
  );

static Arcadia_VoidValue
toVoid
  (
    Arcadia_Process* process,
    State* state
  )
{
#if 0
 // Precondition prevents that.
  if (CodePoint_Start != state->symbol) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed);
    Arcadia_Process_jump(process);
  }
#endif
#define check(x) \
  if (!is(state, (x))) { \
    Arcadia_Process_setStatus(process, Arcadia_Status_ConversionFailed); \
    Arcadia_Process_jump(process); \
  } \
  next(state);

  next(state);
  check('v');
  check('o');
  check('i');
  check('d');
  check(CodePoint_End);
  return Arcadia_VoidValue_Void;
#undef check
}

Arcadia_VoidValue
R_toVoid
  (
    Arcadia_Process* process,
    char const* p,
    size_t n
  )
{
  State state;
  state.start = p;
  state.end = p + n;
  state.current = p;
  state.symbol = CodePoint_Start;
  return toVoid(process, &state);
}
