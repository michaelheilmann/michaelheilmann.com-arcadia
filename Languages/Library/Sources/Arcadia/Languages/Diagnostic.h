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

#if !defined(ARCADIA_LANGUAGES_DIAGNOSTIC_H_INCLUDED)
#define ARCADIA_LANGUAGES_DIAGNOSTIC_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Languages/DiagnosticType.h"

/// @brief A diagnostic message of the compiler.
Arcadia_declareObjectType(u8"Arcadia.Languages.Diagnostic", Arcadia_Languages_Diagnostic,
                          u8"Arcadia.Object");

struct Arcadia_Languages_DiagnosticDispatch {
  Arcadia_ObjectDispatch _parent;
  Arcadia_String *(*getMessage)(Arcadia_Thread*, Arcadia_Languages_Diagnostic*);
};

struct Arcadia_Languages_Diagnostic {
  Arcadia_Object _parent;
  /// @brief The diagnostic type.
  Arcadia_Languages_DiagnosticType type;
};

/// @brief Get the type of this diagnostic.
/// @param thread A pointer to this thread.
/// @param self A pointer to this diagnostic.
/// @return The diagnostic type.
Arcadia_Languages_DiagnosticType
Arcadia_Languages_Diagnostic_getType
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  );

/// @brief Get the message of this diagnostic.
/// @param thread A pointer to this thread.
/// @param self A pointer to this diagnostic.
/// @return The diagnostic message.
Arcadia_String*
Arcadia_Languages_Diagnostic_getMessage
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  );

#endif // ARCADIA_LANGUAGES_DIAGNOSTIC_H_INCLUDED
