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

#include "R/FileHandle.h"

#include "R/FileSystem.h"
#include "R/FilePath.h"
#include "R/Object.h"
#include "R/String.h"
#include "R/ArgumentsValidation.h"

#define Flags_OpenRead (1)

#define Flags_OpenWrite (2)

static void
R_FileHandle_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_FileHandle_destruct
  (
    Arcadia_Process* process,
    R_FileHandle* self
  );

static void
R_FileHandle_visit
  (
    Arcadia_Process* process,
    R_FileHandle* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_FileHandle_constructImpl,
  .destruct = &R_FileHandle_destruct,
  .visit = &R_FileHandle_visit,
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

Rex_defineObjectType(u8"R.FileHandle", R_FileHandle, u8"R.Object", R_Object, &_typeOperations);

static void
R_FileHandle_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_FileHandle* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_FileHandle_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->fileSystem = R_Argument_getObjectReferenceValue(process, &argumentValues[0], _R_FileSystem_getType(process));
  R_Object_lock(process, _self->fileSystem);
  _self->fd = NULL;
  _self->flags = 0;
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_FileHandle_destruct
  (
    Arcadia_Process* process,
    R_FileHandle* self
  )
{
  if (self->fd) {
    if (self->fd != stdin && self->fd != stderr && self->fd != stdout) {
      fclose(self->fd);
    }
    self->fd = NULL;
    self->flags = 0;
  }
  R_Object_unlock(process, self->fileSystem);
  self->fileSystem = NULL;
}

static void
R_FileHandle_visit
  (
    Arcadia_Process* process,
    R_FileHandle* self
  )
{
  R_Object_visit(self->fileSystem);
}

R_FileHandle*
R_FileHandle_create
  (
    Arcadia_Process* process,
    R_FileSystem* fileSystem
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  if (fileSystem) {
    R_Value_setObjectReferenceValue(&argumentValues[0], fileSystem);
  }
  R_FileHandle* self = R_allocateObject(process, _R_FileHandle_getType(process), 1, &argumentValues[0]);
  return self;
}

void R_FileHandle_close(R_FileHandle* self) {
  if (self->fd) {
    if (self->fd != stdin && self->fd != stderr && self->fd != stdout) {
      fclose(self->fd);
    }
    self->fd = NULL;
    self->flags = 0;
  }
}

Arcadia_BooleanValue R_FileHandle_isClosed(Arcadia_Process* process, R_FileHandle const* self) {
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return 0 == ((Flags_OpenRead | Flags_OpenWrite) & self->flags);
}

Arcadia_BooleanValue R_FileHandle_isOpened(Arcadia_Process* process, R_FileHandle const* self) {
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return 0 != (Flags_OpenWrite & self->flags);
}

Arcadia_BooleanValue R_FileHandle_isOpenedForReading(Arcadia_Process* process, R_FileHandle const* self) {
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return 0 != (Flags_OpenRead & self->flags);
}

Arcadia_BooleanValue R_FileHandle_isOpenedForWriting(Arcadia_Process* process, R_FileHandle const* self) {
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return Flags_OpenWrite == (Flags_OpenWrite & self->flags);
}

void R_FileHandle_openForReading(Arcadia_Process* process, R_FileHandle* self, R_FilePath* path) {
  R_FileHandle_close(self);
  R_String* nativePathString = R_FilePath_toNative(process, path);
  self->fd = fopen(R_String_getBytes(nativePathString), "rb");
  if (!self->fd) {
    Arcadia_Process_setStatus(process, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Process_jump(process);
  }
  self->flags |= Flags_OpenRead;
}

void R_FileHandle_openForWriting(Arcadia_Process* process, R_FileHandle* self, R_FilePath* path) {
  R_FileHandle_close(self);
  R_String* nativePathString = R_FilePath_toNative(process, path);
  self->fd = fopen(R_String_getBytes(nativePathString), "wb");
  if (!self->fd) {
    Arcadia_Process_setStatus(process, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Process_jump(process);
  }
  self->flags |= Flags_OpenWrite;
}

void R_FileHandle_read(Arcadia_Process* process, R_FileHandle* self, void* bytes, Arcadia_SizeValue bytesToRead, Arcadia_SizeValue* bytesRead) {
  if (!bytes || !bytesRead) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (!R_FileHandle_isOpenedForReading(process, self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
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
      Arcadia_Process_setStatus(process, Arcadia_Status_FileSystemOperationFailed);
      Arcadia_Process_jump(process);
    }
  } else{
    *bytesRead = bytesReadNow;
  }
}

void R_FileHandle_write(Arcadia_Process* process, R_FileHandle* self, void const* bytes, Arcadia_SizeValue bytesToWrite, Arcadia_SizeValue* bytesWritten) {
  if (!bytes || !bytesWritten) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (!R_FileHandle_isOpenedForWriting(process, self)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  size_t bytesWrittenNow = fwrite(bytes, 1, bytesToWrite, self->fd);
  if (ferror(self->fd)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Process_jump(process);
  }
  *bytesWritten = bytesWrittenNow;
}
