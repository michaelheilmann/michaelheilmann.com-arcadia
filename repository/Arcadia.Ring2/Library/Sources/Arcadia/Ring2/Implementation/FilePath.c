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

// Last modified: 2024-10-07

#include "Arcadia/Ring2/Implementation/FilePath.h"

#include "Arcadia/Ring2/Implementation/ByteBuffer.h"
#include "Arcadia/Ring2/Implementation/Utf8ByteBufferReader.h"
#include "Arcadia/Ring2/Implementation/Utf8ByteBufferWriter.h"
#include <string.h>

typedef struct Context {
  Arcadia_Utf8Writer* temporaryWriter;
  Arcadia_ByteBuffer* temporaryBuffer;
  Arcadia_Utf8Reader* reader;
  Arcadia_FilePath* target;
} Context;

static void
next
  (
    Arcadia_Process* process,
    Context* context
  );

static void
saveAndNext
  (
    Arcadia_Process* process,
    Context* context
  );

static Arcadia_BooleanValue
isEnd
  (
    Arcadia_Process* process,
    Context* context
  );

static Arcadia_BooleanValue
isDriveLetter
  (
    Arcadia_Process* process,
    Context* context
  );

static Arcadia_BooleanValue
isColon
  (
    Arcadia_Process* process,
    Context* context
  );

static Arcadia_BooleanValue isDirectorySeparator(Arcadia_Process* process, Context* context);

static Arcadia_BooleanValue isSlash(Arcadia_Process* process, Context* context);

static void
normalize
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self
  );

/* https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file#fully-qualified-vs-relative-paths */
static void
parseWindowsFilePath
  (
    Arcadia_Process* process,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  );

static void
parseUnixFilePath
  (
    Arcadia_Process* process,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  );

static void
parseGenericFilePath
  (
    Arcadia_Process* process,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  );

static void
next
  (
    Arcadia_Process* process,
    Context* context
  )
{ Arcadia_Utf8Reader_next(process, context->reader); }

static void
saveAndNext
  (
    Arcadia_Process* process,
    Context* context
  )
{
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(process, context->reader);
  Arcadia_Utf8Writer_writeCodePoints(process, context->temporaryWriter, &codePoint, 1);
  next(process, context);
}

static Arcadia_BooleanValue
isEnd
  (
    Arcadia_Process* process,
    Context* context
  )
{ return !Arcadia_Utf8Reader_hasCodePoint(process, context->reader); }

static Arcadia_BooleanValue
isDriveLetter
  (
    Arcadia_Process* process,
    Context* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(process, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(process, context->reader);
  return ('a' <= codePoint && codePoint <= 'z')
      || ('A' <= codePoint && codePoint <= 'Z');
}

static Arcadia_BooleanValue
isColon
  (
    Arcadia_Process* process,
    Context* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(process, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(process, context->reader);
  return ':' == codePoint;
}

static Arcadia_BooleanValue
isDirectorySeparator
  (
    Arcadia_Process* process,
    Context* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(process, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(process, context->reader);
  return ('\\' == codePoint || '/' == codePoint);
}

static Arcadia_BooleanValue
isSlash
  (
    Arcadia_Process* process,
    Context* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(process, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(process, context->reader);
  return '/' == codePoint;
}

// <filename> <dot-dot> => delete this
// <dot> => delete this
static void
normalize
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self
  )
{
  Arcadia_SizeValue previous = 0, current = 1;
  while (current < Arcadia_List_getSize(process, self->fileNames)) {
    Arcadia_Value t;
    t = Arcadia_List_getAt(process, self->fileNames, previous);
    Arcadia_String* previousString = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&t);
    t = Arcadia_List_getAt(process, self->fileNames, current);
    Arcadia_String* currentString = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&t);
    if (!Arcadia_String_isEqualTo_pn(process, previousString, "..", sizeof("..") - 1) &&
        !Arcadia_String_isEqualTo_pn(process, previousString, u8".", sizeof(u8".")) &&
         Arcadia_String_isEqualTo_pn(process, currentString, u8"..", sizeof(u8"..") - 1)) {
   // Remove previous and current.
      Arcadia_List_remove(process, self->fileNames, previous, 2);
    } else if (Arcadia_String_isEqualTo_pn(process, currentString, u8".", sizeof(u8".") - 1)) {
      // Remove current.
      Arcadia_List_remove(process, self->fileNames, current, 1);
    } else {
      previous++;
      current++;
    }
  }
  if (!self->root && Arcadia_List_isEmpty(process, self->fileNames)) {
    // If the path is empty, then the path is `.`.
    Arcadia_List_appendObjectReferenceValue(process, self->fileNames, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8".", sizeof(u8".") - 1)));
  }
}

static void
parseWindowsFilePath
  (
    Arcadia_Process* process,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  )
{
  Context context;
  context.reader = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(process, source);
  context.temporaryBuffer = Arcadia_ByteBuffer_create(process);
  context.temporaryWriter = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context.temporaryBuffer);
  context.target = target;

  target->relative = Arcadia_BooleanValue_False;
  target->root = NULL;
  Arcadia_List_clear(process, target->fileNames);

  if (isDriveLetter(process, &context)) {
    saveAndNext(process, &context);
    if (isColon(process, &context)) {
      next(process, &context);
      if (isDirectorySeparator(process, &context)) {
        // absolute.
        context.target->relative = Arcadia_BooleanValue_False;
        next(process, &context);
        Arcadia_Value temporaryValue;
        Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        context.target->root = Arcadia_String_create(process, temporaryValue);
        Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
      } else {
        // relative to "root" drive and the diretory on the drive
        context.target->relative = Arcadia_BooleanValue_True;
        Arcadia_Value temporaryValue;
        Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        context.target->root = Arcadia_String_create(process, temporaryValue);
        Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
      }
    } else {
      while (!isEnd(process, &context) && !isDirectorySeparator(process, &context)) {
        saveAndNext(process, &context);
      }
      if (Arcadia_ByteBuffer_getNumberOfBytes(process, context.temporaryBuffer)) {
        Arcadia_Value temporary;
        Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(process, temporary));
        Arcadia_List_append(process, context.target->fileNames, temporary);
        Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
      }
      target->relative = Arcadia_BooleanValue_True;
    }
  } else if (isDirectorySeparator(process, &context)) {
    // relative to the root of the current drive.
    context.target->relative = Arcadia_BooleanValue_True;
    next(process, &context);
  } else {
    context.target->relative = Arcadia_BooleanValue_True;
  }
  // read the remaining directories
  Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
  while (!isEnd(process, &context)) {
    if (isDirectorySeparator(process, &context)) {
      next(process, &context);
      if (Arcadia_ByteBuffer_getNumberOfBytes(process, context.temporaryBuffer)) {
        Arcadia_Value temporary;
        Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(process, temporary));
        Arcadia_List_append(process, context.target->fileNames, temporary);
        Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
      }
    } else {
      saveAndNext(process, &context);
    }
  }
  if (Arcadia_ByteBuffer_getNumberOfBytes(process, context.temporaryBuffer)) {
    Arcadia_Value temporary;
    Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
    Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(process, temporary));
    Arcadia_List_append(process, context.target->fileNames, temporary);
    Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
  }
}

static void
parseUnixFilePath
  (
    Arcadia_Process* process,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  )
{
  Context context;
  context.reader = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(process, source);
  context.temporaryBuffer = Arcadia_ByteBuffer_create(process);
  context.temporaryWriter = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context.temporaryBuffer);
  context.target = target;

  target->relative = Arcadia_BooleanValue_True;
  target->root = NULL;
  Arcadia_List_clear(process, target->fileNames);

  if (isSlash(process, &context)) {
    target->relative = Arcadia_BooleanValue_False;
    target->root = Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"/", sizeof(u8"/") - 1));
    next(process, &context);
  }
  // read the remaining directories
  Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
  while (!isEnd(process, &context)) {
    if (isDirectorySeparator(process, &context)) {
      next(process, &context);
      if (Arcadia_ByteBuffer_getNumberOfBytes(process, context.temporaryBuffer)) {
        Arcadia_Value temporary;
        Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(process, temporary));
        Arcadia_List_append(process, context.target->fileNames, temporary);
        Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
      }
    } else {
      saveAndNext(process, &context);
    }
  }
  if (Arcadia_ByteBuffer_getNumberOfBytes(process, context.temporaryBuffer)) {
    Arcadia_Value temporary;
    Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
    Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(process, temporary));
    Arcadia_List_append(process, context.target->fileNames, temporary);
    Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
  }
}

static void
parseGenericFilePath
  (
    Arcadia_Process* process,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  )
{
  Context context;
  context.reader = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(process, source);
  context.temporaryBuffer = Arcadia_ByteBuffer_create(process);
  context.temporaryWriter = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, context.temporaryBuffer);
  context.target = target;

  target->relative = Arcadia_BooleanValue_True;
  target->root = NULL;
  Arcadia_List_clear(process, target->fileNames);

  if (isSlash(process, &context)) {
    target->relative = Arcadia_BooleanValue_False;
    target->root = Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"/", sizeof(u8"/") - 1));
    next(process, &context);
  }
  // read the remaining directories
  Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
  while (!isEnd(process, &context)) {
    if (isDirectorySeparator(process, &context)) {
      next(process, &context);
      if (Arcadia_ByteBuffer_getNumberOfBytes(process, context.temporaryBuffer)) {
        Arcadia_Value temporary;
        Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(process, temporary));
        Arcadia_List_append(process, context.target->fileNames, temporary);
        Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
      }
    } else {
      saveAndNext(process, &context);
    }
  }
  if (Arcadia_ByteBuffer_getNumberOfBytes(process, context.temporaryBuffer)) {
    Arcadia_Value temporary;
    Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
    Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(process, temporary));
    Arcadia_List_append(process, context.target->fileNames, temporary);
    Arcadia_ByteBuffer_clear(process, context.temporaryBuffer);
  }
}

static void
Arcadia_FilePath_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_FilePath_destruct
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self
  );

static void
Arcadia_FilePath_visit
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_FilePath_constructImpl,
  .destruct = &Arcadia_FilePath_destruct,
  .visit = &Arcadia_FilePath_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Rex_defineObjectType(u8"Arcadia.Library.FilePath", Arcadia_FilePath, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_FilePath_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_FilePath* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_FilePath_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->fileNames = NULL;
  _self->relative = Arcadia_BooleanValue_False;
  _self->root = NULL;
  _self->fileNames = Arcadia_List_create(process);
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_FilePath_destruct
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_FilePath_visit
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self
  )
{
  Arcadia_Object_visit(process, self->fileNames);
  Arcadia_Object_visit(process, self->root);
}

Arcadia_FilePath*
Arcadia_FilePath_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_FilePath* self = R_allocateObject(process, _Arcadia_FilePath_getType(process), 0, &argumentValues[0]);
  return self;
}

Arcadia_FilePath*
Arcadia_FilePath_parseWindows
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_TypeValue _type = _Arcadia_FilePath_getType(process);
  Arcadia_Value argumentValues[] = { { .tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_FilePath* self = R_allocateObject(process, _type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = Arcadia_BooleanValue_False;
  self->root = NULL;
  self->fileNames = Arcadia_List_create(process);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(process);
  Arcadia_ByteBuffer_append_pn(process, byteBuffer, bytes, numberOfBytes);
  parseWindowsFilePath(process, self, byteBuffer);
  normalize(process, self);
  return self;
}

Arcadia_FilePath*
Arcadia_FilePath_parseUnix
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_TypeValue _type = _Arcadia_FilePath_getType(process);
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_FilePath* self = R_allocateObject(process, _type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = Arcadia_BooleanValue_False;
  self->root = NULL;
  self->fileNames = Arcadia_List_create(process);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(process);
  Arcadia_ByteBuffer_append_pn(process, byteBuffer, bytes, numberOfBytes);
  parseUnixFilePath(process, self, byteBuffer);
  normalize(process, self);
  return self;
}

Arcadia_FilePath*
Arcadia_FilePath_parseNative
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
 {
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  return Arcadia_FilePath_parseWindows(process, bytes, numberOfBytes);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  return Arcadia_FilePath_parseUnix(process, bytes, numberOfBytes);
#else
  #error("operating system not (yet) supported")
#endif
}

Arcadia_FilePath*
Arcadia_FilePath_parseGeneric
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_TypeValue _type = _Arcadia_FilePath_getType(process);
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_FilePath* self = R_allocateObject(process, _type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = Arcadia_BooleanValue_False;
  self->root = NULL;
  self->fileNames = Arcadia_List_create(process);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(process);
  Arcadia_ByteBuffer_append_pn(process, byteBuffer, bytes, numberOfBytes);
  parseGenericFilePath(process, self, byteBuffer);
  normalize(process, self);
  return self;
}

Arcadia_String*
Arcadia_FilePath_toNative
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self
  )
{
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  Arcadia_ByteBuffer* temporaryBuffer = Arcadia_ByteBuffer_create(process);
  Arcadia_Utf8Writer* temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, temporaryBuffer);
  Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, self->fileNames);

  if (self->root) {
    Arcadia_Utf8Writer_writeBytes(process, temporary, Arcadia_String_getBytes(process, self->root), Arcadia_String_getNumberOfBytes(process, self->root));
    Arcadia_Natural32Value x;
    x = ':';
    Arcadia_Utf8Writer_writeCodePoints(process, temporary, &x, 1);
    if (!self->relative) {
      x = '\\';
      Arcadia_Utf8Writer_writeCodePoints(process, temporary, &x, 1);
    } else {
      /* Intentionally empty. */
    }
  }
  if (n > 0) {
    Arcadia_Value e = Arcadia_List_getAt(process, self->fileNames, 0);
    Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
    Arcadia_Utf8Writer_writeBytes(process, temporary, Arcadia_String_getBytes(process, fileName), Arcadia_String_getNumberOfBytes(process, fileName));
    i++;

    for (; i < n; ++i) {
      Arcadia_Natural32Value x;
      x = '\\';
      Arcadia_Utf8Writer_writeCodePoints(process, temporary, &x, 1);

      Arcadia_Value e = Arcadia_List_getAt(process, self->fileNames, i);
      Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
      Arcadia_Utf8Writer_writeBytes(process, temporary, Arcadia_String_getBytes(process, fileName), Arcadia_String_getNumberOfBytes(process, fileName));
    }
  }
  Arcadia_Natural32Value x = '\0';
  Arcadia_Utf8Writer_writeCodePoints(process, temporary, &x, 1);
  Arcadia_Value temporaryValue;
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)temporaryBuffer);
  return Arcadia_String_create(process, temporaryValue);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_ByteBuffer* temporaryBuffer = Arcadia_ByteBuffer_create(process);
  Arcadia_Utf8Writer* temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(process, temporaryBuffer);
  Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, self->fileNames);
  if (self->root) {
    Arcadia_Utf8Writer_writeBytes(process, temporary, Arcadia_String_getBytes(process, self->root), Arcadia_String_getNumberOfBytes(process, self->root));
  }
  if (n > 0) {
    Arcadia_Value e = Arcadia_List_getAt(process, self->fileNames, 0);
    Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
    Arcadia_Utf8Writer_writeBytes(process, temporary, Arcadia_String_getBytes(process, fileName), Arcadia_String_getNumberOfBytes(process, fileName));
    i++;

    for (; i < n; ++i) {
      Arcadia_Natural32Value x;
      x = '/';
      Arcadia_Utf8Writer_writeCodePoints(process, temporary, &x, 1);

      Arcadia_Value e = Arcadia_List_getAt(process, self->fileNames, i);
      Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
      Arcadia_Utf8Writer_writeBytes(process, temporary, Arcadia_String_getBytes(process, fileName), Arcadia_String_getNumberOfBytes(process, fileName));
    }
  }
  Arcadia_Natural32Value x = '\0';
  Arcadia_Utf8Writer_writeCodePoints(process, temporary, &x, 1);
  Arcadia_Value temporaryValue;
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)temporaryBuffer);
  return Arcadia_String_create(process, temporaryValue);
#else
  #error("operating system not (yet) supported")
#endif
}

#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h> // for GetFullPathName
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  #include <stdlib.h> // for realpath
  #include <linux/limits.h> // for PATH_MAX
#endif

Arcadia_FilePath*
Arcadia_FilePath_getFullPath
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self
  )
{
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
#define BUFFER_LENGTH (4096)
  Arcadia_String* s = Arcadia_FilePath_toNative(process, self);
  char buffer[BUFFER_LENGTH];
  DWORD result = GetFullPathName(Arcadia_String_getBytes(process, s), BUFFER_LENGTH, buffer, NULL);
  if (!result) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  return Arcadia_FilePath_parseNative(process, buffer, strlen(buffer));
#undef BUFFER_LENGTH
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_String* s = Arcadia_FilePath_toNative(process, self);
  char buffer[PATH_MAX];
  char* result = realpath(Arcadia_String_getBytes(process, s), buffer);
  if (!result) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  return Arcadia_FilePath_parseNative(process, buffer, strlen(buffer));
#else
  #error("operating system not (yet) supported")
#endif
}

Arcadia_BooleanValue
Arcadia_FilePath_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self,
    Arcadia_FilePath* other
  )
{
  self = Arcadia_FilePath_getFullPath(process, self);
  other = Arcadia_FilePath_getFullPath(process, other);
  if (self == other) {
    return Arcadia_BooleanValue_True;
  }
  if (self->relative != other->relative) {
    return Arcadia_BooleanValue_False;
  }
  if (Arcadia_List_getSize(process, self->fileNames) != Arcadia_List_getSize(process, other->fileNames)) {
    return Arcadia_BooleanValue_False;
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, self->fileNames); i < n; ++i) {
    Arcadia_Value x = Arcadia_List_getAt(process, self->fileNames, i);
    Arcadia_Value y = Arcadia_List_getAt(process, other->fileNames, i);
    if (!Arcadia_Value_isEqualTo(process, &x, &y)) {
      return Arcadia_BooleanValue_False;
    }
  }
  if ((self->root == NULL && other->root != NULL) || (self->root != NULL && other->root == NULL)) {
    return Arcadia_BooleanValue_False;
  }
  if (self->root != NULL) {
    Arcadia_Value args[2] = { { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = self->root },
                              { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = other->root } };
    if (!Arcadia_Value_isEqualTo(process, &args[0], &args[1])) {
      return Arcadia_BooleanValue_False;
    }
  }
  return Arcadia_BooleanValue_True;
}

Arcadia_BooleanValue
Arcadia_FilePath_isAbsolute
  (
    Arcadia_FilePath* self
  )
{ return !self->relative; }

Arcadia_BooleanValue
Arcadia_FilePath_isRelative
  (
    Arcadia_FilePath* self
  )
{ return self->relative; }

void
Arcadia_FilePath_append
  (
    Arcadia_Process* process,
    Arcadia_FilePath* self,
    Arcadia_FilePath* other
  )
{
  if (!Arcadia_FilePath_isRelative(other)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, other->fileNames); i < n; ++i) {
    Arcadia_Value v = Arcadia_List_getAt(process, other->fileNames, i);
    Arcadia_List_append(process, self->fileNames, v);
  }
}
