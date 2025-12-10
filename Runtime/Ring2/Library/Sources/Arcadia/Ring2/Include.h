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

#include "Arcadia/Ring2/Print/print.h"

#include "Arcadia/Ring2/Time/Include.h"

#if defined(_DEBUG)

/* Diagnostics for a value stack. */
static inline void
Arcadia_Diagnostics_logValueStack
  (
    Arcadia_Thread* thread,
    Arcadia_LogFlags logFlags
  )
{
  Arcadia_SizeValue size = Arcadia_ValueStack_getSize(thread);
  for (Arcadia_SizeValue index = 0; index < size; ++index) {
    Arcadia_Value value = Arcadia_ValueStack_getValue(thread, index);
    Arcadia_TypeValue type = Arcadia_Value_getType(thread, &value);
    Arcadia_AtomValue typeName = Arcadia_Type_getName(type);
    Arcadia_logf(Arcadia_LogFlags_Debug,
                 "%zu) %.*s\n",
                 index,
                 Arcadia_Atom_getNumberOfBytes(thread, typeName) > INT_MAX ? INT_MAX : Arcadia_Atom_getNumberOfBytes(thread, typeName),
                 Arcadia_Atom_getBytes(thread, typeName));
  }
}

/* Diagnostics for a value stack element. */
static inline void
Arcadia_Diagnostics_logValueStackElement
  (
    Arcadia_Thread* thread,
    Arcadia_LogFlags logFlags,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value value = Arcadia_ValueStack_getValue(thread, index);
  Arcadia_TypeValue type = Arcadia_Value_getType(thread, &value);
  Arcadia_AtomValue typeName = Arcadia_Type_getName(type);
  Arcadia_logf(logFlags,
               "%zu) %.*s\n",
               index,
               Arcadia_Atom_getNumberOfBytes(thread, typeName) > INT_MAX ? INT_MAX : Arcadia_Atom_getNumberOfBytes(thread, typeName),
               Arcadia_Atom_getBytes(thread, typeName));
}

/* Diagnostics for a value. */
static inline void
Arcadia_Diagnostics_logValue
  (
    Arcadia_Thread* thread,
    Arcadia_LogFlags logFlags,
    Arcadia_Value value
  )
{
  Arcadia_Type* type = Arcadia_Value_getType(thread, &value);
  Arcadia_Atom* atom = Arcadia_Type_getName(type);
  Arcadia_logf(logFlags, u8"%.*s\n", Arcadia_Atom_getNumberOfBytes(thread, atom) > INT_MAX ? INT_MAX : Arcadia_Atom_getNumberOfBytes(thread, atom),
                                     Arcadia_Atom_getBytes(thread, atom));
}

/* Diagnostics for an object value. */
static inline void
Arcadia_Diagnostics_logObjectType
  (
    Arcadia_Thread* thread,
    Arcadia_LogFlags logFlags,
    Arcadia_Object* object
  )
{
  Arcadia_Type* type = Arcadia_Object_getType(thread, object);
  Arcadia_Atom* atom = Arcadia_Type_getName(type);
  Arcadia_logf(logFlags, u8"%.*s\n", Arcadia_Atom_getNumberOfBytes(thread, atom) > INT_MAX ? INT_MAX : Arcadia_Atom_getNumberOfBytes(thread, atom),
                                     Arcadia_Atom_getBytes(thread, atom));
}

#endif

#undef ARCADIA_RING2_PRIVATE
#pragma pop_macro("ARCADIA_RING2_PRIVATE")

#endif // ARCADIA_RING2_INCLUDE_H_INCLUDED
