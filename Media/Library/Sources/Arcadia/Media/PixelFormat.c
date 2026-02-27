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

#define ARCADIA_MEDIA_PRIVATE (1)
#include "Arcadia/Media/PixelFormat.h"

#include "Arcadia/Ring2/Include.h"

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
};

Arcadia_defineEnumerationType(u8"Arcadia.Media.PixelFormat", Arcadia_Media_PixelFormat,
                              &_typeOperations);

Arcadia_SizeValue
Arcadia_Media_PixelFormat_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelFormat self
  )
{
  switch (self) {
    case Arcadia_Media_PixelFormat_AlphaBlueGreenRedNatural8:
      return 4;
    case Arcadia_Media_PixelFormat_AlphaGrayNatural8:
      return 2;
    case Arcadia_Media_PixelFormat_AlphaRedGreenBlueNatural8:
      return 4;
    case Arcadia_Media_PixelFormat_BlueGreenRedNatural8:
      return 3;
    case Arcadia_Media_PixelFormat_BlueGreenRedAlphaNatural8:
      return 4;
    case Arcadia_Media_PixelFormat_GrayNatural8:
      return 1;
    case Arcadia_Media_PixelFormat_GrayAlphaNatural8:
      return 2;
    case Arcadia_Media_PixelFormat_RedGreenBlueNatural8:
      return 3;
    case Arcadia_Media_PixelFormat_RedGreenBlueAlphaNatural8:
      return 4;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

Arcadia_SizeValue
Arcadia_Media_PixelFormat_getNumberOfComponents
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelFormat self
  )
{
  switch (self) {
    case Arcadia_Media_PixelFormat_AlphaBlueGreenRedNatural8:
      return 3;
    case Arcadia_Media_PixelFormat_AlphaGrayNatural8:
      return 2;
    case Arcadia_Media_PixelFormat_AlphaRedGreenBlueNatural8:
      return 4;
    case Arcadia_Media_PixelFormat_BlueGreenRedNatural8:
      return 3;
    case Arcadia_Media_PixelFormat_BlueGreenRedAlphaNatural8:
      return 4;
    case Arcadia_Media_PixelFormat_GrayNatural8:
      return 1;
    case Arcadia_Media_PixelFormat_GrayAlphaNatural8:
      return 2;
    case Arcadia_Media_PixelFormat_RedGreenBlueNatural8:
      return 3;
    case Arcadia_Media_PixelFormat_RedGreenBlueAlphaNatural8:
      return 4;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}
