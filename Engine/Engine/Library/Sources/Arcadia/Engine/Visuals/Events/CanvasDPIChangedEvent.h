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

#if !defined(ARCADIA_VISUALS_EVENTS_CANVASDPICHANGEDMESSAGE_H_INCLUDED)
#define ARCADIA_VISUALS_EVENTS_CANVASDPICHANGEDMESSAGE_H_INCLUDED

#include "Arcadia/Engine/Visuals/Events/CanvasEvent.h"
typedef struct Arcadia_Engine_Visuals_Window Arcadia_Engine_Visuals_Window;

// https://michaelheilmann.com/Arcadia/Engine/#Arcadia_Visuals_CanvasDPIChangedEvent
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.CanvasDPIChangedEvent", Arcadia_Visuals_CanvasDPIChangedEvent,
                          u8"Arcadia.Engine.Visuals.CanvasEvent");

struct Arcadia_Visuals_CanvasDPIChangedEventDispatch {
  Arcadia_Visuals_CanvasEventDispatch parent;
};

struct Arcadia_Visuals_CanvasDPIChangedEvent {
  Arcadia_Visuals_CanvasEvent _parent;
  Arcadia_Integer32Value horizontalDpi;
  Arcadia_Integer32Value verticalDpi;
};

#endif // ARCADIA_VISUALS_EVENTS_CANVASDPICHANGEDMESSAGE_H_INCLUDED
