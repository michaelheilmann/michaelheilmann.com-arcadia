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

// Last modified: 2024-08-28

#if !defined(R_BYTEBUFFER_H_INCLUDED)
#define R_BYTEBUFFER_H_INCLUDED

#include "r/boolean.h"
#include "r/size.h"

typedef struct R_ByteBuffer R_ByteBuffer;

void _R_ByteBuffer_registerType();

struct R_ByteBuffer {
  char* p;
  R_SizeValue sz;
  R_SizeValue cp;
};

/**
 * @ingroup r
 * @brief Create a Byte buffer.
 * @return The Byte buffer.
 * @remarks The Byte buffer is empty.
 */
R_ByteBuffer*
R_ByteBuffer_create
  (
  );

/**
 * @ingroup r
 * @brief Get if a sequence of Bytes is a suffix of a Byte buffer.
 * @param self A pointer to the Byte buffer.
 * @param bytes A pointer to an array of @a numberOfBytes Bytes.
 * @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
 * @return
 * R_BooleanValue_True if the sequence of Bytes is a suffix of the string buffer.
 * R_BooleanValue_False otherwise.
 */
R_BooleanValue
R_ByteBuffer_endsWith_pn
  (
    R_ByteBuffer* self,
    char const* bytes,
    R_SizeValue numberOfBytes
  );

/**
 * @ingroup r
 * @brief Get if the specified sequence of Bytes is a prefix of a Byte buffer.
 * @param self A pointer to the Byte buffer.
 * @param bytes A pointer to an array of @a numberOfBytes Bytes.
 * @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
 * @return
 * R_BooleanValue_True if the sequence of Bytes is a prefix of the Byte buffer.
 * R_BooleanValue_False otherwise.
 */
R_BooleanValue
R_ByteBuffer_startsWith_pn
  (
    R_ByteBuffer* self,
    char const* bytes,
    R_SizeValue numberOfBytes
  );

/**
 * @ingroup r
 * @brief Append Bytes to a Byte buffer.
 * @param self A pointer to this Byte buffer.
 * @param bytes A pointer to the array of Bytes.
 * @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
 * @error R_Status_ArgumentValueInvalid @a bytes is a null pointer
 * @error R_Status_AllocationFailed an allocation failed
 */
void
R_ByteBuffer_append_pn
  (
    R_ByteBuffer* self,
    char const* bytes,
    R_SizeValue numberOfBytes
  );

/**
 * @ingroup r
 * @brief Prepend Bytes to this Byte buffer.
 * @param self A pointer to this Byte buffer.
 * @param bytes A pointer to the array of Bytes.
 * @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
 * @error R_Status_ArgumentValueInvalid @a bytes is a null pointer
 * @error R_Status_AllocationFailed an allocation failed
 */
void
R_ByteBuffer_insert_pn
  (
    R_ByteBuffer* self,
    R_SizeValue index,
    char const* bytes,
    R_SizeValue numberOfBytes
  );

/**
 * @ingroup r
 * @brief Compare this Byte buffer with another Byte buffer for equality.
 * @param self A pointer to this Byte buffer.
 * @param other A pointer to the other Byte buffer.
 * @return R_BooleanValue_True if @a self is equal to @a other. R_BooleanValue_False otherwise.
 */
R_BooleanValue
R_ByteBuffer_isEqualTo
  (
    R_ByteBuffer const* self,
    R_ByteBuffer const* other
  );

/**
 * @ingroup r
 * @brief Set the number of Bytes in a Byte buffer to zero.
 * @param self A pointer to this Byte buffer.
 */
void
R_ByteBuffer_clear
  (
    R_ByteBuffer* self
  );

#endif // R_BYTEBUFFER_H_INCLUDED
