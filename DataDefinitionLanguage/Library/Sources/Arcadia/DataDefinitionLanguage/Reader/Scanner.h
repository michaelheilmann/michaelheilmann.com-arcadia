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

#if !defined(ARCADIA_DATADEFINITIONLANGUAGE_READER_SCANNER_H_INCLUDED)
#define ARCADIA_DATADEFINITIONLANGUAGE_READER_SCANNER_H_INCLUDED

#include "Arcadia/DataDefinitionLanguage/Reader/WordType.h"

/// @code
/// class Arcadia.DataDefinitionLanguage.Scanner
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DataDefinitionLanguage.Scanner", Arcadia_DataDefinitionLanguage_Scanner, u8"Arcadia.Object");

/// @brief Create a Data Definition Language scanner.
/// @param thread A pointer to this thread.
/// @return A pointer to this thread.
Arcadia_DataDefinitionLanguage_Scanner*
Arcadia_DataDefinitionLanguage_Scanner_create
  (
    Arcadia_Thread* thread
  );

/// @brief Get the text of the word.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language scanner.
/// @return The text of the word.
Arcadia_ImmutableUtf8String*
Arcadia_DataDefinitionLanguage_Scanner_getWordText
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Scanner* self
  );

/// @brief Get the type of the word.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language scanner.
/// @return The type of the word.
Arcadia_Natural32Value
Arcadia_DataDefinitionLanguage_Scanner_getWordType
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Scanner* self
  );

/// @brief Get the position of the word as a zero-based index into the input Bytes.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Defintion Language scanner.
/// @return The position.
Arcadia_Natural32Value
Arcadia_DataDefinitionLanguage_Scanner_getWordPosition
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Scanner* self
  );

/// @brief Get the length in input Bytes of the word.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language scanner.
/// @return The length.
Arcadia_Natural32Value
Arcadia_DataDefinitionLanguage_Scanner_getWordlength
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Scanner* self
  );

/// @brief Move to next token.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language scanner.
void
Arcadia_DataDefinitionLanguage_Scanner_step
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Scanner* self
  );

/// @brief Set the input.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language scanner.
/// @param input A pointer to the UTF8 reader.
void
Arcadia_DataDefinitionLanguage_Scanner_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Scanner* self,
    Arcadia_Utf8Reader* input
  );

#endif // ARCADIA_DATADEFINITIONLANGUAGE_READER_SCANNER_H_INCLUDED
