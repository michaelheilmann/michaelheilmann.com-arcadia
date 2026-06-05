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

#if !defined(ARCADIA_RING1_MODULE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/ARMS/Include.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Size.h"

/// @brief The immutable byte array representation native to Arcadia Ring 1.
/// @warning Arcadia_RuntimeByteArray's precondition is an initialized type system.
typedef struct Arcadia_RuntimeByteArray Arcadia_RuntimeByteArray;

struct Arcadia_RuntimeByteArray {
  Arcadia_SizeValue numberOfBytes;
  Arcadia_Natural8Value bytes[];
};

typedef Arcadia_RuntimeByteArray* Arcadia_RuntimeByteArrayValue;

Arcadia_RuntimeByteArray*
Arcadia_RuntimeByteArray_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

/// @brief
/// Visit this Arcadia_RuntimeByteArrayValue object.
/// @param thread
/// A pointer to the Arcadia_Thread object.
/// @param self
/// A pointer to this Arcadia_RuntimeByteArrayValue object.
void
Arcadia_RuntimeByteArray_visit
  (
    Arcadia_Thread* thread,
    Arcadia_RuntimeByteArrayValue self
  );

#if defined(Arcadia_ARMS_Configuration_WithBarriers) && 1 == Arcadia_ARMS_Configuration_WithBarriers

/// @brief
/// Ensure this Arcadia_RuntimeByteArrayValue object is gray.
/// @param thread
/// A pointer to this Arcadia_Thread object.
/// @param self
/// A pointer to this Arcadia_RuntimeByteArrayValue object.
void
Arcadia_RuntimeByteArray_ensureGray
  (
    Arcadia_Thread* thread,
    Arcadia_RuntimeByteArrayValue self
  );

#endif

/// @brief Get a pointer to the Bytes in an immutable Byte Array.
/// @return A pointer to the Bytes of the immutable Byte array.
/// @warning The Bytes of the array must not be modified.
Arcadia_Natural8Value const*
Arcadia_RuntimeByteArray_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_RuntimeByteArrayValue self
  );

/// @brief Get the number of Bytes in an immutable Byte array.
/// @param runtimeByteArrayA pointer to the immutable Byte array.
/// @return The number of Bytes in the imumutable Byte array.
Arcadia_SizeValue
Arcadia_RuntimeByteArray_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_RuntimeByteArrayValue self
  );

/// @return A pointer to an "foreign value" type of name "Arcadia.ImmutableByteArray".
Arcadia_TypeValue
_Arcadia_RuntimeByteArrayValue_getType
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEBYTEARRAY_H_INCLUDED
