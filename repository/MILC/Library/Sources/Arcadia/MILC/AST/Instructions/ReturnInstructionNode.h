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

#if !defined(ARCADIA_MILC_AST_RETURNINSTRUCTIONNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_RETURNINSTRUCTIONNODE_H_INCLUDED

#include "Arcadia/MILC/AST/InstructionNode.h"
typedef struct Arcadia_MILC_AST_OperandNode Arcadia_MILC_AST_OperandNode;

/// @code
/// class Arcadia.MILC.AST.ReturnInstructionNode extends Arcadia.MILC.AST.InstructionNode
/// @endcode
/// Represents
/// @code
/// 'return' (BooleanLiteral | NumberLiteral | StringLiteral | VariableName)
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.ReturnInstructionNode", Arcadia_MILC_AST_ReturnInstructionNode,
                          u8"Arcadia.MILC.AST.InstructionNode");

struct Arcadia_MILC_AST_ReturnInstructionNodeDispatch {
  Arcadia_MILC_AST_InstructionNodeDispatch parent;
};

struct Arcadia_MILC_AST_ReturnInstructionNode {
  Arcadia_MILC_AST_InstructionNode parent;
  Arcadia_MILC_AST_OperandNode* operand;
};

/// @brief Create a MIL return instruction AST node.
/// @return A pointer to this MIL return instruction AST node.
Arcadia_MILC_AST_ReturnInstructionNode*
Arcadia_MILC_AST_ReturnInstructionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_OperandNode* operand
  );

#endif // ARCADIA_MILC_AST_RETURNINSTRUCTIONNODE_H_INCLUDED
