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

#if !defined(ARCADIA_VISUALS_WINDOWS_TEMPORARYWINDOW_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS_TEMPORARYWINDOW_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <Windows.h>

/// A temporary Windows window.
/// Used by temporary WGL windows, temporary Vulkan windows, and temporary D3D windows.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.TemporaryWindow", Arcadia_Visuals_Windows_TemporaryWindow, u8"Arcadia.Object");

struct Arcadia_Visuals_Windows_TemporaryWindow {
  Arcadia_Object parent;
  HINSTANCE instanceHandle;
  ATOM classAtom;
  HWND windowHandle;
  HDC deviceContextHandle;
};

Arcadia_Visuals_Windows_TemporaryWindow*
Arcadia_Visuals_Windows_TemporaryWindow_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_Windows_TemporaryWindow_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TemporaryWindow* self
  );

void
Arcadia_Visuals_Windows_TemporaryWindow_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TemporaryWindow* self
  );

#endif // ARCADIA_VISUALS_WINDOWS_TEMPORARYWINDOW_H_INCLUDED
