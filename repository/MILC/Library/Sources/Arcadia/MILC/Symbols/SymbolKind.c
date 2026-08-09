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

#define ARCADIA_MILC_PRIVATE (1)
#include "Arcadia/MILC/Symbols/SymbolKind.h"

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
};

Arcadia_defineEnumerationType(u8"Arcadia.MILC.SymbolKind", Arcadia_MILC_SymbolKind,
                              &_typeOperations);

Arcadia_String*
Arcadia_MILC_SymbolKind_toString
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_SymbolKind kind
  )
{
  switch (kind) {
    case Arcadia_MILC_SymbolKind_Class: {
      return Arcadia_String_createFromCxxString(thread, u8"class");
    } break;
    case Arcadia_MILC_SymbolKind_Constructor: {
      return Arcadia_String_createFromCxxString(thread, u8"constructor");
    } break;
    case Arcadia_MILC_SymbolKind_Enumeration: {
      return Arcadia_String_createFromCxxString(thread, u8"enumeration");
    } break;
    case Arcadia_MILC_SymbolKind_EnumerationConstant: {
      return Arcadia_String_createFromCxxString(thread, u8"enumeration constant");
    } break;
    case Arcadia_MILC_SymbolKind_Field: {
      return Arcadia_String_createFromCxxString(thread, u8"field");
    } break;
    case Arcadia_MILC_SymbolKind_Method: {
      return Arcadia_String_createFromCxxString(thread, u8"method");
    } break;
    case Arcadia_MILC_SymbolKind_Module: {
      return Arcadia_String_createFromCxxString(thread, u8"module");
    } break;
    case Arcadia_MILC_SymbolKind_Procedure: {
      return Arcadia_String_createFromCxxString(thread, u8"procedure");
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}