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

#if !defined(ARCADIA_MILC_AST_DEFINITIONS_CLASSDEFINITIONNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_DEFINITIONS_CLASSDEFINITIONNODE_H_INCLUDED

#include "Arcadia/MILC/AST/DefinitionNode.h"
#include "Arcadia/Collections/Include.h"
typedef struct Arcadia_MILC_AST_IdentifierNode Arcadia_MILC_AST_IdentifierNode;

/// @code
/// class Arcadia.MILC.AST.ClassDefinitionNode extends Arcadia.MILC.AST.DefinitionNode {
///   constructor(className:Arcadia.String, extendedClassName:Arcadia.String, classBody:Arcadia.List)
/// }
/// @endcode
/// See https://mmichaelheilmann.com/specifications/mil/#class-definition for more information.
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.ClassDefinitionNode", Arcadia_MILC_AST_ClassDefinitionNode,
                          u8"Arcadia.MILC.AST.DefinitionNode");

struct Arcadia_MILC_AST_ClassDefinitionNodeDispatch {
  Arcadia_MILC_AST_DefinitionNodeDispatch _parent;
};

struct Arcadia_MILC_AST_ClassDefinitionNode {
  Arcadia_MILC_AST_DefinitionNode _parent;
  Arcadia_MILC_AST_IdentifierNode* className;
  Arcadia_MILC_AST_IdentifierNode* extendedClassName;
  Arcadia_List* classBody;
};

/// @brief Create a MIL class definition AST node.
/// @return A pointer to this MIL class definition AST node.
Arcadia_MILC_AST_ClassDefinitionNode*
Arcadia_MILC_AST_ClassDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_IdentifierNode* className,
    Arcadia_MILC_AST_IdentifierNode* extendedClassName,
    Arcadia_List* classBody
  );

#endif // ARCADIA_MILC_AST_DEFINITIONS_CLASSDEFINITIONNODE_H_INCLUDED
