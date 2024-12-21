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

#include "R/Convert/StringToReal.h"

#include "R/Convert/parse.i"

R_Real32Value
toReal32
  (
    State* state
  )
{
  next(state);
  if (isPlus(state) || isMinus(state)) {
    next(state);
  }
  if (isDigit(state)) {
    do {
      next(state);
    } while (isDigit(state));
  } else if (isPeriod(state)) {
    next(state);
    if (!isDigit(state)) {
      R_setStatus(R_Status_ConversionFailed);
      R_jump();
    }
    do {
      next(state);
    } while (isDigit(state));
  } else {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  if (isExponentPrefix(state)) {
    next(state);
    if (isPlus(state) || isMinus(state)) {
      next(state);
    }
    if (!isDigit(state)) {
      R_setStatus(R_Status_ConversionFailed);
      R_jump();
    }
    do {
      next(state);
    } while (isDigit(state));
  }
  // @todo: Should be replaced by a "to_chars"-like function.
  char* start;
  if (Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), &start, (state->end - state->start) + 1)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  c_memcpy(start, state->start, state->end - state->start);
  start[state->end - state->start] = '\0';
  char* end;
  float d = strtof(start, &end);
  if (start == end) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), start);
  return d;
}

R_Real32Value
toReal64
  (
    State* state
  )
{
  next(state);
  if (isPlus(state) || isMinus(state)) {
    next(state);
  }
  if (isDigit(state)) {
    do {
      next(state);
    } while (isDigit(state));
  } else if (isPeriod(state)) {
    next(state);
    if (!isDigit(state)) {
      R_setStatus(R_Status_ConversionFailed);
      R_jump();
    }
    do {
      next(state);
    } while (isDigit(state));
  } else {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  if (isExponentPrefix(state)) {
    next(state);
    if (isPlus(state) || isMinus(state)) {
      next(state);
    }
    if (!isDigit(state)) {
      R_setStatus(R_Status_ConversionFailed);
      R_jump();
    }
    do {
      next(state);
    } while (isDigit(state));
  }
  // @todo: Should be replaced by a "to_chars"-like function.
  char* start;
  if (Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), &start, (state->end - state->start) + 1)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  c_memcpy(start, state->start, state->end - state->start);
  start[state->end - state->start] = '\0';
  char* end = NULL;
  double d = strtod(start, &end);
  if (start == end) {
    R_setStatus(R_Status_ConversionFailed);
    R_jump();
  }
  Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), start);
  return d;
}

R_Real32Value
R_toReal32
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
  return toReal32(&state);
}

R_Real64Value
R_toReal64
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
  return toReal64(&state);
}
