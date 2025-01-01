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
#include "R.h"
#include "Module/Visuals/Include.h"

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  R_Value target;
  R_Value_setVoidValue(&target, Arcadia_VoidValue_Void);
  R_List* arguments = R_List_create(process);
  for (int argi = 1; argi < argc; ++argi) {
    R_String* argument = R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, argv[argi], strlen(argv[argi])));
    R_List_appendObjectReferenceValue(process, arguments, (R_ObjectReferenceValue)argument);
  }
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(arguments); i < n; ++i) {
    R_String* argument = (R_String*)R_List_getObjectReferenceValueAt(process, arguments, i);
    R_Utf8StringReader* r = R_Utf8StringReader_create(process, argument);
    R_String* key = NULL,
            * value = NULL;
    if (!R_CommandLine_parseArgument(process, (R_Utf8Reader*)r, &key, &value)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    if (R_String_isEqualTo_pn(key, u8"target", sizeof(u8"target") - 1)) {
      if (!value) {
        R_CommandLine_raiseNoValueError(process, key);
      }
      R_Value_setObjectReferenceValue(&target, value);
    } else {
      R_CommandLine_raiseUnknownArgumentError(process, key, value);
    }
    fwrite(R_String_getBytes(key), 1, R_String_getNumberOfBytes(key), stdout);
    if (value) {
      fwrite(u8"=", 1, sizeof(u8"=") - 1, stdout);
      fwrite(R_String_getBytes(value), 1, R_String_getNumberOfBytes(value), stdout);
    }
    fwrite(u8"\n", 1, sizeof(u8"\n") - 1, stdout);
  }
  if (R_Value_isVoidValue(&target)) {
    R_CommandLine_raiseRequiredArgumentMissingError(process, R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, u8"target", sizeof(u8"target") - 1)));
  }
  R_List* pixelBufferList = R_List_create(process);
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
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  ImageWriter* imageWriter = (ImageWriter*)NativeWindowsImageWriter_create(process);
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  ImageWriter* imageWriter = (ImageWriter*)NativeLinuxImageWriter_create(process);
#else
  #error("environment not (yet) supported")
#endif
  for (Arcadia_SizeValue i = 0, n = sizeof(sizes) / sizeof(size_t); i < n; ++i) {
    PixelBuffer* pixelBuffer = PixelBuffer_create(process, 0, sizes[i], sizes[i], PixelFormat_An8Rn8Gn8Bn8);
    R_List_appendObjectReferenceValue(process, pixelBufferList, (R_ObjectReferenceValue)pixelBuffer);
  }
  ImageWriter_writeIcoToPath(process, imageWriter, pixelBufferList, R_Value_getObjectReferenceValue(&target));
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    R_shutdown();
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  status[0] = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
