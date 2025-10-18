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

#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/Factorywindow.h"

#define WindowClassName "Arcadia.Visuals.OpenGL4.WGL.FactoryWindow"
#define WindowTitle "Arcadia OpenGL 4 WGL Factory Window"

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.WGL.FactoryWindow", Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

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
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow* self
  )
{
  if (self->deviceContextHandle) {
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
  }
  if (self->windowHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
  }
  if (self->instanceHandle) {
    UnregisterClass(WindowClassName, self->instanceHandle);
    self->instanceHandle = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  self->instanceHandle = NULL;
  self->classAtom = 0;
  self->windowHandle = NULL;
  self->deviceContextHandle = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow*
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow);
}

void
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow* self
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
    if (!GetClassInfoEx(self->instanceHandle, WindowClassName, &wcex)) {
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
      wcex.lpszClassName = WindowClassName;
      wcex.hIconSm = NULL;
      self->classAtom = RegisterClassExA(&wcex);
      if (!self->classAtom) {
        fprintf(stderr, "%s:%d: failed to register window class\n", __FILE__, __LINE__);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    }

    self->windowHandle = CreateWindowA(WindowClassName,
                                       WindowTitle,
                                       WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                       NULL,
                                       NULL,
                                       self->instanceHandle,
                                       NULL);
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
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (self->deviceContextHandle) {
      ReleaseDC(self->windowHandle, self->deviceContextHandle);
      self->deviceContextHandle = NULL;
    }
    if (self->windowHandle) {
      DestroyWindow(self->windowHandle);
      self->windowHandle = NULL;
    }
    if (self->classAtom) {
      UnregisterClass(WindowClassName, self->instanceHandle);
      self->classAtom = 0;
    }
    if (self->instanceHandle) {
      self->instanceHandle = NULL;
    }
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_FactoryWindow* self
  )
{
  if (self->deviceContextHandle) {
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
  }
  if (self->windowHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
  }
  if (self->classAtom) {
    UnregisterClass(WindowClassName, self->instanceHandle);
    self->classAtom = 0;
  }
  if (self->instanceHandle) {
    self->instanceHandle = NULL;
  }
}
