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

#if !defined(ARCADIA_MILC_AST_LABELDEFINITIONSTATEMENTNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_LABELDEFINITIONSTATEMENTNODE_H_INCLUDED

#include "Arcadia/MILC/AST/DefinitionStatementNode.h"

/// @code
/// class Arcadia.MILC.AST.LabelDefintionStatementNode extends Arcadia.MILC.AST.DefinitionStatement {
///   ...
/// }
/// @endcode
/// Represents
/// @code
/// name ':'
/// @endcode
///
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.LabelDefinitionStatementNode", Arcadia_MILC_AST_LabelDefinitionStatementNode,
                          u8"Arcadia.MILC.AST.DefinitionStatementNode");

struct Arcadia_MILC_AST_LabelDefinitionStatementNodeDispatch {
  Arcadia_MILC_AST_DefinitionStatementNodeDispatch parent;
};

struct Arcadia_MILC_AST_LabelDefinitionStatementNode {
  Arcadia_MILC_AST_DefinitionStatementNode parent;
  Arcadia_String* labelName;
};

/// @brief Create a MIL label instruction AST node.
/// @return A pointer to this MIL label instruction AST node.
Arcadia_MILC_AST_LabelDefinitionStatementNode*
Arcadia_MILC_AST_LabelDefinitionStatementNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* labelName
  );

#endif // ARCADIA_MILC_AST_LABELDEFINITIONSTATEMENTNODE_H_INCLUDED
