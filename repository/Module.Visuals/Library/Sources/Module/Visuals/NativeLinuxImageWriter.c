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

// Last modified: 2024-09-19

#include "Module/Visuals/NativeLinuxImageWriter.h"

#include "Module/Visuals/ImageWriterParameters.h"
#include "Module/Visuals/Linux/Include.h"

#include <png.h>

static void
NativeLinuxImageWriter_writePngToPathImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
NativeLinuxImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static void
NativeLinuxImageWriter_writeBmpToPathImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
NativeLinuxImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
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
NativeLinuxImageWriter_writeIcoToPathImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
NativeLinuxImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
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

void LibPngState_destroy(Arcadia_Process* process, LibPngState* state) {
  if (state->row_pointers) {
    free(state->row_pointers);
    state->row_pointers = NULL;
  }
  png_destroy_write_struct(&state->png_struct, &state->png_info);
  free(state);
}

LibPngState* LibPngState_create(Arcadia_Process* process) {
  LibPngState* state = malloc(sizeof(LibPngState));
  if (!state) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  state->png_struct = NULL;
  state->png_info = NULL;
  state->row_pointers = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    state->png_struct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!state->png_struct) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    state->png_info = png_create_info_struct(state->png_struct);
    if (!state->png_info) {
      png_destroy_write_struct(&state->png_struct, (png_infopp)NULL);
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    Arcadia_Process_popJumpTarget(process);
  } else {
    Arcadia_Process_popJumpTarget(process);
    if (!state->png_info) {
      png_destroy_write_struct(&state->png_struct, (png_infopp)NULL);
    }
    free(state);
    state = NULL;
    Arcadia_Process_jump(process);
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
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(ws->process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_ByteBuffer_append_pn(ws->process, ws->byteBuffer, data, length);
    Arcadia_Process_popJumpTarget(ws->process);
  } else {
    Arcadia_Process_popJumpTarget(ws->process);
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
NativeLinuxImageWriter_writePngToPathImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  LibPngState* state = NULL;
  int bitDepth;
  int colorType;

  switch (PixelBuffer_getPixelFormat(sourcePixelBuffer)) {
    case PixelFormat_An8Rn8Gn8Bn8:
    case PixelFormat_An8Bn8Gn8Rn8:
    case PixelFormat_Bn8Gn8Rn8An8:
    case PixelFormat_Rn8Gn8Bn8An8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(process, sourcePixelBuffer);
      PixelBuffer_setPixelFormat(process, pixelBuffer, PixelFormat_Rn8Gn8Bn8An8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGBA;
    } break;
    case PixelFormat_Bn8Gn8Rn8:
    case PixelFormat_Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(process, sourcePixelBuffer);
      PixelBuffer_setPixelFormat(process, pixelBuffer, PixelFormat_Rn8Gn8Bn8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGB;
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    } break;
  };
  uint32_t width = PixelBuffer_getWidth(sourcePixelBuffer);
  uint32_t height = PixelBuffer_getHeight(sourcePixelBuffer);
  uint32_t lineStride = PixelBuffer_getLineStride(process, sourcePixelBuffer);
  uint32_t pixelBytes = PixelBuffer_getBytesPerPixel(process, sourcePixelBuffer);
  uint8_t* pixels = sourcePixelBuffer->bytes;

  state = LibPngState_create(process);
  FILE* fp = NULL;
  if (!setjmp(png_jmpbuf(state->png_struct))) {
    state->row_pointers = malloc(sizeof(uint8_t*) * height);
    if (!state->row_pointers) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    for (size_t i = 0; i < height; ++i) {
      state->row_pointers[i] = pixels + lineStride * i;
    }
    Arcadia_FilePath* filePath = Arcadia_FilePath_parseNative(process, Arcadia_String_getBytes(process, targetPath), Arcadia_String_getNumberOfBytes(process, targetPath));
    Arcadia_String* filePathString = Arcadia_FilePath_toNative(process, filePath);
    fp = fopen(Arcadia_String_getBytes(process, filePathString), "wb");
    if (!fp) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
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
    LibPngState_destroy(process, state);
    state = NULL;
    if (fp) {
      fclose(fp);
      fp = NULL;
    }
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  LibPngState_destroy(process, state);
  state = NULL;
  if (fp) {
    fclose(fp);
    fp = NULL;
  }
}

static void
NativeLinuxImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  LibPngState* state = NULL;
  int bitDepth;
  int colorType;

  switch (PixelBuffer_getPixelFormat(sourcePixelBuffer)) {
    case PixelFormat_An8Rn8Gn8Bn8:
    case PixelFormat_An8Bn8Gn8Rn8:
    case PixelFormat_Bn8Gn8Rn8An8:
    case PixelFormat_Rn8Gn8Bn8An8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(process, sourcePixelBuffer);
      PixelBuffer_setPixelFormat(process, pixelBuffer, PixelFormat_Rn8Gn8Bn8An8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGBA;
    } break;
    case PixelFormat_Bn8Gn8Rn8:
    case PixelFormat_Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(process, sourcePixelBuffer);
      PixelBuffer_setPixelFormat(process, pixelBuffer, PixelFormat_Rn8Gn8Bn8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGB;
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    } break;
  };
  uint32_t width = PixelBuffer_getWidth(sourcePixelBuffer);
  uint32_t height = PixelBuffer_getHeight(sourcePixelBuffer);
  uint32_t lineStride = PixelBuffer_getLineStride(process, sourcePixelBuffer);
  uint32_t pixelBytes = PixelBuffer_getBytesPerPixel(process, sourcePixelBuffer);
  uint8_t* pixels = sourcePixelBuffer->bytes;

  state = LibPngState_create(process);
  if (!setjmp(png_jmpbuf(state->png_struct))) {
    state->row_pointers = malloc(sizeof(uint8_t*) * height);
    if (!state->row_pointers) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
      Arcadia_Process_jump(process);
    }
    for (size_t i = 0; i < height; ++i) {
      state->row_pointers[i] = pixels + lineStride * i;
    }
    LibPngWriteState writeState = { .byteBuffer = targetByteBuffer, .process = process };
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
    LibPngState_destroy(process, state);
    state = NULL;
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  LibPngState_destroy(process, state);
  state = NULL;
}

static void
NativeLinuxImageWriter_writeBmpToPathImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(process);
  ImageWriter_writeBmpToByteBuffer(process, (ImageWriter*)self, sourcePixelBuffer, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(process, Arcadia_FileSystem_create(process),
                               Arcadia_FilePath_parseUnix(process, Arcadia_String_getBytes(process, targetPath), Arcadia_String_getNumberOfBytes(process, targetPath)), targetByteBuffer);
}

static void
NativeLinuxImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{ _Visuals_Linux_writeBmpToByteBuffer(process, sourcePixelBuffer, targetByteBuffer); }

static void
NativeLinuxImageWriter_writeIcoToPathImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(process);
  ImageWriter_writeIcoToByteBuffer(process, (ImageWriter*)self, sourcePixelBuffers, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(process, Arcadia_FileSystem_create(process), Arcadia_FilePath_parseUnix(process, Arcadia_String_getBytes(process, targetPath), Arcadia_String_getNumberOfBytes(process, targetPath)), targetByteBuffer);
}

static void
NativeLinuxImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Process* process,
    NativeLinuxImageWriter* self,
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
    .numberOfImages = Arcadia_List_getSize(process, sourcePixelBuffers)
  };
  Arcadia_ByteBuffer_append_pn(process, targetByteBuffer, &iconDir, sizeof(ICONDIR));

  Arcadia_ByteBuffer* temporary = Arcadia_ByteBuffer_create(process);
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_List_getSize(process, sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(process, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(process, temporary);
    ImageWriter_writePngToByteBuffer(process, (ImageWriter*)self, pixelBuffer, temporary);
    if (PixelFormat_An8Rn8Gn8Bn8 != PixelBuffer_getPixelFormat(pixelBuffer)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    size_t width = PixelBuffer_getNumberOfColumns(pixelBuffer),
           height = PixelBuffer_getNumberOfRows(pixelBuffer);
    if (width > 256) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    if (height > 256) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
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
                                  .imageSize = Arcadia_ByteBuffer_getSize(process, temporary),
                                  .offset = sizeof(ICONDIR) + Arcadia_List_getSize(process, sourcePixelBuffers) * sizeof(ICONDIRENTRY) + offset };
    Arcadia_ByteBuffer_append_pn(process, targetByteBuffer, &iconDirEntry, sizeof(ICONDIRENTRY));
    offset += Arcadia_ByteBuffer_getSize(process, temporary);
  }
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_List_getSize(process, sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(process, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(process, temporary);
    ImageWriter_writePngToByteBuffer(process, (ImageWriter*)self, pixelBuffer, temporary);
    Arcadia_ByteBuffer_append_pn(process, targetByteBuffer, temporary->p, temporary->sz);
    offset += Arcadia_ByteBuffer_getSize(process, temporary);
  }
}

static void
NativeLinuxImageWriter_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &NativeLinuxImageWriter_constructImpl,
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

Rex_defineObjectType("NativeLinuxImageWriter", NativeLinuxImageWriter, "ImageWriter", ImageWriter, &_typeOperations);

static void
NativeLinuxImageWriter_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  NativeLinuxImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_Type* _type = _NativeLinuxImageWriter_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  ((ImageWriter*)_self)->writeBmpToByteBuffer = (void (*)(Arcadia_Process*, ImageWriter*, PixelBuffer*,Arcadia_ByteBuffer*))NativeLinuxImageWriter_writeBmpToByteBufferImpl;
  ((ImageWriter*)_self)->writeBmpToPath = (void (*)(Arcadia_Process*, ImageWriter*, PixelBuffer*, Arcadia_String*))NativeLinuxImageWriter_writeBmpToPathImpl;
  ((ImageWriter*)_self)->writeIcoToByteBuffer = (void (*)(Arcadia_Process*, ImageWriter*, Arcadia_List*, Arcadia_ByteBuffer*))NativeLinuxImageWriter_writeIcoToByteBufferImpl;
  ((ImageWriter*)_self)->writeIcoToPath = (void (*)(Arcadia_Process*, ImageWriter*, Arcadia_List*, Arcadia_String*))NativeLinuxImageWriter_writeIcoToPathImpl;
  ((ImageWriter*)_self)->writePngToByteBuffer = (void (*)(Arcadia_Process*, ImageWriter*, PixelBuffer*, Arcadia_ByteBuffer*))NativeLinuxImageWriter_writePngToByteBufferImpl;
  ((ImageWriter*)_self)->writePngToPath = (void (*)(Arcadia_Process*, ImageWriter*, PixelBuffer*, Arcadia_String*))NativeLinuxImageWriter_writePngToPathImpl;
  Arcadia_Object_setType(process, _self, _type);
}

NativeLinuxImageWriter*
NativeLinuxImageWriter_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  NativeLinuxImageWriter* self = R_allocateObject(process, _NativeLinuxImageWriter_getType(process), 0, &argumentValues[0]);
  return self;
}
