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

#include "Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h"

#include "Arcadia/Ring1/Include.h"

static Arcadia_BooleanValue g_registered = Arcadia_BooleanValue_False;

static void
_onTypeRemoved
  (
    Arcadia_Process* process,
    const uint8_t* bytes,
    size_t numberOfBytes
  )
{ g_registered = Arcadia_BooleanValue_False; }

void
_ensureTypeRegistered
  (
    Arcadia_Process1* process
  )
{
  if (!g_registered) {
    Arcadia_Process1_registerType(process, TypeName, sizeof(TypeName) - 1, process, &_onTypeRemoved, NULL, NULL);
    g_registered = Arcadia_BooleanValue_True;
  }
}
