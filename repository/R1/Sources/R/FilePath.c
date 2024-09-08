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

// Last modified: 2024-09-08

#include "R/FilePath.h"

#include "R.h"

typedef struct Context {
  R_Utf8Writer* temporary;
  R_Utf8Reader* reader;
  R_FilePath* target;
} Context;

static void next(Context* context) {
  R_Utf8Reader_next(context->reader);
}

static void saveAndNext(Context* context) {
  R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(context->reader);
  R_Utf8Writer_writeCodePoints(context->temporary, &codePoint, 1);
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
  context.reader = R_Utf8Reader_create(source);
  context.temporary = R_Utf8Writer_create(R_ByteBuffer_create());
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
        context.target->root = R_String_create(context.temporary->target->p, context.temporary->target->sz);
        R_ByteBuffer_clear(context.temporary->target);
      } else {
        // relative to "root" drive and the diretory on the drive
        context.target->relative = R_BooleanValue_True;
        context.target->root = R_String_create(context.temporary->target->p, context.temporary->target->sz);
        R_ByteBuffer_clear(context.temporary->target);
      }
    } else {
      while (!isEnd(&context) && !isDirectorySeparator(&context)) {
        saveAndNext(&context);
      }
      if (context.temporary->target->sz) {
        R_Value temporary;
        R_Value_setObjectReferenceValue(&temporary, R_String_create(context.temporary->target->p, context.temporary->target->sz));
        R_List_append(context.target->fileNames, temporary);
        R_ByteBuffer_clear(context.temporary->target);
      }
    }
  } else if (isDirectorySeparator(&context)) {
    // relative to the root of the current drive.
    context.target->relative = R_BooleanValue_True;
    next(&context);
  } else {
    context.target->relative = R_BooleanValue_True;
  } 
  // read the remaining directories
  R_ByteBuffer_clear(context.temporary->target);
  while (!isEnd(&context)) {
    if (isDirectorySeparator(&context)) {
      next(&context);
      if (context.temporary->target->sz) {
        R_Value temporary;
        R_Value_setObjectReferenceValue(&temporary, R_String_create(context.temporary->target->p, context.temporary->target->sz));
        R_List_append(context.target->fileNames, temporary);
        R_ByteBuffer_clear(context.temporary->target);
      }
    } else {
      saveAndNext(&context);
    }
  }
  if (context.temporary->target->sz) {
    R_Value temporary;
    R_Value_setObjectReferenceValue(&temporary, R_String_create(context.temporary->target->p, context.temporary->target->sz));
    R_List_append(context.target->fileNames, temporary);
    R_ByteBuffer_clear(context.temporary->target);
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
  context.reader = R_Utf8Reader_create(source);
  context.temporary = R_Utf8Writer_create(R_ByteBuffer_create());
  context.target = target;

  target->relative = R_BooleanValue_True;
  target->root = NULL;
  R_List_clear(target->fileNames);

  if (isSlash(&context)) {
    target->relative = R_BooleanValue_False;
    target->root = R_String_create("/", sizeof("/") - 1);
    next(&context);
  }
  // read the remaining directories
  R_ByteBuffer_clear(context.temporary->target);
  while (!isEnd(&context)) {
    if (isDirectorySeparator(&context)) {
      next(&context);
      if (context.temporary->target->sz) {
        R_Value temporary;
        R_Value_setObjectReferenceValue(&temporary, R_String_create(context.temporary->target->p, context.temporary->target->sz));
        R_List_append(context.target->fileNames, temporary);
        R_ByteBuffer_clear(context.temporary->target);
      }
    } else {
      saveAndNext(&context);
    }
  }
  if (context.temporary->target->sz) {
    R_Value temporary;
    R_Value_setObjectReferenceValue(&temporary, R_String_create(context.temporary->target->p, context.temporary->target->sz));
    R_List_append(context.target->fileNames, temporary);
    R_ByteBuffer_clear(context.temporary->target);
  }
}

static void
R_FilePath_finalize
  (
    R_FilePath* self
  );

static void
R_FilePath_visit
  (
    R_FilePath* self
  );

static void
R_FilePath_finalize
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

void
_R_FilePath_registerType
  (
  )
{
  R_registerObjectType("R.FilePath", sizeof("R.FilePath") - 1, sizeof(R_FilePath), &R_FilePath_visit, &R_FilePath_finalize);
}

R_FilePath*
R_FilePath_create
  (
  )
{
  R_FilePath* self = R_allocateObject("R.FilePath", sizeof("R.FilePath") - 1, sizeof(R_FilePath));
  self->fileNames = NULL;
  self->relative = R_BooleanValue_False;
  self->root = NULL;
  self->fileNames = R_List_create(); 
  return self;
}

R_FilePath*
R_FilePath_parseWindowsFilePath
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_FilePath* self = R_allocateObject("R.FilePath", sizeof("R.FilePath") - 1, sizeof(R_FilePath));
  self->fileNames = NULL;
  self->relative = R_BooleanValue_False;
  self->root = NULL;
  self->fileNames = R_List_create();
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  R_ByteBuffer_append_pn(byteBuffer, bytes, numberOfBytes);
  parseWindowsFilePath(self, byteBuffer);
  normalize(self);
  return self;
}

R_FilePath*
R_FilePath_parseUnixFilePath
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_FilePath* self = R_allocateObject("R.FilePath", sizeof("R.FilePath") - 1, sizeof(R_FilePath));
  self->fileNames = NULL;
  self->relative = R_BooleanValue_False;
  self->root = NULL;
  self->fileNames = R_List_create();
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  R_ByteBuffer_append_pn(byteBuffer, bytes, numberOfBytes);
  parseUnixFilePath(self, byteBuffer);
  normalize(self);
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
  return R_FilePath_parseWindowsFilePath(bytes, numberOfBytes);
#elif #elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  return R_FilePath_parseUnixFilePath(bytes, numberOfBytes);
#else
  #error("operating system not supported")
#endif
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
    R_List_appendObjectReferenceValue(self->fileNames, (R_ObjectReferenceValue)R_String_create(".", sizeof(".") - 1));
  }
}

R_String*
R_FilePath_toNative
  (
    R_FilePath* self
  )
{
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  R_Utf8Writer* temporary = R_Utf8Writer_create(R_ByteBuffer_create());
  R_SizeValue i = 0, n = R_List_getSize(self->fileNames);

  if (self->root) {
    R_Utf8Writer_writeBytes(temporary, self->root->p, self->root->sz);
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
    R_Utf8Writer_writeBytes(temporary, fileName->p, fileName->sz);
    i++;

    for (; i < n; ++i) {
      R_Natural32Value x;
      x = '\\';
      R_Utf8Writer_writeCodePoints(temporary, &x, 1);

      R_Value e = R_List_getAt(self->fileNames, i);
      R_String* fileName = (R_String*)R_Value_getObjectReferenceValue(&e);
      R_Utf8Writer_writeBytes(temporary, fileName->p, fileName->sz);
    }
  }
  R_Natural32Value x = '\0';
  R_Utf8Writer_writeCodePoints(temporary, &x, 1);
  return R_String_create(temporary->target->p, temporary->target->sz);
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  if (self->root) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Utf8Writer* temporary = R_Utf8Writer_create(R_ByteBuffer_create());
  R_SizeValue i = 0, n = R_List_getSize(self->fileNames);
  if (self->relative) {
    R_Natural32Value x;
    x = '/';
    R_Utf8Writer_writeCodePoints(temporary, &x, 1);
  }
  if (n > 0) {
    R_Value e = R_List_getAt(self->fileNames, 0);
    R_String* fileName = (R_String*)R_Value_getObjectReferenceValue(&e);
    R_Utf8Writer_writeBytes(temporary, fileName->p, fileName->sz);
    i++;

    for (; i < n; ++i) {
      R_Natural32Value x;
      x = '/';
      R_Utf8Writer_writeCodePoints(temporary, &x, 1);

      R_Value e = R_List_getAt(self->fileNames, i);
      R_String* fileName = (R_String*)R_Value_getObjectReferenceValue(&e);
      R_Utf8Writer_writeBytes(temporary, fileName->p, fileName->sz);
    }
  }
  R_Natural32Value x = '\0';
  R_Utf8Writer_writeCodePoints(temporary, &x, 1);
  return R_String_create(temporary->target->p, temporary->target->sz);
#else
  #error("operating system not yet supported")
#endif
}

#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
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
  DWORD result = GetFullPathName(s->p, BUFFER_LENGTH, buffer, NULL);
  if (!result) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return R_FilePath_parseNative(buffer, strlen(buffer));
#undef BUFFER_LENGTH
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  #error("operating system not yet supported")
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
    R_String* x = (R_String*)R_List_getObjectReferenceValueAt(self->fileNames, i);
    R_String* y = (R_String*)R_List_getObjectReferenceValueAt(other->fileNames, i);
    if (!R_String_isEqualTo(x, y)) {
      return R_BooleanValue_False;
    }
  }
  if ((self->root == NULL && other->root != NULL) || (self->root != NULL && other->root == NULL)) {
    return R_BooleanValue_False;
  } 
  if (self->root != NULL) {
    if (!R_String_isEqualTo(self->root, other->root)) {
      return R_BooleanValue_False;
    }
  }
  return R_BooleanValue_True;
}
