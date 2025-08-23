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

#if !defined(ARCADIA_VISUALS_WINDOWS_WGLFACTORYWINDOW_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS_WGLFACTORYWINDOW_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <Windows.h>

Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.WglFactoryWindow", Arcadia_Visuals_Windows_WglFactoryWindow, u8"Arcadia.Object");

struct Arcadia_Visuals_Windows_WglFactoryWindow {
  Arcadia_Object parent;
  HINSTANCE instanceHandle;
  ATOM classAtom;
  HWND windowHandle;
  HDC deviceContextHandle;
};

Arcadia_Visuals_Windows_WglFactoryWindow*
Arcadia_Visuals_Windows_WglFactoryWindow_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_Windows_WglFactoryWindow_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglFactoryWindow* self
  );

void
Arcadia_Visuals_Windows_WglFactoryWindow_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglFactoryWindow* self
  );

#endif // ARCADIA_VISUALS_WINDOWS_WGLFACTORYWINDOW_H_INCLUDED
