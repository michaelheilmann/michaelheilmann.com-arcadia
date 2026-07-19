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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__EXTENSIONS_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__EXTENSIONS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Collections/Include.h"
#include <X11/Xlib.h>

/// Obtain the set of GLX extension strings.
/// @remarks The GLX extension strings are obtained via a call to
/// glXQueryExtensionsString. That call returns the GLX extension
/// strings in a single string separated by whitespaces. A GLX
/// extension string itself does not contain whitespaces.
Arcadia_Set*
Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_getExtensions
  (
    Arcadia_Thread* thread,
    Display* display
  );

/// Obtain the set of GLX extension strings.
/// Check if the specified extension string is contained in that set.
Arcadia_BooleanValue
Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_hasExtension
  (
    Arcadia_Thread* thread,
    Display* display,
    Arcadia_String* extension
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX__EXTENSIONS_H_INCLUDED
