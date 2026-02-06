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

#if !defined(ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Audials/Include.h"
typedef struct Arcadia_Engine_Audials_Implementation_SoundSourceResource Arcadia_Engine_Audials_Implementation_SoundSourceResource;

/// @code
/// class Arcadia.Engine.Audials.Implementation.BackendContext extends Arcadia.Audials.BackendContext {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Engine.Audials.Implementation.BackendContext", Arcadia_Engine_Audials_Implementation_BackendContext,
                          u8"Arcadia.Engine.Audials.BackendContextBase");

struct Arcadia_Engine_Audials_Implementation_BackendContextDispatch {
  Arcadia_Engine_Audials_BackendContextBaseDispatch _parent;

  Arcadia_Engine_Audials_Implementation_SoundSourceResource*
  (*createSoundSourceResource)
    (
      Arcadia_Thread* thread,
      Arcadia_Engine_Audials_Implementation_BackendContext* self
    );
};

struct Arcadia_Engine_Audials_Implementation_BackendContext {
  Arcadia_Engine_Audials_BackendContextBase _parent;
};

Arcadia_Engine_Audials_Implementation_SoundSourceResource*
Arcadia_Engine_Audials_Implementation_BackendContext_createSoundSourceResource
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_BackendContext* self
  );

#endif // ARCADIA_ENGINE_AUDIALS_IMPLEMENTATION_BACKENDCONTEXT_H_INCLUDED
