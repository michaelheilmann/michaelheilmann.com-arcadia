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

#if !defined(ARCADIA_MIL_AST_JUMPINSTRUCTIONNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_JUMPINSTRUCTIONNODE_H_INCLUDED

#include "Arcadia/MIL/AST/InstructionNode.h"

/// @code
/// class Arcadia.MIL.AST.JumpInstructionNode extends Arcadia.MIL.AST.InstructionNode
/// @endcode
/// Represents
/// @code
/// jumpStatement : 'jump' operand labelName
/// labelName : lexical.string | lexical.name
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.JumpInstructionNode", Arcadia_MIL_AST_JumpInstructionNode,
                          u8"Arcadia.MIL.AST.InstructionNode");

struct Arcadia_MIL_AST_JumpInstructionNode {
  Arcadia_MIL_AST_InstructionNode parent;
  /// The name of the label.
  Arcadia_String* labelName;
};

/// @brief Create a MIL jump instruction AST node.
/// @return A pointer to this MIL jump instruction AST node.
Arcadia_MIL_AST_JumpInstructionNode*
Arcadia_MIL_AST_JumpInstructionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* labelName
  );

#endif // ARCADIA_MIL_AST_JUMPINSTRUCTIONNODE_H_INCLUDED
