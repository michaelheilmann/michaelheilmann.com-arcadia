// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(MODULE_VISUALS_FONT_H_INCLUDED)
#define MODULE_VISUALS_FONT_H_INCLUDED

#include "R/Include.h"
#include "Module/Visuals/NativeWindowsBitmap.h"
#include "Module/Visuals/PixelBuffer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// @copde
/// class TextureFontWindows {
///   /* The default code point is "Latin Capital Letter A" / "U+0041". */
///   construct()
/// }
/// @endcode
Rex_declareObjectType(u8"TextureFontWindows", TextureFontWindows, u8"Arcadia.Object");

struct TextureFontWindows {
  Arcadia_Object _parent;
  NativeWindowsBitmap* bitmap;
  HFONT hFont;
  HDC hDeviceContext;
  Arcadia_Natural32Value codePoint;
};

TextureFontWindows*
TextureFontWindows_create
  (
    Arcadia_Thread* thread
  );

void
TextureFontWindows_setCodePoint
  (
    Arcadia_Thread* thread,
    TextureFontWindows* self,
    Arcadia_Natural32Value codePoint
  );

PixelBuffer*
TextureFontWindows_getPixelBuffer
  (
    Arcadia_Thread* thread,
    TextureFontWindows* self
  );

#endif // MODULE_VISUALS_FONT_H_INCLUDED
