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

#if !defined(MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED)
#define MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED

#include "R/Include.h"
#include "Module/Visuals/NativeWindow.h"
#include "Module/Visuals/NativeWindowsIcon.h"
#include "Module/Visuals/PixelBuffer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// The window is in "closed" state when it is creeated by NativeWindowsWindow_create.
// A successful call to NativeWindowsWindow_open puts the window in "opened" state.
// The window is put in "closed" state if it is destructed or by a successful call to NativeWindowsWindow_close.
Rex_declareObjectType(u8"NativeWindowsWindow", NativeWindowsWindow, u8"NativeWindow");

struct NativeWindowsWindow {
  NativeWindow _parent;
  ATOM classAtom;
  HINSTANCE instanceHandle;
  HWND windowHandle;
  HDC deviceContextHandle;

  Arcadia_String* title;
  NativeWindowsIcon* smallIcon;
  NativeWindowsIcon* bigIcon;
};

NativeWindowsWindow*
NativeWindowsWindow_create
  (
    Arcadia_Thread* thread
  );

#endif // MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED
