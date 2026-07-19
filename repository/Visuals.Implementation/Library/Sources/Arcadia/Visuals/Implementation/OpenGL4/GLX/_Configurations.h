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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__CONFIGURATIONS_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__CONFIGURATIONS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Collections/Include.h"
#include <X11/Xlib.h>

/// @brief Get all available configurations.
/// @param thread A pointer to this thread.
/// @param self This OpenGL/GLX device information.
/// @return A list of Arcadia_Visuals_Configuration objects.
Arcadia_List*
Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_getConfigurations
  (
    Arcadia_Thread* thread,
    Display* display
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__CONFIGURATIONS_H_INCLUDED
