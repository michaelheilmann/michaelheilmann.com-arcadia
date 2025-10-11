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

#if !defined(ARCADIA_MIL_AST_DEFINITIONS_PROCEDUREDEFINITIONNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_DEFINITIONS_PROCEDUREDEFINITIONNODE_H_INCLUDED

#include "Arcadia/MIL/AST/DefinitionNode.h"

/// @code
/// class Arcadia.MIL.ProcedureDefinitionAst extends Arcadia.MIL.AST.DefinitionNode
/// @endcode
/// See https://michaelheilmann.com/specifications/mil/#procedure-definition for more information.
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.ProcedureDefinitionNode", Arcadia_MIL_AST_ProcedureDefinitionNode,
                          u8"Arcadia.MIL.AST.DefinitionNode");

struct Arcadia_MIL_AST_ProcedureDefinitionNode {
  Arcadia_MIL_AST_DefinitionNode _parent;
  Arcadia_BooleanValue entry;
  Arcadia_String* nativeName;
  Arcadia_String* procedureName;
  Arcadia_List* procedureParameters;
  Arcadia_List* procedureBody;
};

/// @brief Create a MIL procedure definition AST node.
/// @return A pointer to this MIL procedure definition AS node.
Arcadia_MIL_AST_ProcedureDefinitionNode*
Arcadia_MIL_AST_ProcedureDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue entry,
    Arcadia_String* nativeName,
    Arcadia_String* procedureName,
    Arcadia_List* procedureParameters,
    Arcadia_List* procedureBody
  );

#endif // ARCADIA_MIL_AST_DEFINITIONS_PROCEDUREDEFINITIONNODE_H_INCLUDED
