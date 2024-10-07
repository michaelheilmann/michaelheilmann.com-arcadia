// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(CIL_PARSER_H_INCLUDED)
#define CIL_PARSER_H_INCLUDED

#include "R.h"

typedef enum Cil_AstType {
  // A program.
  Cil_AstType_Program,
  // A statement.
  Cil_AstType_Statement,
} Cil_AstType;

/// @code
/// class Cil.Parser
/// @endcode
typedef struct Cil_Parser Cil_Parser;
void _Cil_Parser_registerType();

/// @brief Create a CIL parser.
/// @return A pointer to this CIL parser.
Cil_Parser*
Cil_Parser_create
  (
  );

/// @brief Translate the token stream into an AST.
/// @param self A pointer to this CIL parser. 
void
Cil_Parser_run
  (
    Cil_Parser* self
  );

/// @brief Set the input.
/// @param self A pointer to this CIL parser.
/// @param input A pointer to the UTF8 reader.
void
Cil_Parser_setInput
  (
    Cil_Parser* self,
    R_Utf8Reader* input
  );

#endif // CIL_PARSER_H_INCLUDED

