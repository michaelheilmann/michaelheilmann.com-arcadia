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

#if !defined(ARCADIA_ENGINE_BACKEND_H_INCLUDED)
#define ARCADIA_ENGINE_BACKEND_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Engine/BackendContext.h"

// Arcadia.Engine.Backend objects represent backends like "OpenGL" or "OpenAL".
// Arcadia.Engine provides a list of the available backends.
// Arcadia.Engine.Backend allow for the creation of contexts to backends via Arcadia.Engine.Backend.createBackendContext(...) : Arcadia.Engine.BackendContext.
// A Arcadia.Engine.BackendContext is a heavyweight object, potentially occupying contested system resources like audio devices or video devices.
Arcadia_declareObjectType(u8"Arcadia.Engine.Backend", Arcadia_Engine_Backend,
                          u8"Arcadia.Object");

struct Arcadia_Engine_BackendDispatch {
  Arcadia_ObjectDispatch _parent;

  Arcadia_String* (*getName)(Arcadia_Thread*, Arcadia_Engine_Backend*);
  Arcadia_Engine_BackendContext* (*createBackendContext)(Arcadia_Thread*, Arcadia_Engine_Backend*);
};

struct Arcadia_Engine_Backend {
  Arcadia_Object _parent;
};

/// @brief Get the name of this backend.
/// @param thread A pointer to this thread.
/// @param self A pointer to this window.
Arcadia_String*
Arcadia_Engine_Backend_getName
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Backend* self
  );

/// @brief Create a backend context of this backend.
/// @papram self A pointer to this backend.
/// @return A Arcadia_Engine_BackendContext to the system.
Arcadia_Engine_BackendContext*
Arcadia_Engine_Backend_createBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Backend* self
  );

#endif // ARCADIA_ENGINE_BACKEND_H_INCLUDED
