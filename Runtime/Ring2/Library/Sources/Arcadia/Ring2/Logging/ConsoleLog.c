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

#define ARCADIA_RING2_MODULE (1)
#include "Arcadia/Ring2/Logging/ConsoleLog.h"

#include "Arcadia/Ring2/FileSystem/Include.h"

static void
Arcadia_ConsoleLog_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self
  );

static void
Arcadia_ConsoleLog_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLogDispatch* self
  );

static void
Arcadia_ConsoleLog_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self
  );

static void
Arcadia_ConsoleLog_informationImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    Arcadia_String* message
  );

static void
Arcadia_ConsoleLog_warningImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    Arcadia_String* message
  );

static void
Arcadia_ConsoleLog_errorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    Arcadia_String* message
  );

static void
writeBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    const Arcadia_Natural8Value* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_ConsoleLog_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_ConsoleLog_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_ConsoleLog_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ConsoleLog", Arcadia_ConsoleLog,
                         u8"Arcadia.Log", Arcadia_Log,
                         &_typeOperations);

static void
Arcadia_ConsoleLog_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self
  )
{
  Arcadia_EnterConstructor(Arcadia_ConsoleLog);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  self->colorEnabled = Arcadia_BooleanValue_True;
  self->fileHandle = Arcadia_FileSystem_createFileHandle(thread, fileSystem);
  Arcadia_FileHandle_openStandardOutput(thread, self->fileHandle);
  Arcadia_LeaveConstructor(Arcadia_ConsoleLog);
}

static void
Arcadia_ConsoleLog_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLogDispatch* self
  )
{
  ((Arcadia_LogDispatch*)self)->information = (void (*)(Arcadia_Thread*, Arcadia_Log*, Arcadia_String*)) & Arcadia_ConsoleLog_informationImpl;
  ((Arcadia_LogDispatch*)self)->warning = (void (*)(Arcadia_Thread*, Arcadia_Log*, Arcadia_String*)) & Arcadia_ConsoleLog_warningImpl;
  ((Arcadia_LogDispatch*)self)->error = (void (*)(Arcadia_Thread*, Arcadia_Log*, Arcadia_String*)) & Arcadia_ConsoleLog_errorImpl;
}

static void
Arcadia_ConsoleLog_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self
  )
{
  if (self->fileHandle) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->fileHandle);
  }
}

static void
Arcadia_ConsoleLog_informationImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    Arcadia_String* message
  )
{
  const char* p = Arcadia_String_getBytes(thread, message);
  Arcadia_SizeValue n = Arcadia_String_getNumberOfBytes(thread, message);
  if (self->colorEnabled) {
    writeBytes(thread, self, u8"\033[38;2;0;255;0m", sizeof(u8"\033[38;2;0;255;0m") - 1);
  }
  writeBytes(thread, self, p, n);
  if (self->colorEnabled) {
    writeBytes(thread, self, u8"\033[0m", sizeof(u8"\033[0m") - 1);
  }
}

static void
Arcadia_ConsoleLog_warningImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    Arcadia_String* message
  )
{
  const char* p = Arcadia_String_getBytes(thread, message);
  Arcadia_SizeValue n = Arcadia_String_getNumberOfBytes(thread, message);
  if (self->colorEnabled) {
    writeBytes(thread, self, u8"\033[38;2;0;255;0m", sizeof(u8"\033[38;2;0;255;0m") - 1);
  }
  writeBytes(thread, self, p, n);
  if (self->colorEnabled) {
    writeBytes(thread, self, u8"\033[0m", sizeof(u8"\033[0m") - 1);
  }
}

static void
Arcadia_ConsoleLog_errorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    Arcadia_String* message
  )
{
  const char* p = Arcadia_String_getBytes(thread, message);
  Arcadia_SizeValue n = Arcadia_String_getNumberOfBytes(thread, message);
  if (self->colorEnabled) {
    writeBytes(thread, self, u8"\033[38;2;255;0;0m", sizeof(u8"\033[38;2;255;0;0m") - 1);
  }
  writeBytes(thread, self, p, n);
}

static void
writeBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    const Arcadia_Natural8Value* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_SizeValue written = 0, toWrite = numberOfBytes;
  Arcadia_SizeValue numberOfAttempts = 0, maximumNumberOfAttempts = 3;
  while (toWrite) {
    Arcadia_SizeValue writtenNow = 0;
    Arcadia_FileHandle_write(thread, self->fileHandle, bytes + written, toWrite, &writtenNow);
    if (writtenNow == 0) {
      if (numberOfAttempts == maximumNumberOfAttempts) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationFailed);
        Arcadia_Thread_jump(thread);
      }
      numberOfAttempts++;
    } else {
      numberOfAttempts = 0;
      toWrite -= writtenNow;
      written += writtenNow;
    }
  }
}

Arcadia_ConsoleLog*
Arcadia_ConsoleLog_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_ConsoleLog);
}

void
Arcadia_ConsoleLog_setColorEnabled
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    Arcadia_BooleanValue colorEnabled
  )
{ self->colorEnabled = colorEnabled; }

Arcadia_BooleanValue
Arcadia_ConsoleLog_getColorEnabled
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self
  )
{ return self->colorEnabled; }
