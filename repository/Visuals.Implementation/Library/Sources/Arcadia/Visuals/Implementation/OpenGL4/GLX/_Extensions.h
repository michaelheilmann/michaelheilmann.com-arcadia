#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__EXTENSIONS_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__EXTENSIONS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include <X11/Xlib.h>

/// Obtain the set of GLX extension strings.
/// @remarks The GLX extension strings are obtained via a call to
/// glXQueryExtensionsString. That call returns the GLX extension
/// strings in a single string separated by whitespaces. A GLX
/// extension string itself does not contain whitespaces.
Arcadia_Set*
Arcadia_Visuals_Implementation_OpenGL4_GLX_getExtensions
  (
    Arcadia_Thread* thread,
    Display* display
  );

/// Obtain the set of GLX extension strings.
/// Check if the specified extension string is contained in that set.
Arcadia_BooleanValue
Arcadia_Visuals_Implementation_OpenGL4_GLX_hasExtension
  (
    Arcadia_Thread* thread,
    Display* display,
    Arcadia_String* extension
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__EXTENSIONS_H_INCLUDED
