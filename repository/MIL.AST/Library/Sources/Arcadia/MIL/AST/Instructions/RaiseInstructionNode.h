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

#if !defined(ARCADIA_MIL_AST_RAISEINSTRUCTIONNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_RAISEINSTRUCTIONNODE_H_INCLUDED

#include "Arcadia/MIL/AST/InstructionNode.h"
typedef struct Arcadia_MIL_AST_OperandNode Arcadia_MIL_AST_OperandNode;

/// @code
/// class Arcadia.MIL.AST.RaiseInstructionNode extends Arcadia.MIL.AST.InstructionNode
/// @endcode
/// Represents
/// @code
/// 'raise'
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.RaiseInstructionNode", Arcadia_MIL_AST_RaiseInstructionNode,
                          u8"Arcadia.MIL.AST.InstructionNode");

struct Arcadia_MIL_AST_RaiseInstructionNodeDispatch {
  Arcadia_MIL_AST_InstructionNodeDispatch parent;
};

struct Arcadia_MIL_AST_RaiseInstructionNode {
  Arcadia_MIL_AST_InstructionNode parent;
  Arcadia_MIL_AST_OperandNode* operand;
};

/// @brief Create a MIL raise ínstruction AST node.
/// @return A pointer to this MIL raise instruction AST node.
Arcadia_MIL_AST_RaiseInstructionNode*
Arcadia_MIL_AST_RaiseInstructionNode_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_MIL_AST_RAISEINSTRUCTIONNODE_H_INCLUDED
