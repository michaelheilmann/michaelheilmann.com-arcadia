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

// Last modified: 2025-02-02

#if !defined(ARCADIA_RING1_IMPLEMENTATION_VALUESTACK_PRIVATE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_VALUESTACK_PRIVATE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Stack.h"
typedef struct Arcadia_Value Arcadia_Value;

/// A stack object is usually an element of another struct.
struct Arcadia_ValueStack {
  Arcadia_Value* elements;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
/// @error Arcadia_Status_AllocationFailed an allocation failed
void
Arcadia_ValueStack_initialize
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack * self
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
void
Arcadia_ValueStack_uninitialize
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
/// @error Arcadia_Status_AllocationFailed an allocation failed
void
Arcadia_ValueStack_increaseCapacity
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self,
    Arcadia_SizeValue additionalCapacity
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
/// @error Arcadia_Status_AllocationFailed an allocation failed
void
Arcadia_ValueStack_ensureFreeCapacity
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_VALUESTACK_PRIVATE_H_INCLUDED
