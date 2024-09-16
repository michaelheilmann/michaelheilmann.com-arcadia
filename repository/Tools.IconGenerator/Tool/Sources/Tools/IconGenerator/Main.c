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

// Last modified: 2024-09-16

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
  if (argc != 2) {
    fprintf(stderr, "usage Tools.IconGenerator <ico-file-path>\n");
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_List* pixelBufferList = R_List_create();
  R_SizeValue sizes[] = {
    8,
    16,
    32,
    48,
    64,
    96,
    128,
    256,
  };
  for (R_SizeValue i = 0, n = sizeof(sizes) / sizeof(size_t); i < n; ++i) {
    PixelBuffer* pixelBuffer = PixelBuffer_createOpaqueRed(0, sizes[i], sizes[i], PixelFormat_An8Rn8Gn8Bn8);
    R_List_appendObjectReferenceValue(pixelBufferList, (R_ObjectReferenceValue)pixelBuffer);
  }
  writeIconToPath(pixelBufferList, R_String_create(argv[1], strlen(argv[1])));
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
