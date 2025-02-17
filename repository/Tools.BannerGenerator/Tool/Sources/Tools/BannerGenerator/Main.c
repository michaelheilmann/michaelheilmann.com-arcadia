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
  Arcadia_Value target, width, height;
  Arcadia_Value_setVoidValue(&target,Arcadia_VoidValue_Void);
  Arcadia_Value_setVoidValue(&width, Arcadia_VoidValue_Void);
  Arcadia_Value_setVoidValue(&height, Arcadia_VoidValue_Void);
  Arcadia_List* arguments = Arcadia_List_create(process);
  for (int argi = 1; argi < argc; ++argi) {
    Arcadia_String* argument = Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), argv[argi], strlen(argv[argi])));
    Arcadia_List_appendObjectReferenceValue(process, arguments, (Arcadia_ObjectReferenceValue)argument);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, arguments); i < n; ++i) {
    Arcadia_String* argument = (Arcadia_String*)Arcadia_List_getObjectReferenceValueAt(process, arguments, i);
    Arcadia_Utf8StringReader *r = Arcadia_Utf8StringReader_create(process, argument);
    Arcadia_String *key = NULL,
             *value = NULL;
    if (!Arcadia_CommandLine_parseArgument(process, (Arcadia_Utf8Reader*)r, &key, &value)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    if (Arcadia_String_isEqualTo_pn(process, key, u8"target", sizeof(u8"target") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(process, key);
      }
      Arcadia_Value_setObjectReferenceValue(&target, value);
    } else if (Arcadia_String_isEqualTo_pn(process, key, u8"width", sizeof(u8"width") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(process, key);
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Process_pushJumpTarget(process, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Value_setInteger32Value(&width, Arcadia_String_toInteger32(process, value));
        Arcadia_Process_popJumpTarget(process);
      } else {
        Arcadia_Process_popJumpTarget(process);
        Arcadia_CommandLine_raiseValueInvalidError(process, key, value);
      }
    } else if(Arcadia_String_isEqualTo_pn(process, key, u8"height", sizeof(u8"height") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(process, key);
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Process_pushJumpTarget(process, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Value_setInteger32Value(&height, Arcadia_String_toInteger32(process, value));
        Arcadia_Process_popJumpTarget(process);
      } else {
        Arcadia_Process_popJumpTarget(process);
        Arcadia_CommandLine_raiseValueInvalidError(process, key, value);
      }
    } else {
      Arcadia_CommandLine_raiseUnknownArgumentError(process, key, value);
    }
    fwrite(Arcadia_String_getBytes(process, key), 1, Arcadia_String_getNumberOfBytes(process, key), stdout);
    if (value) {
      fwrite(u8"=", 1, sizeof(u8"=") - 1, stdout);
      fwrite(Arcadia_String_getBytes(process, value), 1, Arcadia_String_getNumberOfBytes(process, value), stdout);
    }
    fwrite(u8"\n", 1, sizeof(u8"\n") - 1, stdout);
  }
  if (Arcadia_Value_isVoidValue(&target)) {
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(process, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"target", sizeof(u8"target") - 1)));
  }
  if (Arcadia_Value_isVoidValue(&width)) {
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(process, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"width", sizeof(u8"width") - 1)));
  }
  if (Arcadia_Value_isVoidValue(&height)) {
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(process, Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), u8"height", sizeof(u8"height") - 1)));
  }
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  ImageWriter* imageWriter = (ImageWriter*)NativeWindowsImageWriter_create(process);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  ImageWriter* imageWriter = (ImageWriter*)NativeLinuxImageWriter_create(process);
#else
  #error("environment not (yet) supported")
#endif
  PixelBuffer* pixelBuffer = PixelBuffer_create(process, 0, Arcadia_Value_getInteger32Value(&width), Arcadia_Value_getInteger32Value(&height), PixelFormat_An8Rn8Gn8Bn8);
  ImageWriter_writePngToPath(process, imageWriter, pixelBuffer, Arcadia_Value_getObjectReferenceValue(&target));
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
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  Arcadia_Status status = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
