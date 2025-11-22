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

#if !defined(ARCADIA_LANGUAGES_STRINGTABLE_H_INCLUDED)
#define ARCADIA_LANGUAGES_STRINGTABLE_H_INCLUDED

#if !defined(ARCADIA_LANGUAGES_PRIVATE)
  #error("do not include directly, include `Arcadia/Languages/Include.h` instead")
#endif

#include "Arcadia/Ring2/Include.h"

// Unmanaged.
typedef struct Arcadia_Languages_StringTable_Node Arcadia_Languages_StringTable_Node;

Arcadia_declareObjectType(u8"Arcadia.Languages.StringTable", Arcadia_Languages_StringTable,
                          u8"Arcadia.Object");

struct Arcadia_Languages_StringTable {
  Arcadia_Object _parent;
  Arcadia_Languages_StringTable_Node** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

Arcadia_Languages_StringTable*
Arcadia_Languages_StringTable_create
  (
    Arcadia_Thread* thread
  );

Arcadia_String*
Arcadia_Languages_StringTable_getOrCreateString
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_StringTable* self,
    Arcadia_StringBuffer* stringBuffer
  );

#endif // ARCADIA_LANGUAGES_STRINGTABLE_H_INCLUDED
