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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_HASHMAP_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_HASHMAP_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Implementation/Collections/Map.h"

typedef struct _Arcadia_HashMap_Node _Arcadia_HashMap_Node;

Arcadia_declareObjectType(u8"Arcadia.HashMap", Arcadia_HashMap, u8"Arcadia.Map");

struct Arcadia_HashMap {
  Arcadia_Map _parent;
  _Arcadia_HashMap_Node** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_HashMap_create
Arcadia_HashMap*
Arcadia_HashMap_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_HASHMAP_H_INCLUDED
