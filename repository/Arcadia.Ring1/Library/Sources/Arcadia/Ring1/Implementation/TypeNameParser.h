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

// Last modified: 2024-08-27

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPENAMEPARSER_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPENAMEPARSER_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Configure.h"
#include "Arcadia/Ring1/Implementation/Size.h"

/// @brief Get if a sequence of Bytes is an UTF8 string.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @error Arcadia_Status_ArgumentValueInvald @a bytes is a  null pointer
/// @error Arcadia_Status_EncodingError the Bytes are not a type name
void
R_Names_parseTypeName
  (
    Arcadia_Process* process,
    const char *bytes,
    size_t numberOfBytes
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPENAMEPARSER_H_INCLUDED
