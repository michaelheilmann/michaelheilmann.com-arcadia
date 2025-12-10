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

#if !defined(ARCADIA_AUDIALS_IMPLEMENTATION_OPENAL_RESOURCES_SOUNDSOURCERESOURCE_H_INCLUDED)
#define ARCADIA_AUDIALS_IMPLEMENTATION_OPENAL_RESOURCES_SOUNDSOURCERESOURCE_H_INCLUDED

#include "Arcadia/Audials/Implementation/Resources/SoundSourceResource.h"
typedef struct Arcadia_Audials_Implementation_OpenAL_BackendContext Arcadia_Audials_Implementation_OpenAL_BackendContext;

#define AL_LIBTYPE_STATIC
#include <AL/al.h>

Arcadia_declareObjectType(u8"Arcadia.Audials.Implementation.OpenAL.SoundSourceResource", Arcadia_Audials_Implementation_OpenAL_SoundSourceResource,
                          u8"Arcadia.Audials.Implementation.SoundSourceResource");

struct Arcadia_Audials_Implementation_OpenAL_SoundSourceResourceDispatch {
  Arcadia_Audials_Implementation_SoundSourceResourceDispatch _parent;
};

struct Arcadia_Audials_Implementation_OpenAL_SoundSourceResource {
  Arcadia_Audials_Implementation_SoundSourceResource _parent;
  Arcadia_Real32Value volume;
  Arcadia_Natural8Value dirtyBits;
  Arcadia_ByteBuffer* byteBuffer;
  ALuint alBufferID;
  ALuint alSourceID;
};

Arcadia_Audials_Implementation_OpenAL_SoundSourceResource*
Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* backendContext
  );

#endif // ARCADIA_AUDIALS_IMPLEMENTATION_OPENAL_RESOURCES_SOUNDSOURCERESOURCE_H_INCLUDED
