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

#if !defined(ARCADIA_VISUALS_SCENE_NODE_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_NODE_H_INCLUDED

#include "Arcadia/Math/Include.h"

typedef struct Arcadia_Visuals_BackendContext Arcadia_Visuals_BackendContext;

// The base of all scene nodes.
// A "resource" is owned by a "backend context". That is, the "backend context" holds a STRONG reference to its "resources".
// In addition, the "backend context" retains a GC lock unless its "resources" such that they are only gc'ed if the "backend context" drops this lock.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                          u8"Arcadia.Object")

struct Arcadia_Visuals_Scene_Node {
  Arcadia_Object _parent;

  void (*setBackendContext)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*, Arcadia_Visuals_BackendContext*);
  void (*render)(Arcadia_Thread*, Arcadia_Visuals_Scene_Node*);
};

// Change the backend context of this node.
void
Arcadia_Visuals_Scene_Node_setBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_Node* self,
    Arcadia_Visuals_BackendContext* backendContext
  );

// Render this node.
void
Arcadia_Visuals_Scene_Node_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_Node* self
  );

#endif // ARCADIA_VISUALS_SCENE_NODE_H_INCLUDED
