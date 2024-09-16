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

#include "R/Boolean.h"
#include "R/Natural8.h"
#include "R/Size.h"

typedef struct R_StringBuffer R_StringBuffer;
void _R_StringBuffer_registerType();

struct R_StringBuffer {
  char* p;
  size_t sz;
  size_t cp;
};

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
    size_t numberOfBytes
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

#endif // R_STRINGBUFFER_H_INCLUDED
