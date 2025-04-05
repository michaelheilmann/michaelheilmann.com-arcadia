// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Module/Visuals/Windows/WglIntermediateWindow.h"

#define ClassName "Arcadia.Visuals.Windows.WglIntermediateWindow"

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );

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
Visuals_Window_WglIntermediateWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Visuals_Window_WglIntermediateWindow_destruct
  (
    Arcadia_Thread* thread,
    Visuals_Window_WglIntermediateWindow* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Visuals_Window_WglIntermediateWindow_constructImpl,
  .destruct = &Visuals_Window_WglIntermediateWindow_destruct,
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

Arcadia_defineObjectType(u8"Visuals.Windows.WglIntermediateWindow", Visuals_Window_WglIntermediateWindow, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Visuals_Window_WglIntermediateWindow_destruct
  (
    Arcadia_Thread* thread,
    Visuals_Window_WglIntermediateWindow* self
  )
{
  if (self->glResourceContextHandle) {
    if (self->glResourceContextHandle == wglGetCurrentContext()) {
      wglMakeCurrent(self->deviceContextHandle, NULL);
    }
    wglDeleteContext(self->glResourceContextHandle);
    self->glResourceContextHandle = NULL;
  }
  if (self->deviceContextHandle) {
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
  }
  if (self->windowHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
  }
  if (self->instanceHandle) {
    UnregisterClass(ClassName, self->instanceHandle);
    self->instanceHandle = NULL;
  }
}

static void
Visuals_Window_WglIntermediateWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Visuals_Window_WglIntermediateWindow* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Visuals_Window_WglIntermediateWindow_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->instanceHandle = NULL;
  _self->classAtom = 0;
  _self->windowHandle = NULL;
  _self->deviceContextHandle = NULL;
  _self->glResourceContextHandle = NULL;
  _self->choosePixelFormat = NULL;
  _self->createContextAttribs = NULL;
  Arcadia_Object_setType(thread, _self, _type);
}

Visuals_Window_WglIntermediateWindow*
Visuals_Window_WglIntermediateWindow_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Visuals_Window_WglIntermediateWindow* self = Arcadia_allocateObject(thread, _Visuals_Window_WglIntermediateWindow_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Visuals_Window_WglIntermediateWindow_open
  (
    Arcadia_Thread* thread,
    Visuals_Window_WglIntermediateWindow* self
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);


  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    self->instanceHandle = GetModuleHandleA(NULL);
    if (!self->instanceHandle) {
      fprintf(stderr, "%s:%d: failed to acquire module handle\n", __FILE__, __LINE__);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }

    WNDCLASSEXA wcex;
    memset(&wcex, 0, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = (WNDPROC)WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = ClassName;
    wcex.hIconSm = NULL;

    self->classAtom = RegisterClassExA(&wcex);
    if (!self->classAtom) {
      fprintf(stderr, "%s:%d: failed to register window class\n", __FILE__, __LINE__);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }

    self->windowHandle = CreateWindowA(ClassName, "Arcadia Intermediate Window",
                                       WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, self->instanceHandle, NULL);
    if (!self->windowHandle) {
      fprintf(stderr, "%s:%d: failed to create window\n", __FILE__, __LINE__);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->deviceContextHandle = GetDC(self->windowHandle);
    if (!self->deviceContextHandle) {
      fprintf(stderr, "%s:%d: failed to create device context\n", __FILE__, __LINE__);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    ShowWindow(self->windowHandle, SW_SHOWDEFAULT);
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int ipfd = ChoosePixelFormat(self->deviceContextHandle, &pfd);
    if (-1 == ipfd) {
      DWORD dwError = GetLastError();
      fprintf(stderr, "%s:%d: failed to select pixel format (%lu)\n", __FILE__, __LINE__, dwError);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (!SetPixelFormat(self->deviceContextHandle, ipfd, &pfd)) {
      DWORD dwError = GetLastError();
      fprintf(stderr, "%s:%d: failed to set pixel format (%lu)\n", __FILE__, __LINE__, dwError);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->glResourceContextHandle = wglCreateContext(self->deviceContextHandle);
    if (!self->glResourceContextHandle) {
      DWORD dwError = GetLastError();
      fprintf(stderr, "%s:%d: failed to create wgl context (%lu)\n", __FILE__, __LINE__, dwError);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (!wglMakeCurrent(self->deviceContextHandle, self->glResourceContextHandle)) {
      DWORD dwError = GetLastError();
      fprintf(stderr, "%s:%d: failed to make wgl context current (%lu)\n", __FILE__, __LINE__, dwError);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->choosePixelFormat = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    if (!self->choosePixelFormat) {
      self->choosePixelFormat = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatEXT");
      if (!self->choosePixelFormat) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    }
    self->createContextAttribs = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    if (!self->createContextAttribs) {
      self->createContextAttribs = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsEXT");
      if (!self->createContextAttribs) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    }
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (self->createContextAttribs) {
      self->createContextAttribs = NULL;
    }
    if (self->choosePixelFormat) {
      self->choosePixelFormat = NULL;
    }
    if (self->glResourceContextHandle) {
      if (self->glResourceContextHandle == wglGetCurrentContext()) {
        wglMakeCurrent(self->deviceContextHandle, NULL);
      }
      wglDeleteContext(self->glResourceContextHandle);
      self->glResourceContextHandle = NULL;
    }
    if (self->deviceContextHandle) {
      ReleaseDC(self->windowHandle, self->deviceContextHandle);
      self->deviceContextHandle = NULL;
    }
    if (self->windowHandle) {
      DestroyWindow(self->windowHandle);
      self->windowHandle = NULL;
    }
    if (self->classAtom) {
      UnregisterClass(ClassName, self->instanceHandle);
      self->classAtom = 0;
    }
    if (self->instanceHandle) {
      self->instanceHandle = NULL;
    }
    Arcadia_Thread_jump(thread);
  }
}

void
Visuals_Window_WglIntermediateWindow_close
  (
    Arcadia_Thread* thread,
    Visuals_Window_WglIntermediateWindow* self
  )
{
  if (self->createContextAttribs) {
    self->createContextAttribs = NULL;
  }
  if (self->choosePixelFormat) {
    self->choosePixelFormat = NULL;
  }
  if (self->glResourceContextHandle) {
    if (self->glResourceContextHandle == wglGetCurrentContext()) {
      wglMakeCurrent(self->deviceContextHandle, NULL);
    }
    wglDeleteContext(self->glResourceContextHandle);
    self->glResourceContextHandle = NULL;
  }
  if (self->deviceContextHandle) {
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
  }
  if (self->windowHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
  }
  if (self->classAtom) {
    UnregisterClass(ClassName, self->instanceHandle);
    self->classAtom = 0;
  }
  if (self->instanceHandle) {
    self->instanceHandle = NULL;
  }
}
