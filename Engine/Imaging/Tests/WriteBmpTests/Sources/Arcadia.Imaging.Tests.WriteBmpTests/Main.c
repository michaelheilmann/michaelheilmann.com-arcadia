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

#include <stdlib.h>
#include <string.h>

#include "Arcadia/Imaging/Include.h"

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_String* extension = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"bmp", sizeof(u8"bmp") - 1)));
  Arcadia_Imaging_ImageWriterParameters* parameters = NULL;
  Arcadia_String* path = NULL;
  Arcadia_List* pixelBufferList = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Imaging_PixelBuffer* pixelBuffer = NULL;
  Arcadia_Imaging_ImageManager* imageManager = Arcadia_Imaging_ImageManager_getOrCreate(thread);
  Arcadia_List* writers = Arcadia_Imaging_ImageManager_getWriters(thread, imageManager, extension);
  Arcadia_Tests_assertTrue(thread, 0 != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)writers));
  Arcadia_Object* object = Arcadia_List_getObjectReferenceValueAt(thread, writers, 0);
  Arcadia_Tests_assertTrue(thread, Arcadia_Object_isInstanceOf(thread, object, _Arcadia_Imaging_ImageWriter_getType(thread)));
  Arcadia_Imaging_ImageWriter* writer = (Arcadia_Imaging_ImageWriter*)object;
  
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBufferList);
  pixelBuffer = Arcadia_Imaging_PixelBuffer_create(thread, 0, 256, 256, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8);
  Arcadia_List_insertBackObjectReferenceValue(thread, pixelBufferList, pixelBuffer);
  path = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"rn8gn8bn8.bmp", sizeof(u8"rn8gn8bn8.bmp") - 1)));
  parameters = Arcadia_Imaging_ImageWriterParameters_createFile(thread, path, extension);
  Arcadia_Imaging_ImageWriter_write(thread, writer, pixelBufferList, parameters);

  Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBufferList);
  pixelBuffer = Arcadia_Imaging_PixelBuffer_create(thread, 0, 256, 256, Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8);
  Arcadia_List_insertBackObjectReferenceValue(thread, pixelBufferList, pixelBuffer);
  path = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"rn8gn8bn8an8.bmp", sizeof(u8"rn8gn8bn8an8.bmp") - 1)));
  parameters = Arcadia_Imaging_ImageWriterParameters_createFile(thread, path, extension);
  Arcadia_Imaging_ImageWriter_write(thread, writer, pixelBufferList, parameters);

  Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBufferList);
  pixelBuffer = Arcadia_Imaging_PixelBuffer_create(thread, 0, 256, 256, Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8);
  Arcadia_List_insertBackObjectReferenceValue(thread, pixelBufferList, pixelBuffer);
  path = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"an8rn8gn8bn8.bmp", sizeof(u8"an8rn8gn8bn8.bmp") - 1)));
  parameters = Arcadia_Imaging_ImageWriterParameters_createFile(thread, path, extension);
  Arcadia_Imaging_ImageWriter_write(thread, writer, pixelBufferList, parameters);

  Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBufferList);
  pixelBuffer = Arcadia_Imaging_PixelBuffer_create(thread, 0, 256, 256, Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8);
  Arcadia_List_insertBackObjectReferenceValue(thread, pixelBufferList, pixelBuffer);
  path = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"bn8gn8rn8.bmp", sizeof(u8"bn8gn8rn8.bmp") - 1)));
  parameters = Arcadia_Imaging_ImageWriterParameters_createFile(thread, path, extension);
  Arcadia_Imaging_ImageWriter_write(thread, writer, pixelBufferList, parameters);

  Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBufferList);
  pixelBuffer = Arcadia_Imaging_PixelBuffer_create(thread, 0, 256, 256, Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8);
  Arcadia_List_insertBackObjectReferenceValue(thread, pixelBufferList, pixelBuffer);
  path = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"bn8gn8rn8an8.bmp", sizeof(u8"bn8gn8rn8an8.bmp") - 1)));
  parameters = Arcadia_Imaging_ImageWriterParameters_createFile(thread, path, extension);
  Arcadia_Imaging_ImageWriter_write(thread, writer, pixelBufferList, parameters);

  Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBufferList);
  pixelBuffer = Arcadia_Imaging_PixelBuffer_create(thread, 0, 256, 256, Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8);
  Arcadia_List_insertBackObjectReferenceValue(thread, pixelBufferList, pixelBuffer);
  path = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"an8bn8gn8rn8.bmp", sizeof(u8"an8bn8gn8rn8.bmp") - 1)));
  parameters = Arcadia_Imaging_ImageWriterParameters_createFile(thread, path, extension);
  Arcadia_Imaging_ImageWriter_write(thread, writer, pixelBufferList, parameters);
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
