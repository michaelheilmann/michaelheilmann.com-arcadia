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

// Last modified: 2024-11-13

#if !defined(MODULE_VISUALS_NATIVEWINDOWSICON_H_INCLUDED)
#define MODULE_VISUALS_NATIVEWINDOWSICON_H_INCLUDED
 
#include "R.h"

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

Rex_declareObjectType("NativeWindowsIcon", NativeWindowsIcon, "R.Object")

struct NativeWindowsIcon {
  R_Object _parent;
  HICON hIcon;
};

void
IconWindows_construct
  (
    NativeWindowsIcon* self,
    R_Integer32Value width,
    R_Integer32Value height,
    R_Natural8Value red,
    R_Natural8Value green,
    R_Natural8Value blue
  );

NativeWindowsIcon*
NativeWindowsIcon_create
  (
    R_Integer32Value width,
    R_Integer32Value height,
    R_Natural8Value red,
    R_Natural8Value green,
    R_Natural8Value blue
  );

#endif // MODULE_VISUALS_NATIVEWINDOWSICON_H_INCLUDED
