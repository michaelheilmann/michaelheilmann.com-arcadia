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

#if !defined(ARCADIA_ENGINE_VISUALS_NODE_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_NODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Engine/Node.h"
#include "Arcadia/Math/Include.h"
typedef struct Arcadia_Engine_Visuals_EnterPassNode Arcadia_Engine_Visuals_EnterPassNode;
typedef struct Arcadia_Engine_Visuals_NodeFactory Arcadia_Engine_Visuals_NodeFactory;
typedef struct Arcadia_Visuals_BackendContext Arcadia_Visuals_BackendContext; // FIXME

// The base of all visuals nodes.
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.Node", Arcadia_Engine_Visuals_Node,
                          u8"Arcadia.Engine.Node")

struct Arcadia_Engine_Visuals_NodeDispatch {
  Arcadia_Engine_NodeDispatch parent;
  void (*render)(Arcadia_Thread*, Arcadia_Engine_Visuals_Node*, Arcadia_Engine_Visuals_EnterPassNode*);
};

struct Arcadia_Engine_Visuals_Node {
  Arcadia_Engine_Node _parent;
};

// Render this node.
void
Arcadia_Engine_Visuals_Node_render
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Node* self,
    Arcadia_Engine_Visuals_EnterPassNode* enterPassNode
  );

#endif // ARCADIA_ENGINE_VISUALS_NODE_H_INCLUDED
