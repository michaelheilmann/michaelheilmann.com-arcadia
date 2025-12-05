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

#if !defined(ARCADIA_DDLS_SYMBOLS_SCHEMASYMBOL_H_INCLUDED)
#define ARCADIA_DDLS_SYMBOLS_SCHEMASYMBOL_H_INCLUDED

#include "Arcadia/DDLS/Symbols/Symbol.h"

/// @code
/// {
///   type : "Schema",
///   name : <name>,
///   definition : <Symbol> - <SchemaSymbol>
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DDLS.SchemaSymbol", Arcadia_DDLS_SchemaSymbol,
                          u8"Arcadia.DDLS.Symbol");

struct Arcadia_DDLS_SchemaSymbol {
  Arcadia_DDLS_Symbol parent;
  Arcadia_String* name;
  Arcadia_DDLS_Symbol* definition;
};

Arcadia_DDLS_SchemaSymbol*
Arcadia_DDLS_SchemaSymbol_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

#endif // ARCADIA_DDLS_SYMBOLS_SCHEMASYMBOL_H_INCLUDED
