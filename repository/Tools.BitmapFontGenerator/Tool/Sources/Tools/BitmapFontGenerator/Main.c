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

// Last modified: 2024-09-28

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
  Arcadia_Value target;
  Arcadia_Value_setVoidValue(&target,Arcadia_VoidValue_Void);
  R_List* arguments = R_List_create(process);
  for (int argi = 1; argi < argc; ++argi) {
    Arcadia_String* argument = Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getBackendNoLock(process), argv[argi], strlen(argv[argi])));
    R_List_appendObjectReferenceValue(process, arguments, (Arcadia_ObjectReferenceValue)argument);
  }
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(arguments); i < n; ++i) {
    Arcadia_String* argument = (Arcadia_String*)R_List_getObjectReferenceValueAt(process, arguments, i);
    R_Utf8StringReader *r = R_Utf8StringReader_create(process, argument);
    Arcadia_String *key = NULL,
             *value = NULL;
    if (!R_CommandLine_parseArgument(process, (R_Utf8Reader*)r, &key, &value)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    if (Arcadia_String_isEqualTo_pn(process, key, u8"target", sizeof(u8"target") - 1)) {
      if (!value) {
        R_CommandLine_raiseNoValueError(process, key);
      }
      Arcadia_Value_setObjectReferenceValue(&target, value);
    } else {
      R_CommandLine_raiseUnknownArgumentError(process, key, value);
    }
    fwrite(Arcadia_String_getBytes(process, key), 1, Arcadia_String_getNumberOfBytes(process, key), stdout);
    if (value) {
      fwrite(u8"=", 1, sizeof(u8"=") - 1, stdout);
      fwrite(Arcadia_String_getBytes(process, value), 1, Arcadia_String_getNumberOfBytes(process, value), stdout);
    }
    fwrite(u8"\n", 1, sizeof(u8"\n") - 1, stdout);
  }
  if (Arcadia_Value_isVoidValue(&target)) {
    R_CommandLine_raiseRequiredArgumentMissingError(process, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getBackendNoLock(process), u8"target", sizeof(u8"target") - 1)));
  }
  TextureFontWindows* font = TextureFontWindows_create(process);
  PixelBuffer* pixelBuffer = TextureFontWindows_getPixelBuffer(process, font);
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  ImageWriter* imageWriter = (ImageWriter*)NativeWindowsImageWriter_create(process);
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  ImageWriter* imageWriter = (ImageWriter*)NativeLinuxImageWriter_create();
#else
  #error("environment not (yet) supported")
#endif
  ImageWriter_writePngToPath(process, imageWriter, pixelBuffer, Arcadia_Value_getObjectReferenceValue(&target));
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
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
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
