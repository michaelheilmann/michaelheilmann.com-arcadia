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

#if !defined(ARCADIA_MILC_AST_BINARYINSTRUCTIONNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_BINARYINSTRUCTIONNODE_H_INCLUDED

#include "Arcadia/MILC/AST/InstructionNode.h"
#include "Arcadia/MILC/AST/Instructions/BinaryInstructionKind.h"
typedef struct Arcadia_MILC_AST_OperandNode Arcadia_MILC_AST_OperandNode;

/// @code
/// class Arcadia.MILC.AST.BinaryInstructionNode extends Arcadia.MILC.AST.InstructionNode
/// @endcode
/// Represents instructions with two operands and a result.
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.BinaryInstructionNode", Arcadia_MILC_AST_BinaryInstructionNode,
                          u8"Arcadia.MILC.AST.InstructionNode");

struct Arcadia_MILC_AST_BinaryInstructionNodeDispatch {
  Arcadia_MILC_AST_InstructionNodeDispatch parent;
};

struct Arcadia_MILC_AST_BinaryInstructionNode {
  Arcadia_MILC_AST_InstructionNode parent;
  Arcadia_MILC_AST_BinaryInstructionKind kind;
  Arcadia_MILC_AST_OperandNode* target;
  Arcadia_MILC_AST_OperandNode* operand1;
  Arcadia_MILC_AST_OperandNode* operand2;
};

Arcadia_MILC_AST_BinaryInstructionNode*
Arcadia_MILC_AST_BinaryInstructionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_BinaryInstructionKind kind,
    Arcadia_MILC_AST_OperandNode* target,
    Arcadia_MILC_AST_OperandNode* operand1,
    Arcadia_MILC_AST_OperandNode* operand2
  );

#endif // ARCADIA_MILC_AST_BINARYINSTRUCTIONNODE_H_INCLUDED
