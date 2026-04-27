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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRINGEXTENSIONS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRINGEXTENSIONS_H_INCLUDED

#if !defined(ARCADIA_RING1_MODULE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif
#include "Arcadia/Ring1/Implementation/ImmutableUTF8String.h"
#include "Arcadia/Ring1/Implementation/Value.h"

/// @brief Get the first occurence of a code point in a string.
/// @param thread A pointer to this thread.
/// @param self A pointer to this string.
/// @param codePoint the code point.
/// @return An Arcadia.Size value denoting the zero-based code point index from the start of the string if the code point was found, Arcadia.Void otherwise.
Arcadia_Value
Arcadia_ImmutableUTF8String_findFirstOccurrence
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUTF8String* self,
    Arcadia_Natural32Value codePoint
  );

/// @brief Get the first occurence of a code point in a string.
/// @param thread A pointer to this thread.
/// @param self A pointer to this string.
/// @param codePoint the code point.
/// @return An Arcadia.Size value denoting the zero-based code point index from the start of the string if the code point was found, Arcadia.Void otherwise.
Arcadia_Value
Arcadia_ImmutableUTF8String_findLastOccurrence
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUTF8String* self,
    Arcadia_Natural32Value codePoint
  );

/// @brief Create an empty string.
/// @param thread A pointer to this thread.
/// @return A pointer to the string.
Arcadia_ImmutableUTF8String*
Arcadia_ImmutableUTF8String_createEmpty
  (
    Arcadia_Thread* thread
  );

/// @brief Create a string that is a substring of the specified string.
/// @param start The code point index of at which the substring starts at.
/// @param length The length, in code points, of the substring as a Arcadia_SizeValue or an Arcadia_Void value.
/// @return A pointer to the substring.
Arcadia_ImmutableUTF8String*
Arcadia_ImmutableUTF8String_substring
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUTF8String* self,
    Arcadia_SizeValue start,
    Arcadia_Value length
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRINGEXTENSIONS_H_INCLUDED
