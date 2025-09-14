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

#if !defined(ARCADIA_AUDIALS_BACKEND_H_INCLUDED)
#define ARCADIA_AUDIALS_BACKEND_H_INCLUDED

#include "Arcadia/Audials/System.h"

// Arcadia.Audials.Backend objects represent audials backends like "OpenAL".
// Arcadia.Engine provides the list of backends and it also allows for activating/deactivating exactly one backend.
// Switching backends invalidates windows, contexts, and resources.
Arcadia_declareObjectType(u8"Arcadia.Audials.Backend", Arcadia_Audials_Backend,
                          u8"Arcadia.Engine.Backend");

struct Arcadia_Audials_Backend {
  Arcadia_Engine_Backend _parent;
  void (*open)(Arcadia_Thread*, Arcadia_Audials_Backend*);
  void (*close)(Arcadia_Thread*, Arcadia_Audials_Backend*);
  Arcadia_String *(*getName)(Arcadia_Thread*, Arcadia_Audials_Backend*);
  Arcadia_Audials_System* (*createSystem)(Arcadia_Thread*, Arcadia_Audials_Backend*);
};

/// @brief Ensure this backend is opened.
/// @param thread A pointer to this thread.
/// @param self A pointer to this backend.
void
Arcadia_Audials_Backend_open
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Backend* self
  );

/// @brief Ensure this backend is closed.
/// @param thread A pointer to this thread.
/// @param self A pointer to this backend.
void
Arcadia_Audials_Backend_close
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Backend* self
  );

/// @brief Get the name of this backend.
/// @param thread A pointer to this thread.
/// @param self A pointer to this window.
Arcadia_String*
Arcadia_Audials_Backend_getName
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Backend* self
  );

/// @brief Create the system.
/// @papram self A pointer to this backend.
/// @return The system.
Arcadia_Audials_System*
Arcadia_Audials_System_createSystem
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Backend* self
  );

#endif // ARCADIA_AUDIALS_BACKEND_H_INCLUDED
