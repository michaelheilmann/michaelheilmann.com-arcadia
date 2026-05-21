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

#if !defined(ARCADIA_MILC_SYMBOLS_SYMBOL_H_INCLUDED)
#define ARCADIA_MILC_SYMBOLS_SYMBOL_H_INCLUDED

#include "Arcadia/MILC/Symbols/SymbolKind.h"

/// @code
/// class Arcadia.MILC.Symbol {
///
///   field kind:Arcadia.MILC.SymbolKind
///
///   field name:Arcadia.String
///
///   constructor(kind:Arcadia.MILC.SymbolKind, name:Arcadia.String)
///
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MILC.Symbol", Arcadia_MILC_Symbol,
                          u8"Arcadia.Object");

struct Arcadia_MILC_SymbolDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_Symbol {
  Arcadia_Object _parent;
  /// The name of this symbol.
  Arcadia_String* name;
  /// The kind of this symbol.
  Arcadia_MILC_SymbolKind kind;
  /// The enclosing symbol.
  Arcadia_MILC_Symbol* enclosing;
};

Arcadia_MILC_Symbol*
Arcadia_MILC_Symbol_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_SymbolKind kind,
    Arcadia_String* name
  );

#endif // ARCADIA_MILC_SYMBOLS_SYMBOL_H_INCLUDED
