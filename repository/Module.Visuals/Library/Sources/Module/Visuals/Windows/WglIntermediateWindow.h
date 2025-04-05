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

#if !defined(MODULE_VISUALS_WINDOWS_WGLINTERMEDIATEWINDOW_H_INCLUDED)
#define MODULE_VISUALS_WINDOWS_WGLINTERMEDIATEWINDOW_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/GL.h>
#include <GL/wglext.h>

Arcadia_declareObjectType(u8"Visuals.Windows.WglIntermediateWindow", Visuals_Window_WglIntermediateWindow, u8"Arcadia.Object");

struct Visuals_Window_WglIntermediateWindow {
  Arcadia_Object parent;
  HINSTANCE instanceHandle;
  ATOM classAtom;
  HWND windowHandle;
  HDC deviceContextHandle;
  HGLRC glResourceContextHandle;
  PFNWGLCHOOSEPIXELFORMATARBPROC choosePixelFormat;
  PFNWGLCREATECONTEXTATTRIBSARBPROC createContextAttribs;
};

Visuals_Window_WglIntermediateWindow*
Visuals_Window_WglIntermediateWindow_create
  (
    Arcadia_Thread* thread
  );

void
Visuals_Window_WglIntermediateWindow_open
  (
    Arcadia_Thread* thread,
    Visuals_Window_WglIntermediateWindow* self
  );

void
Visuals_Window_WglIntermediateWindow_close
  (
    Arcadia_Thread* thread,
    Visuals_Window_WglIntermediateWindow* self
  );

#endif // MODULE_VISUALS_WINDOWS_WGLINTERMEDIATEWINDOW_H_INCLUDED
