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

#include "Module/Visuals/Windows/TemporaryWindow.h"

#define WindowClassName "Arcadia.Visuals.Windows.TemporaryWindow"
#define WindowTitle "Arcadia Temporary Window"

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );

static void
Arcadia_Visuals_Windows_TemporaryWindow_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TemporaryWindow* self
  );

static void
Arcadia_Visuals_Windows_TemporaryWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Windows_TemporaryWindow_constructImpl,
  .destruct = &Arcadia_Visuals_Windows_TemporaryWindow_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.TemporaryWindow", Arcadia_Visuals_Windows_TemporaryWindow, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

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
Arcadia_Visuals_Windows_TemporaryWindow_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TemporaryWindow* self
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
Arcadia_Visuals_Windows_TemporaryWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Windows_TemporaryWindow* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_TemporaryWindow_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->instanceHandle = NULL;
  _self->classAtom = 0;
  _self->windowHandle = NULL;
  _self->deviceContextHandle = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

Arcadia_Visuals_Windows_TemporaryWindow*
Arcadia_Visuals_Windows_TemporaryWindow_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Visuals_Windows_TemporaryWindow* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Windows_TemporaryWindow_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_Visuals_Windows_TemporaryWindow_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TemporaryWindow* self
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
    //ShowWindow(self->windowHandle, SW_SHOWDEFAULT);
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
Arcadia_Visuals_Windows_TemporaryWindow_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_TemporaryWindow* self
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
