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
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE

#if !defined(ARCADIA_VPL_TREE_CONSTANTRECORD_H_INCLUDED)
#define ARCADIA_VPL_TREE_CONSTANTRECORD_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Tree/Node.h"

// <constant record> : 'constant' 'record' <constant record name> '{' <constant record body> '}'
// <constant record body> : <constant record field>
// <constant record name> : <name>
Arcadia_declareObjectType(u8"Arcadia.VPL.Tree.ConstantRecord", Arcadia_VPL_Tree_ConstantRecord,
                          u8"Arcadia.VPL.Tree.Node");

struct Arcadia_VPL_Tree_ConstantRecordDispatch {
  Arcadia_VPL_Tree_NodeDispatch _parent;
};

struct Arcadia_VPL_Tree_ConstantRecord {
  Arcadia_VPL_Tree_Node _parent;
  Arcadia_String* name;
  Arcadia_List* fields;
};

Arcadia_VPL_Tree_ConstantRecord*
Arcadia_VPL_Tree_ConstantRecord_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

#endif // ARCADIA_VPL_TREE_CONSTANTRECORD_H_INCLUDED
