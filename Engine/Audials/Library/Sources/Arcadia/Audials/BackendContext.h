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

#if !defined(ARCADIA_AUDIALS_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_AUDIALS_BACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Engine/Include.h"

/// @code
/// class Arcadia.Audials.BackendContext extends Arcadia.Engine.BackendContext {
///
///   constructor
///     (
///     )
///
///   method update
///     (
///     ) : Void
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Audials.BackendContext", Arcadia_Audials_BackendContext,
                          u8"Arcadia.Engine.BackendContext")

struct Arcadia_Audials_BackendContextDispatch {
  Arcadia_Engine_BackendContextDispatch parent;

  void (*update)(Arcadia_Thread* thread, Arcadia_Audials_BackendContext* self);
};

struct Arcadia_Audials_BackendContext {
  Arcadia_Engine_BackendContext _parent;
};

/// @brief Update this backend context.
/// @param thread A pointer to this thread.
/// @param self A pointer to this backend context.
void
Arcadia_Audials_BackendContext_update
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_BackendContext* self
  );

#endif // ARCADIA_AUDIALS_BACKENDCONTEXT_H_INCLUDED
