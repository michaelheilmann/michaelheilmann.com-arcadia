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

#if !defined(ARCADIA_LANGUAGES_SCANNER_H_INCLUDED)
#define ARCADIA_LANGUAGES_SCANNER_H_INCLUDED

#if !defined(ARCADIA_LANGUAGES_PRIVATE)
  #error("do not include directly, include `Arcadia/Languages/Include.h` instead")
#endif

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Languages/StringTable.h"

/// @brief The base of all scanners.
Arcadia_declareObjectType(u8"Arcadia.Languages.Scanner", Arcadia_Languages_Scanner,
                          u8"Arcadia.Object");

struct Arcadia_Languages_Scanner {
  Arcadia_Object _parent;

  Arcadia_String* (*getWordText)(Arcadia_Thread* thread, Arcadia_Languages_Scanner* self);

  Arcadia_Natural32Value (*getWordType)(Arcadia_Thread* thread, Arcadia_Languages_Scanner* self);

  Arcadia_Natural32Value (*getWordStart)(Arcadia_Thread* thread, Arcadia_Languages_Scanner* self);
  Arcadia_Natural32Value (*getWordLength)(Arcadia_Thread* thread, Arcadia_Languages_Scanner* self);

  void (*step)(Arcadia_Thread* thread, Arcadia_Languages_Scanner* self);

  void (*setInput)(Arcadia_Thread* thread, Arcadia_Languages_Scanner* self, Arcadia_String* input);
  Arcadia_String* (*getInput)(Arcadia_Thread* thread, Arcadia_Languages_Scanner* self);

  Arcadia_Languages_StringTable* (*getStringTable)(Arcadia_Thread* thread, Arcadia_Languages_Scanner* self);

};

/// @brief Get the text of the word.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scanner.
/// @return The text of the word.
Arcadia_String*
Arcadia_Languages_Scanner_getWordText
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

/// @brief Get the type of the word.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scanner.
/// @return The type of the word.
Arcadia_Natural32Value
Arcadia_Languages_Scanner_getWordType
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

/// @brief Get the start of the word as an offset in Bytes from the beginning of the input.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scanner.
/// @return The start of the word as an offset in Bytes from the beginning of the input.
Arcadia_Natural32Value
Arcadia_Languages_Scanner_getWordStart
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

/// @brief Get the length of the current word in Bytes.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scanner.
/// @return The length of the word as a length in Bytes.
Arcadia_Natural32Value
Arcadia_Languages_Scanner_getWordLength
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

/// @brief Move to next word.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scanner.
void
Arcadia_Languages_Scanner_step
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

/// @brief Set the input.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scanner.
/// @param input A pointer to the input string.
void
Arcadia_Languages_Scanner_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self,
    Arcadia_String* input
  );

/// @brief Get the input.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scanner.
/// @return A pointer to the input string.
Arcadia_String*
Arcadia_Languages_Scanner_getInput
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

/// @brief Get the string table used by this scanner.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scanner.
/// @return A pointer to the string table used by this scanner.
Arcadia_Languages_StringTable*
Arcadia_Languages_Scanner_getStringTable
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

#endif // ARCADIA_LANGUAGES_SCANNER_H_INCLUDED
