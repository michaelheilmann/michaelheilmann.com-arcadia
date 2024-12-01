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

// Last modified: 2024-10-07

#include "R/Utf8.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/cstdlib.h"

R_BooleanValue
R_isUtf8
  (
    void const* bytes,
    R_SizeValue numberOfBytes,
    R_SizeValue* numberOfSymbols
  )
{
  R_SizeValue numberOfSymbols1 = 0;
  uint8_t const* start = (uint8_t const*)bytes;
  uint8_t const* end = start + numberOfBytes;
  uint8_t const* current = start;

  while (current != end) {
    uint8_t x = (*current);
    if (x <= 0x7f) {
      current += 1;
      numberOfSymbols1++;
    } else if (x <= 0x7ff) {
      if (end - current < 2) {
        return R_BooleanValue_False;
      }
      for (R_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          return R_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else if (x <= 0xffff) {
      if (end - current < 3) {
        return R_BooleanValue_False;
      }
      for (R_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          return R_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else if (x <= 0x10ffff) {
      if (end - current < 4) {
        return R_BooleanValue_False;
      }
      for (R_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          return R_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else {
      return R_BooleanValue_False;
    }
  }
  if (numberOfSymbols) {
    *numberOfSymbols = numberOfSymbols1;
  }
  return R_BooleanValue_True;
}

