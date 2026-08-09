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

#if !defined(ARCADIA_MILC_AST_VARIABLEDEFINITIONNODE_H_INCLUDED)
#define ARCADIA_MILC_AST_VARIABLEDEFINITIONNODE_H_INCLUDED

#include "Arcadia/MILC/AST/DefinitionNode.h"
typedef struct Arcadia_MILC_AST_IdentifierNode Arcadia_MILC_AST_IdentifierNode;

/// The definition of a parameter variable, local variable, or member variable.
Arcadia_declareObjectType(u8"Arcadia.MILC.AST.FieldDefinitionNode", Arcadia_MILC_AST_FieldDefinitionNode,
                          u8"Arcadia.MILC.AST.DefinitionNode");

struct Arcadia_MILC_AST_FieldDefinitionNodeDispatch {
  Arcadia_MILC_AST_DefinitionNodeDispatch _parent;
};

struct Arcadia_MILC_AST_FieldDefinitionNode {
  Arcadia_MILC_AST_DefinitionNode _parent;
  Arcadia_String* name;
  Arcadia_MILC_AST_IdentifierNode* type;
};

Arcadia_MILC_AST_FieldDefinitionNode*
Arcadia_MILC_AST_FieldDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_MILC_AST_IdentifierNode* type
  );

#endif // ARCADIA_MILC_AST_VARIABLEDEFINITIONNODE_H_INCLUDED
