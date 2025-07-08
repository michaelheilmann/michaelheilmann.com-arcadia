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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_WRITER_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_WRITER_H_INCLUDED

#include "Arcadia/DataDefinitionLanguage/Tree/Include.h"

/// @code
/// class Arcadia.DataDefinitionLanguage.Writer
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.Writer", Arcadia_DataDefinitionLanguage_Writer, u8"Arcadia.Object");

/// @brief Create a Data Definition Language writer.
/// @param thread A pointer to the thread.
/// @return A pointer to this thread.
Arcadia_DataDefinitionLanguage_Writer*
Arcadia_DataDefinitionLanguage_Writer_create
  (
    Arcadia_Thread* thread
  );

/// @brief Move to next token.
/// @param thread A pointer to the thread.
/// @param self A pointer to this Data Definition Language writer.
/// @param node A pointer to the node to write.
/// @param stringBuffer A pointer to the string buffer to append the data to.
/// @error Arcadia_Status_SemanticalError two map contains two entries with the same key
/// @error Arcadia_Status_LexicalError a literal string (boolean, number, string, void) does not represent a valid literal
void
Arcadia_DataDefinitionLanguage_Writer_write
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Writer* self,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    Arcadia_StringBuffer* stringBuffer
  );

#endif // ARCADIA_DATADEFINITIONLANGUAGE_WRITER_WRITER_H_INCLUDED
