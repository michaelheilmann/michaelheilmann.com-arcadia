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

#if !defined(R_MIL_SCANNER_H_INCLUDED)
#define R_MIL_SCANNER_H_INCLUDED

#include "R/Mil/TokenType.h"

/// @code
/// class Cil.Scanner
/// @endcode
Rex_declareObjectType("Cil.Scanner", R_Mil_Scanner, "R.Object");

void
R_Mil_Scanner_construct
  (
    R_Mil_Scanner* self
  );

/// @brief Create a CIL scanner.
/// @return A pointer to this CIL scanner.
R_Mil_Scanner*
R_Mil_Scanner_create
  (
  );

/// @brief Get the text of the token.
/// @param self A pointer to this CIL scanner.
/// @return The text of the token.
R_String*
R_Mil_Scanner_getTokenText
  (
    R_Mil_Scanner* self
  );

/// @brief Get the type of the token.
/// @param self A pointer to this CIL scanner.
/// @return The type of the token.
R_Natural32Value
R_Mil_Scanner_getTokenType
  (
    R_Mil_Scanner* self
  );

/// @brief Move to next token.
/// @param self A pointer to this CIL scanner.
void
R_Mil_Scanner_step
  (
    R_Mil_Scanner* self
  );

/// @brief Set the input.
/// @param self A pointer to this CIL scanner.
/// @param input A pointer to the UTF8 reader.
void
R_Mil_Scanner_setInput
  (
    R_Mil_Scanner* self,
    R_Utf8Reader* input
  );

#endif // R_MIL_SCANNER_H_INCLUDED
