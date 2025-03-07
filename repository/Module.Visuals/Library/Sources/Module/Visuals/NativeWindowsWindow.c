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

#include "Module/Visuals/NativeWindowsWindow.h"

#include <limits.h>

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );

static void
NativeWindowsWindow_destruct
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static void
NativeWindowsWindow_visit
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static void
NativeWindowsWindow_setTitleHelper
  (
    Arcadia_Thread* thread,
    HWND windowHandle,
    Arcadia_String* title
  );

static void
NativeWindowsWindow_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
openImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static void
closeImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_BooleanValue quitRequested
  );

static void
updateImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static NativeWindowsIcon*
getBigIconImpl 
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    NativeWindowsIcon* icon
  );

static NativeWindowsIcon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    NativeWindowsIcon* icon
  );

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  );

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_String* title
  );

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static const char g_title[] = "Liminality";

static const char g_className[] = "Liminality Window Class";

static Arcadia_BooleanValue g_quitRequested = Arcadia_BooleanValue_False;

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &NativeWindowsWindow_constructImpl,
  .destruct = &NativeWindowsWindow_destruct,
  .visit = &NativeWindowsWindow_visit,
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

Rex_defineObjectType(u8"NativeWindowsWindow", NativeWindowsWindow, u8"NativeWindow", NativeWindow, &_typeOperations);

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  ) 
{
  switch (uMsg) {
    case WM_CLOSE: {
      g_quitRequested = Arcadia_BooleanValue_True;
      return 0;
    } break;
    case WM_KEYUP: {
      if (LOWORD(wParam) == VK_ESCAPE) {
        g_quitRequested = Arcadia_BooleanValue_True;
      }
      return 0;
    } break;
    default: {
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
    } break;
  };
}

static void
NativeWindowsWindow_destruct
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  )
{
  if (NULL != self->windowDeviceContextHandle) {
    ReleaseDC(self->windowHandle, self->windowDeviceContextHandle);
    self->windowDeviceContextHandle = NULL;
  }
  if (NULL != self->windowHandle) {
    DeleteObject(self->windowHandle);
    self->windowHandle = NULL;
  }
  self->instanceHandle = NULL;
}

static void
NativeWindowsWindow_visit
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  )
{
  if (self->title) {
    Arcadia_Object_visit(thread, self->title);
  }
  if (self->smallIcon) {
    Arcadia_Object_visit(thread, self->smallIcon);
  }
  if (self->bigIcon) {
    Arcadia_Object_visit(thread, self->bigIcon);
  }
}

static void
NativeWindowsWindow_setTitleHelper
  (
    Arcadia_Thread* thread,
    HWND windowHandle,
    Arcadia_String* title
  )
{
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_Value value;
  Arcadia_Value_setObjectReferenceValue(&value, (Arcadia_ObjectReferenceValue)title);
  Arcadia_StringBuffer_append(thread, stringBuffer, value);
  Arcadia_Value_setObjectReferenceValue(&value, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"", 1)));
  Arcadia_StringBuffer_append(thread, stringBuffer, value);
  SendMessage(windowHandle, WM_SETTEXT, 0, (LPARAM)Arcadia_StringBuffer_getBytes(thread, stringBuffer));
}

static void
NativeWindowsWindow_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  NativeWindowsWindow* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _NativeWindowsWindow_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->instanceHandle = NULL;
  _self->windowHandle = NULL;
  _self->title = Arcadia_String_create_pn(Arcadia_Process_getThread(process), Arcadia_ImmutableByteArray_create(Arcadia_Process_getThread(process), g_title, sizeof(g_title) - 1));
  _self->bigIcon = NULL;
  _self->smallIcon = NULL;

  ((NativeWindow*)_self)->open = (void(*)(Arcadia_Thread*, NativeWindow*)) & openImpl;

  ((NativeWindow*)_self)->close = (void(*)(Arcadia_Thread*, NativeWindow*)) & closeImpl;

  ((NativeWindow*)_self)->getQuitRequested = (Arcadia_BooleanValue(*)(Arcadia_Thread*, NativeWindow*)) & getQuitRequestedImpl;
  ((NativeWindow*)_self)->setQuitRequested = (void(*)(Arcadia_Thread*, NativeWindow*,Arcadia_BooleanValue)) & setQuitRequestedImpl;

  ((NativeWindow*)_self)->update = (void(*)(Arcadia_Thread*, NativeWindow*)) &updateImpl;

  ((NativeWindow*)_self)->getRequiredBigIconSize = (void(*)(Arcadia_Thread*, NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredBigIconSizeImpl;
  ((NativeWindow*)_self)->getRequiredSmallIconSize = (void(*)(Arcadia_Thread*, NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredSmallIconSizeImpl;

  ((NativeWindow*)_self)->getBigIcon = (NativeIcon*(*)(Arcadia_Thread*, NativeWindow*)) & getBigIconImpl;
  ((NativeWindow*)_self)->setBigIcon = (void(*)(Arcadia_Thread*, NativeWindow*, NativeIcon*)) & setBigIconImpl;

  ((NativeWindow*)_self)->getSmallIcon = (NativeIcon*(*)(Arcadia_Thread*, NativeWindow*)) & getSmallIconImpl;
  ((NativeWindow*)_self)->setSmallIcon = (void(*)(Arcadia_Thread*, NativeWindow*, NativeIcon*)) & setSmallIconImpl;

  ((NativeWindow*)_self)->getTitle = (Arcadia_String*(*)(Arcadia_Thread*, NativeWindow*)) & getTitleImpl;
  ((NativeWindow*)_self)->setTitle = (void(*)(Arcadia_Thread*, NativeWindow*, Arcadia_String*)) & setTitleImpl;

  ((NativeWindow*)_self)->getCanvasSize = (void(*)(Arcadia_Thread*, NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getCanvasSizeImpl;

  Arcadia_Object_setType(Arcadia_Process_getThread(process), _self, _type);
}

static void
openImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  )
{ 
  if (self->windowHandle) {
    return;
  }

  self->instanceHandle = GetModuleHandleA(NULL);
  if (!self->instanceHandle) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // Register the window class.
  WNDCLASS wc = { 0 };

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = self->instanceHandle;
  wc.lpszClassName = g_className;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Prevent the busy cursor from showing up.

  if (!RegisterClass(&wc)) {
    self->instanceHandle = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  self->windowHandle =
    CreateWindowEx
      (
        0,                               // Optional window styles.
        g_className,                     // Window class
        "Windows Window",                // Window text
        WS_OVERLAPPEDWINDOW,             // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,    // Default position
        CW_USEDEFAULT, CW_USEDEFAULT,    // Default size
        NULL,                            // Parent window    
        NULL,                            // Menu
        self->instanceHandle,            // Instance handle
        NULL                             // Additional application data
      );

  if (!self->windowHandle) {
    UnregisterClass(g_className, self->instanceHandle);
    self->instanceHandle = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->instanceHandle);
    self->instanceHandle = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  self->windowDeviceContextHandle = GetDC(self->windowHandle);
  if (!self->windowDeviceContextHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->instanceHandle);
    self->instanceHandle = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    NativeWindowsWindow_setTitleHelper(thread, self->windowHandle, self->title);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->instanceHandle);
    self->instanceHandle = NULL;
    Arcadia_Thread_jump(thread);
  }

  ShowWindow(self->windowHandle, SW_SHOW);
}

static void
closeImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  ) 
{
  if (!self->windowHandle) {
    return;
  }
  ReleaseDC(self->windowHandle, self->windowDeviceContextHandle);
  self->windowDeviceContextHandle = NULL;
  DestroyWindow(self->windowHandle);
  self->windowHandle = NULL;
  self->instanceHandle = NULL;
}

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  )
{ return g_quitRequested; }

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_BooleanValue quitRequested
  )
{ g_quitRequested = quitRequested; }

static void
updateImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  )
{
  MSG msg = { 0 };
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if (msg.message == WM_QUIT) {
      g_quitRequested = Arcadia_BooleanValue_True;
    }
  }
}

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = GetSystemMetrics(SM_CXICON);
  *height = GetSystemMetrics(SM_CYICON);
}

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = GetSystemMetrics(SM_CXSMICON);
  *height = GetSystemMetrics(SM_CYSMICON);
}

static NativeWindowsIcon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  )
{ return self->bigIcon; }

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    NativeWindowsIcon* icon
  )
{
  self->bigIcon = icon;
  if (self->windowHandle) {
    if (self->bigIcon) {
      SendMessage(self->windowHandle, WM_SETICON, ICON_BIG, (LPARAM)self->bigIcon->hIcon);
    } else {
      SendMessage(self->windowHandle, WM_SETICON, ICON_BIG, (LPARAM)NULL);
    }
  }
}

static NativeWindowsIcon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  )
{ return self->smallIcon; }

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    NativeWindowsIcon* icon
  )
{
  self->smallIcon = icon;
  if (self->windowHandle) {
    if (self->smallIcon) {
      SendMessage(self->windowHandle, WM_SETICON, ICON_SMALL, (LPARAM)self->smallIcon->hIcon);
    } else {
      SendMessage(self->windowHandle, WM_SETICON, ICON_SMALL, (LPARAM)NULL);
    }
  }
}

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self
  )
{ return self->title; }

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_String* title
  )
{
  if (!title) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->title = title;
  if (self->windowHandle) {
    NativeWindowsWindow_setTitleHelper(thread, self->windowHandle, title);
  }
}

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    NativeWindowsWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ 
  if (!self->windowHandle) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  RECT clientRectangle;
  if (!GetClientRect(self->windowHandle, &clientRectangle)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_StaticAssert(LONG_MAX <= INT32_MAX, "<internal error>");
  *width = clientRectangle.right - clientRectangle.left;
  *height = clientRectangle.bottom - clientRectangle.top;
}

NativeWindowsWindow*
NativeWindowsWindow_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  NativeWindowsWindow* self = Arcadia_allocateObject(thread, _NativeWindowsWindow_getType(thread), 0, &argumentValues[0]);
  return self;
}
