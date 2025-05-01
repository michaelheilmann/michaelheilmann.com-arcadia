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

#include "Module/Visuals/Windows/WglDeviceInfo.h"

// Pass the names (from left to right) to wglGetProcAddress.
// Stop if wglGetProcAddress finds a function of a name and return the function.
// If wglGetProcess does not find a function for any of the names return null.
static void*
linkv
  (
    Arcadia_Thread* thread,
    va_list names
  );

// Pass the names (from left to right) to wglGetProcAddress.
// Stop if wglGetProcAddress finds a function of a name and return the function.
// If wglGetProcess does not find a function for any of the names return null.
static void*
link
  (
    Arcadia_Thread* thread,
    ...
  );

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );



static void*
linkv
  (
    Arcadia_Thread* thread,
    va_list names
  )
{
  const Arcadia_Natural8Value* name = va_arg(names, const Arcadia_Natural8Value*);
  while (name) {
    void* p = wglGetProcAddress(name);
    if (p) {
      return p;
    }
    name = va_arg(names, const Arcadia_Natural8Value*);
  }
  return NULL;
}

static void*
link
  (
    Arcadia_Thread* thread,
    ...
  )
{
  va_list names;
  va_start(names, thread);
  void* p = linkv(thread, names);
  va_end(names);
  return p;
}


static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  )
{ return DefWindowProc(hWnd, uMsg, wParam, lParam); }



static void
Arcadia_Visuals_Windows_WglDeviceInfo_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Windows_WglDeviceInfo_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglDeviceInfo* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Windows_WglDeviceInfo_constructImpl,
  .destruct = &Arcadia_Visuals_Windows_WglDeviceInfo_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.WglDeviceInfo", Arcadia_Visuals_Windows_WglDeviceInfo, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Visuals_Windows_WglDeviceInfo_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglDeviceInfo* self
  )
{
  if (self->glResourceContextHandle) {
    if (self->glResourceContextHandle == wglGetCurrentContext()) {
      wglMakeCurrent(self->window->deviceContextHandle, NULL);
    }
    wglDeleteContext(self->glResourceContextHandle);
    self->glResourceContextHandle = NULL;
  }
  if (self->window) {
    Arcadia_Visuals_Windows_TemporaryWindow_close(thread, self->window);
    self->window = NULL;
  }
}

static void
Arcadia_Visuals_Windows_WglDeviceInfo_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Windows_WglDeviceInfo* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_WglDeviceInfo_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->window = NULL;
  _self->glResourceContextHandle = NULL;
  _self->_wglChoosePixelFormat = NULL;
  _self->_wglCreateContextAttribs = NULL;
  _self->_wglGetExtensionsString = NULL;
  _self->_wglGetPixelFormatAttribfv = NULL;
  _self->_wglGetPixelFormatAttribiv = NULL;
  Arcadia_Object_setType(thread, _self, _type);
}

Arcadia_Visuals_Windows_WglDeviceInfo*
Arcadia_Visuals_Windows_WglDeviceInfo_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_Visuals_Windows_WglDeviceInfo* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Windows_WglDeviceInfo_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_Visuals_Windows_WglDeviceInfo_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglDeviceInfo* self
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);

  self->window = Arcadia_Visuals_Windows_TemporaryWindow_create(thread);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Visuals_Windows_TemporaryWindow_open(thread, self->window);
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int ipfd = ChoosePixelFormat(self->window->deviceContextHandle, &pfd);
    if (-1 == ipfd) {
      DWORD dwError = GetLastError();
      fprintf(stderr, "%s:%d: failed to select pixel format (%lu)\n", __FILE__, __LINE__, dwError);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (!SetPixelFormat(self->window->deviceContextHandle, ipfd, &pfd)) {
      DWORD dwError = GetLastError();
      fprintf(stderr, "%s:%d: failed to set pixel format (%lu)\n", __FILE__, __LINE__, dwError);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->glResourceContextHandle = wglCreateContext(self->window->deviceContextHandle);
    if (!self->glResourceContextHandle) {
      DWORD dwError = GetLastError();
      fprintf(stderr, "%s:%d: failed to create wgl context (%lu)\n", __FILE__, __LINE__, dwError);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (!wglMakeCurrent(self->window->deviceContextHandle, self->glResourceContextHandle)) {
      DWORD dwError = GetLastError();
      fprintf(stderr, "%s:%d: failed to make wgl context current (%lu)\n", __FILE__, __LINE__, dwError);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->_wglChoosePixelFormat = (PFNWGLCHOOSEPIXELFORMATARBPROC)link(thread, "wglChoosePixelFormatARB", "wglChoosePixelFormatEXT", NULL);
    if (!self->_wglChoosePixelFormat) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->_wglCreateContextAttribs = (PFNWGLCREATECONTEXTATTRIBSARBPROC)link(thread, "wglCreateContextAttribsARB", "wglCreateContextAttribsEXT", NULL);
    if (!self->_wglCreateContextAttribs) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->_wglGetExtensionsString = (PFNWGLGETEXTENSIONSSTRINGARBPROC)link(thread, "wglGetExtensionsStringARB", "wglGetExtensionsStringEXT", NULL);
    if (!self->_wglGetExtensionsString) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->_wglGetPixelFormatAttribfv = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)link(thread, "wglGetPixelFormatAttribfvARB", "wglGetPixelFormatAttribfvEXT", NULL);
    if (!self->_wglGetPixelFormatAttribfv) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->_wglGetPixelFormatAttribiv = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)link(thread, "wglGetPixelFormatAttribivARB", "wglGetPixelFormatAttribivEXT", NULL);
    if (!self->_wglGetPixelFormatAttribiv) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (self->_wglCreateContextAttribs) {
      self->_wglCreateContextAttribs = NULL;
    }
    if (self->_wglChoosePixelFormat) {
      self->_wglChoosePixelFormat = NULL;
    }
    if (self->glResourceContextHandle) {
      if (self->glResourceContextHandle == wglGetCurrentContext()) {
        wglMakeCurrent(self->window->deviceContextHandle, NULL);
      }
      wglDeleteContext(self->glResourceContextHandle);
      self->glResourceContextHandle = NULL;
    }
    Arcadia_Visuals_Windows_TemporaryWindow_close(thread, self->window);
    self->window = NULL;
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Visuals_Windows_WglDeviceInfo_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglDeviceInfo* self
  )
{
  if (self->_wglGetPixelFormatAttribiv) {
    self->_wglGetPixelFormatAttribiv = NULL;
  }
  if (self->_wglGetPixelFormatAttribfv) {
    self->_wglGetPixelFormatAttribfv = NULL;
  }
  if (self->_wglGetExtensionsString) {
    self->_wglGetExtensionsString = NULL;
  }
  if (self->_wglCreateContextAttribs) {
    self->_wglCreateContextAttribs = NULL;
  }
  if (self->_wglChoosePixelFormat) {
    self->_wglChoosePixelFormat = NULL;
  }
  if (self->glResourceContextHandle) {
    if (self->glResourceContextHandle == wglGetCurrentContext()) {
      wglMakeCurrent(self->window->deviceContextHandle, NULL);
    }
    wglDeleteContext(self->glResourceContextHandle);
    self->glResourceContextHandle = NULL;
  }
  Arcadia_Visuals_Windows_TemporaryWindow_close(thread, self->window);
  self->window = NULL;
}

Arcadia_BooleanValue
Arcadia_Visuals_Windows_WglDeviceInfo_isVersionSupported
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_WglDeviceInfo* self,
    Arcadia_Natural8Value majorVersion,
    Arcadia_Natural8Value minorVersion
  )
{
  Arcadia_Visuals_Windows_TemporaryWindow* temporaryWindow = Arcadia_Visuals_Windows_TemporaryWindow_create(thread);
  Arcadia_Visuals_Windows_TemporaryWindow_open(thread, temporaryWindow);
  HGLRC temporaryGlResourceContext = NULL;
  static int pixelFormatAttribs[] = {
    0x2003, // WGL_ACCELERATION_ARB
    0x2027, // WGL_FULL_ACCELERATION_ARB
    0x201b, 8, // WGL_ALPHA_BITS_ARB
    0x2022, 24, // WGL_DEPTH_BITS_ARB
    0x2001, 1, // WGL_DRAW_TO_WINDOW_ARB
    0x2015, 8, // WGL_RED_BITS_ARB
    0x2017, 8, // WGL_GREEN_BITS_ARB
    0x2019, 8, // WGL_BLUE_BITS_ARB
    0x2013, 0x202B, // WGL_PIXEL_TYPE_ARB,  WGL_TYPE_RGBA_ARB
    0x2010, 1, // WGL_SUPPORT_OPENGL_ARB
    0x2014,	32, // WGL_COLOR_BITS_ARB
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  PIXELFORMATDESCRIPTOR pfd = (PIXELFORMATDESCRIPTOR){ sizeof(pfd),
                                                        1,
                                                        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 8, PFD_MAIN_PLANE,
                                                        24, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int pixelFormat;
  UINT numFormats;
  self->_wglChoosePixelFormat(temporaryWindow->deviceContextHandle, &pixelFormatAttribs[0], NULL, 1, &pixelFormat, &numFormats);
  if (!numFormats) {
    //fprintf(stderr, "%s:%d: failed to select pixel format\n", __FILE__, __LINE__);
    Arcadia_Visuals_Windows_TemporaryWindow_close(thread, temporaryWindow);
    return Arcadia_BooleanValue_False;
  }
  if (!DescribePixelFormat(temporaryWindow->deviceContextHandle, pixelFormat, sizeof(pfd), &pfd)) {
    //fprintf(stderr, "%s:%d: failed to describe pixel format\n", __FILE__, __LINE__);
    Arcadia_Visuals_Windows_TemporaryWindow_close(thread, temporaryWindow);
    return Arcadia_BooleanValue_False;
  }
  if (!SetPixelFormat(temporaryWindow->deviceContextHandle, pixelFormat, &pfd)) {
    //fprintf(stderr, "%s:%d: failed to set pixel format\n", __FILE__, __LINE__);
    Arcadia_Visuals_Windows_TemporaryWindow_close(thread, temporaryWindow);
    return Arcadia_BooleanValue_False;
  }
  if (majorVersion > INT_MAX || minorVersion > INT_MAX) {
    Arcadia_Visuals_Windows_TemporaryWindow_close(thread, temporaryWindow);
    return Arcadia_BooleanValue_False;
  }
  const int contextAttribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
    WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
    WGL_CONTEXT_FLAGS_ARB, 0,
    0
  };
  temporaryGlResourceContext = self->_wglCreateContextAttribs(temporaryWindow->deviceContextHandle, NULL, &contextAttribs[0]);
  if (!temporaryGlResourceContext) {
    //fprintf(stderr, "%s:%d: failed to create wgl context\n", __FILE__, __LINE__);
    Arcadia_Visuals_Windows_TemporaryWindow_close(thread, temporaryWindow);
    return Arcadia_BooleanValue_False;
  }
  wglDeleteContext(temporaryGlResourceContext);
  temporaryGlResourceContext = NULL;
  Arcadia_Visuals_Windows_TemporaryWindow_close(thread, temporaryWindow);
  temporaryWindow = NULL;
  return Arcadia_BooleanValue_True;
}
