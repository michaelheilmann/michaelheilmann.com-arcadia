// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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
#include "Tools/Visuals2d/Include.h"

void
main1
  (
    int argc,
    char** argv
  )
{
  R_Value target, width, height;
  R_Value_setVoidValue(&target,R_VoidValue_Void);
  R_Value_setVoidValue(&width, R_VoidValue_Void);
  R_Value_setVoidValue(&height, R_VoidValue_Void);
  R_List* arguments = R_List_create();
  for (int argi = 1; argi < argc; ++argi) {
    R_String* argument = R_String_create_pn(argv[argi], strlen(argv[argi]));
    R_List_appendObjectReferenceValue(arguments, (R_ObjectReferenceValue)argument);
  }
  R_String* prefix = R_String_create_pn(u8"--", sizeof(u8"--") - 1);
  for (R_SizeValue i = 0, n = R_List_getSize(arguments); i < n; ++i) {
    R_String* argument = (R_String*)R_List_getObjectReferenceValueAt(arguments, i);
    R_Utf8StringReader *r = R_Utf8StringReader_create(argument);
    R_String *key = NULL,
             *value = NULL;
    if (!R_CommandLine_parseArgument((R_Utf8Reader*)r, &key, &value)) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    if (R_String_isEqualTo_pn(key, u8"target", sizeof(u8"target") - 1)) {
      if (!value) {
        R_CommandLine_raiseNoValueError(key);
      }
      R_Value_setObjectReferenceValue(&target, value);
    } else if (R_String_isEqualTo_pn(key, u8"width", sizeof(u8"width") - 1)) {
      if (!value) {
        R_CommandLine_raiseNoValueError(key);
      }
      R_JumpTarget jumpTarget;
      R_pushJumpTarget(&jumpTarget);
      if (R_JumpTarget_save(&jumpTarget)) {
        R_Value_setInteger32Value(&width, R_String_toInteger32(value));
        R_popJumpTarget();
      } else {
        R_popJumpTarget();
        R_CommandLine_raiseValueInvalidError(key, value);
      }
    } else if(R_String_isEqualTo_pn(key, u8"height", sizeof(u8"height") - 1)) {
      if (!value) {
        R_CommandLine_raiseNoValueError(key);
      }
      R_JumpTarget jumpTarget;
      R_pushJumpTarget(&jumpTarget);
      if (R_JumpTarget_save(&jumpTarget)) {
        R_Value_setInteger32Value(&height, R_String_toInteger32(value));
        R_popJumpTarget();
      } else {
        R_popJumpTarget();
        R_CommandLine_raiseValueInvalidError(key, value);
      }
    } else {
      R_CommandLine_raiseUnknownArgumentError(key, value);
    }
    fwrite(key->p, 1, key->numberOfBytes, stdout);
    if (value) {
      fwrite(u8"=", 1, sizeof(u8"=") - 1, stdout);
      fwrite(value->p, 1, value->numberOfBytes, stdout);
    }
    fwrite(u8"\n", 1, sizeof(u8"\n") - 1, stdout);
  }
  if (R_Value_isVoidValue(&target)) {
    R_CommandLine_raiseRequiredArgumentMissingError(R_String_create_pn(u8"target", sizeof(u8"target") - 1));
  }
  if (R_Value_isVoidValue(&width)) {
    R_CommandLine_raiseRequiredArgumentMissingError(R_String_create_pn(u8"target", sizeof(u8"target") - 1));
  }
  if (R_Value_isVoidValue(&height)) {
    R_CommandLine_raiseRequiredArgumentMissingError(R_String_create_pn(u8"target", sizeof(u8"target") - 1));
  }
  PixelBuffer* pixelBuffer = PixelBuffer_createOpaqueBlack(0, R_Value_getInteger32Value(&width), R_Value_getInteger32Value(&height), PixelFormat_An8Rn8Gn8Bn8);
#if 0
  writeBmpToPath(pixelBuffer, R_String_create(u8"test.bmp", sizeof("u8test.bmp") - 1));
#endif
  writePngToPath(pixelBuffer, R_Value_getObjectReferenceValue(&target));
#if 0
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  writePngToByteBuffer(pixelBuffer, byteBuffer);
  R_FileSystem_setFileContents(R_FileSystem_create(), R_FilePath_parseUnixFilePath("test2.png", sizeof("test2.png") - 1), byteBuffer);
  R_ByteBuffer* iconByteBuffer = R_ByteBuffer_create();
#endif
}

int
main
  (
    int argc,
    char** argv
  )
{
  R_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    _PixelBuffer_registerType();
    _ImageWriterParameters_registerType();
    main1(argc, argv);
    R_popJumpTarget();
  }
  status[0] = R_getStatus();
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
