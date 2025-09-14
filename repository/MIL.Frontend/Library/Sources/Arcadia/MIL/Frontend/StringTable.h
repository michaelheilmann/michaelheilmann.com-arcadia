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

#if !defined(ARCADIA_MIL_FRONTEND_STRINGTABLE_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_STRINGTABLE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareObjectType(u8"Arcadia.MIL.StringTable", Arcadia_MIL_StringTable, u8"Arcadia.Object");

// Unmanaged.
typedef struct Arcadia_MIL_StringTable_Node Arcadia_MIL_StringTable_Node;

struct Arcadia_MIL_StringTable_Node {
  Arcadia_MIL_StringTable_Node* next;
  Arcadia_String* string;
};

struct Arcadia_MIL_StringTable {
  Arcadia_Object _parent;
  Arcadia_MIL_StringTable_Node** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

Arcadia_MIL_StringTable*
Arcadia_MIL_StringTable_create
  (
    Arcadia_Thread* thread
  );

Arcadia_String*
Arcadia_MIL_StringTable_getOrCreateString
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_StringTable* self,
    Arcadia_StringBuffer* stringBuffer
  );

#endif // ARCADIA_MIL_FRONTEND_STRINGTABLE_H_INCLUDED
