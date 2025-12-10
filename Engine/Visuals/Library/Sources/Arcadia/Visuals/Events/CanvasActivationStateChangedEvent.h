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

#if !defined(ARCADIA_VISUALS_EVENTS_CANVASACTIVATIONSTATECHANGEDEVENT_H_INCLUDED)
#define ARCADIA_VISUALS_EVENTS_CANVASACTIVATIONSTATECHANGEDEVENT_H_INCLUDED

#include "Arcadia/Visuals/Events/CanvasEvent.h"
typedef struct Arcadia_Visuals_Window Arcadia_Visuals_Window;

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Visuals_CanvasActivationStateChangedEvent
Arcadia_declareObjectType(u8"Arcadia.Visuals.CanvasActivationStateChangedEvent", Arcadia_Visuals_CanvasActivationStateChangedEvent,
                          u8"Arcadia.Visuals.CanvasEvent");

struct Arcadia_Visuals_CanvasActivationStateChangedEventDispatch {
  Arcadia_Visuals_CanvasEventDispatch parent;
};

struct Arcadia_Visuals_CanvasActivationStateChangedEvent {
  Arcadia_Visuals_CanvasEvent _parent;
  Arcadia_BooleanValue active;
};

#endif // ARCADIA_VISUALS_EVENTS_CANVASACTIVATIONSTATECHANGEDEVENT_H_INCLUDED
