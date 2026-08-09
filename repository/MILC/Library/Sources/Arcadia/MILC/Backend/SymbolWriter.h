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

#if !defined(ARCADIA_MILC_BACKEND_SYMBOLWRITER_H_INCLUDED)
#define ARCADIA_MILC_BACKEND_SYMBOLWRITER_H_INCLUDED

#include "Arcadia/MILC/Backend/SymbolInfo.h"
#include "Arcadia/MILC/Backend/CXXFileType.h"

/// @brief A writer for symbols.
Arcadia_declareObjectType(u8"Arcadia.MILC.Backend.SymbolWriter", Arcadia_MILC_Backend_SymbolWriter,
                          u8"Arcadia.Object");

struct Arcadia_MILC_Backend_SymbolWriterDispatch {
  Arcadia_ObjectDispatch _parent;
  void (*write)(Arcadia_Thread* thread, Arcadia_MILC_Backend_SymbolWriter* self, Arcadia_MILC_Context* context, Arcadia_MILC_Backend_CXXFileType fileType,
                Arcadia_MILC_Backend_SymbolInfo* symbolInfo, Arcadia_StringBuilder* stringBuilder);
};

struct Arcadia_MILC_Backend_SymbolWriter {
  Arcadia_Object _parent;
};

Arcadia_MILC_Backend_SymbolWriter*
Arcadia_MILC_Backend_SymbolWriter_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_MILC_Backend_SymbolWriter_write
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_CXXFileType fileType,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  );

#endif // ARCADIA_MILC_BACKEND_SYMBOLWRITER_H_INCLUDED
