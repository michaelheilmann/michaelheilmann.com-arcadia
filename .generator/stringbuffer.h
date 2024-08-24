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

#if !defined(GENERATOR_STRINGBUFFER_H_INCLUDED)
#define GENERATOR_STRINGBUFFER_H_INCLUDED

#include "configure.h"
#include "arcadia/r1.h"

#include <stddef.h>

typedef struct StringBuffer StringBuffer;

void _StringBuffer_registerType();

struct StringBuffer {
  char* p;
  size_t sz;
  size_t cp;
};

/**
 * @ingroup r
 * @brief Create a string buffer.
 * @return The string buffer.
 * @remarks The string buffer is empty.
 */
StringBuffer*
StringBuffer_create
  (
  );

/**
 * @ingroup r
 * @brief Get if a sequence of Bytes is a suffix of a string buffer.
 * @param w A pointer to the string buffer.
 * @param bytes A pointer to an array of @a numberOfBytes Bytes.
 * @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
 * @return
 * R_BooleanValue_True if the sequence of Bytes is a suffix of the string buffer.
 * R_BooleanValue_False otherwise.
 */
R_BooleanValue
StringBuffer_endsWith_pn
  (
    StringBuffer* w,
    char const* bytes,
    size_t numberOfBytes
  );

/**
 * @ingroup r
 * @brief Get if the specified sequence of Bytes is a prefix of a string buffer.
 * @param w A pointer to the string buffer.
 * @param bytes A pointer to an array of @a numberOfBytes Bytes.
 * @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
 * @return
 * R_BooleanValue_True if the sequence of Bytes is a prefix of the string buffer.
 * R_BooleanValue_False otherwise.
 */
R_BooleanValue
StringBuffer_startsWith_pn
  (
    StringBuffer* w,
    char const* bytes,
    size_t numberOfBytes
  );

/**
 * @ingroup r
 * @brief Append Bytes to a string buffer.
 * @param w A pointer to the string buffer.
 * @param bytes A pointer to the array of Bytes.
 * @param numberOfBytes The number of Bytes in the array pointed to by @a bytes.
 */
void
StringBuffer_append_pn
  (
    StringBuffer* w,
    char const* bytes,
    size_t numberOfBytes
  );

/**
 * @ingroup r
 * @brief Compare two string buffers for equality.
 * @param v The first string buffer.
 * @param w The second string buffer.
 * @return R_BooleanValue_True if @a x is equal to @a y. R_BooleanValue_False otherwise.
 */
R_BooleanValue
StringBuffer_areEqual
  (
    StringBuffer* v,
    StringBuffer* w
  );

/**
 * @ingroup r
 * @brief Set the number of characters in a string buffer to zero.
 * @param w A pointer to the string buffer.
 */
void
StringBuffer_clear
  (
    StringBuffer* w
  );

#endif // GENERATOR_STRINGBUFFER_H_INCLUDED
