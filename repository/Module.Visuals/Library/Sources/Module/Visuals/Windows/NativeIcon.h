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

// Last modified: 2024-11-13

#if !defined(MODULE_VISUALS_WINDOWS_NATIVEICON_H_INCLUDED)
#define MODULE_VISUALS_WINDOWS_NATIVEICON_H_INCLUDED
 
#include "Arcadia/Ring2/Include.h"
#include "Module/Visuals/NativeIcon.h"

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/// @code
/// class Windows.NativeIcon {
///   construct(width:Integer32, height:Integer32, red:Natural8, green:Natural8, blue:Natural8, alpha:Natural8)
/// }
/// @endcode
Arcadia_declareObjectType(u8"Windows.NativeIcon", Windows_NativeIcon, u8"Arcadia.Object")

struct Windows_NativeIcon {
  NativeIcon _parent;
  HICON hIcon;
};

Windows_NativeIcon*
Windows_NativeIcon_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  );

#endif // MODULE_VISUALS_WINDOWS_NATIVEICON_H_INCLUDED
