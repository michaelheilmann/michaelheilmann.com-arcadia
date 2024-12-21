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

// Last modified: 2024-09-26

#if !defined(R_CONVERT_VOIDTOSTRING_H_INCLUDED)
#define R_CONVERT_VOIDTOSTRING_H_INCLUDED

#include "Arms.h"
#include "R/Void.h"
#include "R/Size.h"

/// @brief Convert a "void" value into a "string" value.
/// @param value The "void" value.
/// @return A pointer to the string.
void
R_Void_toString
  (
    Arms_MemoryManager* memoryManager,
    R_VoidValue value,
    char** buffer,
    R_SizeValue* bufferLength
  );

#endif // R_CONVERT_VOIDTOSTRING_H_INCLUDED
