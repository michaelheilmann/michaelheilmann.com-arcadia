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

// Last modified: 2024-11-11

#if !defined(MODULE_VISUALS_WINDOWS_WGLCONTEXTINFO_H_INCLUDED)
#define MODULE_VISUALS_WINDOWS_WGLCONTEXTINFO_H_INCLUDED

#include "Module/Visuals/Windows/TemporaryWindow.h"
#include <GL/GL.h>
#include <GL/wglext.h>

/// @brief Information on an available WGL context.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.WglContextInfo", Arcadia_Visuals_Windows_WglContextInfo, u8"Arcadia.Object");

struct Arcadia_Visuals_Windows_WglContextInfo {
  Arcadia_Object parent;
  Arcadia_Visuals_Windows_TemporaryWindow* window;
  HGLRC glResourceContextHandle;

  PFNWGLCHOOSEPIXELFORMATARBPROC _wglChoosePixelFormat; // wglChoosePixelFormat(ARB|EXT)
  PFNWGLCREATECONTEXTATTRIBSARBPROC _wglCreateContextAttribs; // wglCreateContextAttribs(ARB|EXT)
  PFNWGLGETEXTENSIONSSTRINGARBPROC _wglGetExtensionsString; // wglGetExtensionString(ARB|EXT)
  PFNWGLGETPIXELFORMATATTRIBIVARBPROC _wglGetPixelFormatAttribiv; // wglGetPixelFormatAttribiv(ARB|EXT)
  PFNWGLGETPIXELFORMATATTRIBFVARBPROC _wglGetPixelFormatAttribfv; // wglGetPixelFormatAttribiv(ARB|EXT)
};

/// @code
/// construct(Natural8 majorVersion, Natural8 minorVersion)
/// @endcode
Arcadia_Visuals_Windows_WglContextInfo*
Arcadia_Visuals_Windows_WglContextInfo_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value majorVersion,
    Arcadia_Natural8Value minorVersion
  );

void
Arcadia_Visuals_Windows_WglContextInfo_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglContextInfo* self
  );

void
Arcadia_Visuals_Windows_WglContextInfo_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglContextInfo* self
  );

/// @brief Get the major version of this WGL context info.
/// @param thread This thread.
/// @param self This WGL context info.
/// @return The major version of this WGL context info.
Arcadia_Natural8Value
Arcadia_Visuals_Windows_WglContextInfo_getMajorVersion
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglContextInfo* self
  );

/// @brief Get the minor version of this WGL context info.
/// @param thread This thread.
/// @param self This WGL context info.
/// @return The minor version of this WGL context info.
Arcadia_Natural8Value
Arcadia_Visuals_Windows_WglContextInfo_getMinorVersion
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglContextInfo* self
  );

#endif // MODULE_VISUALS_WINDOWS_WGLCONTEXTINFO_H_INCLUDED
