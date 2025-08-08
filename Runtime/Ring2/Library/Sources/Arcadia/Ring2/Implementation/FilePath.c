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
    Arcadia_Thread* thread,
    Context* context
  );

static void
saveAndNext
  (
    Arcadia_Thread* thread,
    Context* context
  );

static Arcadia_BooleanValue
isEnd
  (
    Arcadia_Thread* thread,
    Context* context
  );

static Arcadia_BooleanValue
isDriveLetter
  (
    Arcadia_Thread* thread,
    Context* context
  );

static Arcadia_BooleanValue
isColon
  (
    Arcadia_Thread* thread,
    Context* context
  );

static Arcadia_BooleanValue
isDirectorySeparator
  (
    Arcadia_Thread* thread,
    Context* context
  );

static Arcadia_BooleanValue
isSlash
  (
    Arcadia_Thread* thread,
    Context* context
  );

static void
normalize
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

/* https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file#fully-qualified-vs-relative-paths */
static void
parseWindowsFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  );

static void
parseUnixFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  );

static void
parseGenericFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  );

static void
next
  (
    Arcadia_Thread* thread,
    Context* context
  )
{ Arcadia_Utf8Reader_next(thread, context->reader); }

static void
saveAndNext
  (
    Arcadia_Thread* thread,
    Context* context
  )
{
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->reader);
  Arcadia_Utf8Writer_writeCodePoints(thread, context->temporaryWriter, &codePoint, 1);
  next(thread, context);
}

static Arcadia_BooleanValue
isEnd
  (
    Arcadia_Thread* thread,
    Context* context
  )
{ return !Arcadia_Utf8Reader_hasCodePoint(thread, context->reader); }

static Arcadia_BooleanValue
isDriveLetter
  (
    Arcadia_Thread* thread,
    Context* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->reader);
  return ('a' <= codePoint && codePoint <= 'z')
      || ('A' <= codePoint && codePoint <= 'Z');
}

static Arcadia_BooleanValue
isColon
  (
    Arcadia_Thread* thread,
    Context* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->reader);
  return ':' == codePoint;
}

static Arcadia_BooleanValue
isDirectorySeparator
  (
    Arcadia_Thread* thread,
    Context* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->reader);
  return ('\\' == codePoint || '/' == codePoint);
}

static Arcadia_BooleanValue
isSlash
  (
    Arcadia_Thread* thread,
    Context* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->reader)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value codePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->reader);
  return '/' == codePoint;
}

// <filename> <dot-dot> => delete this
// <dot> => delete this
static void
normalize
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
{
  Arcadia_SizeValue previous = 0, current = 1;
  while (current < Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->fileNames)) {
    Arcadia_Value t;
    t = Arcadia_List_getAt(thread, self->fileNames, previous);
    Arcadia_String* previousString = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&t);
    t = Arcadia_List_getAt(thread, self->fileNames, current);
    Arcadia_String* currentString = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&t);
    if (!Arcadia_String_isEqualTo_pn(thread, previousString, "..", sizeof("..") - 1) &&
        !Arcadia_String_isEqualTo_pn(thread, previousString, u8".", sizeof(u8".")) &&
         Arcadia_String_isEqualTo_pn(thread, currentString, u8"..", sizeof(u8"..") - 1)) {
   // Remove previous and current.
      Arcadia_List_removeAt(thread, self->fileNames, previous, 2);
    } else if (Arcadia_String_isEqualTo_pn(thread, currentString, u8".", sizeof(u8".") - 1)) {
      // Remove current.
      Arcadia_List_removeAt(thread, self->fileNames, current, 1);
    } else {
      previous++;
      current++;
    }
  }
  if (!self->root && Arcadia_Collection_isEmpty(thread, (Arcadia_Collection*)self->fileNames)) {
    // If the path is empty, then the path is `.`.
    Arcadia_List_insertBackObjectReferenceValue(thread, self->fileNames, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8".", sizeof(u8".") - 1)));
  }
}

static void
parseWindowsFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  )
{
  Context context;
  context.reader = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, source);
  context.temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context.temporaryWriter = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, context.temporaryBuffer);
  context.target = target;

  target->relative = Arcadia_BooleanValue_False;
  target->root = NULL;
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)target->fileNames);

  if (isDriveLetter(thread, &context)) {
    saveAndNext(thread, &context);
    if (isColon(thread, &context)) {
      next(thread, &context);
      if (isDirectorySeparator(thread, &context)) {
        // absolute.
        context.target->relative = Arcadia_BooleanValue_False;
        next(thread, &context);
        Arcadia_Value temporaryValue;
        Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        context.target->root = Arcadia_String_create(thread, temporaryValue);
        Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
      } else {
        // relative to "root" drive and the diretory on the drive
        context.target->relative = Arcadia_BooleanValue_True;
        Arcadia_Value temporaryValue;
        Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        context.target->root = Arcadia_String_create(thread, temporaryValue);
        Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
      }
    } else {
      while (!isEnd(thread, &context) && !isDirectorySeparator(thread, &context)) {
        saveAndNext(thread, &context);
      }
      if (Arcadia_ByteBuffer_getNumberOfBytes(thread, context.temporaryBuffer)) {
        Arcadia_Value temporary;
        Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(thread, temporary));
        Arcadia_List_insertBack(thread, context.target->fileNames, temporary);
        Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
      }
      target->relative = Arcadia_BooleanValue_True;
    }
  } else if (isDirectorySeparator(thread, &context)) {
    // relative to the root of the current drive.
    context.target->relative = Arcadia_BooleanValue_True;
    next(thread, &context);
  } else {
    context.target->relative = Arcadia_BooleanValue_True;
  }
  // read the remaining directories
  Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
  while (!isEnd(thread, &context)) {
    if (isDirectorySeparator(thread, &context)) {
      next(thread, &context);
      if (Arcadia_ByteBuffer_getNumberOfBytes(thread, context.temporaryBuffer)) {
        Arcadia_Value temporary;
        Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(thread, temporary));
        Arcadia_List_insertBack(thread, context.target->fileNames, temporary);
        Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
      }
    } else {
      saveAndNext(thread, &context);
    }
  }
  if (Arcadia_ByteBuffer_getNumberOfBytes(thread, context.temporaryBuffer)) {
    Arcadia_Value temporary;
    Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
    Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(thread, temporary));
    Arcadia_List_insertBack(thread, context.target->fileNames, temporary);
    Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
  }
}

static void
parseUnixFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  )
{
  Context context;
  context.reader = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, source);
  context.temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context.temporaryWriter = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, context.temporaryBuffer);
  context.target = target;

  target->relative = Arcadia_BooleanValue_True;
  target->root = NULL;
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)target->fileNames);

  if (isSlash(thread, &context)) {
    target->relative = Arcadia_BooleanValue_False;
    target->root = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"/", sizeof(u8"/") - 1));
    next(thread, &context);
  }
  // read the remaining directories
  Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
  while (!isEnd(thread, &context)) {
    if (isDirectorySeparator(thread, &context)) {
      next(thread, &context);
      if (Arcadia_ByteBuffer_getNumberOfBytes(thread, context.temporaryBuffer)) {
        Arcadia_Value temporary;
        Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(thread, temporary));
        Arcadia_List_insertBack(thread, context.target->fileNames, temporary);
        Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
      }
    } else {
      saveAndNext(thread, &context);
    }
  }
  if (Arcadia_ByteBuffer_getNumberOfBytes(thread, context.temporaryBuffer)) {
    Arcadia_Value temporary;
    Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
    Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(thread, temporary));
    Arcadia_List_insertBack(thread, context.target->fileNames, temporary);
    Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
  }
}

static void
parseGenericFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* target,
    Arcadia_ByteBuffer* source
  )
{
  Context context;
  context.reader = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, source);
  context.temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context.temporaryWriter = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, context.temporaryBuffer);
  context.target = target;

  target->relative = Arcadia_BooleanValue_True;
  target->root = NULL;
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)target->fileNames);

  if (isSlash(thread, &context)) {
    target->relative = Arcadia_BooleanValue_False;
    target->root = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"/", sizeof(u8"/") - 1));
    next(thread, &context);
  }
  // read the remaining directories
  Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
  while (!isEnd(thread, &context)) {
    if (isDirectorySeparator(thread, &context)) {
      next(thread, &context);
      if (Arcadia_ByteBuffer_getNumberOfBytes(thread, context.temporaryBuffer)) {
        Arcadia_Value temporary;
        Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
        Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(thread, temporary));
        Arcadia_List_insertBack(thread, context.target->fileNames, temporary);
        Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
      }
    } else {
      saveAndNext(thread, &context);
    }
  }
  if (Arcadia_ByteBuffer_getNumberOfBytes(thread, context.temporaryBuffer)) {
    Arcadia_Value temporary;
    Arcadia_Value_setObjectReferenceValue(&temporary, (Arcadia_ObjectReferenceValue)context.temporaryBuffer);
    Arcadia_Value_setObjectReferenceValue(&temporary, Arcadia_String_create(thread, temporary));
    Arcadia_List_insertBack(thread, context.target->fileNames, temporary);
    Arcadia_ByteBuffer_clear(thread, context.temporaryBuffer);
  }
}

static void
Arcadia_FilePath_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_FilePath_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

static void
Arcadia_FilePath_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_FilePath_constructImpl,
  .destruct = &Arcadia_FilePath_destruct,
  .visit = &Arcadia_FilePath_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Library.FilePath", Arcadia_FilePath,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_FilePath_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_FilePath* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_FilePath_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->fileNames = NULL;
  _self->relative = Arcadia_BooleanValue_False;
  _self->root = NULL;
  _self->fileNames = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_FilePath_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_FilePath_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->fileNames);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->root);
}

Arcadia_FilePath*
Arcadia_FilePath_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_FilePath* self = Arcadia_allocateObject(thread, _Arcadia_FilePath_getType(thread), 0, &argumentValues[0]);
  return self;
}

Arcadia_FilePath*
Arcadia_FilePath_clone
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self  
  )
{
  Arcadia_FilePath* clone = Arcadia_FilePath_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->fileNames); i < n; ++i) {
    Arcadia_List_insertBack(thread, clone->fileNames, Arcadia_List_getAt(thread, self->fileNames, i));
  }
  clone->root = self->root;
  clone->relative = self->relative;
  return clone;
}

Arcadia_FilePath*
Arcadia_FilePath_parseWindows
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  )
{
  Arcadia_TypeValue _type = _Arcadia_FilePath_getType(thread);
  Arcadia_Value argumentValues[] = { Arcadia_Value_Initializer() };
  Arcadia_FilePath* self = Arcadia_allocateObject(thread, _type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = Arcadia_BooleanValue_False;
  self->root = NULL;
  self->fileNames = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_ByteBuffer_append_pn(thread, byteBuffer, Arcadia_String_getBytes(thread, string), Arcadia_String_getNumberOfBytes(thread, string));
  parseWindowsFilePath(thread, self, byteBuffer);
  normalize(thread, self);
  return self;
}

Arcadia_FilePath*
Arcadia_FilePath_parseUnix
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  )
{
  Arcadia_TypeValue _type = _Arcadia_FilePath_getType(thread);
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_FilePath* self = Arcadia_allocateObject(thread, _type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = Arcadia_BooleanValue_False;
  self->root = NULL;
  self->fileNames = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_ByteBuffer_append_pn(thread, byteBuffer, Arcadia_String_getBytes(thread, string), Arcadia_String_getNumberOfBytes(thread, string));
  parseUnixFilePath(thread, self, byteBuffer);
  normalize(thread, self);
  return self;
}

Arcadia_FilePath*
Arcadia_FilePath_parseNative
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  )
 {
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  return Arcadia_FilePath_parseWindows(thread, string);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  return Arcadia_FilePath_parseUnix(thread, string);
#else
  #error("operating system not (yet) supported")
#endif
}

Arcadia_String*
Arcadia_FilePath_toNative
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
{
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  Arcadia_ByteBuffer* temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_Utf8Writer* temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, temporaryBuffer);
  Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->fileNames);

  if (self->root) {
    Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, self->root), Arcadia_String_getNumberOfBytes(thread, self->root));
    Arcadia_Natural32Value x;
    x = ':';
    Arcadia_Utf8Writer_writeCodePoints(thread, temporary, &x, 1);
    if (!self->relative) {
      x = '\\';
      Arcadia_Utf8Writer_writeCodePoints(thread, temporary, &x, 1);
    } else {
      /* Intentionally empty. */
    }
  }
  if (n > 0) {
    Arcadia_Value e = Arcadia_List_getAt(thread, self->fileNames, 0);
    Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
    Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, fileName), Arcadia_String_getNumberOfBytes(thread, fileName));
    i++;

    for (; i < n; ++i) {
      Arcadia_Natural32Value x;
      x = '\\';
      Arcadia_Utf8Writer_writeCodePoints(thread, temporary, &x, 1);

      Arcadia_Value e = Arcadia_List_getAt(thread, self->fileNames, i);
      Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
      Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, fileName), Arcadia_String_getNumberOfBytes(thread, fileName));
    }
  }
  Arcadia_Natural32Value x = '\0';
  Arcadia_Utf8Writer_writeCodePoints(thread, temporary, &x, 1);
  Arcadia_Value temporaryValue;
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)temporaryBuffer);
  return Arcadia_String_create(thread, temporaryValue);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_ByteBuffer* temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_Utf8Writer* temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, temporaryBuffer);
  Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->fileNames);
  if (self->root) {
    Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, self->root), Arcadia_String_getNumberOfBytes(thread, self->root));
  }
  if (n > 0) {
    Arcadia_Value e = Arcadia_List_getAt(thread, self->fileNames, 0);
    Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
    Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, fileName), Arcadia_String_getNumberOfBytes(thread, fileName));
    i++;

    for (; i < n; ++i) {
      Arcadia_Natural32Value x;
      x = '/';
      Arcadia_Utf8Writer_writeCodePoints(thread, temporary, &x, 1);

      Arcadia_Value e = Arcadia_List_getAt(thread, self->fileNames, i);
      Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
      Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, fileName), Arcadia_String_getNumberOfBytes(thread, fileName));
    }
  }
  Arcadia_Natural32Value x = '\0';
  Arcadia_Utf8Writer_writeCodePoints(thread, temporary, &x, 1);
  Arcadia_Value temporaryValue;
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)temporaryBuffer);
  return Arcadia_String_create(thread, temporaryValue);
#else
  #error("operating system not (yet) supported")
#endif
}

Arcadia_FilePath*
Arcadia_FilePath_parseGeneric
  (
    Arcadia_Thread* thread,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_TypeValue _type = _Arcadia_FilePath_getType(thread);
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_FilePath* self = Arcadia_allocateObject(thread, _type, 0, &argumentValues[0]);
  self->fileNames = NULL;
  self->relative = Arcadia_BooleanValue_False;
  self->root = NULL;
  self->fileNames = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_ByteBuffer_append_pn(thread, byteBuffer, bytes, numberOfBytes);
  parseGenericFilePath(thread, self, byteBuffer);
  normalize(thread, self);
  return self;
}

Arcadia_String*
Arcadia_FilePath_toGeneric
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
{
  Arcadia_ByteBuffer* temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_Utf8Writer* temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, temporaryBuffer);
  Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->fileNames);
  if (self->root) {
    Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, self->root), Arcadia_String_getNumberOfBytes(thread, self->root));
  }
  if (n > 0) {
    Arcadia_Value e = Arcadia_List_getAt(thread, self->fileNames, 0);
    Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
    Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, fileName), Arcadia_String_getNumberOfBytes(thread, fileName));
    i++;

    for (; i < n; ++i) {
      Arcadia_Natural32Value x;
      x = '/';
      Arcadia_Utf8Writer_writeCodePoints(thread, temporary, &x, 1);

      Arcadia_Value e = Arcadia_List_getAt(thread, self->fileNames, i);
      Arcadia_String* fileName = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&e);
      Arcadia_Utf8Writer_writeBytes(thread, temporary, Arcadia_String_getBytes(thread, fileName), Arcadia_String_getNumberOfBytes(thread, fileName));
    }
  }
  Arcadia_Natural32Value x = '\0';
  Arcadia_Utf8Writer_writeCodePoints(thread, temporary, &x, 1);
  Arcadia_Value temporaryValue;
  Arcadia_Value_setObjectReferenceValue(&temporaryValue, (Arcadia_ObjectReferenceValue)temporaryBuffer);
  return Arcadia_String_create(thread, temporaryValue);
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
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
{
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
#define BUFFER_LENGTH (4096)
  Arcadia_String* s = Arcadia_FilePath_toNative(thread, self);
  char buffer[BUFFER_LENGTH];
  DWORD result = GetFullPathName(Arcadia_String_getBytes(thread, s), BUFFER_LENGTH, buffer, NULL);
  if (!result) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_FilePath_parseNative(thread, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, buffer, strlen(buffer)))));
#undef BUFFER_LENGTH
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_String* s = Arcadia_FilePath_toNative(thread, self);
  char buffer[PATH_MAX];
  char* result = realpath(Arcadia_String_getBytes(thread, s), buffer);
  if (!result) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_FilePath_parseNative(thread, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, buffer, strlen(buffer)))));
#else
  #error("operating system not (yet) supported")
#endif
}

Arcadia_BooleanValue
Arcadia_FilePath_isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self,
    Arcadia_FilePath* other
  )
{
  self = Arcadia_FilePath_getFullPath(thread, self);
  other = Arcadia_FilePath_getFullPath(thread, other);
  if (self == other) {
    return Arcadia_BooleanValue_True;
  }
  if (self->relative != other->relative) {
    return Arcadia_BooleanValue_False;
  }
  if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->fileNames) != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)other->fileNames)) {
    return Arcadia_BooleanValue_False;
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->fileNames); i < n; ++i) {
    Arcadia_Value x = Arcadia_List_getAt(thread, self->fileNames, i);
    Arcadia_Value y = Arcadia_List_getAt(thread, other->fileNames, i);
    if (!Arcadia_Value_isEqualTo(thread, &x, &y)) {
      return Arcadia_BooleanValue_False;
    }
  }
  if ((self->root == NULL && other->root != NULL) || (self->root != NULL && other->root == NULL)) {
    return Arcadia_BooleanValue_False;
  }
  if (self->root != NULL) {
    Arcadia_Value args[2] = { Arcadia_Value_Initializer(),
                              Arcadia_Value_Initializer() };
    Arcadia_Value_setObjectReferenceValue(&args[0], self->root);
    Arcadia_Value_setObjectReferenceValue(&args[1], other->root);
    if (!Arcadia_Value_isEqualTo(thread, &args[0], &args[1])) {
      return Arcadia_BooleanValue_False;
    }
  }
  return Arcadia_BooleanValue_True;
}

Arcadia_BooleanValue
Arcadia_FilePath_isAbsolute
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
{ return !self->relative; }

Arcadia_BooleanValue
Arcadia_FilePath_isRelative
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
{ return self->relative; }

void
Arcadia_FilePath_append
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self,
    Arcadia_FilePath* other
  )
{
  if (!Arcadia_FilePath_isRelative(thread, other)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)other->fileNames); i < n; ++i) {
    Arcadia_Value v = Arcadia_List_getAt(thread, other->fileNames, i);
    Arcadia_List_insertBack(thread, self->fileNames, v);
  }
}
