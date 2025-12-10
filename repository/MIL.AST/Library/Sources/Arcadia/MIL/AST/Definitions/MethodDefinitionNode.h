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

#if !defined(ARCADIA_MIL_AST_DEFINITIONS_METHODDEFINITIONNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_DEFINITIONS_METHODDEFINITIONNODE_H_INCLUDED

#include "Arcadia/MIL/AST/DefinitionNode.h"

/// @code
/// class Arcadia.MIL.AST.MethodDefinitionNode extends Arcadia.MIL.AST.DefinitionNode
/// @endcode
/// See https://michaelheilmann.com/specifications/mil/#method-definition for more information.
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.MethodDefinitionNode", Arcadia_MIL_MethodDefinitionNode,
                          u8"Arcadia.MIL.AST.DefinitionNode");

struct Arcadia_MIL_MethodDefinitionNodeDispatch {
  Arcadia_MIL_AST_DefinitionNodeDispatch _parent;
};

struct Arcadia_MIL_MethodDefinitionNode {
  Arcadia_MIL_AST_DefinitionNode _parent;
  Arcadia_String* nativeName;
  Arcadia_String* methodName;
  Arcadia_List* methodParameters;
  Arcadia_List* methodBody;
};

Arcadia_MIL_MethodDefinitionNode*
Arcadia_MIL_MethodDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* nativeName,
    Arcadia_String* methodName,
    Arcadia_List* methodParameters,
    Arcadia_List* methodBody
  );

#endif // ARCADIA_MIL_AST_DEFINITIONS_METHODDEFINITIONNODE_H_INCLUDED
