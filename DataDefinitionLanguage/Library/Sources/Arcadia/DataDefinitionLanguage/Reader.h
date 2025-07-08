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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_READER_READER_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_READER_READER_H_INCLUDED

#include "Arcadia/DataDefinitionLanguage/Tree/Include.h"

/// @code
/// class Arcadia.DataDefinitionLanguage.Reader
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.Reader", Arcadia_DataDefinitionLanguage_Reader, u8"Arcadia.Object");

/// @brief Create a Data Definition Language reader.
/// @param thread A pointer to this thread.
/// @return A pointer to the reader.
Arcadia_DataDefinitionLanguage_Reader*
Arcadia_DataDefinitionLanguage_Reader_create
  (
    Arcadia_Thread* thread
  );

/// @brief Read a Data Definition Language node.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language reader.
/// @param input A pointer to the input.
/// @return A pointer to the node.
Arcadia_DataDefinitionLanguage_Tree_Node*
Arcadia_DataDefinitionLanguage_Reader_reader
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Reader* self,
    Arcadia_Utf8Reader* input
  );

#endif // ARCADIA_DATADEFINITIONLANGUAGE_READER_READER_H_INCLUDED
