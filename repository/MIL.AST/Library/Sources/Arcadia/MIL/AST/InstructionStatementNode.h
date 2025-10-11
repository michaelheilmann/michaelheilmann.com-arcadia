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

#if !defined(ARCADIA_MIL_AST_INSTRUCTIONSTATEMENTNODE2_H_INCLUDED)
#define ARCADIA_MIL_AST_INSTRUCTIONSTATEMENTNODE2_H_INCLUDED

#include "Arcadia/MIL/AST/StatementNode.h"

/// @code
/// class Arcadia.MIL.AST.DefinitionStatementNode2 extends Arcadia.MIL.AST.StatementNode {
///   ...
/// }
/// @endcode
/// represents
/// @code
/// instructionStatement : instruction
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.InstructionStatementNode2", Arcadia_MIL_AST_InstructionStatementNode2,
                          u8"Arcadia.MIL.AST.StatementNode");

struct Arcadia_MIL_AST_InstructionStatementNode2 {
  Arcadia_MIL_AST_StatementNode _parent;
};

#endif // ARCADIA_MIL_AST_INSTRUCTIONSTATEMENTNODE2_H_INCLUDED
