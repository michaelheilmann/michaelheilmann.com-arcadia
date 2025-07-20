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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_COLLECTIONS_IMMUTABLELIST_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_COLLECTIONS_IMMUTABLELIST_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Implementation/Collections/List.h"

Arcadia_declareObjectType(u8"Arcadia.ImmutableList", Arcadia_ImmutableList, u8"Arcadia.List");

struct Arcadia_ImmutableList {
  Arcadia_List parent;
  Arcadia_Value* elements;
  Arcadia_SizeValue size;
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ImmutableList_create
// construct(Arcadia.List other)
Arcadia_ImmutableList*
Arcadia_ImmutableList_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value argument
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_COLLECTIONS_IMMUTABLELIST_H_INCLUDED
