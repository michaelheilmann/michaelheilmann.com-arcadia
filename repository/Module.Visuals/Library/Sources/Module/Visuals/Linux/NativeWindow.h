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

// Last modified: 2025-04-28

#if !defined(MODULE_VISUALS_LINUX_NATIVEWINDOW_H_INCLUDED)
#define MODULE_VISUALS_LINUX_NATIVEWINDOW_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Module/Visuals/NativeWindow.h"
#include "Module/Visuals/PixelBuffer.h"
#include "Module/Visuals/Linux/NativeIcon.h"

#include <X11/Xlib.h>

Arcadia_declareObjectType(u8"Linux.NativeWindow", Linux_NativeWindow, u8"NativeWindow");

struct Linux_NativeWindow {
  NativeWindow _parent;
  Display* display;
  Screen* screen;
  Window window;
  Colormap colormap;
  
  Arcadia_String* title;
  Linux_NativeIcon* smallIcon;
  Linux_NativeIcon* bigIcon;
};

Linux_NativeWindow*
Linux_NativeWindow_create
  (
    Arcadia_Thread* thread
  );

#endif // MODULE_VISUALS_LINUX_NATIVEWINDOW_H_INCLUDED
