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

#if !defined(ARCADIA_ENGINE_VISUALS_NODES_TEXTURENODE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_NODES_TEXTURENODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif

#include "Arcadia/Engine/Visuals/Node.h"
#include "Arcadia/ADL/Include.h"
#include "Arcadia/Engine/Visuals/Nodes/PixelBufferNode.h"
#include "Arcadia/Engine/Visuals/TextureAddressMode.h"
#include "Arcadia/Engine/Visuals/TextureFilter.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.TextureNode", Arcadia_Engine_Visuals_TextureNode,
                          u8"Arcadia.Engine.Visuals.Node")

struct Arcadia_Engine_Visuals_TextureNodeDispatch {
  Arcadia_Engine_Visuals_NodeDispatch parent;

  Arcadia_Engine_Visuals_TextureAddressMode (*getAddressModeU)(Arcadia_Thread*, Arcadia_Engine_Visuals_TextureNode*);
  Arcadia_Engine_Visuals_TextureAddressMode (*getAddressModeV)(Arcadia_Thread*, Arcadia_Engine_Visuals_TextureNode*);
  Arcadia_Integer32Value (*getHeight)(Arcadia_Thread*, Arcadia_Engine_Visuals_TextureNode*);
  Arcadia_Engine_Visuals_TextureFilter (*getMagnificationFilter)(Arcadia_Thread*, Arcadia_Engine_Visuals_TextureNode*);
  Arcadia_Engine_Visuals_TextureFilter (*getMinificationFilter)(Arcadia_Thread*, Arcadia_Engine_Visuals_TextureNode*);
  Arcadia_Integer32Value (*getWidth)(Arcadia_Thread*, Arcadia_Engine_Visuals_TextureNode*);
};

struct Arcadia_Engine_Visuals_TextureNode {
  Arcadia_Engine_Visuals_Node parent;

  Arcadia_ADL_TextureDefinition* source;

  // The pixel buffer node.
  Arcadia_Engine_Visuals_PixelBufferNode* pixelBuffer;

  // The address mode of this texture along the u-axis.
  // @default Arcadia_Visuals_TextureAddressMode_Repeat.
  Arcadia_Engine_Visuals_TextureAddressMode addressModeU;

  // The address mode of this texture along the v-axis.
  // @default Arcadia_Engine_Visuals_TextureAddressMode_Repeat.
  Arcadia_Engine_Visuals_TextureAddressMode addressModeV;

  // @brief The height, in pixels of the frame buffer.
  // @default 240.
  Arcadia_Integer32Value height;

  // The texture magnification filter.
  // @default Arcadia_Engine_Visuals_TextureFilter_Linear
  Arcadia_Engine_Visuals_TextureFilter magnificationFilter;

  // The texture minification filter.
  // @default Arcadia_Engine_Visuals_TextureFilter_Linear
  Arcadia_Engine_Visuals_TextureFilter minificationFilter;

  // @brief The width, in pixels, of the frame buffer.
  // @default 320.
  Arcadia_Integer32Value width;

  // Bitmask indicating what aspects of the texture are dirty.
  Arcadia_Natural8Value dirtyBits;
};

/* Get the address mode of this texture for the u axis. */
Arcadia_Engine_Visuals_TextureAddressMode
Arcadia_Engine_Visuals_TextureNode_getAddressModeU
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_TextureNode* self
  );

/* Get the address mode of this texture for the v axis. */
Arcadia_Engine_Visuals_TextureAddressMode
Arcadia_Engine_Visuals_TextureNode_getAddressModeV
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_TextureNode* self
  );

/* Get the height, in pixels, of this texture. */
Arcadia_Integer32Value
Arcadia_Engine_Visuals_TextureNode_getHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_TextureNode* self
  );

/* Get the magnification filter of this texture. */
Arcadia_Engine_Visuals_TextureFilter
Arcadia_Engine_Visuals_TextureNode_getMagnificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_TextureNode* self
  );

/* Get the minification filter of this texture. */
Arcadia_Engine_Visuals_TextureFilter
Arcadia_Engine_Visuals_TextureNode_getMinificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_TextureNode* self
  );

/* Get the width, in pixels, of this texture. */
Arcadia_Integer32Value
Arcadia_Engine_Visuals_TextureNode_getWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_TextureNode* self
  );

#endif // ARCADIA_ENGINE_VISUALS_NODES_TEXTURENODE_H_INCLUDED
