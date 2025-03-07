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

// Last modified: 2024-09-16

#include <stdlib.h>
#include <string.h>
#include "R/Include.h"
#include "Module/Visuals/Include.h"

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_Value target;
  Arcadia_Value_setVoidValue(&target, Arcadia_VoidValue_Void);
  Arcadia_List* arguments = Arcadia_List_create(thread);
  for (int argi = 1; argi < argc; ++argi) {
    Arcadia_String* argument = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, argv[argi], strlen(argv[argi])));
    Arcadia_List_appendObjectReferenceValue(thread, arguments, (Arcadia_ObjectReferenceValue)argument);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, arguments); i < n; ++i) {
    Arcadia_String* argument = (Arcadia_String*)Arcadia_List_getObjectReferenceValueAt(thread, arguments, i);
    Arcadia_Utf8StringReader* r = Arcadia_Utf8StringReader_create(thread, argument);
    Arcadia_String* key = NULL,
                  * value = NULL;
    if (!Arcadia_CommandLine_parseArgument(thread, (Arcadia_Utf8Reader*)r, &key, &value)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (Arcadia_String_isEqualTo_pn(thread, key, u8"target", sizeof(u8"target") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(thread, key);
      }
      Arcadia_Value_setObjectReferenceValue(&target, value);
    } else {
      Arcadia_CommandLine_raiseUnknownArgumentError(thread, key, value);
    }
    fwrite(Arcadia_String_getBytes(thread, key), 1, Arcadia_String_getNumberOfBytes(thread, key), stdout);
    if (value) {
      fwrite(u8"=", 1, sizeof(u8"=") - 1, stdout);
      fwrite(Arcadia_String_getBytes(thread, value), 1, Arcadia_String_getNumberOfBytes(thread, value), stdout);
    }
    fwrite(u8"\n", 1, sizeof(u8"\n") - 1, stdout);
  }
  if (Arcadia_Value_isVoidValue(&target)) {
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"target", sizeof(u8"target") - 1)));
  }
  Arcadia_List* pixelBufferList = Arcadia_List_create(thread);
  Arcadia_SizeValue sizes[] = {
    8,
    16,
    32,
    48,
    64,
    96,
    128,
    256,
  };
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  ImageWriter* imageWriter = (ImageWriter*)NativeWindowsImageWriter_create(thread);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  ImageWriter* imageWriter = (ImageWriter*)NativeLinuxImageWriter_create(thread);
#else
  #error("environment not (yet) supported")
#endif
  for (Arcadia_SizeValue i = 0, n = sizeof(sizes) / sizeof(size_t); i < n; ++i) {
    PixelBuffer* pixelBuffer = PixelBuffer_create(thread, 0, sizes[i], sizes[i], PixelFormat_An8Rn8Gn8Bn8);
    Arcadia_List_appendObjectReferenceValue(thread, pixelBufferList, (Arcadia_ObjectReferenceValue)pixelBuffer);
  }
  ImageWriter_writeIcoToPath(thread, imageWriter, pixelBufferList, Arcadia_Value_getObjectReferenceValue(&target));
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Status status;
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(thread);
  status = Arcadia_Thread_getStatus(thread);
  thread = NULL;
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
