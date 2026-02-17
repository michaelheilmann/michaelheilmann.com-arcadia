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

#if !defined(ARCADIA_ENGINE_AUDIALS_NODE_H_INCLUDED)
#define ARCADIA_ENGINE_AUDIALS_NODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Engine/Node.h"
#include "Arcadia/Math/Include.h"
typedef struct Arcadia_Engine_Audials_BackendContext Arcadia_Engine_Audials_BackendContext;

// The base of all audials nodes.
// A "resource" is owned by a "backend context".
// That is, the "backend context" holds a STRONG reference to its "resources".
// In addition, the "backend context" retains a GC lock unless its "resources" such that they are only gc'ed if the "backend context" drops this lock.
Arcadia_declareObjectType(u8"Arcadia.Engine.Audials.Node", Arcadia_Engine_Audials_Node,
                          u8"Arcadia.Engine.Node");

struct Arcadia_Engine_Audials_NodeDispatch {
  Arcadia_Engine_NodeDispatch _parent;
  void (*render)(Arcadia_Thread*, Arcadia_Engine_Audials_Node*);
};

struct Arcadia_Engine_Audials_Node {
  Arcadia_Engine_Node _parent;
};

// Render this node.
void
Arcadia_Engine_Audials_Node_render
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Node* self
  );

#endif // ARCADIA_ENGINE_AUDIALS_NODE_H_INCLUDED
