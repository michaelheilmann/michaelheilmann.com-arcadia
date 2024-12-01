// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-11-11

#if !defined(MODULE_VISUALS_NATIVEWINDOWSBITMAP_H_INCLUDED)
#define MODULE_VISUALS_NATIVEWINDOWSBITMAP_H_INCLUDED

#include "R.h"
#include "Module/Visuals/PixelBuffer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// @code
/// class NativeWindowsBitmap {
///   construct(width:Integer32, height: Integer32)
/// }
/// @endcode
Rex_declareObjectType("NativeWindowsBitmap", NativeWindowsBitmap, "R.Object");

struct NativeWindowsBitmap {
  R_Object _parent;
  HDC hDeviceContext;
  HBITMAP hBitmap;
  R_Integer32Value width;
  R_Integer32Value height;
  R_Integer32Value lineStride;
  R_Integer32Value linePadding;
  R_Integer32Value numberOfBitsPerPixel;
  R_Natural8Value pixelFormat;
};

NativeWindowsBitmap*
NativeWindowsBitmap_create
  (
    R_Integer32Value width,
    R_Integer32Value height
  );

void
NativeWindowsBitmap_fill
  (
    NativeWindowsBitmap* self,
    R_Natural8Value r,
    R_Natural8Value g,
    R_Natural8Value b
  );

PixelBuffer*
NativeWindowsBitmap_toPixelBuffer
  (
    NativeWindowsBitmap* self
  );

#endif // MODULE_VISUALS_NATIVEWINDOWSBITMAP_H_INCLUDED
