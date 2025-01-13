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

// Last modified: 2024-11-13

#if !defined(MODULE_VISUALS_NATIVEWINDOWSICON_H_INCLUDED)
#define MODULE_VISUALS_NATIVEWINDOWSICON_H_INCLUDED
 
#include "R.h"
#include "Module/Visuals/NativeIcon.h"

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/// @code
/// class NativeWindowsIcon {
///   construct(width:Integer32, height:Integer32, red:Natural8, green:Natural8, blue:Natural8)
/// }
/// @endcode
Rex_declareObjectType(u8"NativeWindowsIcon", NativeWindowsIcon, u8"Arcadia.Object")

struct NativeWindowsIcon {
  NativeIcon _parent;
  HICON hIcon;
};

NativeWindowsIcon*
NativeWindowsIcon_create
  (
    Arcadia_Process* process,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue
  );

#endif // MODULE_VISUALS_NATIVEWINDOWSICON_H_INCLUDED
