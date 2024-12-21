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

#include <png.h>

static void
NativeLinuxImageWriter_writePngToPathImpl
  (
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_String* targetPath
  );

static void
NativeLinuxImageWriter_writePngToByteBufferImpl
  (
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  );

static void
NativeLinuxImageWriter_writeBmpToPathImpl
  (
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_String* targetPath
  );

static void
NativeLinuxImageWriter_writeBmpToByteBufferImpl
  (
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  );

// The "Linux Imaging Component" ("WIC") does not provide an encoder for "ico" files.
// See https://learn.microsoft.com/en-us/windows/win32/wic/ico-format-overview?redirectedfrom=MSDN for more information.
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
    NativeLinuxImageWriter* self,
    R_List* sourcePixelBuffers,
    R_String* targetPath
  );

static void
NativeLinuxImageWriter_writeIcoToByteBufferImpl
  (
    NativeLinuxImageWriter* self,
    R_List* sourcePixelBuffers,
    R_ByteBuffer* targetByteBuffer
  );

typedef struct LibPngState {
  png_structp png_struct;
  png_infop png_info;
  uint8_t** row_pointers;
} LibPngState;

#include <malloc.h>

void LibPngState_destroy(LibPngState* state) {
  if (state->row_pointers) {
    free(state->row_pointers);
    state->row_pointers = NULL;
  }
  png_destroy_write_struct(&state->png_struct, &state->png_info);
  free(state);
}

LibPngState* LibPngState_create() {
  LibPngState* state = malloc(sizeof(LibPngState));
  if (!state) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  state->png_struct = NULL;
  state->png_info = NULL;
  state->row_pointers = NULL;
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    state->png_struct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!state->png_struct) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    state->png_info = png_create_info_struct(state->png_struct);
    if (!state->png_info) {
      png_destroy_write_struct(&state->png_struct, (png_infopp)NULL);
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    if (!state->png_info) {
      png_destroy_write_struct(&state->png_struct, (png_infopp)NULL);
    }
    free(state);
    state = NULL;
    R_jump();
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
  R_ByteBuffer* p = (R_ByteBuffer*)png_get_io_ptr(png_struct);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_ByteBuffer_append_pn(p, data, length);
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
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
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_String* targetPath
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
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(sourcePixelBuffer);
      PixelBuffer_setPixelFormat(pixelBuffer, PixelFormat_Rn8Gn8Bn8An8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGBA;
    } break;
    case PixelFormat_Bn8Gn8Rn8:
    case PixelFormat_Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(sourcePixelBuffer);
      PixelBuffer_setPixelFormat(pixelBuffer, PixelFormat_Rn8Gn8Bn8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGB;
    } break;
    default: {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    } break;
  };
  uint32_t width = PixelBuffer_getWidth(sourcePixelBuffer);
  uint32_t height = PixelBuffer_getHeight(sourcePixelBuffer);
  uint32_t lineStride = PixelBuffer_getLineStride(sourcePixelBuffer);
  uint32_t pixelBytes = PixelBuffer_getBytesPerPixel(sourcePixelBuffer);
  uint8_t* pixels = sourcePixelBuffer->bytes;

  state = LibPngState_create();
  FILE* fp = NULL;
  if (!setjmp(png_jmpbuf(state->png_struct))) {
    state->row_pointers = malloc(sizeof(uint8_t*) * height);
    if (!state->row_pointers) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    for (size_t i = 0; i < height; ++i) {
      state->row_pointers[i] = pixels + lineStride * i;
    }
    R_FilePath* filePath = R_FilePath_parseNative(R_String_getBytes(targetPath), R_String_getNumberOfBytes(targetPath));
    R_String* filePathString = R_FilePath_toNative(filePath);
    fp = fopen(R_String_getBytes(filePathString), "wb");
    if (!fp) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
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
    LibPngState_destroy(state);
    state = NULL;
    if (fp) {
      fclose(fp);
      fp = NULL;
    }
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  LibPngState_destroy(state);
  state = NULL;
  if (fp) {
    fclose(fp);
    fp = NULL;
  }
}

static void
NativeLinuxImageWriter_writePngToByteBufferImpl
  (
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
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
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(sourcePixelBuffer);
      PixelBuffer_setPixelFormat(pixelBuffer, PixelFormat_Rn8Gn8Bn8An8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGBA;
    } break;
    case PixelFormat_Bn8Gn8Rn8:
    case PixelFormat_Rn8Gn8Bn8: {
      PixelBuffer* pixelBuffer = PixelBuffer_createClone(sourcePixelBuffer);
      PixelBuffer_setPixelFormat(pixelBuffer, PixelFormat_Rn8Gn8Bn8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGB;
    } break;
    default: {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    } break;
  };
  uint32_t width = PixelBuffer_getWidth(sourcePixelBuffer);
  uint32_t height = PixelBuffer_getHeight(sourcePixelBuffer);
  uint32_t lineStride = PixelBuffer_getLineStride(sourcePixelBuffer);
  uint32_t pixelBytes = PixelBuffer_getBytesPerPixel(sourcePixelBuffer);
  uint8_t* pixels = sourcePixelBuffer->bytes;

  state = LibPngState_create();
  if (!setjmp(png_jmpbuf(state->png_struct))) {
    state->row_pointers = malloc(sizeof(uint8_t*) * height);
    if (!state->row_pointers) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    for (size_t i = 0; i < height; ++i) {
      state->row_pointers[i] = pixels + lineStride * i;
    }
    png_set_write_fn(state->png_struct, targetByteBuffer, &on_write, &on_flush),
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
    LibPngState_destroy(state);
    state = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  LibPngState_destroy(state);
  state = NULL;
}

static void
NativeLinuxImageWriter_writeBmpToPathImpl
  (
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_String* targetPath
  )
{
  //ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createFile(targetPath, ImageWriterFormat_Bmp);
  //write(sourcePixelBuffer, imageWriterParameters);
}

static void
NativeLinuxImageWriter_writeBmpToByteBufferImpl
  (
    NativeLinuxImageWriter* self,
    PixelBuffer* sourcePixelBuffer,
    R_ByteBuffer* targetByteBuffer
  )
{
  //ImageWriterParameters* imageWriterParameters = ImageWriterParameters_createByteBuffer(targetByteBuffer, ImageWriterFormat_Bmp);
  //write(sourcePixelBuffer, imageWriterParameters);
}

static void
NativeLinuxImageWriter_writeIcoToPathImpl
  (
    NativeLinuxImageWriter* self,
    R_List* sourcePixelBuffers,
    R_String* targetPath
  )
{
  R_ByteBuffer* targetByteBuffer = R_ByteBuffer_create();
  ImageWriter_writeIcoToByteBuffer((ImageWriter*)self, sourcePixelBuffers, targetByteBuffer);
  R_FileSystem_setFileContents(R_FileSystem_create(), R_FilePath_parseUnix(R_String_getBytes(targetPath), R_String_getNumberOfBytes(targetPath)), targetByteBuffer);
}

static void
NativeLinuxImageWriter_writeIcoToByteBufferImpl
  (
    NativeLinuxImageWriter* self,
    R_List* sourcePixelBuffers,
    R_ByteBuffer* targetByteBuffer
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
    .numberOfImages = R_List_getSize(sourcePixelBuffers)
  };
  R_ByteBuffer_append_pn(targetByteBuffer, &iconDir, sizeof(ICONDIR));

  R_ByteBuffer* temporary = R_ByteBuffer_create();
  for (R_SizeValue i = 0, offset = 0, n = R_List_getSize(sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)R_List_getObjectReferenceValueAt(sourcePixelBuffers, i);
    R_ByteBuffer_clear(temporary);
    ImageWriter_writePngToByteBuffer((ImageWriter*)self, pixelBuffer, temporary);
    if (PixelFormat_An8Rn8Gn8Bn8 != PixelBuffer_getPixelFormat(pixelBuffer)) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    size_t width = PixelBuffer_getNumberOfColumns(pixelBuffer),
           height = PixelBuffer_getNumberOfRows(pixelBuffer);
    if (width > 256) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    if (height > 256) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
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
                                  .imageSize = R_ByteBuffer_getSize(temporary),
                                  .offset = sizeof(ICONDIR) + R_List_getSize(sourcePixelBuffers) * sizeof(ICONDIRENTRY) + offset };
    R_ByteBuffer_append_pn(targetByteBuffer, &iconDirEntry, sizeof(ICONDIRENTRY));
    offset += R_ByteBuffer_getSize(temporary);
  }
  for (R_SizeValue i = 0, offset = 0, n = R_List_getSize(sourcePixelBuffers); i < n; ++i) {
    PixelBuffer* pixelBuffer = (PixelBuffer*)R_List_getObjectReferenceValueAt(sourcePixelBuffers, i);
    R_ByteBuffer_clear(temporary);
    ImageWriter_writePngToByteBuffer((ImageWriter*)self, pixelBuffer, temporary);
    R_ByteBuffer_append_pn(targetByteBuffer, temporary->p, temporary->sz);
    offset += R_ByteBuffer_getSize(temporary);
  }
}

static void
NativeLinuxImageWriter_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &NativeLinuxImageWriter_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
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
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  NativeLinuxImageWriter* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _NativeLinuxImageWriter_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Type* _typeParent = R_Type_getParentObjectType(_type);
    R_Type_getOperations(_typeParent)->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }
  ((ImageWriter*)_self)->writeBmpToByteBuffer = (void (*)(ImageWriter*, PixelBuffer*,R_ByteBuffer*))NativeLinuxImageWriter_writeBmpToByteBufferImpl;
  ((ImageWriter*)_self)->writeBmpToPath = (void (*)(ImageWriter*, PixelBuffer*, R_String*))NativeLinuxImageWriter_writeBmpToPathImpl;
  ((ImageWriter*)_self)->writeIcoToByteBuffer = (void (*)(ImageWriter*, R_List*, R_ByteBuffer*))NativeLinuxImageWriter_writeIcoToByteBufferImpl;
  ((ImageWriter*)_self)->writeIcoToPath = (void (*)(ImageWriter*, R_List*, R_String*))NativeLinuxImageWriter_writeIcoToPathImpl;
  ((ImageWriter*)_self)->writePngToByteBuffer = (void (*)(ImageWriter*, PixelBuffer*, R_ByteBuffer*))NativeLinuxImageWriter_writePngToByteBufferImpl;
  ((ImageWriter*)_self)->writePngToPath = (void (*)(ImageWriter*, PixelBuffer*, R_String*))NativeLinuxImageWriter_writePngToPathImpl;
  R_Object_setType((R_Object*)_self, _type);
}

NativeLinuxImageWriter*
NativeLinuxImageWriter_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  NativeLinuxImageWriter* self = R_allocateObject(_NativeLinuxImageWriter_getType(), 0, &argumentValues[0]);
  R_Value selfValue = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = self };
  NativeLinuxImageWriter_constructImpl(&selfValue, 0, &argumentValues[0]);
  return self;
}
