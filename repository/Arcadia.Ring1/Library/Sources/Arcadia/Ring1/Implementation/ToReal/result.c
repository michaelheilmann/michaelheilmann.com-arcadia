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

// Last modified: 2025-03-07

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ToReal/result.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_ToReal64_BitsToValue
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value* target,
    Arcadia_ToReal64_Result* source
  )
{
  Arcadia_Natural64Value temporary = source->significand | (((Arcadia_Natural64Value)source->exponent) << Arcadia_Real64Value_ExponentBitsShift);
  if (source->negative) {
    temporary |= Arcadia_Natural64Value_Literal(1) << Arcadia_Real64Value_SignBitsShift;
  }
  Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), target, &temporary, Arcadia_Real64Value_NumberOfBytes);
}
