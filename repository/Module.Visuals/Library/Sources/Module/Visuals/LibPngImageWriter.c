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

#include "Module/Visuals/LibPngImageWriter.h"

#include "Module/Visuals/ImageWriterParameters.h"
#include "Module/Visuals/Linux/Include.h"

#include <png.h>

static void
LibPngImageWriter_writePngToPathImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
LibPngImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static void
LibPngImageWriter_writeBmpToPathImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
LibPngImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

// We do not have an encoder for "ico" files under Linux.
//
// The "ico" file format is described on Wikipedia.
// See https://en.wikipedia.org/wiki/ICO_(file_format) for more information.
//
// From the description of the file format:
// - The width and height of any image in an "ico" files may not exceed 256.
// - all source pixel buffers must be of format PixelBuffer_An8Rn8Gn8Bn8.
static void
LibPngImageWriter_writeIcoToPathImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
LibPngImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

typedef struct LibPngState {
  png_structp png_struct;
  png_infop png_info;
  uint8_t** row_pointers;
} LibPngState;

typedef struct LibPngWriteState {
  Arcadia_ByteBuffer* byteBuffer;
  Arcadia_Process* process;
} LibPngWriteState;

#include <malloc.h> // @todo Use functionality provided by Arcadia_Process.

void LibPngState_destroy(Arcadia_Thread* thread, LibPngState* state) {
  if (state->row_pointers) {
    free(state->row_pointers);
    state->row_pointers = NULL;
  }
  png_destroy_write_struct(&state->png_struct, &state->png_info);
  free(state);
}

LibPngState* LibPngState_create(Arcadia_Thread* thread) {
  LibPngState* state = malloc(sizeof(LibPngState));
  if (!state) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  state->png_struct = NULL;
  state->png_info = NULL;
  state->row_pointers = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    state->png_struct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!state->png_struct) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    state->png_info = png_create_info_struct(state->png_struct);
    if (!state->png_info) {
      png_destroy_write_struct(&state->png_struct, (png_infopp)NULL);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (!state->png_info) {
      png_destroy_write_struct(&state->png_struct, (png_infopp)NULL);
    }
    free(state);
    state = NULL;
    Arcadia_Thread_jump(thread);
  }
  return state;
}

static void
on_write
  (
    png_structp png_struct,
    png_bytep data,
    png_size_t length
  )
{
  LibPngWriteState* ws = (LibPngWriteState*)png_get_io_ptr(png_struct);
  Arcadia_Thread* thread = Arcadia_Process_getThread(ws->process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_ByteBuffer_append_pn(thread, ws->byteBuffer, data, length);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    png_error(png_struct, "error");
  }
}

static void
on_flush
  (
    png_structp png_struct
  )
{/*Intentionally empty.*/}

static void
LibPngImageWriter_writePngToPathImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  LibPngState* state = NULL;
  int bitDepth;
  int colorType;

  switch (Arcadia_Visuals_PixelBuffer_getPixelFormat(thread, sourcePixelBuffer)) {
    case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8:
    case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8:
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8:
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8: {
      Arcadia_Visuals_PixelBuffer* pixelBuffer = Arcadia_Visuals_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Visuals_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGBA;
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8:
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
      Arcadia_Visuals_PixelBuffer* pixelBuffer = Arcadia_Visuals_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Visuals_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGB;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };
  uint32_t width = Arcadia_Visuals_PixelBuffer_getWidth(thread, sourcePixelBuffer);
  uint32_t height = Arcadia_Visuals_PixelBuffer_getHeight(thread, sourcePixelBuffer);
  uint32_t lineStride = Arcadia_Visuals_PixelBuffer_getLineStride(thread, sourcePixelBuffer);
  //uint32_t pixelBytes = Arcadia_Visuals_PixelBuffer_getBytesPerPixel(thread, sourcePixelBuffer);
  uint8_t* pixels = sourcePixelBuffer->bytes;

  state = LibPngState_create(thread);
  FILE* fp = NULL;
  if (!setjmp(png_jmpbuf(state->png_struct))) {
    state->row_pointers = malloc(sizeof(uint8_t*) * height);
    if (!state->row_pointers) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    for (size_t i = 0; i < height; ++i) {
      state->row_pointers[i] = pixels + lineStride * i;
    }
    Arcadia_FilePath* filePath = Arcadia_FilePath_parseNative(thread, Arcadia_String_getBytes(thread, targetPath), Arcadia_String_getNumberOfBytes(thread, targetPath));
    Arcadia_String* filePathString = Arcadia_FilePath_toNative(thread, filePath);
    fp = fopen(Arcadia_String_getBytes(thread, filePathString), "wb");
    if (!fp) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    png_init_io(state->png_struct, fp);
    png_set_IHDR
      (
        state->png_struct,
        state->png_info,
        width, height,
        bitDepth,
        colorType,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
      );
    png_write_info(state->png_struct, state->png_info);
    png_write_image(state->png_struct, state->row_pointers);
    png_write_end(state->png_struct, NULL);
  } else {
    LibPngState_destroy(thread, state);
    state = NULL;
    if (fp) {
      fclose(fp);
      fp = NULL;
    }
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  LibPngState_destroy(thread, state);
  state = NULL;
  if (fp) {
    fclose(fp);
    fp = NULL;
  }
}

static void
LibPngImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  LibPngState* state = NULL;
  int bitDepth;
  int colorType;

  switch (Arcadia_Visuals_PixelBuffer_getPixelFormat(thread, sourcePixelBuffer)) {
    case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8:
    case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8:
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8:
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8: {
      Arcadia_Visuals_PixelBuffer* pixelBuffer = Arcadia_Visuals_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Visuals_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGBA;
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8:
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
      Arcadia_Visuals_PixelBuffer* pixelBuffer = Arcadia_Visuals_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Visuals_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGB;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };
  uint32_t width = Arcadia_Visuals_PixelBuffer_getWidth(thread, sourcePixelBuffer);
  uint32_t height = Arcadia_Visuals_PixelBuffer_getHeight(thread, sourcePixelBuffer);
  uint32_t lineStride = Arcadia_Visuals_PixelBuffer_getLineStride(thread, sourcePixelBuffer);
  //uint32_t pixelBytes = Arcadia_Visuals_PixelBuffer_getBytesPerPixel(thread, sourcePixelBuffer);
  uint8_t* pixels = sourcePixelBuffer->bytes;

  state = LibPngState_create(thread);
  if (!setjmp(png_jmpbuf(state->png_struct))) {
    state->row_pointers = malloc(sizeof(uint8_t*) * height);
    if (!state->row_pointers) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    for (size_t i = 0; i < height; ++i) {
      state->row_pointers[i] = pixels + lineStride * i;
    }
    LibPngWriteState writeState = { .byteBuffer = targetByteBuffer, .process = Arcadia_Thread_getProcess(thread) };
    png_set_write_fn(state->png_struct, &writeState, &on_write, &on_flush),
    png_set_IHDR
      (
        state->png_struct,
        state->png_info,
        width, height,
        bitDepth,
        colorType,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
      );
    png_write_info(state->png_struct, state->png_info);
    png_write_image(state->png_struct, state->row_pointers);
    png_write_end(state->png_struct, NULL);
  } else {
    LibPngState_destroy(thread, state);
    state = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  LibPngState_destroy(thread, state);
  state = NULL;
}

static void
LibPngImageWriter_writeBmpToPathImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(thread);
  ImageWriter_writeBmpToByteBuffer(thread, (ImageWriter*)self, sourcePixelBuffer, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_create(thread),
                                     Arcadia_FilePath_parseUnix(thread, Arcadia_String_getBytes(thread, targetPath), Arcadia_String_getNumberOfBytes(thread, targetPath)), targetByteBuffer);
}

static void
LibPngImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{ _Visuals_Linux_writeBmpToByteBuffer(thread, sourcePixelBuffer, targetByteBuffer); }

static void
LibPngImageWriter_writeIcoToPathImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(thread);
  ImageWriter_writeIcoToByteBuffer(thread, (ImageWriter*)self, sourcePixelBuffers, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_create(thread), Arcadia_FilePath_parseUnix(thread, Arcadia_String_getBytes(thread, targetPath), Arcadia_String_getNumberOfBytes(thread, targetPath)), targetByteBuffer);
}

static void
LibPngImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Thread* thread,
    LibPngImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  typedef struct ICONDIR {
    uint16_t reserved1;
    uint16_t type;
    uint16_t numberOfImages;
  } ICONDIR;

  typedef struct ICONDIRENTRY {
    uint8_t width;
    uint8_t height;
    uint8_t numberOfColors;
    uint8_t reserved1;
    uint16_t numberOfColorPlanes;
    uint16_t numberOfBitsPerPixel;
    uint32_t imageSize;
    uint32_t offset;
  } ICONDIRENTRY;

  ICONDIR iconDir = {
    .reserved1 = 0,
    .type = 1,
    .numberOfImages = Arcadia_List_getSize(thread, sourcePixelBuffers)
  };
  Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, &iconDir, sizeof(ICONDIR));

  Arcadia_ByteBuffer* temporary = Arcadia_ByteBuffer_create(thread);
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_List_getSize(thread, sourcePixelBuffers); i < n; ++i) {
    Arcadia_Visuals_PixelBuffer* pixelBuffer = (Arcadia_Visuals_PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(thread, temporary);
    ImageWriter_writePngToByteBuffer(thread, (ImageWriter*)self, pixelBuffer, temporary);
    if (Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8 != Arcadia_Visuals_PixelBuffer_getPixelFormat(thread, pixelBuffer)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    size_t width = Arcadia_Visuals_PixelBuffer_getNumberOfColumns(thread, pixelBuffer),
           height = Arcadia_Visuals_PixelBuffer_getNumberOfRows(thread, pixelBuffer);
    if (width > 256) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (height > 256) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (width == 256) {
      width = 0;
    }
    if (height == 256) {
      height = 256;
    }

    ICONDIRENTRY iconDirEntry = { .width = width,
                                  .height = height,
                                  .numberOfColors = 0,
                                  .reserved1 = 0,
                                  .numberOfColorPlanes = 1,
                                  .numberOfBitsPerPixel = 32,
                                  .imageSize = Arcadia_ByteBuffer_getSize(thread, temporary),
                                  .offset = sizeof(ICONDIR) + Arcadia_List_getSize(thread, sourcePixelBuffers) * sizeof(ICONDIRENTRY) + offset };
    Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, &iconDirEntry, sizeof(ICONDIRENTRY));
    offset += Arcadia_ByteBuffer_getSize(thread, temporary);
  }
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_List_getSize(thread, sourcePixelBuffers); i < n; ++i) {
    Arcadia_Visuals_PixelBuffer* pixelBuffer = (Arcadia_Visuals_PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(thread, temporary);
    ImageWriter_writePngToByteBuffer(thread, (ImageWriter*)self, pixelBuffer, temporary);
    Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, temporary->p, temporary->sz);
    offset += Arcadia_ByteBuffer_getSize(thread, temporary);
  }
}

static void
LibPngImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &LibPngImageWriter_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"LibPngImageWriter", LibPngImageWriter, u8"ImageWriter", ImageWriter, &_typeOperations);

static void
LibPngImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  LibPngImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_Type* _type = _LibPngImageWriter_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  ((ImageWriter*)_self)->writeBmpToByteBuffer = (void (*)(Arcadia_Thread*, ImageWriter*, Arcadia_Visuals_PixelBuffer*,Arcadia_ByteBuffer*))LibPngImageWriter_writeBmpToByteBufferImpl;
  ((ImageWriter*)_self)->writeBmpToPath = (void (*)(Arcadia_Thread*, ImageWriter*, Arcadia_Visuals_PixelBuffer*, Arcadia_String*))LibPngImageWriter_writeBmpToPathImpl;
  ((ImageWriter*)_self)->writeIcoToByteBuffer = (void (*)(Arcadia_Thread*, ImageWriter*, Arcadia_List*, Arcadia_ByteBuffer*))LibPngImageWriter_writeIcoToByteBufferImpl;
  ((ImageWriter*)_self)->writeIcoToPath = (void (*)(Arcadia_Thread*, ImageWriter*, Arcadia_List*, Arcadia_String*))LibPngImageWriter_writeIcoToPathImpl;
  ((ImageWriter*)_self)->writePngToByteBuffer = (void (*)(Arcadia_Thread*, ImageWriter*, Arcadia_Visuals_PixelBuffer*, Arcadia_ByteBuffer*))LibPngImageWriter_writePngToByteBufferImpl;
  ((ImageWriter*)_self)->writePngToPath = (void (*)(Arcadia_Thread*, ImageWriter*, Arcadia_Visuals_PixelBuffer*, Arcadia_String*))LibPngImageWriter_writePngToPathImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

LibPngImageWriter*
LibPngImageWriter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  LibPngImageWriter* self = Arcadia_allocateObject(thread, _LibPngImageWriter_getType(thread), 0, &argumentValues[0]);
  return self;
}
