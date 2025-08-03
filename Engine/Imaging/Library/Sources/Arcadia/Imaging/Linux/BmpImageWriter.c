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

#include "Arcadia/Imaging/Linux/BmpImageWriter.h"

#include "Arcadia/Imaging/ImageWriterParameters.h"
#include "Arcadia/Imaging/Linux/Include.h"

#include "Arcadia/Imaging/PixelBuffer.h"

#define STB_IMAGE_WRITE_STATIC static
#define STBIWDEF
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Arcadia/Imaging/Linux/_stb_image_write.h"

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

static void
Arcadia_Imaging_Linux_BmpImageWriter_constructImpl
  ( 
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Imaging_Linux_BmpImageWriter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self
  );

static Arcadia_ImmutableList*
Arcadia_Imaging_Linux_BmpImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self
  );

static void
Arcadia_Imaging_Linux_BmpImageWriter_writeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self,
    Arcadia_List* source,
    Arcadia_Imaging_ImageWriterParameters* target
  );

static void
Arcadia_Imaging_Linux_BmpImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );
  
static void
Arcadia_Imaging_Linux_BmpImageWriter_writeBmpToPathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static Arcadia_ImmutableList*
Arcadia_Imaging_Linux_BmpImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self
  )
{ return self->supportedTypes; }

static void
Arcadia_Imaging_Linux_BmpImageWriter_writeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self,
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
    Arcadia_Imaging_Linux_BmpImageWriter_writeBmpToByteBufferImpl(thread, self, sourcePixelBuffer, Arcadia_Imaging_ImageWriterParameters_getByteBuffer(thread, target));
  } else if (Arcadia_Imaging_ImageWriterParameters_hasPath(thread, target)) {
    Arcadia_Imaging_Linux_BmpImageWriter_writeBmpToPathImpl(thread, self, sourcePixelBuffer, Arcadia_Imaging_ImageWriterParameters_getPath(thread, target));
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_Imaging_Linux_BmpImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  WriteContext context;
  context.status = Arcadia_Status_Success;
  context.process = process;
  context.byteBuffer = targetByteBuffer;

  int components;
  switch (sourcePixelBuffer->pixelFormat) {
    case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8: {
      sourcePixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, sourcePixelBuffer, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8);
      Arcadia_Imaging_PixelBuffer_setLinePadding(thread, sourcePixelBuffer, 0);
      components = 4;
    } break;
    case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8: {
      sourcePixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, sourcePixelBuffer, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8);
      Arcadia_Imaging_PixelBuffer_setLinePadding(thread, sourcePixelBuffer, 0);
      components = 4;
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
      sourcePixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setLinePadding(thread, sourcePixelBuffer, 0);
      components = 3;
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
      sourcePixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setLinePadding(thread, sourcePixelBuffer, 0);
      components = 3;
    } break;
    
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8: {
      sourcePixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, sourcePixelBuffer, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8);
      Arcadia_Imaging_PixelBuffer_setLinePadding(thread, sourcePixelBuffer, 0);
      components = 3;
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8: {
      sourcePixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, sourcePixelBuffer, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8);
      Arcadia_Imaging_PixelBuffer_setLinePadding(thread, sourcePixelBuffer, 0);
      components = 4;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };

  if (!stbi_write_bmp_to_func((stbi_write_func*)&writeCallback, &context,
                              Arcadia_Imaging_PixelBuffer_getWidth(thread, sourcePixelBuffer),
                              Arcadia_Imaging_PixelBuffer_getHeight(thread, sourcePixelBuffer),
                              components,
                              sourcePixelBuffer->bytes)) {
    context.status = Arcadia_Status_EnvironmentFailed;
  }
  if (context.status) {
    Arcadia_Thread_setStatus(thread, context.status);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_Imaging_Linux_BmpImageWriter_writeBmpToPathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self,
    Arcadia_Imaging_PixelBuffer* sourcePixelBuffer,
    Arcadia_String *targetPath
  )
{ 
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_Imaging_Linux_BmpImageWriter_writeBmpToByteBufferImpl(thread, self, sourcePixelBuffer, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_create(thread),
                                     Arcadia_FilePath_parseUnix(thread, Arcadia_String_getBytes(thread, targetPath), Arcadia_String_getNumberOfBytes(thread, targetPath)), targetByteBuffer);
}

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Imaging_Linux_BmpImageWriter_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Imaging_Linux_BmpImageWriter_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.Linux.BmpImageWriter", Arcadia_Imaging_Linux_BmpImageWriter,
                         u8"Arcadia.Imaging.ImageWriter", Arcadia_Imaging_ImageWriter,
                         &_typeOperations);

static void
Arcadia_Imaging_Linux_BmpImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Imaging_Linux_BmpImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_Type* _type = _Arcadia_Imaging_Linux_BmpImageWriter_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->supportedTypes = NULL;
  Arcadia_List* supportedTypes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, supportedTypes, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"bmp", sizeof(u8"bmp") - 1))));
  _self->supportedTypes = Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(supportedTypes));
  ((Arcadia_Imaging_ImageWriter*)_self)->getSupportedTypes = (Arcadia_ImmutableList*(*)(Arcadia_Thread*,Arcadia_Imaging_ImageWriter*))&Arcadia_Imaging_Linux_BmpImageWriter_getSupportedTypesImpl;
  ((Arcadia_Imaging_ImageWriter*)_self)->write = (void (*)(Arcadia_Thread*, Arcadia_Imaging_ImageWriter*, Arcadia_List*, Arcadia_Imaging_ImageWriterParameters*)) & Arcadia_Imaging_Linux_BmpImageWriter_writeImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Imaging_Linux_BmpImageWriter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Linux_BmpImageWriter* self
  )
{
  if (self->supportedTypes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->supportedTypes);
  }
}

Arcadia_Imaging_Linux_BmpImageWriter*
Arcadia_Imaging_Linux_BmpImageWriter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Imaging_Linux_BmpImageWriter* self = Arcadia_allocateObject(thread, _Arcadia_Imaging_Linux_BmpImageWriter_getType(thread), 0, &argumentValues[0]);
  return self;
}
