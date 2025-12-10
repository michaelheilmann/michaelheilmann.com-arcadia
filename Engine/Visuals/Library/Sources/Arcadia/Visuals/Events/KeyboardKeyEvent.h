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

#if !defined(ARCADIA_VISUALS_EVENTS_KEYBOARDKEYEVENT_H_INCLUDED)
#define ARCADIA_VISUALS_EVENTS_KEYBOARDKEYEVENT_H_INCLUDED

#include "Arcadia/Engine/Include.h"
#include "Arcadia/Visuals/Events/KeyboardKey.h"
#include "Arcadia/Visuals/Events/KeyboardKeyAction.h"
typedef struct Arcadia_Visuals_Window Arcadia_Visuals_Window;

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Visuals_KeyboardKeyEvent
Arcadia_declareObjectType(u8"Arcadia.Visuals.KeyboardKeyEvent", Arcadia_Visuals_KeyboardKeyEvent,
                          u8"Arcadia.Engine.Event");

struct Arcadia_Visuals_KeyboardKeyEventDispatch {
  Arcadia_Engine_EventDispatch _parent;
};

struct Arcadia_Visuals_KeyboardKeyEvent {
  Arcadia_Engine_Event _parent;
  Arcadia_Visuals_KeyboardKey key;
  Arcadia_Visuals_KeyboardKeyAction action;
};

/// @brief Create a keyboard key event.
/// @param key The keyboard key.
/// @param action The action of the keyboard key.
/// #Arcadia_Visuals_KeyboardKeyAction_Pressed if the keyboard key was pressed,
/// #Arcadia_Visuals_KeyboardKeyAction_Released if the keyboard key was released.
/// @return The keyboard key event.
Arcadia_Visuals_KeyboardKeyEvent*
Arcadia_Visuals_KeyboardKeyEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_KeyboardKeyAction action,
    Arcadia_Visuals_KeyboardKey key
  );

Arcadia_Visuals_KeyboardKeyAction
Arcadia_Visuals_KeyboardKeyEvent_getAction
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_KeyboardKeyEvent* self
  );

Arcadia_Visuals_KeyboardKey
Arcadia_Visuals_KeyboardKeyEvent_getKey
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_KeyboardKeyEvent* self
  );

#endif // ARCADIA_VISUALS_EVENTS_KEYBOARDKEYEVENT_H_INCLUDED
