// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Module/Visuals/Events/KeyboardKey.h"

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
};

Arcadia_defineEnumerationType(u8"Arcadia.Visuals.KeyboardKey", Arcadia_Visuals_KeyboardKey, &_typeOperations);

Arcadia_String*
Arcadia_Visuals_KeyboardKey_toString
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_KeyboardKey self
  )
{
  switch (self) {
  #define Alias(alias, aliased)
  #define Define(name, value, description)\
    case Arcadia_Visuals_KeyboardKey_##name: {\
      return Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, description, sizeof(description) - 1)); \
    };
  #include "Module/Visuals/Events/KeyboardKey.i"
  #undef Define
  #undef Alias
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    };
  };
}

