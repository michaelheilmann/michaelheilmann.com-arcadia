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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_FRAMEBUFFERRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_FRAMEBUFFERRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"

// A "frame buffer resource" must be created and activated before rendering of a scene may occur.
// The "default" render target writes to the "default" frame buffer.
// A "texture" render target creates a framebuffer and writes to that frame buffer.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.FrameBufferResource", Arcadia_Visuals_Implementation_FrameBufferResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Visuals_Implementation_FrameBufferResourceDispatch {
  Arcadia_Visuals_Implementation_ResourceDispatch _parent;

  void (*activate)(Arcadia_Thread*, Arcadia_Visuals_Implementation_FrameBufferResource*);
  void (*deactivate)(Arcadia_Thread*, Arcadia_Visuals_Implementation_FrameBufferResource*);
  void (*setSize)(Arcadia_Thread*, Arcadia_Visuals_Implementation_FrameBufferResource*, Arcadia_Integer32Value, Arcadia_Integer32Value);
  void (*getSize)(Arcadia_Thread*, Arcadia_Visuals_Implementation_FrameBufferResource*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);
};

struct Arcadia_Visuals_Implementation_FrameBufferResource {
  Arcadia_Visuals_Implementation_Resource _parent;
};

void
Arcadia_Visuals_Implementation_FrameBufferResource_activate
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  );

void
Arcadia_Visuals_Implementation_FrameBufferResource_deactivate
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  );

void
Arcadia_Visuals_Implementation_FrameBufferResource_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

void
Arcadia_Visuals_Implementation_FrameBufferResource_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_FRAMEBUFFERRESOURCE_H_INCLUDED
