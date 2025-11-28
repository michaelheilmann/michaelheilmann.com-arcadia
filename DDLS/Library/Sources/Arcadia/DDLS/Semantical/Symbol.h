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

/// A schema symbol.
#define Arcadia_DDLS_SymbolKind_Schema (0)

/// A schema reference symbol.
#define Arcadia_DDLS_SymbolKind_SchemaReference (1)

/// A map symbol.
#define Arcadia_DDLS_SymbolKind_Map (2)

/// A map entry symbol.
#define Arcadia_DDLS_SymbolKind_MapEntry (3)

/// A scalar symbol.
#define Arcadia_DDLS_SymbolKind_Scalar (4)

/// A list symbol.
/// @todo Add implementation.
#define Arcadia_DDLS_SymbolLind_List (5)

Arcadia_declareObjectType(u8"Arcadia.DDLS.Symbol", Arcadia_DDLS_Symbol,
                          u8"Arcadia.Object");

struct Arcadia_DDLS_Symbol {
  Arcadia_Object parent;
  Arcadia_Natural8Value kind;
};

#endif // ARCADIA_DDLS_SEMANTICAL_SYMBOL_H_INCLUDED
