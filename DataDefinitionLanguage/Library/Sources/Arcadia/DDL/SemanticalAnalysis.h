// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_SEMANTICALANALYSIS_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_SEMANTICALANALYSIS_H_INCLUDED

#include "Arcadia/DDL/Implementation/Include.h"

/// @code
/// class Arcadia.DataDefinitionLanguage.SemanticalAnalysis
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.SemanticalAnalysis", Arcadia_DataDefinitionLanguage_SemanticalAnalysis,
                          u8"Arcadia.Object");

/// @brief Create a Data Definition Language semantical analysis.
/// @param thread A pointer to the thread.
/// @return A pointer to this thread.
Arcadia_DataDefinitionLanguage_SemanticalAnalysis*
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_create
  (
    Arcadia_Thread* thread
  );

/// @brief Run this Arcadia Data Definition Language semantical analysis on a node.
/// @param thread A pointer to the thread.
/// @param self A pointer to this Data Definition Language semantical analysis.
/// @param node A pointer to the node.
/// @error Arcadia_Status_SemanticalError a map contains two entries with the same key
void
Arcadia_DataDefinitionLanguage_SemanticalAnalysis_run
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* self,
    Arcadia_DDL_Node* node
  );

#endif // ARCADIA_DATADEFINITIONLANGUAGE_SEMANTICALANALYSIS_H_INCLUDED
