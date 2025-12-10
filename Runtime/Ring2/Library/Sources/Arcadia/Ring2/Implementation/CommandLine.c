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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Implementation/CommandLine.h"

#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/Strings/Include.h"
#include "Arcadia/Ring2/FileSystem/FileSystem.h"
#include "Arcadia/Ring2/FileSystem/FileHandle.h"
#include "Arcadia/Ring2/FileSystem/FileHandleExtensions.h"

#include <stdio.h>

static Arcadia_BooleanValue
isEnd
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* reader
  )
{ return !Arcadia_UTF8Reader_hasCodePoint(thread, reader); }

static Arcadia_BooleanValue
isEqual
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* reader
  )
{
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  return '=' == Arcadia_UTF8Reader_getCodePoint(thread, reader);
}

static Arcadia_BooleanValue
isEqualOrEnd
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* reader
  )
{
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_True;
  }
  return '=' == Arcadia_UTF8Reader_getCodePoint(thread, reader);
}

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* reader
  )
{
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
  return '0' <= codePoint && codePoint <= '9';
}

static Arcadia_String*
parseInteger
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* reader,
    Arcadia_UTF8Writer* writer,
    Arcadia_ByteBuffer* writerByteBuffer
  )
{
  Arcadia_Natural32Value codePoint;
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    return NULL;
  }
  // ('+'|'-')?
  codePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
  if (codePoint == '+' || codePoint == '-') {
    Arcadia_UTF8Reader_next(thread, reader);
    Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
  }
  // digit+
  if (!isDigit(thread, reader)) {
    return NULL;
  }
  codePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
  do {
    codePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
    Arcadia_UTF8Reader_next(thread, reader);
    Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
  } while (isDigit(thread, reader));

  Arcadia_Value temporaryValue;
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)writerByteBuffer);
  Arcadia_String* resultString = Arcadia_String_create(thread, temporaryValue);

  return resultString;
}

static Arcadia_String*
parseString
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* reader,
    Arcadia_UTF8Writer* writer,
    Arcadia_ByteBuffer* writerByteBuffer
  )
{
  Arcadia_Natural32Value codePoint;
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    return NULL;
  }
  codePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
  if (codePoint != '"') {
    return NULL;
  }
  Arcadia_UTF8Reader_next(thread, reader);
  Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
  while (Arcadia_BooleanValue_True) {
    codePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
    if (lastWasSlash) {
      switch (codePoint) {
        case 'r': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '\r';
          Arcadia_UTF8Reader_next(thread, reader);
          Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case 'n': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '\n';
          Arcadia_UTF8Reader_next(thread, reader);
          Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case 'v': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '\v';
          Arcadia_UTF8Reader_next(thread, reader);
          Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case 't': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '\t';
          Arcadia_UTF8Reader_next(thread, reader);
          Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case '"': {
          lastWasSlash = Arcadia_BooleanValue_False;
          codePoint = '"';
          Arcadia_UTF8Reader_next(thread, reader);
          Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        case '\\': {
          lastWasSlash = Arcadia_BooleanValue_False;
          Arcadia_UTF8Reader_next(thread, reader);
          Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
        } break;
        default: {
          return NULL;
        }
      };
    } else {
      if (codePoint == '"') {
        Arcadia_UTF8Reader_next(thread, reader);
        break;
      } else if (codePoint == '\\') {
        Arcadia_UTF8Reader_next(thread, reader);
        lastWasSlash = Arcadia_BooleanValue_True;
      } else {
        Arcadia_UTF8Reader_next(thread, reader);
        Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
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
    Arcadia_UTF8Reader* reader,
    Arcadia_String** key,
    Arcadia_String** value
  )
{
  Arcadia_String* value1 = NULL, *key1 = NULL;
  Arcadia_Value temporaryValue;
  Arcadia_ByteBuffer* writerByteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_UTF8Writer* writer = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, writerByteBuffer);
  // '--'
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('-' != Arcadia_UTF8Reader_getCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_UTF8Reader_next(thread, reader);
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('-' != Arcadia_UTF8Reader_getCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_UTF8Reader_next(thread, reader);
  // <name>
  if (isEqualOrEnd(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  do {
    Arcadia_Natural32Value codePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
    Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
    Arcadia_UTF8Reader_next(thread, reader);
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
  Arcadia_UTF8Reader_next(thread, reader);
  if (!Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    return Arcadia_BooleanValue_False;
  }
  if ('"' == Arcadia_UTF8Reader_getCodePoint(thread, reader)) {
    value1 = parseString(thread, reader, writer, writerByteBuffer);
  } else {
    value1 = parseInteger(thread, reader, writer, writerByteBuffer);
  }
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
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"required command-line argument `");
  Arcadia_StringBuffer_insertBackString(thread, stringBuffer, key);
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"` not specified\n");

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);
  Arcadia_FileHandle_writeStringBuffer(thread, fileHandle, stringBuffer);

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
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"unknown command-line argument `");
  Arcadia_StringBuffer_insertBackString(thread, stringBuffer, key);
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"`\n");

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);
  Arcadia_FileHandle_writeStringBuffer(thread, fileHandle, stringBuffer);

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
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);

  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"no value specifiekd for command-line argument `");
  Arcadia_StringBuffer_insertBackString(thread, stringBuffer, key);
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"`\n");

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);
  Arcadia_FileHandle_writeStringBuffer(thread, fileHandle, stringBuffer);

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
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);

  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"value specified for command-line argument `");
  Arcadia_StringBuffer_insertBackString(thread, stringBuffer, key);
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"` is not valid\n");

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);
  Arcadia_FileHandle_writeStringBuffer(thread, fileHandle, stringBuffer);

  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

void
Arcadia_CommandLine_raiseAlreadySpecifiedError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  )
{
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);

  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"command-line argument `");
  Arcadia_StringBuffer_insertBackString(thread, stringBuffer, key);
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"` was already specified\n");

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, fileHandle);
  Arcadia_FileHandle_writeStringBuffer(thread, fileHandle, stringBuffer);

  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}
