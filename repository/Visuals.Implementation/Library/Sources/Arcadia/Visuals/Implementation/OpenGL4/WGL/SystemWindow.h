#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_SYSTEMWINDOW_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_SYSTEMWINDOW_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <Windows.h>

// The "system" window is kept around as long as the system exists.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.WGL.SystemWindow", Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow {
  Arcadia_Object parent;
  HINSTANCE instanceHandle;
  ATOM classAtom;
  HWND windowHandle;
  HDC deviceContextHandle;
};

Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow*
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow* self
  );

void
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow* self
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_WGL_SYSTEMWINDOW_H_INCLUDED
