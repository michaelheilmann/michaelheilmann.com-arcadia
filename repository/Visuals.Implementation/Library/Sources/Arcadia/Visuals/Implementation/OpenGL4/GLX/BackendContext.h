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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX_BACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Shared/Functions.h"
#include <X11/Xlib.h> // For Atom.
#include <GL/glx.h> // For XVisualInfo and GLXFBConfig.

/// @code
/// class Arcadia.Visuals.OpenGL4.GLX.BackendContext extends Arcadia.Visuals.BackendContext {
///   construct()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.GLX.BackendContext", Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext,
                          u8"Arcadia.Visuals.Implementation.OpenGL4.BackendContext")

struct Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContextDispatch {
  Arcadia_Visuals_Implementation_OpenGL4_BackendContextDispatch _parent;
};

struct Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext {
  Arcadia_Visuals_Implementation_OpenGL4_BackendContext _parent;

  // The display used by the OpenGL/GLX context and the X11 windows.
  Display* display;

  Atom _NET_WM_ICON;
  Atom WM_DELETE_WINDOW;
  Atom _NET_FRAME_EXTENTS;
  Atom _MOTIF_WM_HINTS;

  // See https://linux.die.net/man/3/xrandr for more information.
  struct {
    /// The base of the event IDs of the XRANDR extension.
    int eventBase;
    /// The base of the error IDs of the XRANDR extension.
    int errorBase;
  } xrandr;

  // The visuals used by the OpenGL/GLX context and the X11 windows.
  // Default value is NULL.
  XVisualInfo *visualInfo;
  // The frame buffer configuration used by the OpenGL/GLX context and the X11 windows.
  // Default value is NULL.
  GLXFBConfig *frameBufferConfiguration;
  // The color map used by the OpenGL/GLX context and the X11 windows.
  // Default value is None.
  Colormap colormap;
  // The OpenGL/GLX context.
  // Default value is NULL.
  GLXContext context;

  /// The OpenGL and GLX functions available to us.
  _Arcadia_Visuals_Implementation_OpenGL4_Functions _functions;
};

Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext*
Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext*
Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext_getOrCreate
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX_BACKENDCONTEXT_H_INCLUDED
