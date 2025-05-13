#if !defined(ARCADIA_VISUALS_LINUX_GLXDEVICEINFO_H_INCLUDED)
#define ARCADIA_VISUALS_LINUX_GLXDEVICEINFO_H_INCLUDED

#include "Module/Visuals/Configuration.h"

#include <X11/Xlib.h>
#include <GL/glx.h>

Arcadia_declareObjectType(u8"Arcadia.Visuals.Linux.GlxDeviceInfo", Arcadia_Visuals_Linux_GlxDeviceInfo, u8"Arcadia.Object");

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
/// @param thread Thiss thread.
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
