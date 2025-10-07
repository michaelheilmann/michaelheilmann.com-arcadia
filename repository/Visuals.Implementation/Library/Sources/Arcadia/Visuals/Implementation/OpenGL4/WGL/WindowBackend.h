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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_WINDOWBACKEND_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_WINDOWBACKEND_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/System.h"
#include "Arcadia/Visuals/Implementation/Windows/Icon.h"
typedef struct Arcadia_Visuals_Windows_DisplayDevice Arcadia_Visuals_Windows_DisplayDevice;

#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <Windows.h>

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpennGL4.WGL.WindowBackend", Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend,
                          u8"Arcadia.Visuals.WindowBackend");

struct Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend {
  Arcadia_Visuals_WindowBackend _parent;
  Arcadia_Visuals_Implementation_OpenGL4_WGL_System* system;

  HWND windowHandle;
  HDC deviceContextHandle;

  Arcadia_Visuals_Implementation_Windows_Icon* smallIcon;
  Arcadia_Visuals_Implementation_Windows_Icon* bigIcon;
};

Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend*
Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* system,
    Arcadia_Visuals_Windows_DisplayDevice* displayDevice
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_WINDOWBACKEND_H_INCLUDED
