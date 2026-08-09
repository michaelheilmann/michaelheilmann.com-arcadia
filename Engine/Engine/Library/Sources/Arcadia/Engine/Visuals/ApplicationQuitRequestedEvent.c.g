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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Visuals/ApplicationQuitRequestedEvent.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ApplicationQuitRequestedEvent* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_ApplicationQuitRequestedEventDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_Type_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.ApplicationQuitRequestedEvent", Arcadia_Engine_Visuals_ApplicationQuitRequestedEvent,
                         u8"Arcadia.Engine.Visuals.ApplicationEvent", Arcadia_Engine_Visuals_ApplicationEvent,
                         &_typeOperations);
