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

#if !defined(ARCADIA_ENGINE_SYSTEMEVENT_H_INCLUDED)
#define ARCADIA_ENGINE_SYSTEMEVENT_H_INCLUDED

#include "Arcadia/Engine/Event.h"
typedef struct Arcadia_Engine_System Arcadia_Engine_System;

Arcadia_declareEnumerationType(u8"Arcadia.Engine.SystemEventKind", Arcadia_Engine_SystemEventKind);

enum Arcadia_Engine_SystemEventKind {
  /// The backend context will be detached.
  Arcadia_Engine_ResourceEventKind_PreDetach,
  /// The backend context was attached.
  Arcadia_Engine_ResourceEventKind_PostAttach,
};

/// @code
/// class Arcadia.Engine.SystemEvent extends Arcadia.Engine.Event {
///   constructor(timeStamp : Arcadia.Natural64, kind : Arcadia.Engine.SystemEventKind, system : Arcadia.Engine.System)
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Engine.SystemEvent", Arcadia_Engine_SystemEvent,
                          u8"Arcadia.Engine.Event");

struct Arcadia_Engine_SystemEvent {
  Arcadia_Engine_Event _parent; 
  Arcadia_Engine_SystemEventKind kind;
  Arcadia_Engine_System* origin;
};

/// @brief Create a system event.
/// @param thread A pointer to this thread.
/// @return A pointer to the system event.
Arcadia_Engine_SystemEvent*
Arcadia_Engine_SystemEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value timeStamp,
    Arcadia_Engine_SystemEventKind kind,
    Arcadia_Engine_System* origin
  );

#endif // ARCADIA_ENGINE_SYSTEMEVENT_H_INCLUDED
