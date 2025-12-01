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
#include "Arcadia/Ring2/FileSystem/Linux/DirectoryIteratorLinux.h"

#include "Arcadia/Ring2/Implementation/ArgumentsValidation.h"
#include "Arcadia/Ring2/Strings/StringBuffer.h"
#include "Arcadia/Ring2/FileSystem/FilePath.h"

#include <string.h>
#include <errno.h>
#if (Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Macos)
	#include <sys/types.h>
	#include <sys/dir.h>
#else
	#include <dirent.h>
#endif

static void
Arcadia_DirectoryIteratorLinux_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  );

static void
Arcadia_DirectoryIteratorLinux_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  );

static Arcadia_FilePath*
Arcadia_DirectoryIteratorLinux_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  );

static Arcadia_BooleanValue
Arcadia_DirectoryIteratorLinux_hasValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  );

static void
Arcadia_DirectoryIteratorLinux_nextValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_DirectoryIteratorLinux_constructImpl,
  .destruct = &Arcadia_DirectoryIteratorLinux_destructImpl,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DirectoryIteratorLinux", Arcadia_DirectoryIteratorLinux,
                         u8"Arcadia.DirectoryIterator", Arcadia_DirectoryIterator,
                         &_typeOperations);

static void
Arcadia_DirectoryIteratorLinux_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DirectoryIteratorLinux_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  // Clear errno.
  errno = 0;
  // Open directory.
  Arcadia_String* path = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_FilePath_getType(thread));
  Arcadia_String* pathString = Arcadia_FilePath_toNative(thread, path);
  self->dir = opendir(Arcadia_String_getBytes(thread, pathString));
  if (!self->dir) {
    switch (errno) {
      case ENOENT: {
        errno = 0;
        Arcadia_Thread_setStatus(thread, Arcadia_Status_FileNotFound);
        Arcadia_Thread_jump(thread);
      } break;
      case EMFILE:
      case ENOMEM: {
        errno = 0;
        Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
        Arcadia_Thread_jump(thread);
      } break;
      case EACCES:
      case EBADF:
      default: {
        errno = 0;
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      } break;
    };
  }
  // Read first directory entry.
  self->dirent = readdir(self->dir);
  if (!self->dirent) {
    closedir(self->dir);
    self->dir = NULL;
    if (errno) {
      errno = 0;
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
  ((Arcadia_DirectoryIterator*)self)->getValue = (Arcadia_FilePath* (*)(Arcadia_Thread*, Arcadia_DirectoryIterator*)) & Arcadia_DirectoryIteratorLinux_getValue;
  ((Arcadia_DirectoryIterator*)self)->hasValue = (Arcadia_BooleanValue (*)(Arcadia_Thread*, Arcadia_DirectoryIterator*)) &Arcadia_DirectoryIteratorLinux_hasValue;
  ((Arcadia_DirectoryIterator*)self)->nextValue = (void (*)(Arcadia_Thread*, Arcadia_DirectoryIterator*)) &Arcadia_DirectoryIteratorLinux_nextValue;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

Arcadia_DirectoryIteratorLinux*
Arcadia_DirectoryIteratorLinux_create
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* path
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)path);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DirectoryIteratorLinux);
}

static void
Arcadia_DirectoryIteratorLinux_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  )
{
  if (self->dir) {
    if (self->dirent) {
      self->dirent = NULL;
    }
    closedir(self->dir);
    self->dir = NULL;
  }
}

static Arcadia_FilePath*
Arcadia_DirectoryIteratorLinux_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  )
{
  if (self->dirent) {
    Arcadia_String* fileNameString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, self->dirent->d_name, strlen(self->dirent->d_name))));
    return Arcadia_FilePath_parseNative(thread, fileNameString);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static Arcadia_BooleanValue
Arcadia_DirectoryIteratorLinux_hasValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  )
{
  return NULL != self->dirent;
}

static void
Arcadia_DirectoryIteratorLinux_nextValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIteratorLinux* self
  )
{
  errno = 0;
  self->dirent = readdir(self->dir);
  if (!self->dirent) {
    closedir(self->dir);
    self->dir = NULL;
    if (errno) {
      errno = 0;
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
}
