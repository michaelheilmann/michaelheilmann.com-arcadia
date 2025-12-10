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

#if !defined(ARCADIA_AUDIALS_IMPLEMENTATION_RESOURCES_SOUNDSOURCERESOURCE_H_INCLUDED)
#define ARCADIA_AUDIALS_IMPLEMENTATION_RESOURCES_SOUNDSOURCERESOURCE_H_INCLUDED

#include "Arcadia/Audials/Implementation/Resource.h"
#include "Arcadia/Math/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Audials.Implementation.SoundSourceResource", Arcadia_Audials_Implementation_SoundSourceResource,
                          u8"Arcadia.Audials.Implementation.Resource")

struct Arcadia_Audials_Implementation_SoundSourceResourceDispatch {
  Arcadia_Audials_Implementation_ResourceDispatch _parent;

  Arcadia_BooleanValue(*isPlaying)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*);
  void (*pause)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*);
  void (*play)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*);
  void (*stop)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*);
  void (*setVolume)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*, Arcadia_Real32Value);
  Arcadia_Real32Value(*getVolume)(Arcadia_Thread*, Arcadia_Audials_Implementation_SoundSourceResource*);
};

struct Arcadia_Audials_Implementation_SoundSourceResource {
  Arcadia_Audials_Implementation_Resource _parent;
};

Arcadia_BooleanValue
Arcadia_Audials_Implementation_SoundSourceResource_isPlaying
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SoundSourceResource* self
  );

void
Arcadia_Audials_Implementation_SoundSourceResource_pause
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SoundSourceResource* self
  );

void
Arcadia_Audials_Implementation_SoundSourceResource_play
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SoundSourceResource* self
  );

void
Arcadia_Audials_Implementation_SoundSourceResource_stop
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SoundSourceResource* self
  );

void
Arcadia_Audials_Implementation_SoundSourceResource_setVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SoundSourceResource* self,
    Arcadia_Real32Value volume
  );

Arcadia_Real32Value
Arcadia_Audials_Implementation_SoundSourceResource_getVolume
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SoundSourceResource* self
  );

#endif // ARCADIA_AUDIALS_IMPLEMENTATION_RESOURCES_SOUNDSOURCERESOURCE_H_INCLUDED
