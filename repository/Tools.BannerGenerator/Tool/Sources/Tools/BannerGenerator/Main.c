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

#include <stdlib.h>
#include "Arcadia/DDL/Include.h"
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Imaging/Include.h"

static void
main1
  (
    Arcadia_Thread* thread,
    int argc,
    char** argv
  )
{
  Arcadia_Value target, width, height;
  Arcadia_Value_setVoidValue(&target,Arcadia_VoidValue_Void);
  Arcadia_Value_setVoidValue(&width, Arcadia_VoidValue_Void);
  Arcadia_Value_setVoidValue(&height, Arcadia_VoidValue_Void);
  Arcadia_List* arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (int argi = 1; argi < argc; ++argi) {
    Arcadia_String* argument = Arcadia_String_createFromCxxString(thread, argv[argi]);
    Arcadia_List_insertBackObjectReferenceValue(thread, arguments, (Arcadia_ObjectReferenceValue)argument);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)arguments); i < n; ++i) {
    Arcadia_String* argument = (Arcadia_String*)Arcadia_List_getObjectReferenceValueAt(thread, arguments, i);
    Arcadia_UTF8StringReader *r = Arcadia_UTF8StringReader_create(thread, argument);
    Arcadia_String *key = NULL,
                   *value = NULL;
    if (!Arcadia_CommandLine_parseArgument(thread, (Arcadia_UTF8Reader*)r, &key, &value)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (Arcadia_String_isEqualTo_pn(thread, key, u8"target", sizeof(u8"target") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(thread, key);
      }
      Arcadia_Value_setObjectReferenceValue(&target, value);
    } else if (Arcadia_String_isEqualTo_pn(thread, key, u8"width", sizeof(u8"width") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(thread, key);
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Value_setInteger32Value(&width, Arcadia_String_toInteger32(thread, value));
        Arcadia_Thread_popJumpTarget(thread);
      } else {
        Arcadia_Thread_popJumpTarget(thread);
        Arcadia_CommandLine_raiseValueInvalidError(thread, key, value);
      }
    } else if(Arcadia_String_isEqualTo_pn(thread, key, u8"height", sizeof(u8"height") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(thread, key);
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Value_setInteger32Value(&height, Arcadia_String_toInteger32(thread, value));
        Arcadia_Thread_popJumpTarget(thread);
      } else {
        Arcadia_Thread_popJumpTarget(thread);
        Arcadia_CommandLine_raiseValueInvalidError(thread, key, value);
      }
    } else {
      Arcadia_CommandLine_raiseUnknownArgumentError(thread, key, value);
    }
    //
    Arcadia_FileHandle* fileHandle = Arcadia_FileSystem_createFileHandle(thread, Arcadia_FileSystem_getOrCreate(thread));
    Arcadia_FileHandle_openStandardOutput(thread, fileHandle);
    Arcadia_SizeValue numberOfArguments = 0;
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)key); numberOfArguments++;
    if (value) {
      Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)Arcadia_String_createFromCxxString(thread, u8" = ")); numberOfArguments++;
      Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)value); numberOfArguments++;
    }
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)Arcadia_String_createFromCxxString(thread, u8"\n")); numberOfArguments++;
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)fileHandle); numberOfArguments++;
    Arcadia_ValueStack_pushNatural8Value(thread, numberOfArguments);
    Arcadia_print(thread);
    //
  }
  if (Arcadia_Value_isVoidValue(&target)) {
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"target", sizeof(u8"target") - 1)));
  }
  if (Arcadia_Value_isVoidValue(&width)) {
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"width", sizeof(u8"width") - 1)));
  }
  if (Arcadia_Value_isVoidValue(&height)) {
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"height", sizeof(u8"height") - 1)));
  }
  Arcadia_Imaging_ImageManager* imageManager = Arcadia_Imaging_ImageManager_getOrCreate(thread);
  Arcadia_String* extension = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"png", sizeof(u8"png") - 1)));
  Arcadia_List* writers = Arcadia_Imaging_ImageManager_getWriters(thread, imageManager, extension);
  if (!Arcadia_Collection_getSize(thread, (Arcadia_Collection*)writers)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
    Arcadia_Thread_popJumpTarget(thread);
  }
  Arcadia_Imaging_ImageWriter* writer = (Arcadia_Imaging_ImageWriter*)Arcadia_List_getObjectReferenceValueAt(thread, writers, 0);
  Arcadia_Imaging_PixelBuffer* pixelBuffer = Arcadia_Imaging_PixelBuffer_create(thread, 0, Arcadia_Value_getInteger32Value(&width), Arcadia_Value_getInteger32Value(&height), Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8);
  Arcadia_List* pixelBufferList = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, pixelBufferList, pixelBuffer);

  Arcadia_Imaging_ImageWriterParameters* parameters = Arcadia_Imaging_ImageWriterParameters_createFile(thread, (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&target), extension);
  Arcadia_Imaging_ImageWriter_write(thread,
                                    writer,
                                    pixelBufferList,
                                    parameters);
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(thread, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(thread);
  Arcadia_Status status = Arcadia_Thread_getStatus(thread);
  thread = NULL;
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
