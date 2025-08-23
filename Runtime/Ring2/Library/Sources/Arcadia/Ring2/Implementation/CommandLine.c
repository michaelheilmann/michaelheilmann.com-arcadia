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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Implementation/CommandLine.h"

#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/Implementation/Utf8ByteBufferWriter.h"

#include <stdio.h>

static Arcadia_BooleanValue
isEnd
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* reader
  )
{ return !Arcadia_Utf8Reader_hasCodePoint(thread, reader); }

static Arcadia_BooleanValue
isEqual
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* reader
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  return '=' == Arcadia_Utf8Reader_getCodePoint(thread, reader);
}

static Arcadia_BooleanValue
isEqualOrEnd
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* reader
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_True;
  }
  return '=' == Arcadia_Utf8Reader_getCodePoint(thread, reader);
}

static Arcadia_String*
parseString 
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* reader,
    Arcadia_Utf8Writer* writer,
    Arcadia_ByteBuffer* writerByteBuffer
  )
{
  Arcadia_Natural32Value codePoint;
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, reader)) {
    return NULL;
  }
  codePoint = Arcadia_Utf8Reader_getCodePoint(thread, reader);
  if (codePoint != '"') {
    return NULL;
  }
  Arcadia_Utf8Reader_next(thread, reader);
  Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
  while (Arcadia_BooleanValue_True) {
    codePoint = Arcadia_Utf8Reader_getCodePoint(thread, reader);
    if (lastWasSlash) {
      switch (codePoint) {
        case 'r': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '\r';
          Arcadia_Utf8Reader_next(thread, reader);
          Arcadia_Utf8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case 'n': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '\n';
          Arcadia_Utf8Reader_next(thread, reader);
          Arcadia_Utf8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case 'v': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '\v';
          Arcadia_Utf8Reader_next(thread, reader);
          Arcadia_Utf8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case 't': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '\t';
          Arcadia_Utf8Reader_next(thread, reader);
          Arcadia_Utf8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case '"': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '"';
          Arcadia_Utf8Reader_next(thread, reader);
          Arcadia_Utf8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case '\\': {
          lastWasSlash = Arcadia_BooleanValue_False;
          Arcadia_Utf8Reader_next(thread, reader);
          Arcadia_Utf8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        default: {
          return NULL;
        }
      };
    } else {
      if (codePoint == '"') {
        Arcadia_Utf8Reader_next(thread, reader);
        break;
      } else if (codePoint == '\\') {
        Arcadia_Utf8Reader_next(thread, reader);
        lastWasSlash = Arcadia_BooleanValue_True;
      } else {
        Arcadia_Utf8Reader_next(thread, reader);
        Arcadia_Utf8Writer_writeCodePoints(thread, writer, &codePoint, 1);
      }

    }
  }

  Arcadia_Value temporaryValue;
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)writerByteBuffer);
  Arcadia_String* resultString = Arcadia_String_create(thread, temporaryValue);

  return resultString;
}

Arcadia_BooleanValue
Arcadia_CommandLine_parseArgument
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* reader,
    Arcadia_String** key,
    Arcadia_String** value
  )
{
  Arcadia_String* value1 = NULL, *key1 = NULL;
  Arcadia_Value temporaryValue;
  Arcadia_ByteBuffer* writerByteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_Utf8Writer* writer = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, writerByteBuffer);
  // '--'
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('-' != Arcadia_Utf8Reader_getCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Utf8Reader_next(thread, reader);
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('-' != Arcadia_Utf8Reader_getCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Utf8Reader_next(thread, reader);
  // <name>
  if (isEqualOrEnd(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  do {
    Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(thread, reader);
    Arcadia_Utf8Writer_writeCodePoints(thread, writer, &codePoint, 1);
    Arcadia_Utf8Reader_next(thread, reader);
  } while (!isEqualOrEnd(thread, reader));
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)writerByteBuffer);
  key1 = Arcadia_String_create(thread, temporaryValue);
  Arcadia_ByteBuffer_clear(thread, writerByteBuffer);
  if (isEnd(thread, reader)) {
    *key = key1;
    *value = NULL;
    return Arcadia_BooleanValue_True;
  }
  // '=' <value>
  if (!isEqual(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Utf8Reader_next(thread, reader);
  value1 = parseString(thread, reader, writer, writerByteBuffer);
  if (!value1) {
    return Arcadia_BooleanValue_False;
  }
  if (!isEnd(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  *key = key1;
  *value = value1;
  return Arcadia_BooleanValue_True;
}

void
Arcadia_CommandLine_raiseRequiredArgumentMissingError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  )
{
  fwrite(u8"required command-line argument `", 1, sizeof(u8"unkown command-line argument `") - 1, stdout);
  fwrite(Arcadia_String_getBytes(thread, key), 1, Arcadia_String_getNumberOfBytes(thread, key), stdout);
  fwrite(u8"` not specified\n", 1, sizeof(u8"` not specified\n") - 1, stdout);
  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

void
Arcadia_CommandLine_raiseUnknownArgumentError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key,
    Arcadia_String* value
  )
{
  fwrite(u8"unknown command-line argument `", 1, sizeof(u8"unkown command-line argument `") - 1, stdout);
  fwrite(Arcadia_String_getBytes(thread, key), 1, Arcadia_String_getNumberOfBytes(thread, key), stdout);
  fwrite(u8"`\n", 1, sizeof(u8"`\n") - 1, stdout);
  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

void
Arcadia_CommandLine_raiseNoValueError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  )
{
  fwrite(u8"value specified for command-line argument `", 1, sizeof(u8"value specified for command-line argument `") - 1, stdout);
  fwrite(Arcadia_String_getBytes(thread, key), 1, Arcadia_String_getNumberOfBytes(thread, key), stdout);
  fwrite(u8"` is not valid\n", 1, sizeof(u8"` is not valid\n") - 1, stdout);
  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

void
Arcadia_CommandLine_raiseValueInvalidError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key,
    Arcadia_String* value
  )
{
  fwrite(u8"value specified for command-line argument `", 1, sizeof(u8"value specified for command-line argument `") - 1, stdout);
  fwrite(Arcadia_String_getBytes(thread, key), 1, Arcadia_String_getNumberOfBytes(thread, key), stdout);
  fwrite(u8"` is not valid", 1, sizeof(u8"` is not valid") - 1, stdout);
  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}
