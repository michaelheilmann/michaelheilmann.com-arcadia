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

#if !defined(MODULE_VISUALS_WINDOWS_WGLINTERMEDIATEWINDOW_H_INCLUDED)
#define MODULE_VISUALS_WINDOWS_WGLINTERMEDIATEWINDOW_H_INCLUDED

#include "Module/Visuals/Windows/TemporaryWindow.h"
#include "Module/Visuals/Configuration.h"
#include <GL/GL.h>
#include <GL/wglext.h>

/// @brief Information on an available WGL.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.WglDeviceInfo", Arcadia_Visuals_Windows_WglDeviceInfo, u8"Arcadia.Object");

struct Arcadia_Visuals_Windows_WglDeviceInfo {
  Arcadia_Object parent;
  Arcadia_Visuals_Windows_TemporaryWindow* window;
  HGLRC glResourceContextHandle;

  PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormat; // wglChoosePixelFormat(ARB|EXT)
  PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribs; // wglCreateContextAttribs(ARB|EXT)
  PFNWGLGETEXTENSIONSSTRINGARBPROC _wglGetExtensionsString; // wglGetExtensionString(ARB|EXT)
  PFNWGLGETPIXELFORMATATTRIBIVARBPROC _wglGetPixelFormatAttribiv; // wglGetPixelFormatAttribiv(ARB|EXT)
  PFNWGLGETPIXELFORMATATTRIBFVARBPROC _wglGetPixelFormatAttribfv; // wglGetPixelFormatAttribiv(ARB|EXT)
};

Arcadia_Visuals_Windows_WglDeviceInfo*
Arcadia_Visuals_Windows_WglDeviceInfo_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_Windows_WglDeviceInfo_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglDeviceInfo* self
  );

void
Arcadia_Visuals_Windows_WglDeviceInfo_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglDeviceInfo* self
  );

/// @brief Get all available configurations.
/// @param thread Thiss thread.
/// @param self This OpenGL/WGL device information.
/// @return A list of Arcadia_Visuals_Configuration objects.
Arcadia_List*
Arcadia_Visuals_Windows_WglDeviceInfo_getConfigurations
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglDeviceInfo* self
  );

#endif // MODULE_VISUALS_WINDOWS_WGLINTERMEDIATEWINDOW_H_INCLUDED
