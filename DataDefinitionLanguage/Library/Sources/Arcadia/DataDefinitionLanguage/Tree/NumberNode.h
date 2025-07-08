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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_TREE_NUMBERNODE_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_TREE_NUMBERNODE_H_INCLUDED

#include "Arcadia/DataDefinitionLanguage/Tree/Node.h"
#include "Arcadia/Ring2/Include.h"

Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.Tree.NumberNode", Arcadia_DataDefinitionLanguage_Tree_NumberNode,
                          u8"Arcadia.DataDefinitionLanguage.Tree.Node");

struct Arcadia_DataDefinitionLanguage_Tree_NumberNode {
  Arcadia_DataDefinitionLanguage_Tree_Node parent;
  Arcadia_ImmutableUtf8String* value;
};

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createReal32
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value real32Value
  );

Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value real64Value
  );

// A writer which consumes a number node always checks if the string is a valid number literal string.
// If a reader produces a number node, its string is valid number literal string.
Arcadia_DataDefinitionLanguage_Tree_NumberNode*
Arcadia_DataDefinitionLanguage_Tree_NumberNode_createString
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* stringValue
  );

#endif // ARCADIA_DATADEFINITIONLANGUAGE_TREE_NUMBERNODE_H_INCLUDED
