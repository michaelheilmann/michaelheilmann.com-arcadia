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

#if !defined(ARCADIA_VPL_SYMBOLS_SYMBOL_H_INCLUDED)
#define ARCADIA_VPL_SYMBOLS_SYMBOL_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/Languages/Include.h"

// A constant. Can be either a constant record or a constant scalar.
Arcadia_declareObjectType(u8"Arcadia.VPL.Symbols.Symbol", Arcadia_VPL_Symbols_Symbol,
                          u8"Arcadia.Object");

struct Arcadia_VPL_Symbols_SymbolDispatch {
  Arcadia_ObjectDispatch _parent;
  Arcadia_String* (*getName)(Arcadia_Thread*, Arcadia_VPL_Symbols_Symbol*);
  void (*resolveTypes)(Arcadia_Thread*, Arcadia_VPL_Symbols_Symbol*);
};

struct Arcadia_VPL_Symbols_Symbol {
  Arcadia_Object _parent;
};

/// @brief Get the name of this symbol.
/// @param thread A pointer to this thread.
/// @param self A pointer to this symbol.
/// @return The name of this symbol.
Arcadia_String*
Arcadia_VPL_Symbols_Symbol_getName
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Symbol* self
  );

/// @brief Resolve type names.
/// @param thread A pointer to this thread.
/// @param self A pointer to this symbol.
void
Arcadia_VPL_Symbols_Symbol_resolveTypes
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Symbol* self
  );

#endif // ARCADIA_VPL_SYMBOLS_SYMBOL_H_INCLUDED
