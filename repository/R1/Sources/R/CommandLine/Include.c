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

// Last modified: 2024-09-28

#include "R/CommandLine/Include.h"

#include "R/ByteBuffer.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Utf8ByteBufferWriter.h"

#include <stdio.h>

static R_BooleanValue
isEnd
  (
    R_Utf8Reader* reader
  )
{ return !R_Utf8Reader_hasCodePoint(reader); }

static R_BooleanValue
isEqual
  (
    R_Utf8Reader* reader
  )
{
  if (!R_Utf8Reader_hasCodePoint(reader)) {
    return R_BooleanValue_False;
  }
  return '=' == R_Utf8Reader_getCodePoint(reader);
}

static R_BooleanValue
isEqualOrEnd
  (
    R_Utf8Reader* reader
  )
{
  if (!R_Utf8Reader_hasCodePoint(reader)) {
    return R_BooleanValue_True;
  }
  return '=' == R_Utf8Reader_getCodePoint(reader);
}

R_BooleanValue
R_CommandLine_parseArgument
  (
    R_Utf8Reader* reader,
    R_String** key,
    R_String** value
  )
{
  R_String* value1 = NULL, *key1 = NULL;
  R_Value temporaryValue;
  R_ByteBuffer* writerByteBuffer = R_ByteBuffer_create();
  R_Utf8Writer* writer = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(writerByteBuffer);
  // '--'
  if (!R_Utf8Reader_hasCodePoint(reader)) {
    return R_BooleanValue_False;
  }
  if ('-' != R_Utf8Reader_getCodePoint(reader)) {
    return R_BooleanValue_False;
  }
  R_Utf8Reader_next(reader);
  if (!R_Utf8Reader_hasCodePoint(reader)) {
    return R_BooleanValue_False;
  }
  if ('-' != R_Utf8Reader_getCodePoint(reader)) {
    return R_BooleanValue_False;
  }
  R_Utf8Reader_next(reader);
  // <value>
  if (isEqualOrEnd(reader)) {
    return R_BooleanValue_False;
  }
  do {
    R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(reader);
    R_Utf8Writer_writeCodePoints(writer, &codePoint, 1);
    R_Utf8Reader_next(reader);
  } while (!isEqualOrEnd(reader));
  R_Value_setObjectReferenceValue(&temporaryValue, (R_ObjectReferenceValue)writerByteBuffer);
  key1 = R_String_create(temporaryValue);
  R_ByteBuffer_clear(writerByteBuffer);
  if (isEnd(reader)) {
    return R_BooleanValue_True;
  }
  // ('=' <value>)?
  if (!isEqual(reader)) {
    return R_BooleanValue_False;
  }
  R_Utf8Reader_next(reader);
  if (isEnd(reader)) {
    return R_BooleanValue_False;
  }
  do {
    R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(reader);
    R_Utf8Writer_writeCodePoints(writer, &codePoint, 1);
    R_Utf8Reader_next(reader);
  } while (!isEnd(reader));
  R_Value_setObjectReferenceValue(&temporaryValue, (R_ObjectReferenceValue)writerByteBuffer);
  value1 = R_String_create(temporaryValue);
  R_ByteBuffer_clear(writerByteBuffer);
  *key = key1;
  *value = value1;
  return R_BooleanValue_True;
}

void
R_CommandLine_raiseRequiredArgumentMissingError
  (
    R_String* key
  )
{
  fwrite(u8"required command-line argument `", 1, sizeof(u8"unkown command-line argument `") - 1, stdout);
  fwrite(key->p, 1, key->numberOfBytes, stdout);
  fwrite(u8"` not specified", 1, sizeof(u8"` not specified") - 1, stdout);
  R_setStatus(R_Status_ArgumentValueInvalid);
  R_jump();
}

void
R_CommandLine_raiseUnknownArgumentError
  (
    R_String* key,
    R_String* value
  )
{
  fwrite(u8"unknown command-line argument `", 1, sizeof(u8"unkown command-line argument `") - 1, stdout);
  fwrite(key->p, 1, key->numberOfBytes, stdout);
  fwrite(u8"`", 1, sizeof(u8"`") - 1, stdout);
  R_setStatus(R_Status_ArgumentValueInvalid);
  R_jump();
}

void
R_CommandLine_raiseNoValueError
  (
    R_String* key
  )
{
  fwrite(u8"value specified for command-line argument `", 1, sizeof(u8"value specified for command-line argument `") - 1, stdout);
  fwrite(key->p, 1, key->numberOfBytes, stdout);
  fwrite(u8"` is not valid", 1, sizeof(u8"` is not valid") - 1, stdout);
  R_setStatus(R_Status_ArgumentValueInvalid);
  R_jump();
}

void
R_CommandLine_raiseValueInvalidError
  (
    R_String* key,
    R_String* value
  )
{
  fwrite(u8"value specified for command-line argument `", 1, sizeof(u8"value specified for command-line argument `") - 1, stdout);
  fwrite(key->p, 1, key->numberOfBytes, stdout);
  fwrite(u8"` is not valid", 1, sizeof(u8"` is not valid") - 1, stdout);
  R_setStatus(R_Status_ArgumentValueInvalid);
  R_jump();
}
