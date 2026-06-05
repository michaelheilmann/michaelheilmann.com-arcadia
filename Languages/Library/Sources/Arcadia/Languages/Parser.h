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

#if !defined(ARCADIA_LANGUAGES_PARSER_H_INCLUDED)
#define ARCADIA_LANGUAGES_PARSER_H_INCLUDED

#if !defined(ARCADIA_LANGUAGES_MODULE)
  #error("do not include directly, include `Arcadia/Languages/Include.h` instead")
#endif

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Languages/StringTable.h"
#include "Arcadia/Languages/Diagnostics.h"

/// @brief The base of all parsers.
Arcadia_declareObjectType(u8"Arcadia.Languages.Parser", Arcadia_Languages_Parser,
                          u8"Arcadia.Object");

struct Arcadia_Languages_ParserDispatch {
  Arcadia_ObjectDispatch _parent;

  Arcadia_Value (*run)(Arcadia_Thread* thread, Arcadia_Languages_Parser* self, Arcadia_RuntimeByteArray* input);
  Arcadia_Languages_StringTable* (*getStringTable)(Arcadia_Thread* thread, Arcadia_Languages_Parser* self);
  Arcadia_Languages_Diagnostics* (*getDiagnostics)(Arcadia_Thread* thread, Arcadia_Languages_Parser* self);
};

struct Arcadia_Languages_Parser {
  Arcadia_Object _parent;

  /// @brief The input string.
  Arcadia_String* input;
};

/// @brief Run this parser on an input.
/// @param thread A pointer to this thread.
/// @param self A pointer to this parser.
/// @param input The input to run the parser on.
/// @return A value representing the result.
/// This is usually an Arcadia.Object or derived type object representing the root of a conrete tree or an abstract syntax tree.
Arcadia_Value
Arcadia_Languages_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self,
    Arcadia_RuntimeByteArray* input
  );

/// @brief Get the string table used by this parser.
/// @param thread A pointer this thread.
/// @param self A pointer to this parser.
/// @return A pointer to the string table.
Arcadia_Languages_StringTable*
Arcadia_Languages_Parser_getStringTable
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  );

/// @brief Get the diagnostics used by this parser.
/// @param thread A pointer this thread.
/// @param self A pointer to this parser.
/// @return A pointer to the diagnostics.
Arcadia_Languages_Diagnostics*
Arcadia_Languages_Parser_getDiagnostics
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  );

#endif // ARCADIA_LANGUAGES_PARSER_H_INCLUDED
