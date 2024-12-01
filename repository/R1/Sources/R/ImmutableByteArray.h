// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(R_IMMUTABLEBYTEARRAY_H_INCLUDED)
#define R_IMMUTABLEBYTEARRAY_H_INCLUDED

#include "R/Natural8.h"
#include "R/Size.h"

/// An immutable byte array managed by ARMS.
/// 
/// It is typically used when strings are transferred from the C domain into the MI domain, e.g.
/// @code
/// R_Value value = { .tag = R_ValueTag_ImmutableByteArray, .immutableByteArray = R_ImmutableByteArray_create(u8"Hello, World!", strlen(u8"Hello, World!") };
/// R_String_create(&value);
/// @endcode
typedef struct R_ImmutableByteArray {
  R_SizeValue numberOfBytes;
  R_Natural8Value bytes[];
} R_ImmutableByteArray;

typedef R_ImmutableByteArray* R_ImmutableByteArrayValue;

R_ImmutableByteArray*
R_ImmutableByteArray_create
  (
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  );

void
R_ImmutableByteArray_visit
  (
    R_ImmutableByteArray* immutableByteArray
  );

/// @brief Get a pointer to the Bytes in an immutable Byte Array.
/// @return A pointer to the Bytes of the immutable Byte array.
/// @warning The Bytes of the array must not be modified.
R_Natural8Value const*
R_ImmutableByteArray_getBytes
  (
    R_ImmutableByteArray const* immutableByteArray
  );

/// @brief Get the number of Bytes in an immutable Byte array.
/// @param immutableByteArrayA pointer to the immutable Byte array. 
/// @return The number of Bytes in the imumutable Byte array.
R_SizeValue
R_ImmutableByteArray_getNumberOfBytes
  (
    R_ImmutableByteArray const* immutableByteArray
  );

/// @return A pointer to an "foreign value" type of name "R.Foreign.ImmutableByteArray".
R_Type*
_R_ImmutableByteArray_getType
  (
  );

#endif // R_CORE_IMMUTABLEBYTEARRAY_H_INCLUDED
