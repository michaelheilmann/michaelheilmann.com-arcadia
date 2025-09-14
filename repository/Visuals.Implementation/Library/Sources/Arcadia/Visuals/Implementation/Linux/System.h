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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_LINUX_SYSTEM_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_LINUX_SYSTEM_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include <X11/Xlib.h> // For Atom.

/// @code
/// class Arcadia.Visuals.Linux.System extends Arcadia.Visuals.System {
///   construct()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Linux.System", Arcadia_Visuals_Linux_System,
                          u8"Arcadia.Visuals.System")

struct Arcadia_Visuals_Linux_System {
  Arcadia_Visuals_System _parent;
  
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
};

Arcadia_Visuals_Linux_System*
Arcadia_Visuals_Linux_System_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Visuals_Linux_System*
Arcadia_Visuals_Linux_System_getOrCreate
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_LINUX_SYSTEM_H_INCLUDED
