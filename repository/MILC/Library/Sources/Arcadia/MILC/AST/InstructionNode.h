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

#if !defined(ARCADIA_MILC_AST_INSTRUCTIONNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_INSTRUCTIONNODE_H_INCLUDED

#include "Arcadia/MILC/AST/InstructionStatementNode.h"

/// @code
/// class Arcadia.MILC.AST.InstructionMode extends Arcadia.MILC.AST.InstructionStatementNode
/// @endcode
/// represents
/// @code
/// instruction : binaryInstruction
///             | unaryInstruction
///             | invokeInstruction
///             | jumpInstruction
///             | raiseInstruction
///             | returnInstruction
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.InstructionNode", Arcadia_MILC_AST_InstructionNode,
                          u8"Arcadia.MILC.AST.InstructionStatementNode");

struct Arcadia_MILC_AST_InstructionNodeDispatch {
  Arcadia_MILC_AST_InstructionStatementNodeDispatch _parent;
};

struct Arcadia_MILC_AST_InstructionNode {
  Arcadia_MILC_AST_InstructionStatementNode _parent;
};

#endif // ARCADIA_MILC_AST_INSTRUCTIONNODE_H_INCLUDED
