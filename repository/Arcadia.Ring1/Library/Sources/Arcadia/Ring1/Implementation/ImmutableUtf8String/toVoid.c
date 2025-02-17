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

// Last modified: 2025-02-16

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String.h"
#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.h"

Arcadia_VoidValue
_toVoid
  (
    Arcadia_Process1* process,
    Arcadia_ImmutableUtf8String* immutableUtf8StringValue
  )
{
  _State state;
  _State_init(&state, Arcadia_ImmutableUtf8String_getBytes(process, immutableUtf8StringValue),
                      Arcadia_ImmutableUtf8String_getNumberOfBytes(process, immutableUtf8StringValue));
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process1_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    #define check(x) \
      if (!is(&state, (x))) { \
        Arcadia_Process1_setStatus(process, Arcadia_Status_ConversionFailed); \
        Arcadia_Process1_jump(process); \
      } \

    next(&state);
    check('v');
    check('o');
    check('i');
    check('d');
    check(_Unicode_CodePoint_End);
      
    #undef check
    _State_uninit(&state);
    Arcadia_Process1_popJumpTarget(process);   
  } else {
    _State_uninit(&state);
    Arcadia_Process1_popJumpTarget(process);
    Arcadia_Process1_jump(process);
  }

  return Arcadia_VoidValue_Void;
}
