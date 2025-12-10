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

#if !defined(ARCADIA_RING2_STRINGS_STRINGBUFFER_H_INCLUDED)
#define ARCADIA_RING2_STRINGS_STRINGBUFFER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

/// @code
/// class Arcadia.StringBuffer {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.StringBuffer", Arcadia_StringBuffer,
                          u8"Arcadia.Object");

struct Arcadia_StringBufferDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_StringBuffer {
  Arcadia_Object _parent;
  Arcadia_Natural8Value* elements;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_StringBuffer_create
Arcadia_StringBuffer*
Arcadia_StringBuffer_create
  (
    Arcadia_Thread* thread
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_StringBuffer_insertAt
void
Arcadia_StringBuffer_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue codePointIndex,
    Arcadia_Value value
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_StringBuffer_insertBack
void
Arcadia_StringBuffer_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Value value
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_StringBuffer_insertFront
void
Arcadia_StringBuffer_insertFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Value value
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_StringBuffer_compareTo
Arcadia_Integer32Value
Arcadia_StringBuffer_compareTo
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Value other
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_StringBuffer_clear
void
Arcadia_StringBuffer_clear
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_StringBuffer_getNumberOfBytes
Arcadia_SizeValue
Arcadia_StringBuffer_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer const* self
  );

/// @brief Get if a sequence of Bytes is a suffix of this string buffer.
/// @param self A pointer to ths string buffer.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @return
/// Arcadia_BooleanValue_True if the sequence of Bytes is a suffix of the string buffer.
/// Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_StringBuffer_endsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

/// @brief Get if the specified sequence of Bytes is a prefix of this string buffer.
/// @param self A pointer to this string buffer.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @return
/// Arcadia_BooleanValue_True if the sequence of Bytes is a prefix of the string buffer.
/// Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_StringBuffer_startsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

/// @brief Remove code points from the front of this string buffer.
/// @param thread A pointer to this thread.
/// @param self A pointer to this string buffer.
/// @param numberOfCodePoints The number of code points to remove.
/// @error Arcadia_Status_ArgumentValueInvalid @a numberOfCodePoints is greater than the number of code points in this string buffer
void
Arcadia_StringBuffer_removeCodePointsFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue numberOfCodePoints
  );

/// @brief Remove code points from the back of this string buffer.
/// @param thread A pointer to this thread.
/// @param self A pointer to this string buffer.
/// @param numberOfCodePoints The number of code points to remove.
/// @error Arcadia_Status_ArgumentValueInvalid @a numberOfCodePoints is greater than the number of code points in this string buffer
void
Arcadia_StringBuffer_removeCodePointsBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_SizeValue numberOfCodePoints
  );

void
Arcadia_StringBuffer_insertCodePointBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value codePoint
  );

void
Arcadia_StringBuffer_insertCodePointsBack
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  );

void
Arcadia_StringBuffer_insertCodePointFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value codePoint
  );

void
Arcadia_StringBuffer_insertCodePointsFront
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  );

Arcadia_Natural8Value const*
Arcadia_StringBuffer_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer const* self
  );

#endif // ARCADIA_RING2_STRINGS_STRINGBUFFER_H_INCLUDED
