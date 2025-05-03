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

#if !defined(MODULE_VISUALS_LINUX_APPLICATION_H_INCLUDED)
#define MODULE_VISUALS_LINUX_APPLICATION_H_INCLUDED
 
#include "Module/Visuals/Application.h"
#include <X11/Xlib.h> // For Atom.

/// @code
/// class Arcadia.Visuals.Linux.Application extends Arcadia.Visuals.Application {
///   construct()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Linux.Application", Arcadia_Visuals_Linux_Application, u8"Arcadia.Visuals.Application")

struct Arcadia_Visuals_Linux_Application {
  Arcadia_Visuals_Application _parent;
  Display* display;
  Atom _NET_WM_ICON;
  Atom WM_DELETE_WINDOW;
};

Arcadia_Visuals_Linux_Application*
Arcadia_Visuals_Linux_Application_create
  (
    Arcadia_Thread* thread
  );

#endif // MODULE_VISUALS_LINUX_APPLICATION_H_INCLUDED
