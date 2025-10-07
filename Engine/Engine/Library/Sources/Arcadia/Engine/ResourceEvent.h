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

#if !defined(ARCADIA_ENGINE_RESOURCEEVENT_H_INCLUDED)
#define ARCADIA_ENGINE_RESOURCEEVENT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType(u8"Arcadia.Engine.ResourceEventKind", Arcadia_Engine_ResourceEventKind);

enum Arcadia_Engine_ResourceEventKind {
  /// A resource was attached.
  Arcadia_Engine_ResourceEventKind_Attached,
  /// A resource was detached.
  Arcadia_Engine_ResourceEventKind_Detached,
};

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Engine_Event
Arcadia_declareObjectType(u8"Arcadia.Engine.ResourceEvent", Arcadia_Engine_ResourceEvent,
                          u8"Arcadia.Engine.Event");

struct Arcadia_Engine_ResourceEvent {
  Arcadia_Object _parent;
  Arcadia_Natural64Value timestamp;
};

#endif // ARCADIA_ENGINE_RESOURCEEVENT_H_INCLUDED
