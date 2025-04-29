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

// Last modified: 2024-10-07

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Implementation/FileHandle.h"

#include "Arcadia/Ring2/Implementation/FileSystem.h"
#include "Arcadia/Ring2/Implementation/FilePath.h"
#include "Arcadia/Ring2/Implementation/String.h"
#include "R/ArgumentsValidation.h"

#define Flags_OpenRead (1)

#define Flags_OpenWrite (2)

static void
Arcadia_FileHandle_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_FileHandle_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  );

static void
Arcadia_FileHandle_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_FileHandle_constructImpl,
  .destruct = &Arcadia_FileHandle_destruct,
  .visit = &Arcadia_FileHandle_visit,
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

Arcadia_defineObjectType(u8"Arcadia.FileHandle", Arcadia_FileHandle, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_FileHandle_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_FileHandle* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_FileHandle_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->fileSystem = R_Argument_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_FileSystem_getType(thread));
  Arcadia_Object_lock(thread, _self->fileSystem);
  _self->fd = NULL;
  _self->flags = 0;
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_FileHandle_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{
  if (self->fd) {
    if (self->fd != stdin && self->fd != stderr && self->fd != stdout) {
      fclose(self->fd);
    }
    self->fd = NULL;
    self->flags = 0;
  }
  Arcadia_Object_unlock(thread, self->fileSystem);
  self->fileSystem = NULL;
}

static void
Arcadia_FileHandle_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{
  Arcadia_Object_visit(thread, self->fileSystem);
}

Arcadia_FileHandle*
Arcadia_FileHandle_create
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* fileSystem
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  if (fileSystem) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[0], fileSystem);
  }
  Arcadia_FileHandle* self = Arcadia_allocateObject(thread, _Arcadia_FileHandle_getType(thread), 1, &argumentValues[0]);
  return self;
}

void
Arcadia_FileHandle_close
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{
  if (self->fd) {
    if (self->fd != stdin && self->fd != stderr && self->fd != stdout) {
      fclose(self->fd);
    }
    self->fd = NULL;
    self->flags = 0;
  }
}

Arcadia_BooleanValue
Arcadia_FileHandle_isClosed
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return 0 == ((Flags_OpenRead | Flags_OpenWrite) & self->flags);
}

Arcadia_BooleanValue
Arcadia_FileHandle_isOpened
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return 0 != (Flags_OpenWrite & self->flags);
}

Arcadia_BooleanValue
Arcadia_FileHandle_isOpenedForReading
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return 0 != (Flags_OpenRead & self->flags);
}

Arcadia_BooleanValue
Arcadia_FileHandle_isOpenedForWriting
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Flags_OpenWrite == (Flags_OpenWrite & self->flags);
}

void
Arcadia_FileHandle_openForReading
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_FileHandle_close(thread, self);
  Arcadia_String* nativePathString = Arcadia_FilePath_toNative(thread, path);
  self->fd = fopen(Arcadia_String_getBytes(thread, nativePathString), "rb");
  if (!self->fd) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Thread_jump(thread);
  }
  self->flags |= Flags_OpenRead;
}

void
Arcadia_FileHandle_openForWriting
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_FileHandle_close(thread, self);
  Arcadia_String* nativePathString = Arcadia_FilePath_toNative(thread, path);
  self->fd = fopen(Arcadia_String_getBytes(thread, nativePathString), "wb");
  if (!self->fd) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Thread_jump(thread);
  }
  self->flags |= Flags_OpenWrite;
}

void
Arcadia_FileHandle_read
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    void* bytes,
    Arcadia_SizeValue bytesToRead,
    Arcadia_SizeValue* bytesRead
  )
{
  if (!bytes || !bytesRead) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_FileHandle_isOpenedForReading(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!bytesToRead) {
    *bytesRead = 0;
    return;
  }
  size_t bytesReadNow = fread(bytes, 1, bytesToRead, self->fd);
  if (bytesReadNow < bytesToRead) {
    if (feof(self->fd)) {
      *bytesRead = bytesReadNow;
    } else if (ferror(self->fd)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_FileSystemOperationFailed);
      Arcadia_Thread_jump(thread);
    }
  } else{
    *bytesRead = bytesReadNow;
  }
}

void
Arcadia_FileHandle_write
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    void const* bytes,
    Arcadia_SizeValue bytesToWrite,
    Arcadia_SizeValue* bytesWritten
  )
{
  if (!bytes || !bytesWritten) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_FileHandle_isOpenedForWriting(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  size_t bytesWrittenNow = fwrite(bytes, 1, bytesToWrite, self->fd);
  if (ferror(self->fd)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Thread_jump(thread);
  }
  *bytesWritten = bytesWrittenNow;
}
