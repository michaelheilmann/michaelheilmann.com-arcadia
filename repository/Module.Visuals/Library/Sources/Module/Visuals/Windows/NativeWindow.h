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

// Last modified: 2024-11-11

#if !defined(MODULE_VISUALS_WINDOWS_NATIVEWINDOW_H_INCLUDED)
#define MODULE_VISUALS_WINDOWS_NATIVEWINDOW_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Module/Visuals/NativeWindow.h"
#include "Module/Visuals/Windows/NativeIcon.h"
#include "Module/Visuals/PixelBuffer.h"

#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <Windows.h>

// @todo Rename to Windows_NativeWindow.
// @todo Move to Windows/NativeWindow.(c|h).
Arcadia_declareObjectType(u8"Windows.NativeWindow", Windows_NativeWindow, u8"NativeWindow");

struct Windows_NativeWindow {
  NativeWindow _parent;
  ATOM classAtom;
  HINSTANCE instanceHandle;
  HWND windowHandle;
  HDC deviceContextHandle;
  HGLRC glResourceContextHandle;

  Arcadia_String* title;
  Windows_NativeIcon* smallIcon;
  Windows_NativeIcon* bigIcon;
};

Windows_NativeWindow*
Windows_NativeWindow_create
  (
    Arcadia_Thread* thread
  );

#endif // MODULE_VISUALS_WINDOWS_NATIVEWINDOW_H_INCLUDED
