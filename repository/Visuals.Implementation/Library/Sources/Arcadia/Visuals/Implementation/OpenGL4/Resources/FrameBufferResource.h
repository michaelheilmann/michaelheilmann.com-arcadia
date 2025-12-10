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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_FRAMEBUFFERRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_FRAMEBUFFERRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resources/FrameBufferResource.h"
#include "Arcadia/Visuals/Implementation/Resources/TextureResource.h"
typedef struct Arcadia_Visuals_Implementation_OpenGL4_BackendContext Arcadia_Visuals_Implementation_OpenGL4_BackendContext;
typedef struct Arcadia_Visuals_Implementation_OpenGL4_TextureResource Arcadia_Visuals_Implementation_OpenGL4_TextureResource;


#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #include <GL/glcorearb.h> // For GLuint.
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include <GL/glcorearb.h> // For GLuint.
#else
  #error("environment not (yet) supported")
#endif

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.FrameBufferResource", Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource,
                          u8"Arcadia.Visuals.Implementation.FrameBufferResource")

#define Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_Default (1)

struct Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResourceDispatch {
  Arcadia_Visuals_Implementation_FrameBufferResourceDispatch _parent;
};

struct Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource {
  Arcadia_Visuals_Implementation_FrameBufferResource _parent;
  // A pointer to the backing texture.
  Arcadia_Visuals_Implementation_OpenGL4_TextureResource* texture;
  Arcadia_BooleanValue dirty;
  // @brief The width, in pixels, of the frame buffer.
  // @default 320.
  Arcadia_Integer32Value width;
  // @brief The height, in pixels of the frame buffer.
  // @default 240.
  Arcadia_Integer32Value height;
  // The OpenGL ID of the frame buffer.
  GLuint frameBufferID;
};

Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource*
Arcadia_Visuals_Implementation_OpenGL4_FrameBufferResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_FRAMEBUFFERRESOURCE_H_INCLUDED
