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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_READER_STRINGTABLE_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_READER_STRINGTABLE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// Unmanaged.
typedef struct Arcadia_DataDefinitionLanguage_StringTable_Node Arcadia_DataDefinitionLanguage_StringTable_Node;

struct Arcadia_DataDefinitionLanguage_StringTable_Node {
  Arcadia_DataDefinitionLanguage_StringTable_Node* next;
  // We need to compare the hash of the Bytes in a string buffer with the hash of the Bytes in a string.
  // The hash function of string buffer and string cannot be used for that.
  Arcadia_SizeValue hash;
  Arcadia_String* string;
};

Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.StringTable", Arcadia_DataDefinitionLanguage_StringTable, u8"Arcadia.Object");

struct Arcadia_DataDefinitionLanguage_StringTable {
  Arcadia_Object _parent;
  Arcadia_DataDefinitionLanguage_StringTable_Node** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

Arcadia_DataDefinitionLanguage_StringTable*
Arcadia_DataDefinitionLanguage_StringTable_create
  (
    Arcadia_Thread* thread
  );

Arcadia_String*
Arcadia_DataDefinitionLanguage_StringTable_getOrCreateString
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_StringTable* self,
    Arcadia_StringBuffer* stringBuffer
  );

#endif // ARCADIA_DATADEFINITIONLANGUAGE_READER_STRINGTABLE_H_INCLUDED
