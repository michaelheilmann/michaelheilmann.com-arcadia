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

#if !defined(ARCADIA_MILC_DIAGNOSTICS_INTEGERLITERALOUTOFRANGEDIAGNOSTIC_H_INCLUDED)
#define ARCADIA_MILC_DIAGNOSTICS_INTEGERLITERALOUTOFRANGEDIAGNOSTIC_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia/FileSystem/Include.h"
#include "Arcadia/MILC/Symbols/EnumerationConstantSymbol.h"

/// @brief A diagnostic message of the compiler.
/// This diagnostic, if emitted, yields the following error message
/// @code
/// error: value `<value>` of initializer of enumeration constant `<name>` is out of range
/// @endcode
/// where @code{<value>} is the value of the initializer of an enumeration constant
/// and @code{<name>} is the fully qualified name of the enumeration constant.
Arcadia_declareObjectType(u8"Arcadia.MILC.Diagnostics.IntegerLiteralOutOfRangeDiagnostic", Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic,
                          u8"Arcadia.Languages.Diagnostic");

struct Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnosticDispatch {
  Arcadia_Languages_DiagnosticDispatch _parent;
};

struct Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic {
  Arcadia_Languages_Diagnostic _parent;
  /// @brief The symbol of the enumeration constant.
  Arcadia_MILC_EnumerationConstantSymbol* symbol;
  /// @brief The textual value of the initializer of the enumeration constant.
  Arcadia_String* value;
};

Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic*
Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticType type,
    Arcadia_MILC_EnumerationConstantSymbol* symbol,
    Arcadia_String* value
  );

#endif // ARCADIA_MILC_DIAGNOSTICS_INTEGERLITERALOUTOFRANGEDIAGNOSTIC_H_INCLUDED
