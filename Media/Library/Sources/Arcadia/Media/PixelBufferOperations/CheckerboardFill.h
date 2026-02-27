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

#if !defined(ARCADIA_MEDIA_PIXELOPERATIONS_CHECKERBOARDFILL_H_INCLUDED)
#define ARCADIA_MEDIA_PIXELOPERATIONS_CHECKERBOARDFILL_H_INCLUDED

#include "Arcadia/ADL/Include.h"
#include "Arcadia/Media/PixelBufferOperation.h"

Arcadia_declareObjectType(u8"Arcadia.Media.PixelBufferOperations.CheckerboardFill", Arcadia_Media_PixelBufferOperations_CheckerboardFill,
                          u8"Arcadia.Media.PixelBufferOperation");

struct Arcadia_Media_PixelBufferOperations_CheckerboardFillDispatch {
  Arcadia_Media_PixelBufferOperationDispatch parent;
};

struct Arcadia_Media_PixelBufferOperations_CheckerboardFill {
  Arcadia_Media_PixelBufferOperation parent;
  Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* definition;
};

Arcadia_Media_PixelBufferOperations_CheckerboardFill*
Arcadia_Media_PixelBufferOperations_CheckerboardFill_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* definition
  );

#endif // ARCADIA_MEDIA_PIXELOPERATIONS_CHECKERBOARDFILL_H_INCLUDED
