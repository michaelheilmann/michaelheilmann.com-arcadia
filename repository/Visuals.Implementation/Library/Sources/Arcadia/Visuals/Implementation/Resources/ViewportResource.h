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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_VIEWPORTRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_VIEWPORTRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.ViewportResource", Arcadia_Visuals_Implementation_ViewportResource,
                          u8"Arcadia.Visuals.Implementation.Resource")

struct Arcadia_Visuals_Implementation_ViewportResource {
  Arcadia_Visuals_Implementation_Resource _parent;

  void (*setClearColor)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_ViewportResource* self,
      Arcadia_Real32Value red,
      Arcadia_Real32Value green,
      Arcadia_Real32Value blue,
      Arcadia_Real32Value alpha
    );

  void
  (*setRelativeViewportRectangle)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_ViewportResource* self,
      Arcadia_Real32Value left,
      Arcadia_Real32Value bottom,
      Arcadia_Real32Value right,
      Arcadia_Real32Value top
    );

  void
  (*setCanvasSize)
    (
      Arcadia_Thread* thread,
      Arcadia_Visuals_Implementation_ViewportResource* self,
      Arcadia_Real32Value width,
      Arcadia_Real32Value height
    );

};

/// Set the clear color.
/// Default values are red = 193, green = 216, blue = 195, and alpha = 255.
void
Arcadia_Visuals_Implementation_ViewportResource_setClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_ViewportResource* self,
    Arcadia_Real32Value red,
    Arcadia_Real32Value green,
    Arcadia_Real32Value blue,
    Arcadia_Real32Value alpha
  );

/// Set the viewport relative rectangle.
/// x axis going from left to right, y axis going from bottom to top
/// Default values are left = 0, bottom = 0, right = 1, and top  = 1.
void
Arcadia_Visuals_Implementation_ViewportResource_setRelativeViewportRectangle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_ViewportResource* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  );

/// Set the canvas size.
/// Default values are width = 320 and height = 240.
void
Arcadia_Visuals_Implementation_ViewportResource_setCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_ViewportResource* self,
    Arcadia_Real32Value width,
    Arcadia_Real32Value height
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_RESOURCES_VIEWPORTRESOURCE_H_INCLUDED
