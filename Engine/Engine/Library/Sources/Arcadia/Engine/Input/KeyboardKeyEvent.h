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

#if !defined(ARCADIA_ENGINE_INPUT_KEYBOARDKEYEVENT_H_INCLUDED)
#define ARCADIA_ENGINE_INPUT_KEYBOARDKEYEVENT_H_INCLUDED

#include "Arcadia/Engine/Event.h"
#include "Arcadia/Engine/Input/KeyboardKey.h"
#include "Arcadia/Engine/Input/KeyboardKeyAction.h"

// https://michaelheilmann.com/Arcadia/Engine/#Arcadia_Engine_Input_KeyboardKeyEvent
Arcadia_declareObjectType(u8"Arcadia.Engine.Input.KeyboardKeyEvent", Arcadia_Engine_Input_KeyboardKeyEvent,
                          u8"Arcadia.Engine.Event");

struct Arcadia_Engine_Input_KeyboardKeyEventDispatch {
  Arcadia_Engine_EventDispatch _parent;
};

struct Arcadia_Engine_Input_KeyboardKeyEvent {
  Arcadia_Engine_Event _parent;
  Arcadia_Engine_Input_KeyboardKey key;
  Arcadia_Engine_Input_KeyboardKeyAction action;
};

/// @brief Create a keyboard key event.
/// @param key The keyboard key.
/// @param action The action of the keyboard key.
/// #Arcadia_Visuals_KeyboardKeyAction_Pressed if the keyboard key was pressed,
/// #Arcadia_Visuals_KeyboardKeyAction_Released if the keyboard key was released.
/// @return The keyboard key event.
Arcadia_Engine_Input_KeyboardKeyEvent*
Arcadia_Engine_Input_KeyboardKeyEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Engine_Input_KeyboardKeyAction action,
    Arcadia_Engine_Input_KeyboardKey key
  );

Arcadia_Engine_Input_KeyboardKeyAction
Arcadia_Engine_Input_KeyboardKeyEvent_getAction
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Input_KeyboardKeyEvent* self
  );

Arcadia_Engine_Input_KeyboardKey
Arcadia_Engine_Input_KeyboardKeyEvent_getKey
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Input_KeyboardKeyEvent* self
  );

#endif // ARCADIA_ENGINE_INPUT_KEYBOARDKEYEVENT_H_INCLUDED
