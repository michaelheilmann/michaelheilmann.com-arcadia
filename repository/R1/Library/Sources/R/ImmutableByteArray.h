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

// Last modified: 2024-09-20

#if !defined(ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEBYTEARRAY_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEBYTEARRAY_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Size.h"

/// An immutable byte array managed by ARMS.
/// 
/// It is typically used when strings are transferred from the C domain into the Ring2 domain, e.g.
/// @code
/// Arcadia_Value value = { .tag = R_ValueTag_ImmutableByteArray, .immutableByteArray = Arcadia_ImmutableByteArray_create(u8"Hello, World!", strlen(u8"Hello, World!") };
/// Arcadia_String_create(&value);
/// @endcode
typedef struct Arcadia_ImmutableByteArray {
  Arcadia_SizeValue numberOfBytes;
  Arcadia_Natural8Value bytes[];
} Arcadia_ImmutableByteArray;

typedef Arcadia_ImmutableByteArray* Arcadia_ImmutableByteArrayValue;

Arcadia_ImmutableByteArray*
Arcadia_ImmutableByteArray_create
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

void
Arcadia_ImmutableByteArray_visit
  (
    Arcadia_ImmutableByteArray* immutableByteArray
  );

/// @brief Get a pointer to the Bytes in an immutable Byte Array.
/// @return A pointer to the Bytes of the immutable Byte array.
/// @warning The Bytes of the array must not be modified.
Arcadia_Natural8Value const*
Arcadia_ImmutableByteArray_getBytes
  (
    Arcadia_ImmutableByteArray const* immutableByteArray
  );

/// @brief Get the number of Bytes in an immutable Byte array.
/// @param immutableByteArrayA pointer to the immutable Byte array. 
/// @return The number of Bytes in the imumutable Byte array.
Arcadia_SizeValue
Arcadia_ImmutableByteArray_getNumberOfBytes
  (
    Arcadia_ImmutableByteArray const* immutableByteArray
  );

/// @return A pointer to an "foreign value" type of name "R.Foreign.ImmutableByteArray".
Arcadia_TypeValue
_Arcadia_ImmutableByteArray_getType
  (
    Arcadia_Process* process
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEBYTEARRAY_H_INCLUDED
