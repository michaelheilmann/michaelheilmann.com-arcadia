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

// Last modified: 2025-02-16

#if !defined(ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRING_FROMNATURAL_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRING_FROMNATURAL_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Process1.h"
typedef struct Arcadia_ImmutableUtf8String Arcadia_ImmutableUtf8String;

Arcadia_ImmutableUtf8String*
_createFromNatural16
  (
    Arcadia_Process1* process,
    Arcadia_Natural16Value natural16Value
  );

Arcadia_ImmutableUtf8String*
_createFromNatural32
  (
    Arcadia_Process1* process,
    Arcadia_Natural32Value natural32Value
  );

Arcadia_ImmutableUtf8String*
_createFromNatural64
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value natural64Value
  );

Arcadia_ImmutableUtf8String*
_createFromNatural8
  (
    Arcadia_Process1* process,
    Arcadia_Natural8Value natural8Value
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRING_FROMNATURAL_H_INCLUDED
