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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_VALUESTACK_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_VALUESTACK_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Configure.h"
#include "Arcadia/Ring1/Implementation/Size.h"
typedef struct Arcadia_Process1 Arcadia_Process1;
typedef struct Arcadia_ValueStack Arcadia_ValueStack;
typedef struct Arcadia_Value Arcadia_Value;

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
Arcadia_SizeValue
Arcadia_ValueStack_getSize
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
/// @error Arcadia_Status_ArgumentValueInvalid @a value is a null pointer
/// @error Arcadia_Status_AllocationFailed an allocation failed
void
Arcadia_ValueStack_push
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self,
    Arcadia_Value *value
  );

/// @error Arcadia_Status_ArgumentValueInvalid @a self is a null pointer
/// @error Arcadia_Status_ArgumentValueInvalid @a coutn is greater than the size of the stack
void
Arcadia_ValueStack_pop
  (
    Arcadia_Process1* process,
    Arcadia_ValueStack* self,
    Arcadia_SizeValue count
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_VALUESTACK_H_INCLUDED
