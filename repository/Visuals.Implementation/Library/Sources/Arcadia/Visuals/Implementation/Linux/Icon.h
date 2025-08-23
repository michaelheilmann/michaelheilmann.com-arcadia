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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_LINUX_ICON_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_LINUX_ICON_H_INCLUDED

#include "Arcadia/Visuals/Include.h"

/// @code
/// class Arcadia.Visuals.Linux.Icon {
///   construct(width:Integer32, height:Integer32, red:Natural8, green:Natural8, blue:Natural8, alpha:Natural8)
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Linux.Icon", Arcadia_Visuals_Linux_Icon,
                          u8"Arcadia.Visuals.Icon")

struct Arcadia_Visuals_Linux_Icon {
  Arcadia_Visuals_Icon _parent;
  /// The width, in pixels, of the icon.
  /// Always non-negative.
  Arcadia_Integer32Value width;
  /// The height, in pixels, of the icon.
  /// Always non-negative.
  Arcadia_Integer32Value height;
  /// Pointer to an array of (width * height + 2) * sizeof(unsigned long) Bytes.
  /// The first two Bytes contain the width and the height of a pixel rectangle.
  /// The remaining Bytes contain width * height unsigned long XXXXARGB pixels.
  unsigned long* bytes;
  /// The number of Bytes in the array pointed to by @a bytes.
  Arcadia_Natural32Value numberOfBytes;
};

Arcadia_Visuals_Linux_Icon*
Arcadia_Visuals_Linux_Icon_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_LINUX_ICON_H_INCLUDED
