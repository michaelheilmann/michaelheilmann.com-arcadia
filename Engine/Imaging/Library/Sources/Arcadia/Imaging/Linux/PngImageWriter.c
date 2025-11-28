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

#include "Arcadia/Imaging/Linux/PngImageWriter.h"

#include "Arcadia/Imaging/ImageWriterParameters.h"
#include "Arcadia/Imaging/Linux/Include.h"

#include <malloc.h> // @todo Use functionality provided by Arcadia_Process.

#include <png.h>

static void
Arcadia_Imaging_Linux_PngImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self
  );

static void
Arcadia_Imaging_Linux_PngImageWriter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self
  );

static Arcadia_ImmutableList*
Arcadia_Imaging_Linux_PngImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self
  );

static void
Arcadia_Imaging_Linux_PngImageWriter_writeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self,
    Arcadia_List* source,
    Arcadia_Imaging_ImageWriterParameters* target
  );

static void
Arcadia_Imaging_Linux_PngImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static void
Arcadia_Imaging_Linux_PngImageWriter_writePngToPathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
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

static void
LibPngState_destroy
  (
    Arcadia_Thread* thread,
    LibPngState* state
  )
{
  if (state->row_pointers) {
    free(state->row_pointers);
    state->row_pointers = NULL;
  }
  png_destroy_write_struct(&state->png_struct, &state->png_info);
  free(state);
}

static LibPngState*
LibPngState_create
  (
    Arcadia_Thread* thread
  )
{
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
    Arcadia_ByteBuffer_insertBackBytes(thread, ws->byteBuffer, data, length);
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

static Arcadia_ImmutableList*
Arcadia_Imaging_Linux_PngImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self
  )
{ return self->supportedTypes; }

static void
Arcadia_Imaging_Linux_PngImageWriter_writeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self,
    Arcadia_List* source,
    Arcadia_Imaging_ImageWriterParameters* target
  )
{
  Arcadia_Value requestedExtension = Arcadia_Value_makeObjectReferenceValue(Arcadia_Imaging_ImageWriterParameters_getFormat(thread, target));
  if (!Arcadia_List_contains(thread, (Arcadia_List*)self->supportedTypes, requestedExtension)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (1 != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)source)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue sourceObject = Arcadia_List_getObjectReferenceValueAt(thread, source, 0);
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, sourceObject), _Arcadia_Imaging_PixelBuffer_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Imaging_PixelBuffer* sourcePixelBuffer = (Arcadia_Imaging_PixelBuffer*)sourceObject;
  if (Arcadia_Imaging_ImageWriterParameters_hasByteBuffer(thread, target)) {
    Arcadia_Imaging_Linux_PngImageWriter_writePngToByteBufferImpl(thread, self, sourcePixelBuffer, Arcadia_Imaging_ImageWriterParameters_getByteBuffer(thread, target));
  } else if (Arcadia_Imaging_ImageWriterParameters_hasPath(thread, target)) {
    Arcadia_Imaging_Linux_PngImageWriter_writePngToPathImpl(thread, self, sourcePixelBuffer, Arcadia_Imaging_ImageWriterParameters_getPath(thread, target));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_Imaging_Linux_PngImageWriter_writePngToByteBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  LibPngState* state = NULL;
  int bitDepth;
  int colorType;

  switch (Arcadia_Imaging_PixelBuffer_getPixelFormat(thread, sourcePixelBuffer)) {
    case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8:
    case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8:
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8:
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
      Arcadia_Imaging_PixelBuffer* pixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGBA;
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8:
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
      Arcadia_Imaging_PixelBuffer* pixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGB;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };
  uint32_t width = Arcadia_Imaging_PixelBuffer_getWidth(thread, sourcePixelBuffer);
  uint32_t height = Arcadia_Imaging_PixelBuffer_getHeight(thread, sourcePixelBuffer);
  uint32_t lineStride = Arcadia_Imaging_PixelBuffer_getLineStride(thread, sourcePixelBuffer);
  //uint32_t pixelBytes = Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, sourcePixelBuffer);
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
Arcadia_Imaging_Linux_PngImageWriter_writePngToPathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  LibPngState* state = NULL;
  int bitDepth;
  int colorType;

  switch (Arcadia_Imaging_PixelBuffer_getPixelFormat(thread, sourcePixelBuffer)) {
    case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8:
    case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8:
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8:
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
      Arcadia_Imaging_PixelBuffer* pixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGBA;
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8:
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
      Arcadia_Imaging_PixelBuffer* pixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8);
      sourcePixelBuffer = pixelBuffer;
      bitDepth = 8;
      colorType = PNG_COLOR_TYPE_RGB;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };
  uint32_t width = Arcadia_Imaging_PixelBuffer_getWidth(thread, sourcePixelBuffer);
  uint32_t height = Arcadia_Imaging_PixelBuffer_getHeight(thread, sourcePixelBuffer);
  uint32_t lineStride = Arcadia_Imaging_PixelBuffer_getLineStride(thread, sourcePixelBuffer);
  //uint32_t pixelBytes = Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, sourcePixelBuffer);
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
    Arcadia_FilePath* filePath = Arcadia_FilePath_parseNative(thread, targetPath);
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

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Imaging_Linux_PngImageWriter_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Imaging_Linux_PngImageWriter_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.Linux.PngImageWriter", Arcadia_Imaging_Linux_PngImageWriter,
                         u8"Arcadia.Imaging.ImageWriter", Arcadia_Imaging_ImageWriter,
                         &_typeOperations);

static void
Arcadia_Imaging_Linux_PngImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self
  )
{
  Arcadia_Type* _type = _Arcadia_Imaging_Linux_PngImageWriter_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->supportedTypes = NULL;
  Arcadia_List* supportedTypes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, supportedTypes, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"png", sizeof(u8"png") - 1))));
  self->supportedTypes = Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(supportedTypes));
  ((Arcadia_Imaging_ImageWriter*)self)->getSupportedTypes = (Arcadia_ImmutableList*(*)(Arcadia_Thread*,Arcadia_Imaging_ImageWriter*))&Arcadia_Imaging_Linux_PngImageWriter_getSupportedTypesImpl;
  ((Arcadia_Imaging_ImageWriter*)self)->write = (void (*)(Arcadia_Thread*, Arcadia_Imaging_ImageWriter*, Arcadia_List*, Arcadia_Imaging_ImageWriterParameters*)) & Arcadia_Imaging_Linux_PngImageWriter_writeImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Imaging_Linux_PngImageWriter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_PngImageWriter* self
  )
{
  if (self->supportedTypes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->supportedTypes);
  }
}

Arcadia_Imaging_Linux_PngImageWriter*
Arcadia_Imaging_Linux_PngImageWriter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Imaging_Linux_PngImageWriter);
}
