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

#if !defined(ARCADIA_ENGINE_NODE_H_INCLUDED)
#define ARCADIA_ENGINE_NODE_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Engine/Audials/BackendContext.h"
#include "Arcadia/Engine/Visuals/BackendContext.h"

//typedef struct Arcadia_Engine_Audials_BackendContext Arcadia_Engine_Audials_BackendContext;
//typedef struct Arcadia_Engine_Visuals_BackendContext Arcadia_Engine_Visuals_BackendContext;

/// The base of all nodes.
/// 
/// The bases of implementations specific to audials and visuals can be found in Arcadia.Audials and Arcadia.Visuals, respectively.
///
/// Nodes hold references to "resources". "resources" are the representation of nodes in terms of the audials and visuals backends.
/// "resources" are managed by nodes using explicit reference counting.
/// 
/// A "resource" is owned by a "backend context".
/// That is, the "backend context" holds a STRONG reference to its "resources".
/// In addition, the "backend context" retains a GC lock unless its "resources" such that they are only gc'ed if the "backend context" drops this lock.
Arcadia_declareObjectType(u8"Arcadia.Engine.Node", Arcadia_Engine_Node,
                          Arcadia_Object);

struct Arcadia_Engine_NodeDispatch {
  Arcadia_ObjectDispatch _parent;
  void (*setAudialsBackendContext)(Arcadia_Thread*, Arcadia_Engine_Node*, Arcadia_Engine_Audials_BackendContext*);
  void (*setVisualsBackendContext)(Arcadia_Thread*, Arcadia_Engine_Node*, Arcadia_Engine_Visuals_BackendContext*);
};

struct Arcadia_Engine_Node {
  Arcadia_Object _parent;
};

/// @brief Set the audials backend context for this node.
/// @param thread A pointer to this thread.
/// @param self A pointer to this node.
/// @param A pointer to the audials backend context or the null pointer.
void
Arcadia_Engine_Node_setAudialsBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self,
    Arcadia_Engine_Audials_BackendContext* backendContext
  );

/// @brief Set the visuals backend context for this node.
/// @param thread A pointer to this thread.
/// @param self A pointer to this node.
/// @param A pointer to the visuals backend context or the null pointer.
void
Arcadia_Engine_Node_setVisualsBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self,
    Arcadia_Engine_Visuals_BackendContext* backendContext
  );

#endif // ARCADIA_ENGINE_NODE_H_INCLUDED
