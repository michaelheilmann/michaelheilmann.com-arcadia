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

#if !defined(ARCADIA_MIL_AST_DEFINITIONS_CLASSDEFINITIONNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_DEFINITIONS_CLASSDEFINITIONNODE_H_INCLUDED

#include "Arcadia/MIL/AST/DefinitionNode.h"

/// @code
/// class Arcadia.MIL.AST.ClassDefinitionNode extends Arcadia.MIL.AST.DefinitionNode {
///   constructor(className:Arcadia.String, extendedClassName:Arcadia.String, classBody:Arcadia.List)
/// }
/// @endcode
/// See https://mmichaelheilmann.com/specifications/mil/#class-definition for more information.
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.ClassDefinitionNode", Arcadia_MIL_AST_ClassDefinitionNode,
                          u8"Arcadia.MIL.AST.DefinitionNode");

struct Arcadia_MIL_AST_ClassDefinitionNodeDispatch {
  Arcadia_MIL_AST_NodeDispatch _parent;
};

struct Arcadia_MIL_AST_ClassDefinitionNode {
  Arcadia_MIL_AST_Node _parent;
  Arcadia_String* className;
  Arcadia_String* extendedClassName;
  Arcadia_List* classBody;
};

/// @brief Create a MIL class definition AST node.
/// @return A pointer to this MIL class definition AST node.
Arcadia_MIL_AST_ClassDefinitionNode*
Arcadia_MIL_AST_ClassDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* className,
    Arcadia_String* extendedClassName,
    Arcadia_List* classBody
  );

#endif // ARCADIA_MIL_AST_DEFINITIONS_CLASSDEFINITIONNODE_H_INCLUDED
