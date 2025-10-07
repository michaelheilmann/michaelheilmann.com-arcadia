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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_SYSTEM_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_SYSTEM_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/SystemWindow.h"

#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <Windows.h>

/// The system maintains a pixel format and an OpenGL resource context.
/// The pixel format must be remembered as each time a new window is created the pixel format must be set for that window and all windows must have the same pixel format.
/// The OpenGL resource context is a singleton and is either attached to a single window or is not attached.
/// 
/// @code
/// class Arcadia.Visuals.Implementation.OpenGL4.WGL.System extends Arcadia.Visuals.System {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.WGL.System", Arcadia_Visuals_Implementation_OpenGL4_WGL_System,
                          u8"Arcadia.Visuals.System")

struct Arcadia_Visuals_Implementation_OpenGL4_WGL_System {
  Arcadia_Visuals_System _parent;
  // The instance handle of the process.
  HINSTANCE instanceHandle;
  // The atom of the window class.
  ATOM classAtom;
  // The name of the window class.
  char* className;
  // The window callback procedure of the window class.
  WNDPROC defaultWindowCallbackProcedure;

  // The WGL/OpenGL system-wide window.
  Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow* systemWindow;
  // The WGL/OpenGL system-wide resource context handle.
  HGLRC glResourceContextHandle;
  // The WGL/OpenGL system-wide pixel format index.
  int pixelFormatIndex;
};

// @todo Make private.
Arcadia_Visuals_Implementation_OpenGL4_WGL_System*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Visuals_Implementation_OpenGL4_WGL_System*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_getOrCreate
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_SYSTEM_H_INCLUDED
