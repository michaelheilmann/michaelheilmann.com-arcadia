// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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
    NativeWindowsWindow* self
  );

static void
NativeWindowsWindow_visit
  (
    NativeWindowsWindow* self
  );

static void
NativeWindowsWindow_setTitleHelper
  (
    HWND windowHandle,
    R_String* title
  );

static void
NativeWindowsWindow_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static const char g_title[] = "Liminality";

static const char g_className[] = "Liminality Window Class";

static R_BooleanValue g_quitRequested = R_BooleanValue_False;

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &NativeWindowsWindow_constructImpl,
  .destruct = &NativeWindowsWindow_destruct,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("NativeWindowsWindow", NativeWindowsWindow, "R.Object", R_Object, &_typeOperations);

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
      g_quitRequested = R_BooleanValue_True;
      return 0;
    } break;
    case WM_KEYUP: {
      if (LOWORD(wParam) == VK_ESCAPE) {
        g_quitRequested = R_BooleanValue_True;
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
    NativeWindowsWindow* self
  )
{
  if (self->title) {
    R_Object_visit(self->title);
  }
  if (self->smallIcon) {
    R_Object_visit(self->smallIcon);
  }
  if (self->bigIcon) {
    R_Object_visit(self->bigIcon);
  }
}

static void
NativeWindowsWindow_setTitleHelper
  (
    HWND windowHandle,
    R_String* title
  )
{
  R_StringBuffer* stringBuffer = R_StringBuffer_create();
  R_Value value;
  R_Value_setObjectReferenceValue(&value, (R_ObjectReferenceValue)title);
  R_StringBuffer_append(stringBuffer, value);
  R_Value_setObjectReferenceValue(&value, (R_ObjectReferenceValue)R_String_create_pn(R_ImmutableByteArray_create("", 1)));
  R_StringBuffer_append(stringBuffer, value);
  SendMessage(windowHandle, WM_SETTEXT, 0, (LPARAM)R_StringBuffer_getBytes(stringBuffer));
}

static void
NativeWindowsWindow_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  NativeWindowsWindow* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _NativeWindowsWindow_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->instanceHandle = NULL;
  _self->windowHandle = NULL;
  _self->title = R_String_create_pn(R_ImmutableByteArray_create(g_title, sizeof(g_title) - 1));
  _self->bigIcon = NULL;
  _self->smallIcon = NULL;
  R_Object_setType(_self, _type);
}

NativeWindowsWindow*
NativeWindowsWindow_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  NativeWindowsWindow* self = R_allocateObject(_NativeWindowsWindow_getType(), 0, &argumentValues[0]);
  R_Value selfValue = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = self };
  NativeWindowsWindow_constructImpl(&selfValue, 0, &argumentValues[0]);
  return self;
}

void
NativeWindowsWindow_open
  (
    NativeWindowsWindow* self
  )
{ 
  if (self->windowHandle) {
    return;
  }

  self->instanceHandle = GetModuleHandleA(NULL);
  if (!self->instanceHandle) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  // Register the window class.
  WNDCLASS wc = { 0 };

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = self->instanceHandle;
  wc.lpszClassName = g_className;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Prevent the busy cursor from showing up.

  if (!RegisterClass(&wc)) {
    self->instanceHandle = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
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
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->instanceHandle);
    self->instanceHandle = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  self->windowDeviceContextHandle = GetDC(self->windowHandle);
  if (!self->windowDeviceContextHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->instanceHandle);
    self->instanceHandle = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    NativeWindowsWindow_setTitleHelper(self->windowHandle, self->title);
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->instanceHandle);
    self->instanceHandle = NULL;
    R_jump();
  }

  ShowWindow(self->windowHandle, SW_SHOW);
}

void
NativeWindowsWindow_close
  (
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

R_BooleanValue
NativeWindowsWindow_getQuitRequested
  (
    NativeWindowsWindow* self
  )
{ return g_quitRequested; }

void
NativeWindowsWindow_setQuitRequested
  (
    NativeWindowsWindow* self,
    R_BooleanValue quitRequested
  )
{ g_quitRequested = quitRequested; }

void
NativeWindowsWindow_update
  (
    NativeWindowsWindow* self
  )
{
  MSG msg = { 0 };
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if (msg.message == WM_QUIT) {
      g_quitRequested = R_BooleanValue_True;
    }
  }
}

void
NativeWindowsWindow_getRequiredBigIconSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  )
{
  *width = GetSystemMetrics(SM_CXICON);
  *height = GetSystemMetrics(SM_CYICON);
}

void
NativeWindowsWindow_getRequiredSmallIconSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  )
{
  *width = GetSystemMetrics(SM_CXSMICON);
  *height = GetSystemMetrics(SM_CYSMICON);
}

NativeWindowsIcon*
NativeWindowsWindow_getBigIcon
  (
    NativeWindowsWindow* self
  )
{ return self->bigIcon; }

void
NativeWindowsWindow_setBigIcon
  (
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

NativeWindowsIcon*
NativeWindowsWindow_getSmallIcon
  (
    NativeWindowsWindow* self
  )
{ return self->smallIcon; }

void
NativeWindowsWindow_setSmallIcon
  (
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

R_String*
NativeWindowsWindow_getTitle
  (
    NativeWindowsWindow* self
  )
{ return self->title; }

void
NativeWindowsWindow_setTitle
  (
    NativeWindowsWindow* self,
    R_String* title
  )
{
  if (!title) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  self->title = title;
  if (self->windowHandle) {
    NativeWindowsWindow_setTitleHelper(self->windowHandle, title);
  }
}

void
NativeWindowsWindow_getCanvasSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  )
{ 
  if (!self->windowHandle) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  RECT clientRectangle;
  if (!GetClientRect(self->windowHandle, &clientRectangle)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  static_assert(LONG_MAX <= INT32_MAX, "<internal error>");
  *width = clientRectangle.right - clientRectangle.left;
  *height = clientRectangle.bottom - clientRectangle.top;
}
