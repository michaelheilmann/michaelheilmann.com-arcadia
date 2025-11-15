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

#if !defined(ARCADIA_DDL_TREE_STRINGNODE_H_INCLUDED)
#define ARCADIA_DDL_TREE_STRINGNODE_H_INCLUDED

#if !defined(ARCADIA_DDL_PRIVATE) || 1 != ARCADIA_DDL_PRIVATE
  #error("do not include directly, include `Arcadia/DDL/Include.h` instead")
#endif

#include "Arcadia/DDL/Implementation/Node.h"

Arcadia_declareObjectType(u8"Arcadia.DDL.StringNode", Arcadia_DDL_StringNode,
                          u8"Arcadia.DDL.Node");

struct Arcadia_DDL_StringNode {
  Arcadia_DDL_Node parent;
  Arcadia_String* value;
};

Arcadia_DDL_StringNode*
Arcadia_DDL_StringNode_createString
  (
    Arcadia_Thread* thread,
    Arcadia_String* stringValue
  );

#endif // ARCADIA_DDL_TREE_STRINGNODE_H_INCLUDED
