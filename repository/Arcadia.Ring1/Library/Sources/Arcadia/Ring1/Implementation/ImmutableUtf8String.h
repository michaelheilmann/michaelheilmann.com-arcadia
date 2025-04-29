// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2025-02-16

#if !defined(ARCADIA_RING1_IMMUTABLEUTF8STRING_H_INCLUDED)
#define ARCADIA_RING1_IMMUTABLEUTF8STRING_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"
#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Void.h"
typedef struct Arcadia_Process Arcadia_Process;

typedef struct Arcadia_ImmutableUtf8String Arcadia_ImmutableUtf8String;

typedef Arcadia_ImmutableUtf8String* Arcadia_ImmutableUtf8StringValue;

struct Arcadia_ImmutableUtf8String {
  Arcadia_SizeValue hash;
  Arcadia_SizeValue numberOfBytes;
  Arcadia_Natural8Value bytes[];
};

/// @brief Create an immutable UTF8 string object from an UTF8 string.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param bytes A pointer to a sequence of @a numberOfBytes Bytes.
/// @param numberOfBytes The number of Bytes in the sequence of Bytes pointed to by @a bytes.
/// @return A pointer to the immmutable UTF8 string object.
/// @error #Arcadia_Status_ArgumentInvalid @a bytes ia null pointer
/// @error #Arcadia_Status_ArgumentInvalid the sequence of Bytes is an UTF8 string
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Boolean value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param booleanValue The Arcadia_Boolean value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue booleanValue
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Integer16 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param integer16Value The Arcadia_Integer16 value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Integer32 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param integer32Value The Arcadia_Integer32 value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Integer64 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param integer64Value The Arcadia_Integer64 value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Integer8 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param integer8Value The Arcadia_Integer8 value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Natural16 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param natural16Value The Arcadia_Natural16 value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Natural32 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param natural32Value The Arcadia_Natural32 value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Natural64 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param natural64Value The Arcadia_Natural64 value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Natural8 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param natural8Value The Arcadia_Natural8 value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  );

/// @brief Create an immutable UTF8 string object from Arcadia_Boolean value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param voidValue The Arcadia_Void value.
/// @return A pointer to the immmutable UTF8 string object.
Arcadia_ImmutableUtf8String*
Arcadia_ImmutableUtf8String_createFromVoid
  (
    Arcadia_Thread* thread,
    Arcadia_VoidValue voidValue
  );

/// @brief Visit this immutable UTF8 string object.
/// @param self A pointer to this immutable UTF8 string object. 
void
Arcadia_ImmutableUtf8String_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Get a pointer to the Bytes of this immutable UTF8 string object.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object. 
/// @return A pointer to the Bytes of this immutable UTF8 stirng object.
/// @warning The Bytes of the array must not be modified.
Arcadia_Natural8Value const*
Arcadia_ImmutableUtf8String_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Get the number of Bytes in this immutable UTF8 string object.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object. 
/// @return The number of Bytes in this immutable UTF8 string object.
Arcadia_SizeValue
Arcadia_ImmutableUtf8String_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Get the hash of this immutable UTF8 string object.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The hash of this immutable UTF8 string object.
Arcadia_SizeValue
Arcadia_ImmutableUtf8String_getHash
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into a Boolean value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Boolean value.
/// @error #Arcadia_Status_ConversionFailed the string is not a Boolean literal
Arcadia_BooleanValue
Arcadia_ImmutableUtf8String_toBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into an Integer16 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Integer16 value.
/// @error #Arcadia_Status_ConversionFailed the string is not an Integer16 literal
Arcadia_Integer16Value
Arcadia_ImmutableUtf8String_toInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into an Integer32 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Integer32 value.
/// @error #Arcadia_Status_ConversionFailed the string is not an Integer32 literal
Arcadia_Integer32Value
Arcadia_ImmutableUtf8String_toInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into an Integer64 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Integer64 value.
/// @error #Arcadia_Status_ConversionFailed the string is not an Integer64 literal
Arcadia_Integer64Value
Arcadia_ImmutableUtf8String_toInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into an Integer8 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Integer8 value.
/// @error #Arcadia_Status_ConversionFailed the string is not an Integer8 literal
Arcadia_Integer8Value
Arcadia_ImmutableUtf8String_toInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into an Natural16 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Natural16 value.
/// @error #Arcadia_Status_ConversionFailed the string is not an Natural16 literal
Arcadia_Natural16Value
Arcadia_ImmutableUtf8String_toNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into an Natural32 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Natural32 value.
/// @error #Arcadia_Status_ConversionFailed the string is not an Natural32 literal
Arcadia_Natural32Value
Arcadia_ImmutableUtf8String_toNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into an Natural64 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Natural64 value.
/// @error #Arcadia_Status_ConversionFailed the string is not an Natural64 literal
Arcadia_Natural64Value
Arcadia_ImmutableUtf8String_toNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into an Natural8 value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Natural8 value.
/// @error #Arcadia_Status_ConversionFailed the string is not an Natural8 literal
Arcadia_Natural8Value
Arcadia_ImmutableUtf8String_toNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @brief Convert this immutable UTF8 string object into a Void value.
/// @param thread A pointer to the Arcadia_Thread object.
/// @param self A pointer to this immutable UTF8 string object.
/// @return The Void value.
/// @error #Arcadia_Status_ConversionFailed the string is not a Void literal
Arcadia_VoidValue
Arcadia_ImmutableUtf8String_toVoid
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8StringValue self
  );

/// @return A pointer to an "foreign value" type of name "Arcadia.ImmutableUtf8String".
Arcadia_TypeValue
_Arcadia_ImmutableUtf8StringValue_getType
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING1_IMMUTABLEUTF8STRING_H_INCLUDED

