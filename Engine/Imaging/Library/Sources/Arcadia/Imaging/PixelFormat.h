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

#if !defined(ARCADIA_IMAGING_PIXELFORMAT_H_INCLUDED)
#define ARCADIA_IMAGING_PIXELFORMAT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Imaging_PixelFormat
Arcadia_declareEnumerationType(u8"Arcadia.Imaging.PixelFormat", Arcadia_Imaging_PixelFormat);

enum Arcadia_Imaging_PixelFormat {

  Arcadia_Imaging_PixelFormat_An8Ln8,

  Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8,

  Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8,

  Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8,

  Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8,

  Arcadia_Imaging_PixelFormat_Ln8,

  Arcadia_Imaging_PixelFormat_Ln8An8,

  Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8,

  Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8,

};

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Imaging_PixelFormat_getBytesPerPixel
Arcadia_SizeValue
Arcadia_Imaging_PixelFormat_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelFormat self
  );

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Imaging_PixelFormat_getNumberComponents
Arcadia_SizeValue
Arcadia_Imaging_PixelFormat_getNumberOfComponents
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelFormat self
  );

#endif // ARCADIA_IMAGING_PIXELFORMAT_H_INCLUDED
