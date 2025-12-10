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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_TEXTURERESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_TEXTURERESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.TextureResource", Arcadia_Visuals_Implementation_TextureResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Visuals_Implementation_TextureResourceDispatch {
  Arcadia_Visuals_Implementation_ResourceDispatch _parent;

  Arcadia_Visuals_TextureAddressMode(*getAddressModeU)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*);
  Arcadia_Visuals_TextureAddressMode(*getAddressModeV)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*);

  Arcadia_Integer32Value(*getHeight)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*);

  Arcadia_Visuals_TextureFilter(*getMagnificationFilter)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*);
  Arcadia_Visuals_TextureFilter(*getMinificationFilter)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*);

  Arcadia_Integer32Value(*getWidth)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*);

  void (*setAddressModeU)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_TextureAddressMode);
  void (*setAddressModeV)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_TextureAddressMode);

  void (*setHeight)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Integer32Value);

  void (*setMagnificationFilter)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_TextureFilter);
  void (*setMinificationFilter)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Visuals_TextureFilter);

  void (*setWidth)(Arcadia_Thread*, Arcadia_Visuals_Implementation_TextureResource*, Arcadia_Integer32Value);
};

struct Arcadia_Visuals_Implementation_TextureResource {
  Arcadia_Visuals_Implementation_Resource _parent;
};

Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Implementation_TextureResource_getAddressModeU
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Implementation_TextureResource_getAddressModeV
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

Arcadia_Integer32Value
Arcadia_Visuals_Implementation_TextureResource_getHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Implementation_TextureResource_getMagnificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Implementation_TextureResource_getMinificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

Arcadia_Integer32Value
Arcadia_Visuals_Implementation_TextureResource_getWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

void
Arcadia_Visuals_Implementation_TextureResource_setAddressModeU
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Visuals_TextureAddressMode addressMode
  );

void
Arcadia_Visuals_Implementation_TextureResource_setAddressModeV
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Visuals_TextureAddressMode addressMode
  );

void
Arcadia_Visuals_Implementation_TextureResource_setHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Integer32Value height
  );

void
Arcadia_Visuals_Implementation_TextureResource_setMagnificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Visuals_TextureFilter magnificationFilter
  );

void
Arcadia_Visuals_Implementation_TextureResource_setMinificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Visuals_TextureFilter minificationFilter
  );

void
Arcadia_Visuals_Implementation_TextureResource_setWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Integer32Value width
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_TEXTURERESOURCE_H_INCLUDED
