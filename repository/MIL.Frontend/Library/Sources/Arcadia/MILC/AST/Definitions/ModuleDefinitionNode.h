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

#if !defined(ARCADIA_MILC_AST_DEFINITIONS_MODULEDEFINITIONNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_DEFINITIONS_MODULEDEFINITIONNODE_H_INCLUDED

#include "Arcadia/MILC/AST/DefinitionNode.h"
#include "Arcadia/Collections/Include.h"
typedef struct Arcadia_MILC_AST_IdentifierNode Arcadia_MILC_AST_IdentifierNode;

/// @code
/// class Arcadia.MIL.ModuleDefinitionAst extends Arcadia.MILC.AST.DefinitionNode
/// @endcode
/// See https://michaelheilmann.com/specifications/mil/#module-definition for more information.
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.ModuleDefinitionNode", Arcadia_MILC_AST_ModuleDefinitionNode,
                          u8"Arcadia.MILC.AST.DefinitionNode");

struct Arcadia_MILC_AST_ModuleDefinitionNodeDispatch {
  Arcadia_MILC_AST_DefinitionNodeDispatch _parent;
};

struct Arcadia_MILC_AST_ModuleDefinitionNode {
  Arcadia_MILC_AST_DefinitionNode _parent;
  /// The name of the module.
  Arcadia_MILC_AST_IdentifierNode* moduleName;

  /// The body of the module.
  Arcadia_List* moduleBody;
};

/// @brief Create a MIL procedure definition AST node.
/// @param moduleName The name of the module.
/// @param moduleBody The module body.
/// @return A pointer to this MIL procedure definition AS node.
Arcadia_MILC_AST_ModuleDefinitionNode*
Arcadia_MILC_AST_ModuleDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_IdentifierNode* moduleName,
    Arcadia_List* moduleBody
  );

#endif // ARCADIA_MILC_AST_DEFINITIONS_MODULEDEFINITIONNODE_H_INCLUDED
