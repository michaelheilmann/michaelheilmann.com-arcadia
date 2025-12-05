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

#if !defined(ARCADIA_DDLS_SYMBOLS_SCOPE_H_INCLUDED)
#define ARCADIA_DDLS_SYMBOLS_SCOPE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_DDLS_Symbol Arcadia_DDLS_Symbol;

/* Map from names to symbols. An error symbol e replace conflicting symbols e1 and e2. */
Arcadia_declareObjectType(u8"Arcadia.DDLS.Scope", Arcadia_DDLS_Scope,
                          u8"Arcadia.Object");

struct Arcadia_DDLS_Scope {
  Arcadia_Object parent;
  /* The enclosing scope or null. */
  Arcadia_DDLS_Scope* enclosing;
  /* Name to symbol map. */
  Arcadia_Map* symbols;
};

Arcadia_DDLS_Scope*
Arcadia_DDLS_Scope_create
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Scope* enclosing
  );

#endif // ARCADIA_DDLS_SYMBOLS_SCOPE_H_INCLUDED
