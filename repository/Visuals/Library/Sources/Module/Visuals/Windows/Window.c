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

#include "Module/Visuals/Windows/Window.h"

#include "Module/Visuals/Configuration.h"
#include "Module/Visuals/Windows/WglDeviceInfo.h"
#include <limits.h>

static const char g_title[] = "Liminality";

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );

static void
Arcadia_Visuals_Windows_Window_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
Arcadia_Visuals_Windows_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
Arcadia_Visuals_Windows_Window_setTitleHelper
  (
    Arcadia_Thread* thread,
    HWND windowHandle,
    Arcadia_String* title
  );

static void
Arcadia_Visuals_Windows_Window_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_BooleanValue quitRequested
  );

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static Arcadia_Visuals_Windows_Icon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_Icon* icon
  );

static Arcadia_Visuals_Windows_Icon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_Icon* icon
  );

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_String* title
  );

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
createContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_WglDeviceInfo* deviceInfo
  );

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static const char g_className[] = "Aracadia.Visuals.Windows.Window Window Class";

static Arcadia_BooleanValue g_quitRequested = Arcadia_BooleanValue_False;

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Windows_Window_constructImpl,
  .destruct = &Arcadia_Visuals_Windows_Window_destruct,
  .visit = &Arcadia_Visuals_Windows_Window_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.Window", Arcadia_Visuals_Windows_Window, u8"Arcadia.Visuals.Window", Arcadia_Visuals_Window, &_typeOperations);

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
Arcadia_Visuals_Windows_Window_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (NULL != self->deviceContextHandle) {
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
  }
  if (NULL != self->windowHandle) {
    DeleteObject(self->windowHandle);
    self->windowHandle = NULL;
  }
  if (NULL != self->application) {
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->application);
    self->application = NULL;
  }
}

static void
Arcadia_Visuals_Windows_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (self->application) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->application);
  }
  if (self->title) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->title);
  }
  if (self->smallIcon) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->smallIcon);
  }
  if (self->bigIcon) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->bigIcon);
  }
}

static void
Arcadia_Visuals_Windows_Window_setTitleHelper
  (
    Arcadia_Thread* thread,
    HWND windowHandle,
    Arcadia_String* title
  )
{
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_Value value;
  Arcadia_Value_setObjectReferenceValue(&value, (Arcadia_ObjectReferenceValue)title);
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, value);
  Arcadia_Value_setObjectReferenceValue(&value, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"", 1)));
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, value);
  SendMessage(windowHandle, WM_SETTEXT, 0, (LPARAM)Arcadia_StringBuffer_getBytes(thread, stringBuffer));
}

static void
Arcadia_Visuals_Windows_Window_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Windows_Window* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_Window_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->application = NULL;
  _self->title = NULL;
  _self->classAtom = 0;
  _self->windowHandle = NULL;
  _self->deviceContextHandle = NULL;
  _self->glResourceContextHandle = NULL;
  _self->bigIcon = NULL;
  _self->smallIcon = NULL;

  _self->title = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, g_title, sizeof(g_title) - 1));
  _self->application = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_Visuals_Windows_Application_getType(thread));
  Arcadia_Object_lock(thread, (Arcadia_Object*)_self->application);

  ((Arcadia_Visuals_Window*)_self)->open = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & openImpl;
  ((Arcadia_Visuals_Window*)_self)->close = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & closeImpl;

  ((Arcadia_Visuals_Window*)_self)->getQuitRequested = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getQuitRequestedImpl;
  ((Arcadia_Visuals_Window*)_self)->setQuitRequested = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*,Arcadia_BooleanValue)) & setQuitRequestedImpl;

  ((Arcadia_Visuals_Window*)_self)->update = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) &updateImpl;

  ((Arcadia_Visuals_Window*)_self)->getRequiredBigIconSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredBigIconSizeImpl;
  ((Arcadia_Visuals_Window*)_self)->getRequiredSmallIconSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredSmallIconSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->getBigIcon = (Arcadia_Visuals_Icon *(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getBigIconImpl;
  ((Arcadia_Visuals_Window*)_self)->setBigIcon = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*)) & setBigIconImpl;

  ((Arcadia_Visuals_Window*)_self)->getSmallIcon = (Arcadia_Visuals_Icon *(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getSmallIconImpl;
  ((Arcadia_Visuals_Window*)_self)->setSmallIcon = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*)) & setSmallIconImpl;

  ((Arcadia_Visuals_Window*)_self)->getTitle = (Arcadia_String*(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getTitleImpl;
  ((Arcadia_Visuals_Window*)_self)->setTitle = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_String*)) & setTitleImpl;

  ((Arcadia_Visuals_Window*)_self)->getCanvasSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getCanvasSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->beginRender = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*))&beginRenderImpl;
  ((Arcadia_Visuals_Window*)_self)->endRender = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*))&endRenderImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (self->windowHandle) {
    return;
  }

  if (!self->classAtom) {
    // Register the window class.
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = self->application->instanceHandle;
    wc.lpszClassName = g_className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Prevent the busy cursor from showing up.

    self->classAtom = RegisterClass(&wc);
    if (!self->classAtom) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  if (!self->windowHandle) {
    self->windowHandle =
      CreateWindowEx
        (
          0,                                 // Optional window styles.
          g_className,                       // Window class
          g_title,                           // Window text
          WS_OVERLAPPEDWINDOW,               // Window style
          CW_USEDEFAULT, CW_USEDEFAULT,      // Default position
          CW_USEDEFAULT, CW_USEDEFAULT,      // Default size
          NULL,                              // Parent window
          NULL,                              // Menu
          self->application->instanceHandle, // Instance handle
          NULL                               // Additional application data
        );

    if (!self->windowHandle) {
      UnregisterClass(g_className, self->application->instanceHandle);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }

    if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
      DestroyWindow(self->windowHandle);
      self->windowHandle = NULL;
      UnregisterClass(g_className, self->application->instanceHandle);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  self->deviceContextHandle = GetDC(self->windowHandle);
  if (!self->deviceContextHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->application->instanceHandle);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Visuals_Windows_Window_setTitleHelper(thread, self->windowHandle, self->title);
    Arcadia_Visuals_Windows_WglDeviceInfo* deviceInfo = Arcadia_Visuals_Windows_WglDeviceInfo_create(thread);
    Arcadia_Visuals_Windows_WglDeviceInfo_open(thread, deviceInfo);
    createContext(thread, self, deviceInfo);
    Arcadia_Visuals_Windows_WglDeviceInfo_close(thread, deviceInfo);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->application->instanceHandle);
    Arcadia_Thread_jump(thread);
  }

  ShowWindow(self->windowHandle, SW_SHOW);
}

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (!self->windowHandle) {
    return;
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
    UnregisterClass(g_className, self->application->instanceHandle);
    self->classAtom = 0;
  }
}

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return g_quitRequested; }

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_BooleanValue quitRequested
  )
{ g_quitRequested = quitRequested; }

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
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
    Arcadia_Visuals_Windows_Window* self,
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
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = GetSystemMetrics(SM_CXSMICON);
  *height = GetSystemMetrics(SM_CYSMICON);
}

static Arcadia_Visuals_Windows_Icon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return self->bigIcon; }

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_Icon* icon
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

static Arcadia_Visuals_Windows_Icon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return self->smallIcon; }

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_Icon* icon
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
    Arcadia_Visuals_Windows_Window* self
  )
{ return self->title; }

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_String* title
  )
{
  if (!title) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->title = title;
  if (self->windowHandle) {
    Arcadia_Visuals_Windows_Window_setTitleHelper(thread, self->windowHandle, title);
  }
}

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
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

static int
stringToInteger
  (
    Arcadia_Thread* thread,
    Arcadia_String* source
  )
{
  Arcadia_Integer64Value target = Arcadia_String_toInteger64(thread, source);
  if (target < INT_MIN || target > INT_MAX) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (int)target;
}

static Arcadia_BooleanValue
isConfigurationSupported
  (
    Arcadia_Thread* thread,
    Arcadia_List* configurations,
    Arcadia_Visuals_Configuration* configuration
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)configurations); i < n; ++i) {
    Arcadia_Visuals_Configuration* element = Arcadia_List_getObjectReferenceValueAt(thread, configurations, i);
    Arcadia_Value a, b;
    a = Arcadia_Value_makeObjectReferenceValue(element->opengl.version.major);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->opengl.version.major);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->opengl.version.minor);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->opengl.version.minor);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->colorBuffer.redBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->colorBuffer.redBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->colorBuffer.greenBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->colorBuffer.greenBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->colorBuffer.blueBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->colorBuffer.blueBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->colorBuffer.alphaBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->colorBuffer.alphaBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->depthBuffer.depthBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->depthBuffer.depthBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    return Arcadia_BooleanValue_True;
  }
  return Arcadia_BooleanValue_False;
}

static void
createContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_WglDeviceInfo* deviceInfo
  )
{
  // (1) Get supported configuration.
  Arcadia_List* supportedConfigurations = Arcadia_Visuals_Windows_WglDeviceInfo_getConfigurations(thread, deviceInfo);
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)supportedConfigurations); i < n; ++i) {
    Arcadia_Visuals_Configuration* supportedConfiguration = Arcadia_List_getObjectReferenceValueAt(thread, supportedConfigurations, i);
    Arcadia_StringBuffer_clear(thread, stringBuffer);

    fprintf(stdout, u8"index: %zu\n", i);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"red bits: ", sizeof(u8"red bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.redBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"green bits: ", sizeof(u8"green bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.greenBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"blue bits: ", sizeof(u8"blue bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.blueBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"alpha bits: ", sizeof(u8"alpha bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.alphaBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"depth bits: ", sizeof(u8"depth bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->depthBuffer.depthBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"OpenGL major version: ", sizeof(u8"OpenGL major version: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->opengl.version.major));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"OpenGL minor version: ", sizeof(u8"OpenGL minor version: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->opengl.version.minor));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    fwrite(Arcadia_StringBuffer_getBytes(thread, stringBuffer), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, stringBuffer), stdout);

    fprintf(stdout, u8"\n");
  }
  // (2) Get desired configuration.
  Arcadia_Visuals_Configuration* desiredConfiguration = Arcadia_Visuals_Configuration_create(thread);
  // (3) Check if desired configuration is in supported configurations. If yes, continue. If no, fail.
  if (!isConfigurationSupported(thread, supportedConfigurations, desiredConfiguration)) {
    fprintf(stderr, "%s:%d: visuals configuration not supported\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  const int pixelFormatAttribs[] = {
    WGL_ACCELERATION_ARB, // WGL_ACCELERATION_ARB
    WGL_FULL_ACCELERATION_ARB, // WGL_FULL_ACCELERATION_ARB
    WGL_DEPTH_BITS_ARB, stringToInteger(thread, desiredConfiguration->depthBuffer.depthBits), // WGL_DEPTH_BITS_ARB
    WGL_DRAW_TO_WINDOW_ARB, 1, // WGL_DRAW_TO_WINDOW_ARB
    WGL_RED_BITS_ARB, stringToInteger(thread, desiredConfiguration->colorBuffer.redBits), // WGL_RED_BITS_ARB
    WGL_GREEN_BITS_ARB, stringToInteger(thread, desiredConfiguration->colorBuffer.greenBits), // WGL_GREEN_BITS_ARB
    WGL_BLUE_BITS_ARB, stringToInteger(thread, desiredConfiguration->colorBuffer.blueBits), // WGL_BLUE_BITS_ARB
    WGL_ALPHA_BITS_ARB, stringToInteger(thread, desiredConfiguration->colorBuffer.alphaBits), // WGL_ALPHA_BITS_ARB
    WGL_PIXEL_TYPE_ARB,  WGL_TYPE_RGBA_ARB, // WGL_PIXEL_TYPE_ARB // WGL_TYPE_RGBA_ARB
    WGL_SUPPORT_OPENGL_ARB, 1, // WGL_SUPPORT_OPENGL_ARB
    WGL_COLOR_BITS_ARB,	32, // WGL_COLOR_BITS_ARB
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  int pixelFormatIndex;
  int numberOfPixelFormats;
  deviceInfo->_wglChoosePixelFormat(self->deviceContextHandle, &pixelFormatAttribs[0], NULL, 1, &pixelFormatIndex, &numberOfPixelFormats);
  if (!numberOfPixelFormats) {
    fprintf(stderr, "%s:%d: failed to select pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  PIXELFORMATDESCRIPTOR pixelFormatDescriptors;
  if (!DescribePixelFormat(self->deviceContextHandle, pixelFormatIndex, sizeof(pixelFormatDescriptors), &pixelFormatDescriptors)) {
    fprintf(stderr, "%s:%d: failed to describe pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!SetPixelFormat(self->deviceContextHandle, pixelFormatIndex, &pixelFormatDescriptors)) {
    fprintf(stderr, "%s:%d: failed to set pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  int contextAttribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, stringToInteger(thread, desiredConfiguration->opengl.version.major),
    WGL_CONTEXT_MINOR_VERSION_ARB, stringToInteger(thread, desiredConfiguration->opengl.version.minor),
    WGL_CONTEXT_FLAGS_ARB, 0,
    0
  };
  self->glResourceContextHandle = deviceInfo->_wglCreateContextAttribs(self->deviceContextHandle, NULL, &contextAttribs[0]);
  if (!self->glResourceContextHandle) {
    fprintf(stderr, "%s:%d: failed to create OpenGL/WGL context version %"PRIu8".%"PRIu8"\n", \
                     __FILE__, __LINE__, \
                    stringToInteger(thread, desiredConfiguration->opengl.version.major), \
                    stringToInteger(thread, desiredConfiguration->opengl.version.minor));
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  fprintf(stdout, "%s:%d: OpenGL version %"PRIu8".%"PRIu8" selected\n", \
                  __FILE__, __LINE__, \
                  stringToInteger(thread, desiredConfiguration->opengl.version.major), \
                  stringToInteger(thread, desiredConfiguration->opengl.version.minor));
}

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (!wglMakeCurrent(self->deviceContextHandle, self->glResourceContextHandle)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Integer32Value width, height;
  Arcadia_Visuals_Window_getCanvasSize(thread, (Arcadia_Visuals_Window*)self, &width, &height);
  glViewport(0, 0, width, height);
  glClearColor(193.0f/255.0f, 216.0f/255.0f, 195.0f/255.0f, 255.0f/255.0f);
  glClearDepth(1.f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (self->glResourceContextHandle == wglGetCurrentContext()) {
    if (!SwapBuffers(self->deviceContextHandle)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
}

Arcadia_Visuals_Windows_Window*
Arcadia_Visuals_Windows_Window_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* application,
    Arcadia_Visuals_Windows_DisplayDevice* displayDevice
  )
{
  Arcadia_Value argumentValues[] = {
    application ? Arcadia_Value_makeObjectReferenceValue(application) : Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    displayDevice ? Arcadia_Value_makeObjectReferenceValue(displayDevice) : Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Visuals_Windows_Window* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Windows_Window_getType(thread), 2, &argumentValues[0]);
  return self;
}
