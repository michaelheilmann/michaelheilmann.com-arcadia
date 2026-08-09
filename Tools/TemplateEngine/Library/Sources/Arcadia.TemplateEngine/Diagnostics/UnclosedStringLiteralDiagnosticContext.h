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

#if !defined(ARCADIA_TOOLS_TEMPLATEENGINE_DIAGNOSTICS_UNCLOSEDSTRINGLITERALDIAGNOSTICCONTEXT_H_INCLUDED)
#define ARCADIA_TOOLS_TEMPLATEENGINE_DIAGNOSTICS_UNCLOSEDSTRINGLITERALDIAGNOSTICCONTEXT_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia.TemplateEngine/Scanner/WordType.h"

/// @brief Enumeration denoting the reason why a string literal is not closed.
Arcadia_declareEnumerationType(u8"Arcadia.TemplateEngine.Diagnostics.UnclosedStringLiteralDiagnosticContext",
                               Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnosticContext);

enum Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnosticContext {
  /// @brief The end of the line was encountered.
  Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnosticContext_EndOfLine,
  /// @brief The end of the input was encountered.
  Arcadia_TemplateEngine_Diagnostics_UnclosedStringLiteralDiagnosticContext_EndOfInput,
};

#endif // ARCADIA_TOOLS_TEMPLATEENGINE_DIAGNOSTICS_UNCLOSEDSTRINGLITERALDIAGNOSTICCONTEXT_H_INCLUDED
