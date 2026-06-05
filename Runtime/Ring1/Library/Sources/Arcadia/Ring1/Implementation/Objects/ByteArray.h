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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAY_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAY_H_INCLUDED

#if !defined(ARCADIA_RING1_MODULE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Object.h"

/// @code
/// class Arcadia.ByteArray {
///   construct(runtimeByteArray:Arcadia.RuntimeByteArray)
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.ByteArray", Arcadia_ByteArray,
                          u8"Arcadia.Object");

struct Arcadia_ByteArrayDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_ByteArray {
  Arcadia_Object _parent;
  Arcadia_RuntimeByteArray* runtimeByteArray;
};

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_ByteArray_create
Arcadia_ByteArray*
Arcadia_ByteArray_create
  (
    Arcadia_Thread* thread,
    Arcadia_RuntimeByteArray* runtimeByteArray
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_ByteArray_getSize
Arcadia_SizeValue
Arcadia_ByteArray_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_ByteArray_getNumberOfBytes
Arcadia_SizeValue
Arcadia_ByteArray_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_ByteArray_getBytes
Arcadia_Natural8Value const*
Arcadia_ByteArray_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self
  );

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_ByteArray_getAt
Arcadia_Natural8Value
Arcadia_ByteArray_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArray const* self,
    Arcadia_SizeValue index
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAY_H_INCLUDED
