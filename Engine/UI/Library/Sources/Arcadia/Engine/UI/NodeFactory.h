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

#if !defined(ARCADIA_ENGINE_UI_NODES_CANVASNODE_H_INCLUDED)
#define ARCADIA_ENGINE_UI_NODES_CANVASNODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_UI_PRIVATE) || 1 != ARCADIA_ENGINE_UI_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/UI/Include.h` instead")
#endif
#include "Arcadia/Audials/Include.h"
#include "Arcadia/Visuals/Include.h"

// A "UI canvas".
// Defining elements:
// Postion (left, top) and size (width, height) within canvas coordinates.
// NOTE: canvas coordinates != UI canvas coordinates
Arcadia_declareObjectType(u8"Arcadia.Engine.UI.CanvasNode", Arcadia_Engine_UI_CanvasNode,
                          u8"Arcadia.Engine.Node")

struct Arcadia_Engine_UI_CanvasNodeDispatch {
  Arcadia_Engine_NodeDispatch _parent;
};

struct Arcadia_Engine_UI_CanvasNode {
  Arcadia_Engine_Node _parent;
};

Arcadia_Engine_UI_CanvasNode*
Arcadia_Engine_UI_CanvasNode_create
  (
  );

#endif // ARCADIA_ENGINE_UI_NODES_CANVASNODE_H_INCLUDED
