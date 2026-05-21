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

#if !defined(ARCADIA_MILC_SYMBOLS_METHODSYMBOL_H_INCLUDED)
#define ARCADIA_MILC_SYMBOLS_METHODSYMBOL_H_INCLUDED

#include "Arcadia/MILC/Symbols/Symbol.h"

/// @code
/// class Arcadia.MILC.MethodSymbol extends Arcadia.MILC.Symbol {
///
///   constructor(name:Arcadia.String)
///
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MILC.MethodSymbol", Arcadia_MILC_MethodSymbol,
                          u8"Arcadia.MILC.Symbol");

struct Arcadia_MILC_MethodSymbolDispatch {
  Arcadia_MILC_SymbolDispatch _parent;
};

struct Arcadia_MILC_MethodSymbol {
  Arcadia_MILC_Symbol _parent;
};

Arcadia_MILC_MethodSymbol*
Arcadia_MILC_MethodSymbol_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

#endif // ARCADIA_MILC_SYMBOLS_METHODSYMBOL_H_INCLUDED
