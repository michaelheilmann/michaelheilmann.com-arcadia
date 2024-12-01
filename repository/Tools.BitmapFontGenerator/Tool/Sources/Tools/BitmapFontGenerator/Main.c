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
#include "Module/Visuals/Include.h"

void
main1
  (
    int argc,
    char** argv
  )
{
  R_Value target;
  R_Value_setVoidValue(&target,R_VoidValue_Void);
  R_List* arguments = R_List_create();
  for (int argi = 1; argi < argc; ++argi) {
    R_String* argument = R_String_create_pn(R_ImmutableByteArray_create(argv[argi], strlen(argv[argi])));
    R_List_appendObjectReferenceValue(arguments, (R_ObjectReferenceValue)argument);
  }
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
    } else {
      R_CommandLine_raiseUnknownArgumentError(key, value);
    }
    fwrite(R_String_getBytes(key), 1, R_String_getNumberOfBytes(key), stdout);
    if (value) {
      fwrite(u8"=", 1, sizeof(u8"=") - 1, stdout);
      fwrite(R_String_getBytes(value), 1, R_String_getNumberOfBytes(value), stdout);
    }
    fwrite(u8"\n", 1, sizeof(u8"\n") - 1, stdout);
  }
  if (R_Value_isVoidValue(&target)) {
    R_CommandLine_raiseRequiredArgumentMissingError(R_String_create_pn(R_ImmutableByteArray_create(u8"target", sizeof(u8"target") - 1)));
  }
  TextureFontWindows* font = TextureFontWindows_create();
  PixelBuffer* pixelBuffer = TextureFontWindows_getPixelBuffer(font);
  writePngToPath(pixelBuffer, R_Value_getObjectReferenceValue(&target));
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
