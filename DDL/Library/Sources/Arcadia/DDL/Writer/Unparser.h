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

#if !defined(ARCADIA_DDL_WRITER_UNPARSER_H_INCLUDED)
#define ARCADIA_DDL_WRITER_UNPARSER_H_INCLUDED

#if !defined(ARCADIA_DDL_PRIVATE) || 1 != ARCADIA_DDL_PRIVATE
  #error("do not include directly, include `Arcadia/DDL/Include.h` instead")
#endif

#include "Arcadia/DDL/Nodes/Include.h"

/// @code
/// class Arcadia.DataDefinitionLanguage.Unparser
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.Unparser", Arcadia_DataDefinitionLanguage_Unparser,
                          u8"Arcadia.Object");

/// @brief Create a Data Definition Language unparser.
/// @param thread A pointer to the thread.
/// @return A pointer to the Data Definition Language unparser.
Arcadia_DataDefinitionLanguage_Unparser*
Arcadia_DataDefinitionLanguage_Unparser_create
  (
    Arcadia_Thread* thread
  );

/// @brief Move to next token.
/// @param thread A pointer to the thread.
/// @param self A pointer to this Data Definition Language unparser.
/// @param node A pointer to the node to write.
/// @param target A pointer to the UTF8 writer the output is written to.
/// @error Arcadia_Status_SemanticalError two map contains two entries with the same key
/// @error Arcadia_Status_LexicalError a literal string (boolean, number, string, void) does not represent a valid literal
void
Arcadia_DataDefinitionLanguage_Unparser_run
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* self,
    Arcadia_DDL_Node* node,
    Arcadia_UTF8Writer* target
  );

#endif // ARCADIA_DDL_WRITER_UNPARSER_H_INCLUDED
