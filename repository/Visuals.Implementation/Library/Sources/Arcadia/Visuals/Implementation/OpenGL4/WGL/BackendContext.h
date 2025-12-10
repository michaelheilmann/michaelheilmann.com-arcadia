// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_BACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/SystemWindow.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Shared/Functions.h"
typedef struct Arcadia_Visuals_Implementation_SceneNodeFactory Arcadia_Visuals_Implementation_SceneNodeFactory;

#if !defined(WIN32_LEAN_AND_MEAN)
  #define WIN32_LEAN_AND_MEAN
#endif
#if !defined(NOCOMM)
  #define NOCOMM
#endif
#include <Windows.h>

/// The system maintains
/// - a window class for all window
/// - a pixel format for all window
/// - a system window (with the default window classs)
/// - an HGLRC window (compatible with the system window)
///   This context is attached to actual windows on demand
/// - an OpenGL4 context
///
/// @code
/// class Arcadia.Visuals.Implementation.OpenGL4.WGL.BackendContext extends Arcadia.Visuals.BackendContext {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.WGL.BackendContext", Arcadia_Visuals_Implementation_OpenGL4_WGL_BackendContext,
                          u8"Arcadia.Visuals.Implementation.OpenGL4.BackendContext");

struct Arcadia_Visuals_Implementation_OpenGL4_WGL_BackendContextDispatch {
  Arcadia_Visuals_Implementation_OpenGL4_BackendContextDispatch _parent;
};

struct Arcadia_Visuals_Implementation_OpenGL4_WGL_BackendContext {
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext _parent;
  // The instance handle of the process.
  HINSTANCE instanceHandle;
  // The atom of the window class used for window backends.
  ATOM classAtom;
  // The name of the window class used for window backends.
  char* className;
  // The window callback procedure of the window class used for window backends.
  WNDPROC defaultWindowCallbackProcedure;
  // The WGL/OpenGL system-wide pixel format indexused for window backends.
  int pixelFormatIndex;
  // The WGL/OpenGL system-wide window.
  Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow* systemWindow;
  // The WGL/OpenGL system-wide resource context handle.
  HGLRC glResourceContextHandle;
  // The WGL/OpenGL driver library handle.That is, the handle to OPENGL32.DLL.
  HANDLE glDriverLibrary;

  /// The OpenGL and WGL functions available to us.
  _Arcadia_Visuals_Implementation_OpenGL4_Functions _functions;
};

Arcadia_Visuals_Implementation_OpenGL4_WGL_BackendContext*
Arcadia_Visuals_Implementation_OpenGL4_WGL_BackendContext_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Visuals_Implementation_OpenGL4_WGL_BackendContext*
Arcadia_Visuals_Implementation_OpenGL4_WGL_BackendContext_getOrCreate
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_BACKENDCONTEXT_H_INCLUDED
