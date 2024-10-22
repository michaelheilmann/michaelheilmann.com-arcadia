// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-14

#if !defined(CIL_STRINGTABLE_H_INCLUDED)
#define CIL_STRINGTABLE_H_INCLUDED

#include "R.h"

Rex_declareObjectType("Cil.StringTable", Cil_StringTable, "R.Object");

// Unmanaged.
typedef struct Cil_StringTable_Node Cil_StringTable_Node;
struct Cil_StringTable_Node {
  Cil_StringTable_Node* next;
  R_String* string;
};

struct Cil_StringTable {
  R_Object _parent;
  Cil_StringTable_Node** buckets;
  R_SizeValue size;
  R_SizeValue capacity;
};

Cil_StringTable*
Cil_StringTable_create
  (
  );

R_String*
Cil_StringTable_getOrCreateString
  (
    Cil_StringTable* self,
    R_StringBuffer* stringBuffer
  );

#endif // CIL_STRINGTABLE_H_INCLUDED
