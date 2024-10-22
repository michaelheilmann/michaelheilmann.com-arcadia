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

#if !defined(CIL_KEYWORDS_H_INCLUDED)
#define CIL_KEYWORDS_H_INCLUDED

#include "Cil/TokenType.h"

/// @code
/// class Cil.Keywords
/// @endcode
Rex_declareObjectType("Cil.Keywords", Cil_Keywords, "R.Object");

/// @brief Create a CIL keywords object.
/// @return A pointer to this CIL keywords object.
Cil_Keywords*
Cil_Keywords_create
  (
  );

/// @brief Add a CIL keyword.
/// @param string The string of the keyword.
/// @param type The type of the keyword
/// @error R_Status_Exists The keyword already was added.
void
Cil_Keywords_add
  (
    Cil_Keywords* self,
    R_String* string,
    R_Natural32Value type
  );

/// @brief Get the token type.
/// @param self A pointer to this CIL keyword scanner.
/// @param string The string to be tested for being a keyword.
/// @param tokenType A pointer to a variable that is assigned the keyword's token type if the string is a keyword. Not modified otherwise.
/// @return R_BooleanValue_True if the specified string was a keyword. #R_BooleanValue_False otherwise.
R_BooleanValue
Cil_Keywords_scan
  (
    Cil_Keywords* self,
    R_String* string,
    R_Natural32Value* tokenType
  );

#endif // CIL_KEYWORDS_H_INCLUDED

