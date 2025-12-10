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

#if !defined(ARCADIA_DDL_NODES_NODETYPE_H_INCLUDED)
#define ARCADIA_DDL_NODES_NODETYPE_H_INCLUDED

#if !defined(ARCADIA_DDL_NODES_PRIVATE) || 1 != ARCADIA_DDL_NODES_PRIVATE
  #error("do not include directly, include `Arcadia/DDL/Nodes/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType("Arcadia.DDL.NodeType", Arcadia_DDL_NodeType);

enum Arcadia_DDL_NodeType {

#define Define(Name, Description) \
  Arcadia_DDL_NodeType_##Name,

  #include "Arcadia/DDL/Nodes/NodeType.i"

#undef Define

};

#endif // ARCADIA_DDL_NODES_NODETYPE_H_INCLUDED
