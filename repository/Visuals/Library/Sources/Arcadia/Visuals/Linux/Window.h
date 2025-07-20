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

#if !defined(ARCADIA_VISUALS_LINUX_WINDOW_H_INCLUDED)
#define ARCADIA_VISUALS_LINUX_WINDOW_H_INCLUDED

#include "Arcadia/Visuals/Window.h"
#include "Arcadia/Visuals/Linux/Application.h"
#include "Arcadia/Visuals/Linux/GlxDeviceInfo.h"
#include "Arcadia/Visuals/Linux/Icon.h"

#include <X11/Xlib.h>
#include <GL/glx.h>

Arcadia_declareObjectType(u8"Arcadia.Visuals.Linux.Window", Arcadia_Visuals_Linux_Window, u8"Arcadia.Visuals.Window");

struct Arcadia_Visuals_Linux_Window {
  Arcadia_Visuals_Window _parent;

  // Each window holds a lock on the application
  // as it uses the atoms and the display of the
  // application.
  Arcadia_Visuals_Linux_Application* application;

  //Display* display; // Default value is NULL.
  Screen* screen; // Default value is NULL.
  Window window; // Default value is None.
  Colormap colormap; // Default value is None.
  GLXFBConfig *frameBufferConfiguration; // Default value is NULL.
  XVisualInfo *visualInfo; // Default value is NULL.
  GLXContext context; // Default value is NULL.

  Arcadia_String* title;
  Arcadia_Visuals_Linux_Icon* smallIcon;
  Arcadia_Visuals_Linux_Icon* bigIcon;
};

Arcadia_Visuals_Linux_Window*
Arcadia_Visuals_Linux_Window_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* application
  );

#endif // ARCADIA_VISUALS_LINUX_WINDOW_H_INCLUDED
