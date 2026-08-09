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

#if !defined(ARCADIA_MILC_BACKEND_ENUMERATIONSYMBOLWRITER_H_INCLUDED)
#define ARCADIA_MILC_BACKEND_ENUMERATIONSYMBOLWRITER_H_INCLUDED

#include "Arcadia/MILC/Backend/SymbolWriter.h"

/// @brief A writer for an enumeration symbol.
Arcadia_declareObjectType(u8"Arcadia.MILC.Backend.EnumerationSymbolWriter", Arcadia_MILC_Backend_EnumerationSymbolWriter,
                          u8"Arcadia.MILC.Backend.SymbolWriter");

struct Arcadia_MILC_Backend_EnumerationSymbolWriterDispatch {
  Arcadia_MILC_Backend_SymbolWriterDispatch _parent;
};

struct Arcadia_MILC_Backend_EnumerationSymbolWriter {
  Arcadia_MILC_Backend_SymbolWriter _parent;
};

Arcadia_MILC_Backend_EnumerationSymbolWriter*
Arcadia_MILC_Backend_EnumerationSymbolWriter_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_MILC_BACKEND_ENUMERATIONSYMBOLWRITER_H_INCLUDED
