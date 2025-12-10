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
#include "Arcadia/Ring2/FileSystem/FileSystem.h"

#include "Arcadia/Ring2/FileSystem/Implementation/DefaultFileSystem.h"
#include "Arcadia/Ring2/Include.h"

static void
Arcadia_FileSystem_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

static void
Arcadia_FileSystem_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystemDispatch* self
  );

static void
Arcadia_FileSystem_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

static void
Arcadia_FileSystem_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_FileSystem_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_FileSystem_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_FileSystem_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.FileSystem", Arcadia_FileSystem,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_FileSystem_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_FileSystem_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_FileSystem_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystemDispatch* self
  )
{ }

static void
Arcadia_FileSystem_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_FileSystem_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{/*Intentionally empty.*/}

void
Arcadia_FileSystem_createDirectoryFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCall(Arcadia_FileSystem, createDirectoryFile, self, path); }

void
Arcadia_FileSystem_createRegularFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCall(Arcadia_FileSystem, createRegularFile, self, path); }

Arcadia_DirectoryIterator*
Arcadia_FileSystem_createDirectoryIterator
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, createDirectoryIterator, self, path); }

Arcadia_FileHandle*
Arcadia_FileSystem_createFileHandle
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, createFileHandle, self); }

void
Arcadia_FileSystem_deleteDirectoryFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCall(Arcadia_FileSystem, deleteDirectoryFile, self, path); }

void
Arcadia_FileSystem_deleteFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCall(Arcadia_FileSystem, deleteFile, self, path); }

void
Arcadia_FileSystem_deleteRegularFile
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCall(Arcadia_FileSystem, deleteRegularFile, self, path); }

Arcadia_BooleanValue
Arcadia_FileSystem_directoryFileExists
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, directoryFileExists, self, path); }

Arcadia_FilePath*
Arcadia_FileSystem_getWorkingDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, getWorkingDirectory, self); }

Arcadia_FilePath*
Arcadia_FileSystem_getConfigurationDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, getConfigurationDirectory, self); }

Arcadia_FilePath*
Arcadia_FileSystem_getExecutable
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, getExecutable, self); }

Arcadia_ByteBuffer*
Arcadia_FileSystem_getFileContents
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, getFileContents, self, path); }

Arcadia_FileType
Arcadia_FileSystem_getFileType
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, getFileType, self, path); }

Arcadia_Natural64Value
Arcadia_FileSystem_getLastWriteTime
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, getLastWriteTime, self, path); }

Arcadia_FilePath*
Arcadia_FileSystem_getSaveDirectory
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, getSaveDirectory, self); }

Arcadia_BooleanValue
Arcadia_FileSystem_regularFileExists
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileSystem, regularFileExists, self, path); }

void
Arcadia_FileSystem_setFileContents
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path,
    Arcadia_ByteBuffer* contents
  )
{ Arcadia_VirtualCall(Arcadia_FileSystem, setFileContents, self, path, contents); }

Arcadia_FileSystem*
Arcadia_FileSystem_getOrCreate
  (
    Arcadia_Thread* thread
  )
{ return (Arcadia_FileSystem*)Arcadia_DefaultFileSystem_getOrCreate(thread); }
