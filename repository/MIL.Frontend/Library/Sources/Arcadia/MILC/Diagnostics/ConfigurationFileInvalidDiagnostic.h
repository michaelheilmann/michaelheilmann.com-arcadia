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

#if !defined(ARCADIA_MILC_DIAGNOSTICS_CONFIGURATIONFILEINVALIDDIAGNOSTIC_H_INCLUDED)
#define ARCADIA_MILC_DIAGNOSTICS_CONFIGURATIONFILEINVALIDDIAGNOSTIC_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia/FileSystem/Include.h"
#include "Arcadia/MILC/WordType.h"

/// @brief A diagnostic message of the compiler.
/// This diagnostic, if emitted, yields the following error message
/// @code
/// error: configuration file `<path>` is invalid
/// @endode
/// where @code{<path>} is the path to the configuration file.
Arcadia_declareObjectType(u8"Arcadia.MILC.Diagnostics.ConfigurationFileInvalidDiagnostic", Arcadia_MILC_Diagnostics_ConfigurationFileInvalidDiagnostic,
                          u8"Arcadia.Languages.Diagnostic");

struct Arcadia_MILC_Diagnostics_ConfigurationFileInvalidDiagnosticDispatch {
  Arcadia_Languages_DiagnosticDispatch _parent;
};

struct Arcadia_MILC_Diagnostics_ConfigurationFileInvalidDiagnostic {
  Arcadia_Languages_Diagnostic _parent;
  /// @brief The path to the module directory.
  Arcadia_FilePath* path;
};

Arcadia_MILC_Diagnostics_ConfigurationFileInvalidDiagnostic*
Arcadia_MILC_Diagnostics_ConfigurationFileInvalidDiagnostic_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticType type,
    Arcadia_FilePath* path
  );

#endif // ARCADIA_MILC_DIAGNOSTICS_CONFIGURATIONFILEINVALIDDIAGNOSTIC_H_INCLUDED
