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

#if !defined(ARCADIA_MILC_AST_VARIABLEDEFINITIONSTATEMENTNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_VARIABLEDEFINITIONSTATEMENTNODE_H_INCLUDED

#include "Arcadia/MILC/AST/DefinitionStatementNode.h"

/// @code
/// class Arcadia.MILC.AST.VariableDefinitionStatement extends Arcadia.MILC.AST.DefinitionStatement
/// @endcode
/// Represents
/// @code
/// variableDefinitionStatement : 'variable' name
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.VariableDefinitionStatementNode", Arcadia_MILC_AST_VariableDefinitionStatementNode,
                          u8"Arcadia.MILC.AST.DefinitionStatementNode");

struct Arcadia_MILC_AST_VariableDefinitionStatementNodeDispatch {
  Arcadia_MILC_AST_DefinitionStatementNodeDispatch parent;
};

struct Arcadia_MILC_AST_VariableDefinitionStatementNode {
  Arcadia_MILC_AST_DefinitionStatementNode parent;
  Arcadia_String* variableName;
};

/// @brief Create a MIL variable definition statement AST node.
/// @return A pointer to this MIL variable definition statement AST node.
Arcadia_MILC_AST_VariableDefinitionStatementNode*
Arcadia_MILC_AST_VariableDefinitionStatementNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* variableName
  );

#endif // ARCADIA_MILC_AST_VARIABLEDEFINITIONSTATEMENTNODE_H_INCLUDED
