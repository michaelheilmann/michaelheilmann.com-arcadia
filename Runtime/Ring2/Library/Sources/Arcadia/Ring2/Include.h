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

#if !defined(ARCADIA_RING2_INCLUDE_H_INCLUDED)
#define ARCADIA_RING2_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_RING2_PRIVATE")
#undef ARCADIA_RING2_PRIVATE
#define ARCADIA_RING2_PRIVATE (1)

#include "Arcadia/Ring2/Collections/Include.h"

#include "Arcadia/Ring2/Implementation/ArgumentsValidation.h"
#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/Implementation/CommandLine.h"
#include "Arcadia/Ring2/FileSystem/Include.h"
#include "Arcadia/Ring2/Strings/Include.h"

#include "Arcadia/Ring2/Logging/Include.h"

#include "Arcadia/Ring2/Time/Include.h"

#if defined(_DEBUG)

/* Dump the type of a value to the trace channel. */
static inline void
Debug_dumpValueType
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  )
{
  Arcadia_Type* type = Arcadia_Value_getType(thread, &value);
  Arcadia_Atom* atom = Arcadia_Type_getName(type);
  Arcadia_logf(Arcadia_LogFlags_Debug, u8"%.*s\n", (int)Arcadia_clampSizeValue(thread, Arcadia_Atom_getNumberOfBytes(thread, atom), 0, INT_MAX),
                                                   Arcadia_Atom_getBytes(thread, atom));
}

#endif

#if defined(_DEBUG)

/* Dump the type of a value to the trace channel. */
static inline void
Debug_dumpObjectType
  (
    Arcadia_Thread* thread,
    Arcadia_Object* object
  )
{
  Arcadia_Type* type = Arcadia_Object_getType(thread, object);
  Arcadia_Atom* atom = Arcadia_Type_getName(type);
  Arcadia_logf(Arcadia_LogFlags_Debug, u8"%.*s\n", (int)Arcadia_clampSizeValue(thread, Arcadia_Atom_getNumberOfBytes(thread, atom), 0, INT_MAX),
                                                   Arcadia_Atom_getBytes(thread, atom));
}

#endif

#undef ARCADIA_RING2_PRIVATE
#pragma pop_macro("ARCADIA_RING2_PRIVATE")

#endif // ARCADIA_RING2_INCLUDE_H_INCLUDED
