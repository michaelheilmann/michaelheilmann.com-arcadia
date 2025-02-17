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

// Last modified: 2024-09-28

#include "R/CommandLine/Include.h"

#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/Implementation/Utf8ByteBufferWriter.h"

#include <stdio.h>

static Arcadia_BooleanValue
isEnd
  (
    Arcadia_Process* process,
    Arcadia_Utf8Reader* reader
  )
{ return !Arcadia_Utf8Reader_hasCodePoint(process, reader); }

static Arcadia_BooleanValue
isEqual
  (
    Arcadia_Process* process,
    Arcadia_Utf8Reader* reader
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  return '=' == Arcadia_Utf8Reader_getCodePoint(process, reader);
}

static Arcadia_BooleanValue
isEqualOrEnd
  (
    Arcadia_Process* process,
    Arcadia_Utf8Reader* reader
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(process, reader)) {
    return Arcadia_BooleanValue_True;
  }
  return '=' == Arcadia_Utf8Reader_getCodePoint(process, reader);
}

Arcadia_BooleanValue
Arcadia_CommandLine_parseArgument
  (
    Arcadia_Process* process,
    Arcadia_Utf8Reader* reader,
    Arcadia_String** key,
    Arcadia_String** value
  )
{
  Arcadia_String* value1 = NULL, *key1 = NULL;
  Arcadia_Value temporaryValue;
  Arcadia_ByteBuffer* writerByteBuffer = Arcadia_ByteBuffer_create(process);
  Arcadia_Utf8Writer* writer = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, writerByteBuffer);
  // '--'
  if (!Arcadia_Utf8Reader_hasCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('-' != Arcadia_Utf8Reader_getCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Utf8Reader_next(process, reader);
  if (!Arcadia_Utf8Reader_hasCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('-' != Arcadia_Utf8Reader_getCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Utf8Reader_next(process, reader);
  // <value>
  if (isEqualOrEnd(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  do {
    Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(process, reader);
    Arcadia_Utf8Writer_writeCodePoints(process, writer, &codePoint, 1);
    Arcadia_Utf8Reader_next(process, reader);
  } while (!isEqualOrEnd(process, reader));
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)writerByteBuffer);
  key1 = Arcadia_String_create(process, temporaryValue);
  Arcadia_ByteBuffer_clear(process, writerByteBuffer);
  if (isEnd(process, reader)) {
    return Arcadia_BooleanValue_True;
  }
  // ('=' <value>)?
  if (!isEqual(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Utf8Reader_next(process, reader);
  if (isEnd(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  do {
    Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(process, reader);
    Arcadia_Utf8Writer_writeCodePoints(process, writer, &codePoint, 1);
    Arcadia_Utf8Reader_next(process, reader);
  } while (!isEnd(process, reader));
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)writerByteBuffer);
  value1 = Arcadia_String_create(process, temporaryValue);
  Arcadia_ByteBuffer_clear(process, writerByteBuffer);
  *key = key1;
  *value = value1;
  return Arcadia_BooleanValue_True;
}

void
Arcadia_CommandLine_raiseRequiredArgumentMissingError
  (
    Arcadia_Process* process,
    Arcadia_String* key
  )
{
  fwrite(u8"required command-line argument `", 1, sizeof(u8"unkown command-line argument `") - 1, stdout);
  fwrite(Arcadia_String_getBytes(process, key), 1, Arcadia_String_getNumberOfBytes(process, key), stdout);
  fwrite(u8"` not specified", 1, sizeof(u8"` not specified") - 1, stdout);
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}

void
Arcadia_CommandLine_raiseUnknownArgumentError
  (
    Arcadia_Process* process,
    Arcadia_String* key,
    Arcadia_String* value
  )
{
  fwrite(u8"unknown command-line argument `", 1, sizeof(u8"unkown command-line argument `") - 1, stdout);
  fwrite(Arcadia_String_getBytes(process, key), 1, Arcadia_String_getNumberOfBytes(process, key), stdout);
  fwrite(u8"`", 1, sizeof(u8"`") - 1, stdout);
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}

void
Arcadia_CommandLine_raiseNoValueError
  (
    Arcadia_Process* process,
    Arcadia_String* key
  )
{
  fwrite(u8"value specified for command-line argument `", 1, sizeof(u8"value specified for command-line argument `") - 1, stdout);
  fwrite(Arcadia_String_getBytes(process, key), 1, Arcadia_String_getNumberOfBytes(process, key), stdout);
  fwrite(u8"` is not valid", 1, sizeof(u8"` is not valid") - 1, stdout);
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}

void
Arcadia_CommandLine_raiseValueInvalidError
  (
    Arcadia_Process* process,
    Arcadia_String* key,
    Arcadia_String* value
  )
{
  fwrite(u8"value specified for command-line argument `", 1, sizeof(u8"value specified for command-line argument `") - 1, stdout);
  fwrite(Arcadia_String_getBytes(process, key), 1, Arcadia_String_getNumberOfBytes(process, key), stdout);
  fwrite(u8"` is not valid", 1, sizeof(u8"` is not valid") - 1, stdout);
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}
