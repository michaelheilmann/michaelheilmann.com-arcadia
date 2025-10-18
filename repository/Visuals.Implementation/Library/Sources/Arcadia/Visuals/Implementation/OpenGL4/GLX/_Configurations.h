#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__CONFIGURATIONS_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__CONFIGURATIONS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include <X11/Xlib.h>

/// @brief Get all available configurations.
/// @param thread A pointer to this thread.
/// @param self This OpenGL/GLX device information.
/// @return A list of Arcadia_Visuals_Configuration objects.
Arcadia_List*
Arcadia_Visuals_Implementation_OpenGL4_GLX_getConfigurations
  (
    Arcadia_Thread* thread,
    Display* display
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__CONFIGURATIONS_H_INCLUDED
