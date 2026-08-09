// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_ENGINE_INPUT_KEYBOARDKEY_H_INCLUDED)
#define ARCADIA_ENGINE_INPUT_KEYBOARDKEY_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// https://michaelheilmann.com/Arcadia/Engine/#Arcadia_Engine_Input_KeyboardKey
Arcadia_declareEnumerationType(u8"Arcadia.Engine.Input.KeyboardKey",
                               Arcadia_Engine_Input_KeyboardKey);

enum Arcadia_Engine_Input_KeyboardKey {

#define withAliases
#define Alias(alias,aliased) Arcadia_Engine_Input_KeyboardKey_##alias = Arcadia_Engine_Input_KeyboardKey_##aliased,
#define Define(name,value,description) Arcadia_Engine_Input_KeyboardKey_##name = value,

#include "Arcadia/Engine/Input/KeyboardKey.i"

#undef Define
#undef Alias
#undef withAliases

};

// https://michaelheilnmann.com/Arcadia/Engine/#Arcadia_Engine_Input_KeyboardKey_toString
Arcadia_String*
Arcadia_Engine_Input_KeyboardKey_toString
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Input_KeyboardKey self
  );

#endif // ARCADIA_ENGINE_INPUT_KEYBOARDKEY_H_INCLUDED
