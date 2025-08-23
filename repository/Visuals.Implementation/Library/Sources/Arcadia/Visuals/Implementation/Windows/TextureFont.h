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

#if !defined(ARCADIA_VISUALS_WINDOWS_TEXTUREFONT_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS_TEXTUREFONT_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/Windows/Bitmap.h"
#include "Arcadia/Imaging/Include.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// @copde
/// class Arcadia.Visuals.Windows.TextureFontWindows {
///   /* The default code point is "Latin Capital Letter A" / "U+0041". */
///   construct()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.TextureFontWindows", Arcadia_Visuals_Windows_TextureFont,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_Windows_TextureFont {
  Arcadia_Object _parent;
  Arcadia_Visuals_Windows_Bitmap* bitmap;
  HFONT hFont;
  HDC hDeviceContext;
  Arcadia_Natural32Value codePoint;
};

Arcadia_Visuals_Windows_TextureFont*
Arcadia_Visuals_Windows_TextureFont_create
  (
    Arcadia_Thread* thread
  );

void
TextureFontWindows_setCodePoint
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFont* self,
    Arcadia_Natural32Value codePoint
  );

Arcadia_Imaging_PixelBuffer*
Arcadia_Visuals_Windows_TextureFont_getPixelBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TextureFont* self
  );

#endif // ARCADIA_VISUALS_WINDOWS_TEXTUREFONT_H_INCLUDED
