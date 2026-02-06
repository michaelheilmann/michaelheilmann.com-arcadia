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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_TEXTURERESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_TEXTURERESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resources/TextureResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/BackendIncludes.h"
typedef struct Arcadia_Visuals_Implementation_OpenGL4_BackendContext Arcadia_Visuals_Implementation_OpenGL4_BackendContext;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.TextureResource", Arcadia_Visuals_Implementation_OpenGL4_TextureResource,
                          u8"Arcadia.Visuals.Implementation.TextureResource");

struct Arcadia_Visuals_Implementation_OpenGL4_TextureResourceDispatch {
  Arcadia_Visuals_Implementation_TextureResourceDispatch _parent;
};

struct Arcadia_Visuals_Implementation_OpenGL4_TextureResource {
  Arcadia_Visuals_Implementation_TextureResource _parent;

  // The address mode of this texture along the u-axis.
  // @default Arcadia_Visuals_TextureAddressMode_Repeat.
  Arcadia_Engine_Visuals_TextureAddressMode addressModeU;

  // The address mode of this texture along the v-axis.
  // @default Arcadia_Visuals_TextureAddressMode_Repeat.
  Arcadia_Engine_Visuals_TextureAddressMode addressModeV;

  // Bitmask indicating what aspects of the texture are dirty.
  Arcadia_Natural8Value dirtyBits;

  // The OpenGL ID of this texture.
  GLuint id;

  // The texture magnification filter.
  // @default Arcadia_Visuals_TextureFilter_Linear
  Arcadia_Engine_Visuals_TextureFilter magnificationFilter;
  // The texture minification filter.
  // @default Arcadia_Visuals_TextureFilter_Linear
  Arcadia_Engine_Visuals_TextureFilter minificationFilter;
  
  /// @brief The pixel buffer storing the texture data.
  Arcadia_Imaging_PixelBuffer* pixelBuffer;
};

Arcadia_Visuals_Implementation_OpenGL4_TextureResource*
Arcadia_Visuals_Implementation_OpenGL4_TextureResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_RESOURCES_TEXTURERESOURCE_H_INCLUDED
