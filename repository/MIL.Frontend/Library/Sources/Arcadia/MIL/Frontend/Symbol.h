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

#if !defined(ARCADIA_MIL_FRONTEND_SYMBOL_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_SYMBOL_H_INCLUDED

#include "Arcadia/MIL/Frontend/SymbolKind.h"

/// @code
/// class Arcadia.MIL.Symbol {
///
///   field kind:Arcadia.MIL.SymbolKind
///
///   field name:Arcadia.String
///
///   constructor(kind:Arcadia.MIL.SymbolKind, name:Arcadia.String)
///
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.Symbol", Arcadia_MIL_Symbol,
                          u8"Arcadia.Object");

struct Arcadia_MIL_SymbolDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MIL_Symbol {
  Arcadia_Object _parent;
  Arcadia_String* name;
  Arcadia_MIL_SymbolKind kind;
};

Arcadia_MIL_Symbol*
Arcadia_MIL_Symbol_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_SymbolKind kind,
    Arcadia_String* name
  );

#endif // ARCADIA_MIL_FRONTEND_SYMBOL_H_INCLUDED
