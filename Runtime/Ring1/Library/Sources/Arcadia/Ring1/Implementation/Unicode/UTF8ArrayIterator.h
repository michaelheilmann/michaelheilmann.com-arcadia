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

#if !defined (ARCADIA_RING1_UNICODE_UTF8ARRAYITERATOR_MODULE_H_INCLUDED)
#define ARCADIA_RING1_UNICODE_UTF8ARRAYITERATOR_MODULE_H_INCLUDED

#if !defined(ARCADIA_RING1_MODULE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Unicode/UTF8.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Status.h"
#include "Arcadia/Ring1/Implementation/Thread.h"

#define CodePoint_Start (Arcadia_Unicode_CodePoint_Last + 1)
#define CodePoint_End (Arcadia_Unicode_CodePoint_Last + 2)
#define CodePoint_Error (Arcadia_Unicode_CodePoint_Last + 3)

/// @brief Error detecting UTF8 decoder using a struct to be allocated on the stack and as part of other objects.
typedef struct _Arcadia_UTF8ArrayIterator {
  /// @brief Pointer to the array of Bytes.
  const Arcadia_Natural8Value* p;
  /// @brief The number of Bytes in the array pointed to by @a p.
  Arcadia_SizeValue n;

  /// The index of the Byte at which the current code point starts at.
  /// @a 0 if codePoint is CodePoint_Start.
  Arcadia_SizeValue byteIndex;
  /// @brief The index of the code point at which the current code point starts at.
  /// @a 0 if codePoint is CodePoint_Start.
  Arcadia_SizeValue codePointIndex;
  
  /// The length, in Bytes, of the current code point.
  /// @a 0 if codePoint is CodePoint_Start or CodePoint_Error. Not @a 0 otherwise.
  Arcadia_SizeValue numberOfBytes;
  /// The current code point.
  /// If this is CodePoint_Error, then numberOfBytes is 0.
  Arcadia_Natural32Value codePoint;

} _Arcadia_UTF8ArrayIterator;

static inline void
_Arcadia_UTF8ArrayIterator_initialize
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self,
    const Arcadia_Natural8Value* p,
    const Arcadia_SizeValue n
  );

static inline void
_Arcadia_UTF8ArrayIterator_uninitialize
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  );

static inline void
_Arcadia_UTF8ArrayIterator_next
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  );
  
static inline Arcadia_BooleanValue
_Arcadia_UTF8ArrayIterator_hasError
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  );
  
static inline Arcadia_BooleanValue
_Arcadia_UTF8ArrayIterator_hasCodePoint
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  );

static inline Arcadia_SizeValue
_Arcadia_UTF8ArrayIterator_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  );

static inline Arcadia_Natural32Value
_Arcadia_UTF8ArrayIterator_getCodePoint
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  );

static inline void
_Arcadia_UTF8ArrayIterator_initialize
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self,
    const Arcadia_Natural8Value* p,
    const Arcadia_SizeValue n
  )
{
  if (!self || !p || Arcadia_SizeValue_Maximum == n) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->p = p;
  self->n = n;
  self->codePointIndex = 0;
  self->byteIndex = 0;
  self->numberOfBytes = 0;
  self->codePoint = CodePoint_Start;
}

static inline void
_Arcadia_UTF8ArrayIterator_uninitialize
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static inline void
_Arcadia_UTF8ArrayIterator_next
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  )
{
  if (!self || self->codePoint == CodePoint_End || self->codePoint == CodePoint_Error) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (self->byteIndex + self->numberOfBytes == self->n) {
    self->codePoint = CodePoint_End;
    return;
  }
  Arcadia_SizeValue nextByteIndex,
                    nextCodePointIndex;
  if (self->codePoint == CodePoint_Start) {
    nextByteIndex = self->byteIndex;
    nextCodePointIndex = self->codePointIndex;
  } else {
    nextByteIndex = self->byteIndex + self->numberOfBytes;
    nextCodePointIndex = self->codePointIndex + 1;
  }
  Arcadia_Natural8Value byte = self->p[nextByteIndex];
  Arcadia_SizeValue nextNumberOfBytes = 0;
  Arcadia_Natural32Value nextCodePoint = 0;
  if ((byte & 0x80) == 0x00) {
    // To determine if the first Byte is in the range 0xxx xxxx,
    // mask the Byte with 1000 0000 / 0x80. If the result is 0,
    // then the first Byte is in the range 0xxx xxxx.
    nextNumberOfBytes = 1;
  } else if ((byte & 0xE0) == 0xC0) {
    // To determine if the first Byte is in the range 110x xxxx,
    // mask the Byte with 11100000 / 0xE0. If the result is 1100 0000 / 0xC0,
    // then the first Byte is in the range 110x xxxx.
    nextNumberOfBytes = 2;
  } else if ((byte & 0xF0) == 0xE0) {
    // To determine if the first Byte is in the range 1110 xxxx,
    // mask the Byte with 1111 0000 / 0xF0. If the result is 1110 0000 / 0xE0,
    // then the first Byte is in the range 1110 xxxx.
    nextNumberOfBytes = 3;
  } else if ((byte & 0xF8) == 0xF0) {
    // To determine if the first Byte is in the range 1111 0xxx,
    // mask the Byte with 1111 1000 / 0xF8. If the result is 1111 0000 / 0xF0,
    // then the first Byte is in th range 1111 0xxx.
    nextNumberOfBytes = 4;
  } else {
    nextCodePoint = CodePoint_Error; // (*)
    nextNumberOfBytes = 0;
  }
  if (self->n - nextByteIndex < nextNumberOfBytes) {
    nextCodePoint = CodePoint_Error; // (*)
    nextNumberOfBytes = 0;
  }

  // The masks to remove the prefix bits from the first Byte.
  static const Arcadia_Natural8Value mask[] = {
    0b11111111,
    0b00011111,
    0b00001111,
    0b00000111,
  };

  if (nextCodePoint != CodePoint_Error) {
    nextCodePoint = byte & mask[nextNumberOfBytes - 1]; // Warning that nextNumberOfBytes - 1 might yield -1 can be ignored because of (*). 
    for (Arcadia_SizeValue i = 1; i < nextNumberOfBytes; ++i) {
      byte = self->p[nextByteIndex + i]; // We need to mask with 0011 1111
      if (0x80 != (byte & 0xC0)) {
        nextCodePoint = CodePoint_Error;
        nextNumberOfBytes = 0;
        break;
      }
      byte &= 0x3F;
      nextCodePoint <<= 6;
      nextCodePoint |= byte;
    }
  }
  if (nextNumberOfBytes == 1 && nextCodePoint <= 0x7f) {
  } else if (nextNumberOfBytes == 2 && 0x80 <= nextCodePoint && nextCodePoint <= 0x7ff) {
  } else if (nextNumberOfBytes == 3 && 0x800 <= nextCodePoint && nextCodePoint <= 0xffff) {
  } else if (nextNumberOfBytes == 4 && 0x10000 <= nextCodePoint && nextCodePoint > 0x10ffff) {
  } else {
    nextCodePoint = CodePoint_Error;
    nextNumberOfBytes = 0;
  }
  
  self->byteIndex = nextByteIndex;
  self->numberOfBytes = nextNumberOfBytes;
  self->codePointIndex = nextCodePointIndex;
  self->codePoint = nextCodePoint;
}

static inline Arcadia_SizeValue
_Arcadia_UTF8ArrayIterator_getCodePointIndex
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->codePointIndex;  
}

static inline Arcadia_SizeValue
_Arcadia_UTF8ArrayIterator_getByteIndex
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->byteIndex;
}

static inline Arcadia_BooleanValue
_Arcadia_UTF8ArrayIterator_hasCodePoint
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (self->codePoint == CodePoint_Start) {
    _Arcadia_UTF8ArrayIterator_next(thread, self);
  }
  return CodePoint_End != self->codePoint && CodePoint_Error != self->codePoint;
}

static inline Arcadia_BooleanValue
_Arcadia_UTF8ArrayIterator_hasError
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  )
{ 
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (self->codePoint == CodePoint_Start) {
    _Arcadia_UTF8ArrayIterator_next(thread, self);
  }
  return CodePoint_Error == self->codePoint;
}

static inline Arcadia_SizeValue
_Arcadia_UTF8ArrayIterator_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->numberOfBytes;  
}

static inline Arcadia_Natural32Value
_Arcadia_UTF8ArrayIterator_getCodePoint
  (
    Arcadia_Thread* thread,
    _Arcadia_UTF8ArrayIterator* self
  )
{
  if (self->codePoint == CodePoint_Error || self->codePoint == CodePoint_Start || self->codePoint == CodePoint_End) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->codePoint;
}

#endif // ARCADIA_RING1_UNICODE_UTF8ARRAYITERATOR_MODULE_H_INCLUDED
