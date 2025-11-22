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

#if !defined(ARCADIA_DDLS_SEMANTICAL_SYMBOL_H_INCLUDED)
#define ARCADIA_DDLS_SEMANTICAL_SYMBOL_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_DDLS_Scope Arcadia_DDLS_Scope;

/* A map type symbol. */
#define Arcadia_DDLS_SymbolKind_MapType (1)

/* A map entry type symbol. */
#define Arcadia_DDLS_SymbolKind_MapEntryType (2)

/* A scalar type symbol. */
#define Arcadia_DDLS_SymbolKind_ScalarType (3)

Arcadia_declareObjectType(u8"Arcadia.DDLS.Symbol", Arcadia_DDLS_Symbol,
                          u8"Arcadia.Object");

struct Arcadia_DDLS_Symbol {
  Arcadia_Object parent;
  Arcadia_Natural8Value kind;
  Arcadia_DDLS_Scope* scope;
};

#endif // ARCADIA_DDLS_SEMANTICAL_SYMBOL_H_INCLUDED
