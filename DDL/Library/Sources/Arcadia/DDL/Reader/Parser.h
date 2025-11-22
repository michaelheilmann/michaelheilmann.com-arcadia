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

#if !defined(ARCADIA_DDL_READER_PARSER_H_INCLUDED)
#define ARCADIA_DDL_READER_PARSER_H_INCLUDED

#include "Arcadia/DDL/Implementation/Include.h"
#include "Arcadia/Languages/Include.h"

/// @code
/// class Arcadia.DDL.Parser
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DDL.Parser", Arcadia_DDL_Parser,
                          u8"Arcadia.Object");

/// @brief Create a Data Definition Language parser.
/// @return A pointer to the Data Definition Language parser.
Arcadia_DDL_Parser*
Arcadia_DDL_Parser_create
  (
    Arcadia_Thread* thread
  );

/// @brief Move to next token.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language parser.
Arcadia_DDL_Node*
Arcadia_DDL_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

/// @brief Set the input.
/// @param thread A pointer to this thread.
/// @param self A pointer to this Data Definition Language parser.
/// @param input A pointer to the UTF8 reader.
void
Arcadia_DDL_Parser_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self,
    Arcadia_Utf8Reader* input
  );

Arcadia_Languages_StringTable*
Arcadia_DDL_Parser_getStringTable
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* self
  );

#endif // ARCADIA_DDL_READER_PARSER_H_INCLUDED
