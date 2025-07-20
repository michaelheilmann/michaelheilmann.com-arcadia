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

#if !defined(ARCADIA_IMAGING_ICOIMAGEWRITER_H_INCLUDED)
#define ARCADIA_IMAGING_ICOIMAGEWRITER_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Imaging/ImageWriter.h"

// a) "Linux" does not provide an encoder for the "ico" file format.
// b) "Windows" / the "Windows Imaging Component" ("WIC") does not provide an encoder for the "ico" file format.
// See https://learn.microsoft.com/en-us/windows/win32/wic/ico-format-overview?redirectedfrom=MSDN for more information.
//
// This is hand-coded "ico" file format writer which utilizes any available "png" file format writer.
//
// The "ico" file format is described on Wikipedia (https://en.wikipedia.org/wiki/ICO_(file_format)).
//
// From the description of the file format:
// - The width and height of any image in an "ico" files may not exceed 256.
// - all source pixel buffers must be of format PixelBuffer_An8Rn8Gn8Bn8.
Arcadia_declareObjectType(u8"Arcadia.Imaging.IcoImageWriter", IcoImageWriter, u8"Arcadia.Imaging.ImageWriter");

struct IcoImageWriter {
  Arcadia_Imaging_ImageWriter _parent;
  Arcadia_ImmutableList* supportedTypes;
};

IcoImageWriter*
IcoImageWriter_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_IMAGING_ICOIMAGEWRITER_H_INCLUDED
