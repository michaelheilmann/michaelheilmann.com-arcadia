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

#if !defined(MODULE_VISUALS_WINDOWS_WINDOW_H_INCLUDED)
#define MODULE_VISUALS_WINDOWS_WINDOW_H_INCLUDED

#include "Module/Visuals/Window.h"
#include "Module/Visuals/Windows/Application.h"
#include "Module/Visuals/Windows/Icon.h"

#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <Windows.h>

// @todo Rename to Windows_NativeWindow.
// @todo Move to Windows/NativeWindow.(c|h).
Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.Window", Arcadia_Visuals_Windows_Window, u8"Arcadia.Visuals.Window");

struct Arcadia_Visuals_Windows_Window {
  Arcadia_Visuals_Window _parent;
  Arcadia_Visuals_Windows_Application* application;

  ATOM classAtom;
  HWND windowHandle;
  HDC deviceContextHandle;
  HGLRC glResourceContextHandle;

  Arcadia_String* title;
  Arcadia_Visuals_Windows_Icon* smallIcon;
  Arcadia_Visuals_Windows_Icon* bigIcon;
};

Arcadia_Visuals_Windows_Window*
Arcadia_Visuals_Windows_Window_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* application
  );

#endif // MODULE_VISUALS_WINDOWS_WINDOW_H_INCLUDED
