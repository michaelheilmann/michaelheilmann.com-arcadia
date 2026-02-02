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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_SIGNALS_INTERNAL_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_SIGNALS_INTERNAL_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Thread.h"
#include "Arcadia/Ring1/Implementation/ThreadExtensions.h"
#include "Arcadia/Ring1/Implementation/WeakReference.h"
typedef struct Arcadia_Slot Arcadia_Slot;

typedef struct Nodes Nodes;

// The maximum number of slots per signal.
#define MaximumNumberOfSlots (SIZE_MAX - sizeof(Nodes) / sizeof(Arcadia_Slot*))

struct Nodes {
  // The number of times a signal may invoke itself.
  // The maximum is Arcadia_Natural32Value_Maximum.
  Arcadia_Natural32Value reentrancyCount;
  // The allocated array is the least power of two greater than or equal to size if size is greater than 8.
  // Otherwise the size of the allocated array is 8.
  Arcadia_SizeValue size;
  // An element is a pointer to a slot or a null pointer.
  Arcadia_Slot* elements[];
};

#endif // ARCADIA_RING1_IMPLEMENTATION_SIGNALS_INTERNAL_H_INCLUDED
