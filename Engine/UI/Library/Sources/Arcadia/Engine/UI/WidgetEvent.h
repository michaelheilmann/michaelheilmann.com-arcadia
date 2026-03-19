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

#if !defined(ARCADIA_ENGINE_UI_WIDGETEVENT_H_INCLUDED)
#define ARCADIA_ENGINE_UI_WIDGETEVENT_H_INCLUDED

#if !defined(ARCADIA_ENGINE_UI_PRIVATE) || 1 != ARCADIA_ENGINE_UI_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/UI/Include.h` instead")
#endif
#include "Arcadia/Engine/UI/Event.h"
typedef struct Arcadia_Engine_UI_WidgetNode Arcadia_Engine_UI_WidgetNode;

// @code
// constructor(timestamp : Arcadia.Natural64, source : Arcadia.Engine.UI.Widget)
// @endcode
// https://michaelheilmann.com/Arcadia/Engine/UI/#Arcadia_Engine_UI_WidgetEvent
Arcadia_declareObjectType(u8"Arcadia.Engine.UI.WidgetEvent", Arcadia_Engine_UI_WidgetEvent,
                          u8"Arcadia.Engine.UI.Event");

struct Arcadia_Engine_UI_WidgetEventDispatch {
  Arcadia_Engine_UI_EventDispatch _parent;
};

struct Arcadia_Engine_UI_WidgetEvent {
  Arcadia_Engine_UI_Event _parent;
  /// The source of the event.
  Arcadia_Engine_UI_WidgetNode* source;
};

#endif // ARCADIA_ENGINE_UI_WIDGETEVENT_H_INCLUDED
