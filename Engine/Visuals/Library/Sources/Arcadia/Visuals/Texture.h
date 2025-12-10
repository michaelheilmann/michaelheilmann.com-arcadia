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

#if !defined(ARCADIA_VISUALS_TEXTURE_H_INCLUDED)
#define ARCADIA_VISUALS_TEXTURE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif

typedef struct Arcadia_Visuals_BackendContext Arcadia_Visuals_BackendContext;
#include "Arcadia/Visuals/TextureAddressMode.h"
#include "Arcadia/Visuals/TextureFilter.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Texture", Arcadia_Visuals_Texture,
                          u8"Arcadia.Object")

struct Arcadia_Visuals_TextureDispatch {
  Arcadia_ObjectDispatch parent;

  Arcadia_Visuals_TextureAddressMode (*getAddressModeU)(Arcadia_Thread*, Arcadia_Visuals_Texture*);
  Arcadia_Visuals_TextureAddressMode (*getAddressModeV)(Arcadia_Thread*, Arcadia_Visuals_Texture*);
  Arcadia_Integer32Value (*getHeight)(Arcadia_Thread*, Arcadia_Visuals_Texture*);
  Arcadia_Visuals_TextureFilter (*getMagnificationFilter)(Arcadia_Thread*, Arcadia_Visuals_Texture*);
  Arcadia_Visuals_TextureFilter (*getMinificationFilter)(Arcadia_Thread*, Arcadia_Visuals_Texture*);
  Arcadia_Integer32Value (*getWidth)(Arcadia_Thread*, Arcadia_Visuals_Texture*);
  void (*upload)(Arcadia_Thread*, Arcadia_Visuals_Texture*, Arcadia_Visuals_BackendContext*);
};

struct Arcadia_Visuals_Texture {
  Arcadia_Object parent;
};

/* Get the address mode of this texture for the u axis. */
Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Texture_getAddressModeU
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  );

/* Get the address mode of this texture for the v axis. */
Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Texture_getAddressModeV
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  );

/* Get the height, in pixels, of this texture. */
Arcadia_Integer32Value
Arcadia_Visuals_Texture_getHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  );

/* Get the magnification filter of this texture. */
Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Texture_getMagnificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  );

/* Get the minification filter of this texture. */
Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Texture_getMinificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  );

/* Get the width, in pixels, of this texture. */
Arcadia_Integer32Value
Arcadia_Visuals_Texture_getWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  );

/**
 * @brief Update this texture for the specified backend context.
 * This function is effectively performing the following actions:
 * - First, if the texture backend is created in some old backend context and the specified backend context is null or different from the old backend context,
 *   destroy the texture backend of that texture in the old backend context.
 * - Second, if the specified backend context is not null,
 *   create the texture backend in the specified backend context.
 * - Third, if the texture backend is created and properties of the texture changed since the last call to this function,
 *   update the texture backend with the updated property values.
 * Unload uploads to other backend contexts.
 * @param thread A pointer to this thread.
 * @param self A pointer to this texture.
 * @param backendContext A pointer to the backend context or the null pointer.
 */
void
Arcadia_Visuals_Texture_upload
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self,
    Arcadia_Visuals_BackendContext* backendContext
  );

#endif // ARCADIA_VISUALS_TEXTURE_H_INCLUDED
