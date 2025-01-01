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

// Last modified: 2024-09-26

#if !defined(R_CONVERT_BOOLEANTOSTRING_H_INCLUDED)
#define R_CONVERT_BOOLEANTOSTRING_H_INCLUDED

#include "Arms.h"
#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Size.h"

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Boolean_toString
  (
    Arcadia_Process* process,
    Arms_MemoryManager* memoryManager,
    Arcadia_BooleanValue value,
    char** buffer,
    Arcadia_SizeValue* bufferLength
  );

#endif // R_CONVERT_BOOLEANTOSTRING_H_INCLUDED
