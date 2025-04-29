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

#include "Module/Visuals/Windows/NativeWindow.h"

#include "Module/Visuals/Windows/WglIntermediateWindow.h"
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
Windows_NativeWindow_destruct
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static void
Windows_NativeWindow_visit
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static void
Windows_NativeWindow_setTitleHelper
  (
    Arcadia_Thread* thread,
    HWND windowHandle,
    Arcadia_String* title
  );

static void
Windows_NativeWindow_constructImpl
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
    Windows_NativeWindow* self
  );

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Arcadia_BooleanValue quitRequested
  );

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static Windows_NativeIcon*
getBigIconImpl 
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Windows_NativeIcon* icon
  );

static Windows_NativeIcon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Windows_NativeIcon* icon
  );

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Arcadia_String* title
  );

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
createContext
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Visuals_Window_WglIntermediateWindow* intermediateWindow
  );

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  );

static const char g_className[] = "Aracadia.Visuals.Windows.NativeWindow Window Class";

static Arcadia_BooleanValue g_quitRequested = Arcadia_BooleanValue_False;

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Windows_NativeWindow_constructImpl,
  .destruct = &Windows_NativeWindow_destruct,
  .visit = &Windows_NativeWindow_visit,
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

Arcadia_defineObjectType(u8"Windows.NativeWindow", Windows_NativeWindow, u8"NativeWindow", NativeWindow, &_typeOperations);

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
Windows_NativeWindow_destruct
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
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
  self->instanceHandle = NULL;
}

static void
Windows_NativeWindow_visit
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
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
Windows_NativeWindow_setTitleHelper
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
Windows_NativeWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Windows_NativeWindow* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Windows_NativeWindow_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }

  _self->instanceHandle = NULL;
  _self->classAtom = 0;
  _self->windowHandle = NULL;
  _self->deviceContextHandle = NULL;
  _self->glResourceContextHandle = NULL;
  _self->bigIcon = NULL;
  _self->smallIcon = NULL;
  _self->title = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, g_title, sizeof(g_title) - 1));

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

  ((NativeWindow*)_self)->beginRender = (void(*)(Arcadia_Thread*, NativeWindow*))&beginRenderImpl;
  ((NativeWindow*)_self)->endRender = (void(*)(Arcadia_Thread*,NativeWindow*))&endRenderImpl;

  Arcadia_Object_setType(thread, _self, _type);
}

static void
openImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  )
{ 
  if (self->windowHandle) {
    return;
  }

  if (!self->instanceHandle) {
    self->instanceHandle = GetModuleHandleA(NULL);
    if (!self->instanceHandle) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  if (!self->classAtom) {
    // Register the window class.
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = self->instanceHandle;
    wc.lpszClassName = g_className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Prevent the busy cursor from showing up.

    self->classAtom = RegisterClass(&wc);
    if (!self->classAtom) {
      self->instanceHandle = NULL;
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  if (!self->windowHandle) {
    self->windowHandle =
      CreateWindowEx
        (
          0,                               // Optional window styles.
          g_className,                     // Window class
          g_title,                         // Window text
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
  }

  self->deviceContextHandle = GetDC(self->windowHandle);
  if (!self->deviceContextHandle) {
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
    Windows_NativeWindow_setTitleHelper(thread, self->windowHandle, self->title);
    Visuals_Window_WglIntermediateWindow* intermediateWindow = Visuals_Window_WglIntermediateWindow_create(thread);
    Visuals_Window_WglIntermediateWindow_open(thread, intermediateWindow);
    createContext(thread, self, intermediateWindow);
    Visuals_Window_WglIntermediateWindow_close(thread, intermediateWindow);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
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
    Windows_NativeWindow* self
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
    UnregisterClass(g_className, self->instanceHandle);
    self->classAtom = 0;
  }
  self->instanceHandle = NULL;
}

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  )
{ return g_quitRequested; }

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Arcadia_BooleanValue quitRequested
  )
{ g_quitRequested = quitRequested; }

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
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
    Windows_NativeWindow* self,
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
    Windows_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = GetSystemMetrics(SM_CXSMICON);
  *height = GetSystemMetrics(SM_CYSMICON);
}

static Windows_NativeIcon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  )
{ return self->bigIcon; }

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Windows_NativeIcon* icon
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

static Windows_NativeIcon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  )
{ return self->smallIcon; }

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Windows_NativeIcon* icon
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
    Windows_NativeWindow* self
  )
{ return self->title; }

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Arcadia_String* title
  )
{
  if (!title) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->title = title;
  if (self->windowHandle) {
    Windows_NativeWindow_setTitleHelper(thread, self->windowHandle, title);
  }
}

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
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

static void
createContext
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self,
    Visuals_Window_WglIntermediateWindow* intermediateWindow
  )
{
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
  PIXELFORMATDESCRIPTOR pfd = (PIXELFORMATDESCRIPTOR){ sizeof(pfd), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 8, PFD_MAIN_PLANE,
                                                      24, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int pixelFormat;
  UINT numFormats;
  intermediateWindow->choosePixelFormat(self->deviceContextHandle, &pixelFormatAttribs[0], NULL, 1, &pixelFormat, &numFormats);
  if (!numFormats) {
    fprintf(stderr, "%s:%d: failed to select pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!DescribePixelFormat(self->deviceContextHandle, pixelFormat, sizeof(pfd), &pfd)) {
    fprintf(stderr, "%s:%d: failed to describe pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!SetPixelFormat(self->deviceContextHandle, pixelFormat, &pfd)) {
    fprintf(stderr, "%s:%d: failed to set pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  static int contextAttribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_FLAGS_ARB, 0,
    0
  };
  self->glResourceContextHandle = intermediateWindow->createContextAttribs(self->deviceContextHandle, NULL, &contextAttribs[0]);
  if (!self->glResourceContextHandle) {
    fprintf(stderr, "%s:%d: failed to create wgl context\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  )
{ 
  if (!wglMakeCurrent(self->deviceContextHandle, self->glResourceContextHandle)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Integer32Value width, height;
  NativeWindow_getCanvasSize(thread, (NativeWindow*)self, &width, &height);
  glViewport(0, 0, width, height);
  glClearColor(193.0f/255.0f, 216.0f/255.0f, 195.0f/255.0f, 255.0f/255.0f);
  glClearDepth(1.f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Windows_NativeWindow* self
  )
{ 
  if (self->glResourceContextHandle == wglGetCurrentContext()) {
    if (!SwapBuffers(self->deviceContextHandle)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
}

Windows_NativeWindow*
Windows_NativeWindow_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Windows_NativeWindow* self = Arcadia_allocateObject(thread, _Windows_NativeWindow_getType(thread), 0, &argumentValues[0]);
  return self;
}
