#include "Arcadia/MIL/Frontend/SymbolKind.h"

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
};

Arcadia_defineEnumerationType(u8"Arcadia.MIL.SymbolKind", Arcadia_MIL_SymbolKind, &_typeOperations);
