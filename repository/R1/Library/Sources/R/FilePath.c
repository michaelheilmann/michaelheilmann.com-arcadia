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

// Last modified: 2024-10-07

#include "R/FilePath.h"

#include "R/ByteBuffer.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/Utf8ByteBufferReader.h"
#include "R/Utf8ByteBufferWriter.h"

typedef struct Context {
  R_Utf8Writer* temporaryWriter;
  R_ByteBuffer* temporaryBuffer;
  R_Utf8Reader* reader;
  R_FilePath* target;
} Context;

static void next(Context* context) {
  R_Utf8Reader_next(context->reader);
}

static void saveAndNext(Context* context) {
  R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(context->reader);
  R_Utf8Writer_writeCodePoints(context->temporaryWriter, &codePoint, 1);
  next(context);
}

static R_BooleanValue isEnd(Context* context) {
  return !R_Utf8Reader_hasCodePoint(context->reader);
}

static R_BooleanValue isDriveLetter(Context* context) {
  if (!R_Utf8Reader_hasCodePoint(context->reader)) {
    return R_BooleanValue_False;
  }
  R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(context->reader);
  return ('a' <= codePoint && codePoint <= 'z')
      || ('A' <= codePoint && codePoint <= 'Z');
}

static R_BooleanValue isColon(Context* context) {
  if (!R_Utf8Reader_hasCodePoint(context->reader)) {
    return R_BooleanValue_False;
  }
  R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(context->reader);
  return ':' == codePoint;
}

static R_BooleanValue isDirectorySeparator(Context* context) {
  if (!R_Utf8Reader_hasCodePoint(context->reader)) {
    return R_BooleanValue_False;
  }
  R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(context->reader);
  return ('\\' == codePoint || '/' == codePoint);
}

static R_BooleanValue isSlash(Context* context) {
  if (!R_Utf8Reader_hasCodePoint(context->reader)) {
    return R_BooleanValue_False;
  }
  R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(context->reader);
  return '/' == codePoint;
}

static void normalize(R_FilePath* self);

/* https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file#fully-qualified-vs-relative-paths */
static void
parseWindowsFilePath
  (
    R_FilePath* target,
    R_ByteBuffer* source
  )
{
  Context context;
  context.reader = (R_Utf8Reader*)R_Utf8ByteBufferReader_create(source);
  context.temporaryBuffer = R_ByteBuffer_create();
  context.temporaryWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context.temporaryBuffer);
  context.target = target;

  target->relative = R_BooleanValue_False;
  target->root = NULL;
  R_List_clear(target->fileNames);

  if (isDriveLetter(&context)) {
    saveAndNext(&context);
    if (isColon(&context)) {
      next(&context);
      if (isDirectorySeparator(&context)) {
        // absolute.
        context.target->relative = R_BooleanValue_False;
        next(&context);
        R_Value temporaryValue;
        R_Value_setObjectReferenceValue(&temporaryValue, (R_ObjectReferenceValue)context.temporaryBuffer);
        context.target->root = R_String_create(temporaryValue);
        R_ByteBuffer_clear(context.temporaryBuffer);
      } else {
        // relative to "root" drive and the diretory on the drive
        context.target->relative = R_BooleanValue_True;
        R_Value temporaryValue;
        R_Value_setObjectReferenceValue(&temporaryValue, (R_ObjectReferenceValue)context.temporaryBuffer);
        context.target->root = R_String_create(temporaryValue);
        R_ByteBuffer_clear(context.temporaryBuffer);
      }
    } else {
      while (!isEnd(&context) && !isDirectorySeparator(&context)) {
        saveAndNext(&context);
      }
      if (R_ByteBuffer_getNumberOfBytes(context.temporaryBuffer)) {
        R_Value temporary;
        R_Value_setObjectReferenceValue(&temporary, (R_ObjectReferenceValue)context.temporaryBuffer);
        R_Value_setObjectReferenceValue(&temporary, R_String_create(temporary));
        R_List_append(context.target->fileNames, temporary);
        R_ByteBuffer_clear(context.temporaryBuffer);
      }
      target->relative = R_BooleanValue_True;
    }
  } else if (isDirectorySeparator(&context)) {
    // relative to the root of the current drive.
    context.target->relative = R_BooleanValue_True;
    next(&context);
  } else {
    context.target->relative = R_BooleanValue_True;
  }
  // read the remaining directories
  R_ByteBuffer_clear(context.temporaryBuffer);
  while (!isEnd(&context)) {
    if (isDirectorySeparator(&context)) {
      next(&context);
      if (R_ByteBuffer_getNumberOfBytes(context.temporaryBuffer)) {
        R_Value temporary;
        R_Value_setObjectReferenceValue(&temporary, (R_ObjectReferenceValue)context.temporaryBuffer);
        R_Value_setObjectReferenceValue(&temporary, R_String_create(temporary));
        R_List_append(context.target->fileNames, temporary);
        R_ByteBuffer_clear(context.temporaryBuffer);
      }
    } else {
      saveAndNext(&context);
    }
  }
  if (R_ByteBuffer_getNumberOfBytes(context.temporaryBuffer)) {
    R_Value temporary;
    R_Value_setObjectReferenceValue(&temporary, (R_ObjectReferenceValue)context.temporaryBuffer);
    R_Value_setObjectReferenceValue(&temporary, R_String_create(temporary));
    R_List_append(context.target->fileNames, temporary);
    R_ByteBuffer_clear(context.temporaryBuffer);
  }
}

static void
parseUnixFilePath
  (
    R_FilePath* target,
    R_ByteBuffer* source
  )
{
  Context context;
  context.reader = (R_Utf8Reader*)R_Utf8ByteBufferReader_create(source);
  context.temporaryBuffer = R_ByteBuffer_create();
  context.temporaryWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context.temporaryBuffer);
  context.target = target;

  target->relative = R_BooleanValue_True;
  target->root = NULL;
  R_List_clear(target->fileNames);

  if (isSlash(&context)) {
    target->relative = R_BooleanValue_False;
    target->root = R_String_create_pn(R_ImmutableByteArray_create("/", sizeof("/") - 1));
    next(&context);
  }
  // read the remaining directories
  R_ByteBuffer_clear(context.temporaryBuffer);
  while (!isEnd(&context)) {
    if (isDirectorySeparator(&context)) {
      next(&context);
      if (R_ByteBuffer_getNumberOfBytes(context.temporaryBuffer)) {
        R_Value temporary;
        R_Value_setObjectReferenceValue(&temporary, (R_ObjectReferenceValue)context.temporaryBuffer);
        R_Value_setObjectReferenceValue(&temporary, R_String_create(temporary));
        R_List_append(context.target->fileNames, temporary);
        R_ByteBuffer_clear(context.temporaryBuffer);
      }
    } else {
      saveAndNext(&context);
    }
  }
  if (R_ByteBuffer_getNumberOfBytes(context.temporaryBuffer)) {
    R_Value temporary;
    R_Value_setObjectReferenceValue(&temporary, (R_ObjectReferenceValue)context.temporaryBuffer);
    R_Value_setObjectReferenceValue(&temporary, R_String_create(temporary));
    R_List_append(context.target->fileNames, temporary);
    R_ByteBuffer_clear(context.temporaryBuffer);
  }
}

static void
parseGenericFilePath
  (
    R_FilePath* target,
    R_ByteBuffer* source
  )
{
  Context context;
  context.reader = (R_Utf8Reader*)R_Utf8ByteBufferReader_create(source);
  context.temporaryBuffer = R_ByteBuffer_create();
  context.temporaryWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(context.temporaryBuffer);
  context.target = target;

  target->relative = R_BooleanValue_True;
  target->root = NULL;
  R_List_clear(target->fileNames);

  if (isSlash(&context)) {
    target->relative = R_BooleanValue_False;
    target->root = R_String_create_pn(R_ImmutableByteArray_create("/", sizeof("/") - 1));
    next(&context);
  }
  // read the remaining directories
  R_ByteBuffer_clear(context.temporaryBuffer);
  while (!isEnd(&context)) {
    if (isDirectorySeparator(&context)) {
      next(&context);
      if (R_ByteBuffer_getNumberOfBytes(context.temporaryBuffer)) {
        R_Value temporary;
        R_Value_setObjectReferenceValue(&temporary, (R_ObjectReferenceValue)context.temporaryBuffer);
        R_Value_setObjectReferenceValue(&temporary, R_String_create(temporary));
        R_List_append(context.target->fileNames, temporary);
        R_ByteBuffer_clear(context.temporaryBuffer);
      }
    } else {
      saveAndNext(&context);
    }
  }
  if (R_ByteBuffer_getNumberOfBytes(context.temporaryBuffer)) {
    R_Value temporary;
    R_Value_setObjectReferenceValue(&temporary, (R_ObjectReferenceValue)context.temporaryBuffer);
    R_Value_setObjectReferenceValue(&temporary, R_String_create(temporary));
    R_List_append(context.target->fileNames, temporary);
    R_ByteBuffer_clear(context.temporaryBuffer);
  }
}

static void
R_FilePath_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_FilePath_destruct
  (
    R_FilePath* self
  );

static void
R_FilePath_visit
  (
    R_FilePath* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_FilePath_constructImpl,
  .destruct = &R_FilePath_destruct,
  .visit = &R_FilePath_visit,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.FilePath", R_FilePath, "R.Object", R_Object, &_typeOperations);

static void
R_FilePath_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_FilePath* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_FilePath_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->fileNames = NULL;
  _self->relative = R_BooleanValue_False;
  _self->root = NULL;
  _self->fileNames = R_List_create();
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_FilePath_destruct
  (
    R_FilePath* self
  )
{/*Intentionally empty.*/}

static void
R_FilePath_visit
  (
    R_FilePath* self
  )
{
  R_Object_visit(self->fileNames);
  R_Object_visit(self->root);
}

R_FilePath*
R_FilePath_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_FilePath* self = R_allocateObject(_R_FilePath_getType(), 0, &argumentValues[0]);
  R_Value selfValue = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)self };
  R_FilePath_constructImpl(&selfValue, 0, &argumentValues[0]);
  return self;
}

R_FilePath*
R_FilePath_parseWindows
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_Type* _type = _R_FilePath_getType();
  R_Value argumentValues[] = { { .tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_FilePath* self = R_allocateObject(_type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = R_BooleanValue_False;
  self->root = NULL;
  self->fileNames = R_List_create();
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  R_ByteBuffer_append_pn(byteBuffer, bytes, numberOfBytes);
  parseWindowsFilePath(self, byteBuffer);
  normalize(self);
  R_Object_setType((R_Object*)self, _type);
  return self;
}

R_FilePath*
R_FilePath_parseUnix
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_Type* _type = _R_FilePath_getType();
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_FilePath* self = R_allocateObject(_type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = R_BooleanValue_False;
  self->root = NULL;
  self->fileNames = R_List_create();
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  R_ByteBuffer_append_pn(byteBuffer, bytes, numberOfBytes);
  parseUnixFilePath(self, byteBuffer);
  normalize(self);
  R_Object_setType((R_Object*)self, _type);
  return self;
}

R_FilePath*
R_FilePath_parseNative
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
 {
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  return R_FilePath_parseWindows(bytes, numberOfBytes);
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  return R_FilePath_parseUnix(bytes, numberOfBytes);
#else
  #error("operating system not supported")
#endif
}

R_FilePath*
R_FilePath_parseGeneric
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_Type* _type = _R_FilePath_getType();
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_FilePath* self = R_allocateObject(_type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = R_BooleanValue_False;
  self->root = NULL;
  self->fileNames = R_List_create();
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  R_ByteBuffer_append_pn(byteBuffer, bytes, numberOfBytes);
  parseGenericFilePath(self, byteBuffer);
  normalize(self);
  R_Object_setType((R_Object*)self, _type);
  return self;
}

// <filename> <dot-dot> => delete this
// <dot> => delete this
static void
normalize
  (
    R_FilePath* self
  )
{
  R_SizeValue previous = 0, current = 1;
  while (current < R_List_getSize(self->fileNames)) {
    R_Value t;
    t = R_List_getAt(self->fileNames, previous);
    R_String* previousString = (R_String*)R_Value_getObjectReferenceValue(&t);
    t = R_List_getAt(self->fileNames, current);
    R_String* currentString = (R_String*)R_Value_getObjectReferenceValue(&t);
    if (!R_String_isEqualTo_pn(previousString, "..", sizeof("..") - 1) && !R_String_isEqualTo_pn(previousString, ".", sizeof(".")) && R_String_isEqualTo_pn(currentString, "..", sizeof("..") - 1)) {
      // Remove previous and current.
      R_List_remove(self->fileNames, previous, 2);
    } else if (R_String_isEqualTo_pn(currentString, ".", sizeof(".") - 1)) {
      // Remove current.
      R_List_remove(self->fileNames, current, 1);
    } else {
      previous++;
      current++;
    }
  }
  if (!self->root && R_List_isEmpty(self->fileNames)) {
    // If the path is empty, then the path is `.`.
    R_List_appendObjectReferenceValue(self->fileNames, (R_ObjectReferenceValue)R_String_create_pn(R_ImmutableByteArray_create(".", sizeof(".") - 1)));
  }
}

R_String*
R_FilePath_toNative
  (
    R_FilePath* self
  )
{
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  R_ByteBuffer* temporaryBuffer = R_ByteBuffer_create();
  R_Utf8Writer* temporary = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(temporaryBuffer);
  R_SizeValue i = 0, n = R_List_getSize(self->fileNames);

  if (self->root) {
    R_Utf8Writer_writeBytes(temporary, R_String_getBytes(self->root), R_String_getNumberOfBytes(self->root));
    R_Natural32Value x;
    x = ':';
    R_Utf8Writer_writeCodePoints(temporary, &x, 1);
    if (!self->relative) {
      x = '\\';
      R_Utf8Writer_writeCodePoints(temporary, &x, 1);
    } else {
      /* Intentionally empty. */
    }
  }
  if (n > 0) {
    R_Value e = R_List_getAt(self->fileNames, 0);
    R_String* fileName = (R_String*)R_Value_getObjectReferenceValue(&e);
    R_Utf8Writer_writeBytes(temporary, R_String_getBytes(fileName), R_String_getNumberOfBytes(fileName));
    i++;

    for (; i < n; ++i) {
      R_Natural32Value x;
      x = '\\';
      R_Utf8Writer_writeCodePoints(temporary, &x, 1);

      R_Value e = R_List_getAt(self->fileNames, i);
      R_String* fileName = (R_String*)R_Value_getObjectReferenceValue(&e);
      R_Utf8Writer_writeBytes(temporary, R_String_getBytes(fileName), R_String_getNumberOfBytes(fileName));
    }
  }
  R_Natural32Value x = '\0';
  R_Utf8Writer_writeCodePoints(temporary, &x, 1);
  R_Value temporaryValue;
  R_Value_setObjectReferenceValue(&temporaryValue, (R_ObjectReferenceValue)temporaryBuffer);
  return R_String_create(temporaryValue);
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  R_ByteBuffer* temporaryBuffer = R_ByteBuffer_create();
  R_Utf8Writer* temporary = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(temporaryBuffer);
  R_SizeValue i = 0, n = R_List_getSize(self->fileNames);
  if (self->root) {
    R_Utf8Writer_writeBytes(temporary, R_String_getBytes(self->root), R_String_getNumberOfBytes(self->root));
  }
  if (n > 0) {
    R_Value e = R_List_getAt(self->fileNames, 0);
    R_String* fileName = (R_String*)R_Value_getObjectReferenceValue(&e);
    R_Utf8Writer_writeBytes(temporary, R_String_getBytes(fileName), R_String_getNumberOfBytes(fileName));
    i++;

    for (; i < n; ++i) {
      R_Natural32Value x;
      x = '/';
      R_Utf8Writer_writeCodePoints(temporary, &x, 1);

      R_Value e = R_List_getAt(self->fileNames, i);
      R_String* fileName = (R_String*)R_Value_getObjectReferenceValue(&e);
      R_Utf8Writer_writeBytes(temporary, R_String_getBytes(fileName), R_String_getNumberOfBytes(fileName));
    }
  }
  R_Natural32Value x = '\0';
  R_Utf8Writer_writeCodePoints(temporary, &x, 1);
  R_Value temporaryValue;
  R_Value_setObjectReferenceValue(&temporaryValue, (R_ObjectReferenceValue)temporaryBuffer);
  return R_String_create(temporaryValue);
#else
  #error("operating system not yet supported")
#endif
}

#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h> // for GetFullPathName
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  #include <stdlib.h> // for realpath
#endif

R_FilePath*
R_FilePath_getFullPath
  (
    R_FilePath* self
  )
{
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
#define BUFFER_LENGTH (4096)
  R_String* s = R_FilePath_toNative(self);
  char buffer[BUFFER_LENGTH];
  DWORD result = GetFullPathName(R_String_getBytes(s), BUFFER_LENGTH, buffer, NULL);
  if (!result) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  return R_FilePath_parseNative(buffer, c_strlen(buffer));
#undef BUFFER_LENGTH
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  R_String* s = R_FilePath_toNative(self);
  char buffer[PATH_MAX];
  char* result = realpath(R_String_getBytes(s), buffer);
  if (!result) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  return R_FilePath_parseNative(buffer, c_strlen(buffer));
#else
  #error("operating system not yet supported")
#endif
}

R_BooleanValue
R_FilePath_isEqualTo
  (
    R_FilePath* self,
    R_FilePath* other
  )
{
  self = R_FilePath_getFullPath(self);
  other = R_FilePath_getFullPath(other);
  if (self == other) {
    return R_BooleanValue_True;
  }
  if (self->relative != other->relative) {
    return R_BooleanValue_False;
  }
  if (R_List_getSize(self->fileNames) != R_List_getSize(other->fileNames)) {
    return R_BooleanValue_False;
  }
  for (R_SizeValue i = 0, n = R_List_getSize(self->fileNames); i < n; ++i) {
    R_Object* x = R_List_getObjectReferenceValueAt(self->fileNames, i);
    R_Value y = R_List_getAt(other->fileNames, i);
    if (!R_Object_equalTo(x, &y)) {
      return R_BooleanValue_False;
    }
  }
  if ((self->root == NULL && other->root != NULL) || (self->root != NULL && other->root == NULL)) {
    return R_BooleanValue_False;
  }
  if (self->root != NULL) {
    R_Value t;
    R_Value_setObjectReferenceValue(&t, other->root);
    if (!R_Object_equalTo((R_Object*)self->root, &t)) {
      return R_BooleanValue_False;
    }
  }
  return R_BooleanValue_True;
}

R_BooleanValue
R_FilePath_isAbsolute
  (
    R_FilePath* self
  )
{ return !self->relative; }

R_BooleanValue
R_FilePath_isRelative
  (
    R_FilePath* self
  )
{ return self->relative; }

void
R_FilePath_append
  (
    R_FilePath* self,
    R_FilePath* other
  )
{
  if (!R_FilePath_isRelative(other)) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  for (R_SizeValue i = 0, n = R_List_getSize(other->fileNames); i < n; ++i) {
    R_Value v = R_List_getAt(other->fileNames, i);
    R_List_append(self->fileNames, v);
  }
}
