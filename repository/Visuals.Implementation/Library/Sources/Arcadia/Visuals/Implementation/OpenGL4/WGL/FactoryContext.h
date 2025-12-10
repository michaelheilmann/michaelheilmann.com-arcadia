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

#if !defined(ARCADIA_VISUALS_OPENGL_WGL_FACTORYCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_OPENGL_WGL_FACTORYCONTEXT_H_INCLUDED

#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/FactoryWindow.h"
#include "Arcadia/Visuals/Include.h"

#if !defined(WIN32_LEAN_AND_MEAN)
  #define WIN32_LEAN_AND_MEAN
#endif
#if !defined(NOCOMM)
  #define NOCOMM
#endif
#include <GL/glcorearb.h>
#include <GL/wglext.h>

// An old style context. Provides means to enumerate new style context configurations and create new style contexts.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.WGL.FactoryContext", Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContextDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext {
  Arcadia_Object parent;
  Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow* window;
  HGLRC glResourceContextHandle;

  PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormat; // wglChoosePixelFormat(ARB|EXT)
  PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribs; // wglCreateContextAttribs(ARB|EXT)
  PFNWGLGETEXTENSIONSSTRINGARBPROC _wglGetExtensionsString; // wglGetExtensionString(ARB|EXT)
  PFNWGLGETPIXELFORMATATTRIBIVARBPROC _wglGetPixelFormatAttribiv; // wglGetPixelFormatAttribiv(ARB|EXT)
  PFNWGLGETPIXELFORMATATTRIBFVARBPROC _wglGetPixelFormatAttribfv; // wglGetPixelFormatAttribiv(ARB|EXT)
};

Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext*
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext* self
  );

void
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext* self
  );

/// @brief Get all available configurations.
/// @param thread A pointer to this thread.
/// @param self This OpenGL/WGL device information.
/// @return A list of Arcadia_Visuals_Configuration objects.
Arcadia_List*
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext_getConfigurations
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryContext* self
  );

#endif // ARCADIA_VISUALS_OPENGL_WGL_FACTORYCONTEXT_H_INCLUDED
