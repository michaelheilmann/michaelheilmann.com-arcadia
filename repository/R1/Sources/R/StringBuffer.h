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

// Last modified: 2024-09-22

#if !defined(R_STRINGBUFFER_H_INCLUDED)
#define R_STRINGBUFFER_H_INCLUDED

#include "R/Object.h"
#include "R/Value.h"

Rex_declareObjectType("R.StringBuffer", R_StringBuffer, "R.Object");

struct R_StringBuffer {
  R_Object _parent;
  R_Natural8Value* elements;
  R_SizeValue size;
  R_SizeValue capacity;
};

void
R_StringBuffer_construct
  (
    R_StringBuffer* self
  );

/// @brief Create a string buffer.
/// @return The string buffer.
/// @remarks The string buffer is empty.
R_StringBuffer*
R_StringBuffer_create
  (
  );

/// @brief Get if a sequence of Bytes is a suffix of this string buffer.
/// @param self A pointer to ths string buffer.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @return
/// R_BooleanValue_True if the sequence of Bytes is a suffix of the string buffer.
/// R_BooleanValue_False otherwise.
R_BooleanValue
R_StringBuffer_endsWith_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

/// @brief Get if the specified sequence of Bytes is a prefix of this string buffer.
/// @param self A pointer to this string buffer.
/// @param bytes A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @return
/// R_BooleanValue_True if the sequence of Bytes is a prefix of the string buffer.
/// R_BooleanValue_False otherwise.
R_BooleanValue
R_StringBuffer_startsWith_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

/// @brief Append Bytes to a string buffer.
/// @param self A pointer to the string buffer.
/// @param bytes A pointer to the array of Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @error R_Status_ArgumentValueInvalid @a bytes is a null pointer
/// @error R_Status_EncodingInvalid The Bytes are not an UTF-8 Byte sequence.
void
R_StringBuffer_append_pn
  (
    R_StringBuffer* self,
    void const* bytes,
    R_SizeValue numberOfBytes
  );

/// @brief Append Bytes to this string buffer.
/// @param value The Bytes.
/// Either R.ByteBuffer, R.StringBuffer, or R.String.
void
R_StringBuffer_append
  (
    R_StringBuffer* self,
    R_Value value
  );

void
R_StringBuffer_appendCodePoints
  (
    R_StringBuffer* self,
    R_Natural32Value const* codePoints,
    R_SizeValue numberOfCodePoints
  );

/// @brief
/// Compare the contents of two string buffer for lexicographic equivalence.
/// @param self
/// A pointer to this string buffer.
/// @param other
/// A pointer to the other string buffer.
/// @return
/// R_BooleanValue_True if the contents of this string buffer is lexicographically equal to the contents of the other string buffer string buffer.
/// R_BooleanValue_False otherwise.
R_BooleanValue
R_StringBuffer_isEqualTo
  (
    R_StringBuffer* self,
    R_StringBuffer* other
  );

/// @brief Set the number of UTF-8 symbols in this string buffer to zero.
/// @param self A pointer to this string buffer.
void
R_StringBuffer_clear
  (
    R_StringBuffer* self
  );

R_SizeValue
R_StringBuffer_getNumberOfBytes
  (
    R_StringBuffer const* self
  );

R_Natural8Value const*
R_StringBuffer_getBytes
  (
    R_StringBuffer const* self
  );

#endif // R_STRINGBUFFER_H_INCLUDED
