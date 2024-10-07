#if !defined(CIL_STRINGTABLE_H_INCLUDED)
#define CIL_STRINGTABLE_H_INCLUDED

#include "R.h"

typedef struct Cil_StringTable Cil_StringTable;
void _Cil_StringTable_registerType();

// Unmanaged.
typedef struct Cil_StringTable_Node Cil_StringTable_Node;
struct Cil_StringTable_Node {
  Cil_StringTable_Node* next;
  R_String* string;
};

struct Cil_StringTable {
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
