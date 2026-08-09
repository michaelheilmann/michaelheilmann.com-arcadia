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

#if !defined(ARCADIA_STARSHIP_POSITIONCHANGEINPUTEVENT_H_INCLUDED)
#define ARCADIA_STARSHIP_POSITIONCHANGEINPUTEVENT_H_INCLUDED

#include "Arcadia/Engine/Include.h"

/// @brief Event requesting a "position change" of an object.
/// The event specifies a translation.
Arcadia_declareObjectType(u8"Arcadia.Starship.PositionChangeInputEvent", Arcadia_Starship_PositionChangeInputEvent,
                          u8"Arcadia.Engine.Event");

struct Arcadia_Starship_PositionChangeInputEventDispatch {
  Arcadia_Engine_EventDispatch parent;
};

struct Arcadia_Starship_PositionChangeInputEvent {
  Arcadia_Engine_Event parent;

  /// @brief The translation value.
  Arcadia_Math_Vector3Real32* translation;
};

/// @param timestamp The timestamp of the event.
/// @param translation The translation value.
/// @return A pointer to the "position change input" event.
Arcadia_Starship_PositionChangeInputEvent*
Arcadia_Starship_PositionChangeInputEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Math_Vector3Real32* translation
  );

#endif // ARCADIA_STARSHIP_POSITIONCHANGEINPUTEVENT_H_INCLUDED
