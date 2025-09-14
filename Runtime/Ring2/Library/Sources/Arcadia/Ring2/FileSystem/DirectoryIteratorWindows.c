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
#include "Arcadia/Ring2/FileSystem/DirectoryIteratorWindows.h"

#include "Arcadia/Ring2/Implementation/ArgumentsValidation.h"
#include "Arcadia/Ring2/Implementation/StringBuffer.h"
#include "Arcadia/Ring2/Implementation/StringExtensions.h"
#include "Arcadia/Ring2/FileSystem/FilePath.h"

static void
Arcadia_DirectoryIteratorWindows_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );
  
static void
Arcadia_DirectoryIteratorWindows_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorWindows* self
  );

static Arcadia_FilePath*
Arcadia_DirectoryIteratorWindows_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorWindows* self
  );

static Arcadia_BooleanValue
Arcadia_DirectoryIteratorWindows_hasValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorWindows* self
  );

static void
Arcadia_DirectoryIteratorWindows_nextValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorWindows* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_DirectoryIteratorWindows_constructImpl,
  .destruct = &Arcadia_DirectoryIteratorWindows_destructImpl,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DirectoryIteratorWindows", Arcadia_DirectoryIteratorWindows,
                         u8"Arcadia.DirectoryIterator", Arcadia_DirectoryIterator,
                         &_typeOperations);

static void
Arcadia_DirectoryIteratorWindows_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  static uint32_t zeroTerminator = '\0';
  Arcadia_DirectoryIteratorWindows* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DirectoryIteratorWindows_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->path = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_FilePath_getType(thread));
  _self->handle = INVALID_HANDLE_VALUE;
  Arcadia_StringBuffer* queryStringBuilder = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertBack(thread, queryStringBuilder, Arcadia_Value_makeObjectReferenceValue(Arcadia_FilePath_toNative(thread, _self->path)));
  Arcadia_StringBuffer_removeCodePointsBack(thread, queryStringBuilder, 1);
  // (1) Append '/' if the path does not end with '/'.
  if (!Arcadia_StringBuffer_endsWith_pn(thread, queryStringBuilder, u8"\\", sizeof(u8"\\") - 1)) {
    Arcadia_StringBuffer_insertBackCxxString(thread, queryStringBuilder, u8"\\");
  }
  // (2) Append '*\0'.
  Arcadia_StringBuffer_insertBackCxxString(thread, queryStringBuilder, u8"*");
  Arcadia_StringBuffer_insertCodePointsBack(thread, queryStringBuilder, &zeroTerminator, 1);
  Arcadia_String* queryString = Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(queryStringBuilder));
  SetLastError(0);
  _self->handle = FindFirstFileA(Arcadia_String_getBytes(thread, queryString), &_self->data);
  if (INVALID_HANDLE_VALUE == _self->handle) {
    DWORD dwLastError = GetLastError();
    SetLastError(0);
    if (dwLastError == ERROR_FILE_NOT_FOUND) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_FileNotFound);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
  ((Arcadia_DirectoryIterator*)_self)->getValue = (Arcadia_FilePath* (*)(Arcadia_Thread*, Arcadia_DirectoryIterator*)) & Arcadia_DirectoryIteratorWindows_getValue;
  ((Arcadia_DirectoryIterator*)_self)->hasValue = (Arcadia_BooleanValue (*)(Arcadia_Thread*, Arcadia_DirectoryIterator*)) &Arcadia_DirectoryIteratorWindows_hasValue;
  ((Arcadia_DirectoryIterator*)_self)->nextValue = (void (*)(Arcadia_Thread*, Arcadia_DirectoryIterator*)) &Arcadia_DirectoryIteratorWindows_nextValue;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

static void
Arcadia_DirectoryIteratorWindows_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorWindows* self
  )
{
  if (self->handle) {
    FindClose(self->handle);
    self->handle = INVALID_HANDLE_VALUE;
  }
}

static Arcadia_FilePath*
Arcadia_DirectoryIteratorWindows_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorWindows* self
  )
{
  if (INVALID_HANDLE_VALUE == self->handle) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_String* fileNameString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, self->data.cFileName, strlen(self->data.cFileName))));
    return Arcadia_FilePath_parseNative(thread, fileNameString);
  }
}

static Arcadia_BooleanValue
Arcadia_DirectoryIteratorWindows_hasValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorWindows* self
  )
{ return INVALID_HANDLE_VALUE != self->handle; }

static void
Arcadia_DirectoryIteratorWindows_nextValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorWindows* self
  )
{ 
  if (self->handle != INVALID_HANDLE_VALUE) {
    SetLastError(0);
    BOOL result = FindNextFileA(self->handle, &self->data);
    if (!result) {
      FindClose(self->handle);
      self->handle = INVALID_HANDLE_VALUE;
      if (GetLastError() == ERROR_NO_MORE_FILES) {
        SetLastError(0);
      } else {
        SetLastError(0);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    }
  }
}

Arcadia_DirectoryIteratorWindows*
Arcadia_DirectoryIteratorWindows_create
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* path
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)path);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DirectoryIteratorWindows);
}
