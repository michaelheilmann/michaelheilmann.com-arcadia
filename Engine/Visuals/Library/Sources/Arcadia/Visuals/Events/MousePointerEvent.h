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

#if !defined(ARCADIA_VISUALS_EVENTS_MOUSEPOINTEREVENT_H_INCLUDED)
#define ARCADIA_VISUALS_EVENTS_MOUSEPOINTEREVENT_H_INCLUDED

#include "Arcadia/Engine/Include.h"
#include "Arcadia/Visuals/Events/MousePointerAction.h"
typedef struct Arcadia_Visuals_Window Arcadia_Visuals_Window;

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Visuals_MousePointerEvent
Arcadia_declareObjectType(u8"Arcadia.Visuals.MousePointerEvent", Arcadia_Visuals_MousePointerEvent,
                          u8"Arcadia.Engine.Event");

struct Arcadia_Visuals_MousePointerEventDispatch {
  Arcadia_Engine_EventDispatch _parent;
};

struct Arcadia_Visuals_MousePointerEvent {
  Arcadia_Engine_Event _parent;
  Arcadia_Visuals_MousePointerAction action;
  Arcadia_Integer32Value x;
  Arcadia_Integer32Value y;
};

/// @brief Create a mouse pointer event.
/// @param action The action.
/// @param x The position of the mouse pointer along the x-axis.
/// @param y The position of the mouse pointer along the y-axis.
/// @return The mouse pointer event.
Arcadia_Visuals_MousePointerEvent*
Arcadia_Visuals_MousePointerEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_MousePointerAction action,
    Arcadia_Integer32Value x,
    Arcadia_Integer32Value y
  );

#endif // ARCADIA_VISUALS_EVENTS_MOUSEPOINTEREVENT_H_INCLUDED
