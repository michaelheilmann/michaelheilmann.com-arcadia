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
#include "Arcadia/Ring2/FileSystem/FileHandle.h"

#include "Arcadia/Ring2/Include.h"

#define Flags_OpenRead (1)

#define Flags_OpenWrite (2)

static void
Arcadia_FileHandle_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  );

static void
Arcadia_FileHandle_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandleDispatch* self
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
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_FileHandle_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_FileHandle_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_FileHandle_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.FileHandle", Arcadia_FileHandle,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_FileHandle_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_FileHandle_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_FileHandle_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandleDispatch* self
  )
{ }

static void
Arcadia_FileHandle_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_FileHandle_visit
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{/*Intentionally empty.*/}

void
Arcadia_FileHandle_close
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{ Arcadia_VirtualCall(Arcadia_FileHandle, close, self); }

Arcadia_BooleanValue
Arcadia_FileHandle_isClosed
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileHandle, isClosed, self); }

Arcadia_BooleanValue
Arcadia_FileHandle_isOpened
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileHandle, isOpened, self); }

Arcadia_BooleanValue
Arcadia_FileHandle_isOpenedForReading
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileHandle, isOpenedForReading, self); }

Arcadia_BooleanValue
Arcadia_FileHandle_isOpenedForWriting
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle const* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_FileHandle, isOpenedForWriting, self); }

void
Arcadia_FileHandle_openForReading
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCall(Arcadia_FileHandle, openForReading, self, path); }

void
Arcadia_FileHandle_openForWriting
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_FilePath* path
  )
{ Arcadia_VirtualCall(Arcadia_FileHandle, openForWriting, self, path); }

void
Arcadia_FileHandle_read
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    void* bytes,
    Arcadia_SizeValue bytesToRead,
    Arcadia_SizeValue* bytesRead
  )
{ Arcadia_VirtualCall(Arcadia_FileHandle, read, self, bytes, bytesToRead, bytesRead); }

void
Arcadia_FileHandle_write
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    void const* bytes,
    Arcadia_SizeValue bytesToWrite,
    Arcadia_SizeValue* bytesWritten
  )
{ Arcadia_VirtualCall(Arcadia_FileHandle, write, self, bytes, bytesToWrite, bytesWritten); }

void
Arcadia_FileHandle_openStandardError
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{ Arcadia_VirtualCall(Arcadia_FileHandle, openStandardError, self); }

void
Arcadia_FileHandle_openStandardInput
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{ Arcadia_VirtualCall(Arcadia_FileHandle, openStandardInput, self); }

void
Arcadia_FileHandle_openStandardOutput
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
{ Arcadia_VirtualCall(Arcadia_FileHandle, openStandardOutput, self); }
