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

#if !defined(ARCADIA_DDLS_SEMANTICAL_SYMBOLREADER_H_INCLUDED)
#define ARCADIA_DDLS_SEMANTICAL_SYMBOLREADER_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/DDL/Include.h"
#include "Arcadia/DDLS/Semantical/Symbol.h"

Arcadia_declareObjectType(u8"Arcadia.DDLS.SymbolReader", Arcadia_DDLS_SymbolReader,
                          u8"Arcadia.Object");                          
                          
struct Arcadia_DDLS_SymbolReader {
  Arcadia_DDLS_Symbol parent;

  Arcadia_DDLS_Scope* scope;
  
  Arcadia_Value BOOLEAN;
  Arcadia_Value LIST;
  Arcadia_Value MAP;
  Arcadia_Value MAPENTRY;
  Arcadia_Value NUMBER;
  Arcadia_Value STRING;
  Arcadia_Value VOID;

  Arcadia_Value NAME;
  Arcadia_Value TYPE;
  Arcadia_Value ELEMENT;
  Arcadia_Value ENTRIES;
  Arcadia_Value KIND;

  Arcadia_Languages_StringTable* stringTable;
};
                     
Arcadia_DDLS_SymbolReader*
Arcadia_DDLS_SymbolReader_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_StringTable* stringTable
  );

Arcadia_DDLS_Symbol*
Arcadia_DDLS_SymbolReader_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_SymbolReader* self,
    Arcadia_DDL_Node* source
  );

Arcadia_DDLS_Symbol*
Arcadia_DDLS_SemanticalPass
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* source
  );

#endif // ARCADIA_DDLS_SEMANTICAL_SYMBOLREADER_H_INCLUDED
