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
  Arcadia_Process* process = context->process;
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_ByteBuffer_append_pn(thread, context->byteBuffer, data, size);
  }
  Arcadia_Thread_popJumpTarget(thread);
}

void
_Visuals_Linux_writeBmpToByteBuffer
  (
    Arcadia_Thread* thread,
    PixelBuffer* pixelBuffer,
    Arcadia_ByteBuffer* byteBuffer
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  WriteContext context;
  context.process = process;
  context.byteBuffer = byteBuffer;

  int components;
  switch (pixelBuffer->pixelFormat) {
    case PixelFormat_Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(thread, pixelBuffer);
      PixelBuffer_setLinePadding(thread, pixelBuffer, 0);
      components = 3;
    } break;
    case PixelFormat_An8Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(thread, pixelBuffer);
      PixelBuffer_setPixelFormat(thread, pixelBuffer, PixelFormat_Bn8Gn8Rn8An8);
      PixelBuffer_setLinePadding(thread, pixelBuffer, 0);
      components = 4;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };

  if (!stbi_write_bmp_to_func((stbi_write_func*)&writeCallback, &context,
                              PixelBuffer_getWidth(thread, pixelBuffer),
                              PixelBuffer_getHeight(thread, pixelBuffer),
                              components,
                              pixelBuffer->bytes)) {
    context.status = Arcadia_Status_EnvironmentFailed;
  }
  if (context.status) {
    Arcadia_Thread_setStatus(thread, context.status);
    Arcadia_Thread_jump(thread);
  }
}
