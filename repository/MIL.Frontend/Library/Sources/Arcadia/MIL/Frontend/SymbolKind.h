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

#if !defined(ARCADIA_MIL_FRONTEND_SYMBOLTABLE_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_SYMBOLTABLE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType(u8"Arcadia.MIL.SymbolKind", Arcadia_MIL_SymbolKind);

enum Arcadia_MIL_SymbolKind {
  Arcadia_MIL_SymbolKind_Class,
  Arcadia_MIL_SymbolKind_Constructor,
  Arcadia_MIL_SymbolKind_Method,
  Arcadia_MIL_SymbolKind_Field,
};

#endif // ARCADIA_MIL_FRONTEND_SYMBOLTABLE_H_INCLUDED
