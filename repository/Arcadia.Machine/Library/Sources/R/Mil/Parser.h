// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-22

#if !defined(ARCADIA_MIL_PARSER_H_INCLUDED)
#define ARCADIA_MIL_PARSER_H_INCLUDED

#include "R/Include.h"
#include "R/Mil/Ast.h"

/// @code
/// class Arcadia.MilParser
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Mil.Parser", Arcadia_Mil_Parser, u8"Arcadia.Object");

/// @brief Create a MIL parser.
/// @return A pointer to this MIL parser.
Arcadia_Mil_Parser*
Arcadia_Mil_Parser_create
  (
    Arcadia_Thread* thread
  );

/// @brief Translate the token stream into an AST.
/// @param self A pointer to this MIL parser.
/// @return A pointer to the MIL AST.
Arcadia_Mil_ModuleAst*
Arcadia_Mil_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self
  );

/// @brief Set the input.
/// @param self A pointer to this MIL parser.
/// @param input A pointer to the UTF8 reader.
void
Arcadia_Mil_Parser_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Parser* self,
    Arcadia_Utf8Reader* input
  );

#endif // ARCADIA_MIL_PARSER_H_INCLUDED

