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

#if !defined(ARCADIA_DDLS_IMPLEMENTATION_DIAGNOSTICS_H_INCLUDED)
#define ARCADIA_DDLS_IMPLEMENTATION_DIAGNOSTICS_H_INCLUDED

#include "Arcadia/DDLS/Nodes/Include.h"
#include "Arcadia/DDL/Include.h"
#include "Arcadia/Languages/Include.h"

// Used for building diagnostic messages.
Arcadia_declareObjectType(u8"Arcadia.DDLS.Diagnostics", Arcadia_DDLS_Diagnostics,
                          u8"Arcadia.Object");

struct Arcadia_DDLS_DiagnosticsDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_DDLS_Diagnostics {
  Arcadia_Object parent;
  Arcadia_String* BOOLEAN;
  Arcadia_String* LIST;
  Arcadia_String* MAP;
  Arcadia_String* NUMBER;
  Arcadia_String* SCHEMA;
  Arcadia_String* SCHEMAREFERENCE;
  Arcadia_String* STRING;
  Arcadia_String* VOID;
  Arcadia_StringBuffer* stringBuffer;
  Arcadia_Languages_StringTable* stringTable;
};

Arcadia_DDLS_Diagnostics*
Arcadia_DDLS_Diagnostics_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_StringTable* stringTable
  );

void
Arcadia_DDLS_Diagnostics_unexpectedTypeError
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Diagnostics* self,
    Arcadia_DDLS_Node* ddlsNode,
    Arcadia_DDL_Node* node
  );

void
Arcadia_DDLS_Diagnostics_mapEntryAlreadyDefined
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Diagnostics* self,
    Arcadia_String* name
  );

void
Arcadia_DDLS_Diagnostics_mapEntryExistsError
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Diagnostics* self,
    Arcadia_String* name
  );

void
Arcadia_DDLS_Diagnostics_mapEntryNotExistsError
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Diagnostics* self,
    Arcadia_String* name
  );

void
Arcadia_DDLS_Diagnostics_unresolvedSchemaReferenceError
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Diagnostics* self,
    Arcadia_String* name
  );


#endif // ARCADIA_DDLS_IMPLEMENTATION_DIAGNOSTICS_H_INCLUDED
