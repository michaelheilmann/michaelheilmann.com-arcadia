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

#include "R/ByteBuffer.h"
#include "R/Utf8ByteBufferWriter.h"

#include <stdio.h>

static Arcadia_BooleanValue
isEnd
  (
    Arcadia_Process* process,
    R_Utf8Reader* reader
  )
{ return !R_Utf8Reader_hasCodePoint(process, reader); }

static Arcadia_BooleanValue
isEqual
  (
    Arcadia_Process* process,
    R_Utf8Reader* reader
  )
{
  if (!R_Utf8Reader_hasCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  return '=' == R_Utf8Reader_getCodePoint(process, reader);
}

static Arcadia_BooleanValue
isEqualOrEnd
  (
    Arcadia_Process* process,
    R_Utf8Reader* reader
  )
{
  if (!R_Utf8Reader_hasCodePoint(process, reader)) {
    return Arcadia_BooleanValue_True;
  }
  return '=' == R_Utf8Reader_getCodePoint(process, reader);
}

Arcadia_BooleanValue
R_CommandLine_parseArgument
  (
    Arcadia_Process* process,
    R_Utf8Reader* reader,
    R_String** key,
    R_String** value
  )
{
  R_String* value1 = NULL, *key1 = NULL;
  R_Value temporaryValue;
  R_ByteBuffer* writerByteBuffer = R_ByteBuffer_create(process);
  R_Utf8Writer* writer = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(process, writerByteBuffer);
  // '--'
  if (!R_Utf8Reader_hasCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('-' != R_Utf8Reader_getCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  R_Utf8Reader_next(process, reader);
  if (!R_Utf8Reader_hasCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('-' != R_Utf8Reader_getCodePoint(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  R_Utf8Reader_next(process, reader);
  // <value>
  if (isEqualOrEnd(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  do {
    Arcadia_Natural32Value codePoint = R_Utf8Reader_getCodePoint(process, reader);
    R_Utf8Writer_writeCodePoints(process, writer, &codePoint, 1);
    R_Utf8Reader_next(process, reader);
  } while (!isEqualOrEnd(process, reader));
  R_Value_setObjectReferenceValue(&temporaryValue, (R_ObjectReferenceValue)writerByteBuffer);
  key1 = R_String_create(process, temporaryValue);
  R_ByteBuffer_clear(writerByteBuffer);
  if (isEnd(process, reader)) {
    return Arcadia_BooleanValue_True;
  }
  // ('=' <value>)?
  if (!isEqual(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  R_Utf8Reader_next(process, reader);
  if (isEnd(process, reader)) {
    return Arcadia_BooleanValue_False;
  }
  do {
    Arcadia_Natural32Value codePoint = R_Utf8Reader_getCodePoint(process, reader);
    R_Utf8Writer_writeCodePoints(process, writer, &codePoint, 1);
    R_Utf8Reader_next(process, reader);
  } while (!isEnd(process, reader));
  R_Value_setObjectReferenceValue(&temporaryValue, (R_ObjectReferenceValue)writerByteBuffer);
  value1 = R_String_create(process, temporaryValue);
  R_ByteBuffer_clear(writerByteBuffer);
  *key = key1;
  *value = value1;
  return Arcadia_BooleanValue_True;
}

void
R_CommandLine_raiseRequiredArgumentMissingError
  (
    Arcadia_Process* process,
    R_String* key
  )
{
  fwrite(u8"required command-line argument `", 1, sizeof(u8"unkown command-line argument `") - 1, stdout);
  fwrite(R_String_getBytes(key), 1, R_String_getNumberOfBytes(key), stdout);
  fwrite(u8"` not specified", 1, sizeof(u8"` not specified") - 1, stdout);
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}

void
R_CommandLine_raiseUnknownArgumentError
  (
    Arcadia_Process* process,
    R_String* key,
    R_String* value
  )
{
  fwrite(u8"unknown command-line argument `", 1, sizeof(u8"unkown command-line argument `") - 1, stdout);
  fwrite(R_String_getBytes(key), 1, R_String_getNumberOfBytes(key), stdout);
  fwrite(u8"`", 1, sizeof(u8"`") - 1, stdout);
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}

void
R_CommandLine_raiseNoValueError
  (
    Arcadia_Process* process,
    R_String* key
  )
{
  fwrite(u8"value specified for command-line argument `", 1, sizeof(u8"value specified for command-line argument `") - 1, stdout);
  fwrite(R_String_getBytes(key), 1, R_String_getNumberOfBytes(key), stdout);
  fwrite(u8"` is not valid", 1, sizeof(u8"` is not valid") - 1, stdout);
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}

void
R_CommandLine_raiseValueInvalidError
  (
    Arcadia_Process* process,
    R_String* key,
    R_String* value
  )
{
  fwrite(u8"value specified for command-line argument `", 1, sizeof(u8"value specified for command-line argument `") - 1, stdout);
  fwrite(R_String_getBytes(key), 1, R_String_getNumberOfBytes(key), stdout);
  fwrite(u8"` is not valid", 1, sizeof(u8"` is not valid") - 1, stdout);
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}
