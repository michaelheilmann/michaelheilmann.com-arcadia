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

#if !defined(R_MIL_STRINGTABLE_H_INCLUDED)
#define R_MIL_STRINGTABLE_H_INCLUDED

#include "R.h"

Rex_declareObjectType("R.Mil.StringTable", R_Mil_StringTable, "R.Object");

// Unmanaged.
typedef struct R_Mil_StringTable_Node R_Mil_StringTable_Node;
struct R_Mil_StringTable_Node {
  R_Mil_StringTable_Node* next;
  R_String* string;
};

struct R_Mil_StringTable {
  R_Object _parent;
  R_Mil_StringTable_Node** buckets;
  R_SizeValue size;
  R_SizeValue capacity;
};

R_Mil_StringTable*
R_Mil_StringTable_create
  (
  );

R_String*
R_Mil_StringTable_getOrCreateString
  (
    R_Mil_StringTable* self,
    R_StringBuffer* stringBuffer
  );

#endif // R_MIL_STRINGTABLE_H_INCLUDED
