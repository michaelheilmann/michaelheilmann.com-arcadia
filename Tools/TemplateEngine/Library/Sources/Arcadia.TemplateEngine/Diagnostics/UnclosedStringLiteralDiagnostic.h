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

#if !defined(ARCADIA_TOOLS_TEMPLATEENGINE_DIAGNOSTICS_UNCLOSEDSTRINGLITERALDIAGNOSTIC_H_INCLUDED)
#define ARCADIA_TOOLS_TEMPLATEENGINE_DIAGNOSTICS_UNCLOSEDSTRINGLITERALDIAGNOSTIC_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia.TemplateEngine/Diagnostics/UnclosedStringLiteralDiagnosticContext.h"

/// @brief A diagnostic message of the compiler.
/// This diagnostic, if emitted, yields the following error message
/// @code
/// lexical error: unclosed string literal, <reason>
/// @endode
/// where @code{<reason>} is replaced by a textual description of the reason which is usually @code{encountered end of line} or @code{encountered end of input}
Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.Diagnostics.UnclosedStringLiteralDiagnostic", Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnostic,
                          u8"Arcadia.Languages.Diagnostic");

struct Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnosticDispatch {
  Arcadia_Languages_DiagnosticDispatch _parent;
};

struct Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnostic {
  Arcadia_Languages_Diagnostic _parent;
  /// @brief The received symbol.
  Arcadia_Natural32Value received;
};

Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnostic*
Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnostic_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticType type,
    Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnosticContext context
  );

#endif // ARCADIA_TOOLS_TEMPLATEENGINE_DIAGNOSTICS_UNCLOSEDSTRINGLITERALDIAGNOSTIC_H_INCLUDED
