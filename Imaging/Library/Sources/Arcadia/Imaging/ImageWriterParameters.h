// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_IMAGING_IMAGEWRITERPARAMETERS_H_INCLUDED)
#define ARCADIA_IMAGING_IMAGEWRITERPARAMETERS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

/// @code
/// class ImageWriterParameters {
///   construct(path:String,format:String)
///   construct(byteBuffer:ByteBuffer,format:String)
/// }
/// @endcode
/// where @ format is one of "bmp", "ico", "png", "tiff".
Arcadia_declareObjectType(u8"Arcadia.Imagging.ImageWriterParameters", Arcadia_Imaging_ImageWriterParameters,
                          u8"Arcadia.Object");

Arcadia_Imaging_ImageWriterParameters*
Arcadia_Imaging_ImageWriterParameters_createFile
  (
    Arcadia_Thread* thread,
    Arcadia_String* path,
    Arcadia_String* format
  );

Arcadia_Imaging_ImageWriterParameters*
Arcadia_Imaging_ImageWriterParameters_createByteBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* byteBuffer,
    Arcadia_String* format
  );

Arcadia_BooleanValue
Arcadia_Imaging_ImageWriterParameters_hasPath
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  );

Arcadia_String*
Arcadia_Imaging_ImageWriterParameters_getPath
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  );

Arcadia_BooleanValue
Arcadia_Imaging_ImageWriterParameters_hasByteBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  );

Arcadia_ByteBuffer*
Arcadia_Imaging_ImageWriterParameters_getByteBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  );

Arcadia_String*
Arcadia_Imaging_ImageWriterParameters_getFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageWriterParameters* self
  );

#endif // ARCADIA_IMAGING_IMAGEWRITERPARAMETERS_H_INCLUDED
