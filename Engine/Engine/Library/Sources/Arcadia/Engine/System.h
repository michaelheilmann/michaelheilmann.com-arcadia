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

#if !defined(ARCADIA_ENGINE_SYSTEM_H_INCLUDED)
#define ARCADIA_ENGINE_SYSTEM_H_INCLUDED

#include "Arcadia/Engine/BackendContext.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.System", Arcadia_Engine_System,
                          u8"Arcadia.Object")

struct Arcadia_Engine_System {
  Arcadia_Object _parent;
  void (*setBackendContext)(Arcadia_Thread* thread, Arcadia_Engine_System*, Arcadia_Engine_BackendContext*);
  Arcadia_Engine_BackendContext* (*getBackendContext)(Arcadia_Thread* thread, Arcadia_Engine_System*);
  void (*update)(Arcadia_Thread* thread, Arcadia_Engine_System* self);
};

/// @brief Set the backend context of this system.
/// @param thread A pointer to this thread.
/// @param self A pointer to this system.
/// @param A pointer to the backend context or the null pointer.
void
Arcadia_Engine_System_setBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_System* self,
    Arcadia_Engine_BackendContext* backendContext
  );

/// @brief Get the backend context of this system.
/// @param thread A pointer to this thread.
/// @param self A pointer to this system.
/// @return A pointer to the backend context or the null pointer.
Arcadia_Engine_BackendContext*
Arcadia_Engine_System_getBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_System* self
  );

/// @brief Update this system.
/// @param thread A pointer to this thread.
/// @param self A pointer to this system.
void
Arcadia_Engine_System_update
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_System* self
  );

#endif // ARCADIA_ENGINE_SYSTEM_H_INCLUDED
