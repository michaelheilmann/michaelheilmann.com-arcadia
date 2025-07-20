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

#if !defined(ARCADIA_VISUALS_WINDOWS_WGLFACTORY_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS_WGLFACTORY_H_INCLUDED

#include "Arcadia/Visuals/Windows/Wgl/WglFactoryWindow.h"
#include "Arcadia/Visuals/Configuration.h"
#include <GL/GL.h>
#include <GL/wglext.h>

/// @brief The WGL factory allows for acquiring information on available modern OpenGL contexts and creating them.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.WglFactory", Arcadia_Visuals_Windows_WglFactory, u8"Arcadia.Object");

struct Arcadia_Visuals_Windows_WglFactory {
  Arcadia_Object parent;
  Arcadia_Visuals_Windows_WglFactoryWindow* window;
  HGLRC glResourceContextHandle;

  PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormat; // wglChoosePixelFormat(ARB|EXT)
  PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribs; // wglCreateContextAttribs(ARB|EXT)
  PFNWGLGETEXTENSIONSSTRINGARBPROC _wglGetExtensionsString; // wglGetExtensionString(ARB|EXT)
  PFNWGLGETPIXELFORMATATTRIBIVARBPROC _wglGetPixelFormatAttribiv; // wglGetPixelFormatAttribiv(ARB|EXT)
  PFNWGLGETPIXELFORMATATTRIBFVARBPROC _wglGetPixelFormatAttribfv; // wglGetPixelFormatAttribiv(ARB|EXT)
};

Arcadia_Visuals_Windows_WglFactory*
Arcadia_Visuals_Windows_WglFactory_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_Windows_WglFactory_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglFactory* self
  );

void
Arcadia_Visuals_Windows_WglFactory_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglFactory* self
  );

/// @brief Get all available configurations.
/// @param thread Thiss thread.
/// @param self This OpenGL/WGL device information.
/// @return A list of Arcadia_Visuals_Configuration objects.
Arcadia_List*
Arcadia_Visuals_Windows_WglFactory_getConfigurations
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglFactory* self
  );

#endif // ARCADIA_VISUALS_WINDOWS_WGLFACTORY_H_INCLUDED
