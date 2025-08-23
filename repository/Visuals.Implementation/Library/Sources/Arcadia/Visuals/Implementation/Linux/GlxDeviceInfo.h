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

#if !defined(ARCADIA_VISUALS_LINUX_GLXDEVICEINFO_H_INCLUDED)
#define ARCADIA_VISUALS_LINUX_GLXDEVICEINFO_H_INCLUDED

#include "Arcadia/Visuals/Include.h"

#include <X11/Xlib.h>
#include <GL/glx.h>

Arcadia_declareObjectType(u8"Arcadia.Visuals.Linux.GlxDeviceInfo", Arcadia_Visuals_Linux_GlxDeviceInfo,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_Linux_GlxDeviceInfo {
  Arcadia_Object _parent;
  Display* xDisplay;
};

Arcadia_Visuals_Linux_GlxDeviceInfo*
Arcadia_Visuals_Linux_GlxDeviceInfo_create
  (
    Arcadia_Thread* thread
  );

/// @brief Get all available configurations.
/// @param thread A pointer to this thread.
/// @param self This OpenGL/GLX device information.
/// @return A list of Arcadia_Visuals_Configuration objects.
Arcadia_List*
Arcadia_Visuals_Linux_GlxDeviceInfo_getGlxConfigurations
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_GlxDeviceInfo* self
  );

Arcadia_BooleanValue
Arcadia_Visuals_Linux_GlxDeviceInfo_isGlxExtensionSupported
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_GlxDeviceInfo* self,
    const char *glXExtension
  );

#endif // ARCADIA_VISUALS_LINUX_GLXDEVICEINFO_H_INCLUDED
