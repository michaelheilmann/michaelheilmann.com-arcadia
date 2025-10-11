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

#if !defined(ARCADIA_MIL_AST_ENUMERATIONDEFINITIONNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_ENUMERATIONDEFINITIONNODE_H_INCLUDED

#include "Arcadia/MIL/AST/DefinitionNode.h"

/// @code
/// class Arcadia.MIL.AST.EnumerationDefinitionNode extends Arcadia.MIL.AST.DefinitionNode {
///   construct(enumerationName:Arcadia.String, enumerationBody:Arcadia.List)
/// }
/// @endcode
/// Represents
/// @code
/// enumerationDefinition : 'enumeration' name enumerationBody
/// enumerationBody : '{' enumerationMemberDefinition* '}'
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.EnumerationDefinitionNode", Arcadia_MIL_AST_EnumerationDefinitionNode,
                          u8"Arcadia.MIL.AST.DefinitionNode");

struct Arcadia_MIL_AST_EnumerationDefinitionNode {
  Arcadia_MIL_AST_DefinitionNode _parent;
  Arcadia_String* enumerationName;
  Arcadia_List* enumerationBody;
};

/// @brief Create a MIL enumeration definition AST node.
/// @return A pointer to this MIL enumeration definition AST node.
Arcadia_MIL_AST_EnumerationDefinitionNode*
Arcadia_MIL_AST_EnumerationDefinitionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* enumerationName,
    Arcadia_List* enumerationBody
  );

#endif // ARCADIA_MIL_AST_ENUMERATIONDEFINITIONNODE_H_INCLUDED
