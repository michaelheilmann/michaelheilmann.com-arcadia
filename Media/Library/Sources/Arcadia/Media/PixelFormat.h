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

#if !defined(ARCADIA_MEDIA_PIXELFORMAT_H_INCLUDED)
#define ARCADIA_MEDIA_PIXELFORMAT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// https://michaelheilmann.com/Arcadia/Media/#Arcadia_Media_PixelFormat
Arcadia_declareEnumerationType(u8"Arcadia.Media.PixelFormat", Arcadia_Media_PixelFormat);

enum Arcadia_Media_PixelFormat {

  Arcadia_Media_PixelFormat_AlphaBlueGreenRedNatural8,

  Arcadia_Media_PixelFormat_AlphaGrayNatural8,

  Arcadia_Media_PixelFormat_AlphaRedGreenBlueNatural8,

  Arcadia_Media_PixelFormat_BlueGreenRedNatural8,

  Arcadia_Media_PixelFormat_BlueGreenRedAlphaNatural8,

  Arcadia_Media_PixelFormat_GrayNatural8,

  Arcadia_Media_PixelFormat_GrayAlphaNatural8,

  Arcadia_Media_PixelFormat_RedGreenBlueNatural8,

  Arcadia_Media_PixelFormat_RedGreenBlueAlphaNatural8,

};

// https://michaelheilmann.com/Arcadia/Media/#Arcadia_Media_PixelFormat_getNumberOfBytes
Arcadia_SizeValue
Arcadia_Media_PixelFormat_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelFormat self
  );

// https://michaelheilmann.com/Arcadia/Media/#Arcadia_Media_PixelFormat_getNumberComponents
Arcadia_SizeValue
Arcadia_Media_PixelFormat_getNumberOfComponents
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelFormat self
  );

#endif // ARCADIA_MEDIA_PIXELFORMAT_H_INCLUDED
