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

#if !defined(ARCADIA_MILC_DIAGNOSTICS_SYMBOLALREADYDEFINEDDIAGNOSTIC_H_INCLUDED)
#define ARCADIA_MILC_DIAGNOSTICS_SYMBOLALREADYDEFINEDDIAGNOSTIC_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia/MILC/WordType.h"

/// @brief A diagnostic message of the compiler.
/// This diagnostic, if emitted, yields the following error message
/// @code
/// semantical error: the symbol `<symbol>` is already defined
/// @endode
/// where @code{<symbol>} is replaced by the name of the symbol.
Arcadia_declareObjectType(u8"Arcadia.MILC.Diagnostics.SymbolAlreadyDefinedDiagnostic", Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic,
                          u8"Arcadia.Languages.Diagnostic");

struct Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnosticDispatch {
  Arcadia_Languages_DiagnosticDispatch _parent;
};

struct Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic {
  Arcadia_Languages_Diagnostic _parent;
  /// @brief The name of the symbol.
  Arcadia_String* name;
};

Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic*
Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticType type,
    Arcadia_String* name
  );

#endif // ARCADIA_MILC_DIAGNOSTICS_SYMBOLALREADYDEFINEDDIAGNOSTIC_H_INCLUDED
