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

#if !defined(ARCADIA_AUDIALS_IMPLEMENTATION_OPENAL_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_AUDIALS_IMPLEMENTATION_OPENAL_BACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Audials/Include.h"

#define AL_LIBTYPE_STATIC
#include <AL/al.h>
#include <AL/alc.h>
#include <math.h>

/// @code
/// class Arcadia.Audials.Implementation.OpenAL.BackendContext extends Arcadia.Audials.BackendContext {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Audials.Implementation.OpenAL.BackendContext", Arcadia_Audials_Implementation_OpenAL_BackendContext,
                          u8"Arcadia.Audials.BackendContext")

struct Arcadia_Audials_Implementation_OpenAL_BackendContext {
  Arcadia_Audials_BackendContext _parent;
  ALCdevice* alcDevice;
  ALCcontext* alcContext;
  ALuint alBufferId;
  ALuint alSourceId;
};

// @todo Make private.
Arcadia_Audials_Implementation_OpenAL_BackendContext*
Arcadia_Audials_Implementation_OpenAL_BackendContext_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Audials_Implementation_OpenAL_BackendContext*
Arcadia_Audials_Implementation_OpenAL_BackendContext_getOrCreate
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_AUDIALS_IMPLEMENTATION_OPENAL_BACKENDCONTEXT_H_INCLUDED
