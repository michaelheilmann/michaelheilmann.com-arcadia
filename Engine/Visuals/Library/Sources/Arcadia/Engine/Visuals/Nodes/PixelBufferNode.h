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

#if !defined(ARCADIA_ENGINE_VISUALS_NODES_PIXELBUFFERNODE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_NODES_PIXELBUFFERNODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif

#include "Arcadia/Engine/Visuals/Node.h"
#include "Arcadia/ADL/Include.h"
#include "Arcadia/Imaging/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.PixelBufferNode", Arcadia_Engine_Visuals_PixelBufferNode,
                          u8"Arcadia.Engine.Visuals.Node")

struct Arcadia_Engine_Visuals_PixelBufferNodeDispatch {
  Arcadia_Engine_Visuals_NodeDispatch parent;
};

struct Arcadia_Engine_Visuals_PixelBufferNode {
  Arcadia_Engine_Visuals_Node parent;
  // The pixel buffer definition.
  Arcadia_ADL_PixelBufferDefinition* source;
  // The pixel buffer.
  Arcadia_Imaging_PixelBuffer* pixelBuffer;
};

#endif // ARCADIA_ENGINE_VISUALS_NODES_PIXELBUFFERNODE_H_INCLUDED
