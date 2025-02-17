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

// Last modified: 2025-02-02

#include "Module/Visuals/Linux/Include.h"

#include "R/Include.h"
#include "Module/Visuals/PixelBuffer.h"

#define STB_IMAGE_WRITE_STATIC static
#define STBIWDEF
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Module/Visuals/Linux/stb_image_write.h"

typedef struct WriteContext {
  Arcadia_Process* process;
  Arcadia_ByteBuffer* byteBuffer;
  Arcadia_Status status;
} WriteContext;

static void
writeCallback
  (
    WriteContext* writeContext,
    void* data,
    int size
  );

static void
writeCallback
  (
    WriteContext* context,
    void* data,
    int size
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(context->process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_ByteBuffer_append_pn(context->process, context->byteBuffer, data, size);
  }
  Arcadia_Process_popJumpTarget(context->process);
}

void
_Visuals_Linux_writeBmpToByteBuffer
  (
    Arcadia_Process* process,
    PixelBuffer* pixelBuffer,
    Arcadia_ByteBuffer* byteBuffer
  )
{
  WriteContext context;
  context.process = process;
  context.byteBuffer = byteBuffer;

  int components;
  switch (pixelBuffer->pixelFormat) {
    case PixelFormat_Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(process, pixelBuffer);
      PixelBuffer_setLinePadding(process, pixelBuffer, 0);
      components = 3;
    } break;
    case PixelFormat_An8Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(process, pixelBuffer);
      PixelBuffer_setPixelFormat(process, pixelBuffer, PixelFormat_Bn8Gn8Rn8An8);
      PixelBuffer_setLinePadding(process, pixelBuffer, 0);
      components = 4;
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    } break;
  };

  if (!stbi_write_bmp_to_func((stbi_write_func*)&writeCallback, &context,
                              PixelBuffer_getWidth(pixelBuffer),
                              PixelBuffer_getHeight(pixelBuffer),
                               components,
                              pixelBuffer->bytes)) {
    context.status = Arcadia_Status_EnvironmentFailed;
  }
  if (context.status) {
    Arcadia_Process_setStatus(process, context.status);
    Arcadia_Process_jump(process);
  }
}
