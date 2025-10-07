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

#if !defined(ARCADIA_MIL_AST_JUMPSTATEMENTNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_JUMPSTATEMENTNODE_H_INCLUDED

#include "Arcadia/MIL/AST/StatementNode.h"
typedef struct Arcadia_MIL_AST_LabelStatementNode Arcadia_MIL_AST_LabelStatementNode;

/// @code
/// class Arcadia.MIL.AST.JumpStatementNode extends Arcadia.MIL.AST.StatementNode
/// @endcode
/// Represents
/// @code
/// jumpStatement : 'jump' operand labelName
/// labelName : lexical.string | lexical.name
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.JumpStatementNode", Arcadia_MIL_AST_JumpStatementNode,
                          u8"Arcadia.MIL.AST.StatementNode");

struct Arcadia_MIL_AST_JumpStatementNode {
  Arcadia_MIL_AST_StatementNode parent;
  /// The name of the label.
  Arcadia_String* labelName;
  /// The AST of the label if resolution of the label name was successful.
  /// NULL otherwise.
  Arcadia_MIL_AST_LabelStatementNode* labelNode;
};

/// @brief Create a MIL jump statement AST node.
/// @return A pointer to this MIL jump statement AST node.
Arcadia_MIL_AST_JumpStatementNode*
Arcadia_MIL_AST_JumpStatementNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* labelName
  );

#endif // ARCADIA_MIL_AST_JUMPSTATEMENTNODE_H_INCLUDED
