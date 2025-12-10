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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEBYTEARRAY_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEBYTEARRAY_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Size.h"

/// @brief The immutable byte array representation native to Arcadia Ring 1.
/// @warning Arcadia_ImmutableByteArray's precondition is an initialized type system.
typedef struct Arcadia_ImmutableByteArray Arcadia_ImmutableByteArray;

struct Arcadia_ImmutableByteArray {
  Arcadia_SizeValue numberOfBytes;
  Arcadia_Natural8Value bytes[];
};

typedef Arcadia_ImmutableByteArray* Arcadia_ImmutableByteArrayValue;

Arcadia_ImmutableByteArray*
Arcadia_ImmutableByteArray_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

void
Arcadia_ImmutableByteArray_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArrayValue self
  );

/// @brief Get a pointer to the Bytes in an immutable Byte Array.
/// @return A pointer to the Bytes of the immutable Byte array.
/// @warning The Bytes of the array must not be modified.
Arcadia_Natural8Value const*
Arcadia_ImmutableByteArray_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArrayValue self
  );

/// @brief Get the number of Bytes in an immutable Byte array.
/// @param immutableByteArrayA pointer to the immutable Byte array.
/// @return The number of Bytes in the imumutable Byte array.
Arcadia_SizeValue
Arcadia_ImmutableByteArray_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArrayValue self
  );

/// @return A pointer to an "foreign value" type of name "Arcadia.ImmutableByteArray".
Arcadia_TypeValue
_Arcadia_ImmutableByteArrayValue_getType
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEBYTEARRAY_H_INCLUDED
