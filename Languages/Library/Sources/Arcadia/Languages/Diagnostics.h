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

#if !defined(ARCADIA_LANGUAGES_DIAGNOSTICS_H_INCLUDED)
#define ARCADIA_LANGUAGES_DIAGNOSTICS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_Languages_Diagnostic Arcadia_Languages_Diagnostic;

Arcadia_declareObjectType(u8"Arcadia.Languages.Diagnostics", Arcadia_Languages_Diagnostics,
                          u8"Arcadia.Object");

struct Arcadia_Languages_DiagnosticsDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Languages_Diagnostics {
  Arcadia_Object _parent;
  /// @brief List of diagnostics (Arcadia.Languages.Diagnostic or derived type objects).
  Arcadia_List* diagnostics;
  /// @brief The log.
  Arcadia_Log* log;
};

Arcadia_Languages_Diagnostics*
Arcadia_Languages_Diagnostics_create
  (
    Arcadia_Thread* thread,
	  Arcadia_Log* log
  );

Arcadia_BooleanValue
Arcadia_Languages_Diagnostics_hasErrors
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  );
  
void
Arcadia_Languages_Diagnostics_add
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self,
    Arcadia_Languages_Diagnostic* diagnostic
  );

void
Arcadia_Languages_Diagnostics_emit
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  );

#endif // ARCADIA_LANGUAGES_DIAGNOSTICS_H_INCLUDED
