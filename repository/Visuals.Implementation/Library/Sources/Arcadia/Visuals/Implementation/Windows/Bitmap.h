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

#if !defined(ARCADIA_VISUALS_WINDOWS_BITMAP_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS_BITMAP_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Imaging/PixelBuffer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// @code
/// class Arcadia.Visuals.Windows.Bitmap {
///   construct(width:Integer32, height: Integer32)
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.Bitmap", Arcadia_Visuals_Windows_Bitmap,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_Windows_Bitmap {
  Arcadia_Object _parent;
  HDC hDeviceContext;
  HBITMAP hBitmap;
  Arcadia_Integer32Value width;
  Arcadia_Integer32Value height;
  Arcadia_Integer32Value lineStride;
  Arcadia_Integer32Value linePadding;
  Arcadia_Integer32Value numberOfBitsPerPixel;
  Arcadia_Natural8Value pixelFormat;
};

Arcadia_Visuals_Windows_Bitmap*
Arcadia_Visuals_Windows_Bitmap_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

void
Arcadia_Visuals_Windows_Bitmap_fill
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Bitmap* self,
    Arcadia_Natural8Value r,
    Arcadia_Natural8Value g,
    Arcadia_Natural8Value b
  );

Arcadia_Imaging_PixelBuffer*
Arcadia_Visuals_Windows_Bitmap_toPixelBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Bitmap* self
  );

#endif // ARCADIA_VISUALS_WINDOWS_BITMAP_H_INCLUDED
