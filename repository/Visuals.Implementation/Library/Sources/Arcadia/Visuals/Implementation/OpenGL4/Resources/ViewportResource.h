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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_VIEWPORTRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_VIEWPORTRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resources/ViewportResource.h"
typedef struct Arcadia_Visuals_Implementation_OpenGL4_BackendContext Arcadia_Visuals_Implementation_OpenGL4_BackendContext;

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #include <GL/glcorearb.h> // For GLuint.
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include <GL/glcorearb.h> // For GLuint.
#else
  #error("environment not (yet) supported")
#endif

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.ViewportResource", Arcadia_Visuals_Implementation_OpenGL4_ViewportResource,
                          u8"Arcadia.Visuals.Implementation.ViewportResource")

struct Arcadia_Visuals_Implementation_OpenGL4_ViewportResource {
  Arcadia_Visuals_Implementation_ViewportResource _parent;

  struct {
    // Default is 193.
    Arcadia_Real32Value red;
    // Default is 216.
    Arcadia_Real32Value green;
    // Default is 195.
    Arcadia_Real32Value blue;
    // Default is 255.
    Arcadia_Real32Value alpha;
  } clearColor;

  // Default is 1.
  Arcadia_Real32Value clearDepth;

  struct {
    // Default is 0.
    Arcadia_Real32Value left;
    // Default is 0.
    Arcadia_Real32Value bottom;
    // Default is 1.
    Arcadia_Real32Value right;
    // Default is 1.
    Arcadia_Real32Value top;
  } relativeViewportRectangle;

  struct {
    // The width of the canvas.
    // Default is 320.
    Arcadia_Real32Value width;
    // The height of the canvas.
    // Default is 240.
    Arcadia_Real32Value height;
  } canvasSize;
};

Arcadia_Visuals_Implementation_OpenGL4_ViewportResource*
Arcadia_Visuals_Implementation_OpenGL4_ViewportResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_VIEWPORTRESOURCE_H_INCLUDED
