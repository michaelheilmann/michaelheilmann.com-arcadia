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

#if !defined(ARCADIA_ENGINE_UI_WIDGETSIZECHANGEDEVENT_H_INCLUDED)
#define ARCADIA_ENGINE_UI_WIDGETSIZECHANGEDEVENT_H_INCLUDED

#if !defined(ARCADIA_ENGINE_UI_PRIVATE) || 1 != ARCADIA_ENGINE_UI_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/UI/Include.h` instead")
#endif
#include "Arcadia/Engine/UI/WidgetEvent.h"

// https://michaelheilmann.com/Arcadia/Engine/UI/#Arcadia_Engine_UI_WidgetSizeChangedEvent
Arcadia_declareObjectType(u8"Arcadia.Engine.UI.WidgetSizeChangedEvent", Arcadia_Engine_UI_WidgetSizeChangedEvent,
                          u8"Arcadia.Engine.UI.WidgetEvent");

struct Arcadia_Engine_UI_WidgetSizeChangedEventDispatch {
  Arcadia_Engine_UI_WidgetEventDispatch _parent;
};

struct Arcadia_Engine_UI_WidgetSizeChangedEvent {
  Arcadia_Engine_UI_WidgetEvent _parent;
  Arcadia_Integer32Value horizontalSize;
  Arcadia_Integer32Value verticalSize;
};

Arcadia_Engine_UI_WidgetSizeChangedEvent*
Arcadia_Engine_UI_WidgetSizeChangedEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Engine_UI_WidgetNode* source,
    Arcadia_Integer32Value horizontalSize,
    Arcadia_Integer32Value verticalSize
  );

#endif // ARCADIA_ENGINE_UI_WIDGETSIZECHANGEDEVENT_H_INCLUDED
