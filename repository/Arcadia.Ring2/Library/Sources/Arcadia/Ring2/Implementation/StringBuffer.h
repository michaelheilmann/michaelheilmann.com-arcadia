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

// Last modified: 2024-09-22

#if !defined(ARCADIA_RING2_IMPLEMENTATION_STRINGBUFFER_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_STRINGBUFFER_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

/// @code
/// class StringBuffer {
///   constructor()
/// }
/// @endcode
Rex_declareObjectType(u8"Arcadia.StringBuffer", Arcadia_StringBuffer, u8"Arcadia.Object");

struct Arcadia_StringBuffer {
  Arcadia_Object _parent;
  Arcadia_Natural8Value* elements;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

/// @brief Create a string buffer.
/// @return The string buffer.
/// @remarks The string buffer is empty.
Arcadia_StringBuffer*
Arcadia_StringBuffer_create
  (
    Arcadia_Process* process
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
    Arcadia_Process* process,
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
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

/// @brief Append Bytes to a string buffer.
/// @param self A pointer to the string buffer.
/// @param bytes A pointer to the array of Bytes.
/// @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
/// @error Arcadia_Status_ArgumentValueInvalid @a bytes is a null pointer
/// @error Arcadia_Status_EncodingInvalid The Bytes are not an UTF-8 Byte sequence.
void
Arcadia_StringBuffer_append_pn
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

/// @brief Append Bytes to this string buffer.
/// @param value The Bytes.
/// Either R.ByteBuffer, Arcadia.StringBuffer, or Arcadia.String.
void
Arcadia_StringBuffer_append
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    Arcadia_Value value
  );

void
Arcadia_StringBuffer_appendCodePoints
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  );

/// @brief
/// Compare the contents of two string buffer for lexicographic equivalence.
/// @param self
/// A pointer to this string buffer.
/// @param other
/// A pointer to the other string buffer.
/// @return
/// Arcadia_BooleanValue_True if the contents of this string buffer is lexicographically equal to the contents of the other string buffer string buffer.
/// Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_StringBuffer_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_StringBuffer* self,
    Arcadia_StringBuffer* other
  );

/// @brief Set the number of UTF-8 symbols in this string buffer to zero.
/// @param self A pointer to this string buffer.
void
Arcadia_StringBuffer_clear
  (
    Arcadia_StringBuffer* self
  );

Arcadia_SizeValue
Arcadia_StringBuffer_getNumberOfBytes
  (
    Arcadia_StringBuffer const* self
  );

Arcadia_Natural8Value const*
Arcadia_StringBuffer_getBytes
  (
    Arcadia_StringBuffer const* self
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_STRINGBUFFER_H_INCLUDED
