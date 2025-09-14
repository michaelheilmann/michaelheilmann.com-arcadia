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

#include "Arcadia/Visuals/Implementation/Windows/Window.h"

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/Windows/_WindowText.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/FactoryContext.h"
#include <limits.h>

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
getFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_BooleanValue fullscreen
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
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* factoryContext
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

static void
getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  );

static void
setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  );

static void
getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Windows_Window_constructImpl,
  .destruct = &Arcadia_Visuals_Windows_Window_destruct,
  .visit = &Arcadia_Visuals_Windows_Window_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.Window", Arcadia_Visuals_Windows_Window,
                         u8"Arcadia.Visuals.Window", Arcadia_Visuals_Window,
                         &_typeOperations);

static Arcadia_BooleanValue
filter
  (
    Arcadia_Thread* thread,
    Arcadia_Value context,
    Arcadia_Value value
  )
{
  Arcadia_Visuals_Window* window = (Arcadia_Visuals_Window*)Arcadia_Value_getObjectReferenceValue(&context);
  Arcadia_WeakReference* weakReferenceElement = (Arcadia_WeakReference*)Arcadia_Value_getObjectReferenceValue(&value);
  Arcadia_Value valueElement = Arcadia_WeakReference_getValue(thread, weakReferenceElement);
  if (Arcadia_Value_isObjectReferenceValue(&valueElement)) {
    Arcadia_Visuals_Window* windowElement = (Arcadia_Visuals_Window*)Arcadia_Value_getObjectReferenceValue(&valueElement);
    if (window == windowElement) {
      return Arcadia_BooleanValue_False;
    }
  } else {
    return Arcadia_BooleanValue_False;
  }
  return Arcadia_BooleanValue_True;
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
    SetWindowLongPtr(self->windowHandle, GWLP_USERDATA, (LONG_PTR)NULL);
    DeleteObject(self->windowHandle);
    self->windowHandle = NULL;
  }
  Arcadia_List_filter(thread, ((Arcadia_Visuals_System*)self->system)->windows, Arcadia_Value_makeObjectReferenceValue(self), &filter);
  if (NULL != self->system) {
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->system);
    self->system = NULL;
  }
}

static void
Arcadia_Visuals_Windows_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (self->system) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->system);
  }
  if (self->smallIcon) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->smallIcon);
  }
  if (self->bigIcon) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->bigIcon);
  }
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
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (2 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->system = NULL;
  _self->windowHandle = NULL;
  _self->deviceContextHandle = NULL;
  _self->glResourceContextHandle = NULL;
  _self->bigIcon = NULL;
  _self->smallIcon = NULL;

  _self->system = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Windows_System_getType(thread));
  Arcadia_Object_lock(thread, (Arcadia_Object*)_self->system);

  ((Arcadia_Visuals_Window*)_self)->open = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & openImpl;
  ((Arcadia_Visuals_Window*)_self)->close = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & closeImpl;

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

  ((Arcadia_Visuals_Window*)_self)->getPosition = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getPositionImpl;
  ((Arcadia_Visuals_Window*)_self)->setPosition = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & setPositionImpl;

  ((Arcadia_Visuals_Window*)_self)->getSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getSizeImpl;
  ((Arcadia_Visuals_Window*)_self)->setSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & setSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->getFullscreen = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getFullscreenImpl;
  ((Arcadia_Visuals_Window*)_self)->setFullscreen = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_BooleanValue)) & setFullscreenImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
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

  if (!self->windowHandle) {
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    DWORD dwExStyle = 0;
    self->windowHandle =
      CreateWindowEx
        (
          dwExStyle,                     // extended window style
          self->system->className,       // window class
          u8"Arcadia Engine Window",     // window text
          dwStyle,                       // window style
          CW_USEDEFAULT,                 // left
          CW_USEDEFAULT,                 // top
          CW_USEDEFAULT,                 // width
          CW_USEDEFAULT,                 // height
          NULL,                          // parent window
          NULL,                          // menu
          self->system->instanceHandle,  // instance handle
          NULL                           // additional application data
        );

    if (!self->windowHandle) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    SetWindowLongPtr(self->windowHandle, GWLP_USERDATA, (LONG_PTR)self);
    MoveWindow(self->windowHandle, ((Arcadia_Visuals_Window*)self)->bounds.left,
                                   ((Arcadia_Visuals_Window*)self)->bounds.top,
                                   ((Arcadia_Visuals_Window*)self)->bounds.width,
                                   ((Arcadia_Visuals_Window*)self)->bounds.height,
                                   TRUE);
  }

  self->deviceContextHandle = GetDC(self->windowHandle);
  if (!self->deviceContextHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Windows_setWindowText(thread, self->windowHandle, ((Arcadia_Visuals_Window*)self)->title);
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* wglFactoryContext = Arcadia_Visuals_OpenGL_WGL_FactoryContext_create(thread);
    Arcadia_Visuals_OpenGL_WGL_FactoryContext_open(thread, wglFactoryContext);
    createContext(thread, self, wglFactoryContext);
    Arcadia_Visuals_OpenGL_WGL_FactoryContext_close(thread, wglFactoryContext);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
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
    SetWindowLongPtr(self->windowHandle, GWLP_USERDATA, (LONG_PTR)NULL);
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
  }
}

static Arcadia_BooleanValue
getFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return ((Arcadia_Visuals_Window*)self)->fullscreen; }

static void
setFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_BooleanValue fullscreen
  )
{
  if (self->windowHandle) {
    if (((Arcadia_Visuals_Window*)self)->fullscreen != fullscreen) {
      DWORD dwStyle = 0;
      if (fullscreen) {
        dwStyle |= WS_POPUP;
      } else {
        dwStyle |= WS_OVERLAPPEDWINDOW;
      }
      SetWindowLongPtr(self->windowHandle, GWL_STYLE, dwStyle);
      if (!SetWindowPos(self->windowHandle,
                        HWND_TOPMOST,
                        ((Arcadia_Visuals_Window*)self)->bounds.left,
                        ((Arcadia_Visuals_Window*)self)->bounds.top,
                        ((Arcadia_Visuals_Window*)self)->bounds.width,
                        ((Arcadia_Visuals_Window*)self)->bounds.height,
                        SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_DRAWFRAME | SWP_SHOWWINDOW)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      ((Arcadia_Visuals_Window*)self)->fullscreen = fullscreen;
    }
  } else {
    ((Arcadia_Visuals_Window*)self)->fullscreen = fullscreen;
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
{ return ((Arcadia_Visuals_Window*)self)->title; }

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
  ((Arcadia_Visuals_Window*)self)->title = title;
  if (self->windowHandle) {
    Windows_setWindowText(thread, self->windowHandle, title);
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
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* wglFactoryContext
  )
{
  // (1) Get supported configuration.
  Arcadia_List* supportedConfigurations = Arcadia_Visuals_OpenGL_WGL_FactoryContext_getConfigurations(thread, wglFactoryContext);
  Arcadia_StringBuffer* logMessage = Arcadia_StringBuffer_create(thread);
  Arcadia_Log* log = Arcadia_Log_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)supportedConfigurations); i < n; ++i) {
    Arcadia_Visuals_Configuration* supportedConfiguration = Arcadia_List_getObjectReferenceValueAt(thread, supportedConfigurations, i);
    Arcadia_StringBuffer_clear(thread, logMessage);

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"index: ");
    Arcadia_StringBuffer_insertBackString(thread, logMessage, Arcadia_String_createFromSize(thread, i));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"red bits: ");
    Arcadia_StringBuffer_insertBack(thread, logMessage, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.redBits));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"green bits: ");
    Arcadia_StringBuffer_insertBack(thread, logMessage, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.greenBits));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"blue bits: ");
    Arcadia_StringBuffer_insertBack(thread, logMessage, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.blueBits));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"alpha bits: ");
    Arcadia_StringBuffer_insertBack(thread, logMessage, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.alphaBits));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"depth bits: ");
    Arcadia_StringBuffer_insertBack(thread, logMessage, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->depthBuffer.depthBits));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"OpenGL major version: ");
    Arcadia_StringBuffer_insertBack(thread, logMessage, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->opengl.version.major));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"OpenGL minor version: ");
    Arcadia_StringBuffer_insertBack(thread, logMessage, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->opengl.version.minor));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_Log_info(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(logMessage)));   
  }
  // (2) Get desired configuration.
  Arcadia_Visuals_Configuration* desiredConfiguration = Arcadia_Visuals_Configuration_create(thread);
  // (3) Check if desired configuration is in supported configurations. If yes, continue. If no, fail.
  if (!isConfigurationSupported(thread, supportedConfigurations, desiredConfiguration)) {
    Arcadia_StringBuffer_clear(thread, logMessage);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, __FILE__);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8":");
    Arcadia_StringBuffer_insertBackString(thread, logMessage, Arcadia_String_createFromCxxInt(thread, __LINE__));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8": visuals configuration not supported\n");

    Arcadia_Log_error(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(logMessage)));

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  const int pixelFormatAttribs[] = {
    WGL_ACCELERATION_ARB, // WGL_ACCELERATION_ARB
    WGL_FULL_ACCELERATION_ARB, // WGL_FULL_ACCELERATION_ARB
    WGL_DEPTH_BITS_ARB, Arcadia_String_toCxxInt(thread, desiredConfiguration->depthBuffer.depthBits), // WGL_DEPTH_BITS_ARB
    WGL_DRAW_TO_WINDOW_ARB, 1, // WGL_DRAW_TO_WINDOW_ARB
    WGL_RED_BITS_ARB, Arcadia_String_toCxxInt(thread, desiredConfiguration->colorBuffer.redBits), // WGL_RED_BITS_ARB
    WGL_GREEN_BITS_ARB, Arcadia_String_toCxxInt(thread, desiredConfiguration->colorBuffer.greenBits), // WGL_GREEN_BITS_ARB
    WGL_BLUE_BITS_ARB, Arcadia_String_toCxxInt(thread, desiredConfiguration->colorBuffer.blueBits), // WGL_BLUE_BITS_ARB
    WGL_ALPHA_BITS_ARB, Arcadia_String_toCxxInt(thread, desiredConfiguration->colorBuffer.alphaBits), // WGL_ALPHA_BITS_ARB
    WGL_PIXEL_TYPE_ARB,  WGL_TYPE_RGBA_ARB, // WGL_PIXEL_TYPE_ARB // WGL_TYPE_RGBA_ARB
    WGL_SUPPORT_OPENGL_ARB, 1, // WGL_SUPPORT_OPENGL_ARB
    WGL_COLOR_BITS_ARB,	32, // WGL_COLOR_BITS_ARB
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  int pixelFormatIndex;
  int numberOfPixelFormats;
  wglFactoryContext->_wglChoosePixelFormat(self->deviceContextHandle, &pixelFormatAttribs[0], NULL, 1, &pixelFormatIndex, &numberOfPixelFormats);
  if (!numberOfPixelFormats) {
    Arcadia_StringBuffer_clear(thread, logMessage);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, __FILE__);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8":");
    Arcadia_StringBuffer_insertBackString(thread, logMessage, Arcadia_String_createFromCxxInt(thread, __LINE__));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8": failed to select pixel format\n");

    Arcadia_Log_error(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(logMessage)));

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  PIXELFORMATDESCRIPTOR pixelFormatDescriptors;
  if (!DescribePixelFormat(self->deviceContextHandle, pixelFormatIndex, sizeof(pixelFormatDescriptors), &pixelFormatDescriptors)) {
    Arcadia_StringBuffer_clear(thread, logMessage);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, __FILE__);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8":");
    Arcadia_StringBuffer_insertBackString(thread, logMessage, Arcadia_String_createFromCxxInt(thread, __LINE__));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8": failed to describe pixel format\n");

    Arcadia_Log_error(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(logMessage)));

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!SetPixelFormat(self->deviceContextHandle, pixelFormatIndex, &pixelFormatDescriptors)) {
    Arcadia_StringBuffer_clear(thread, logMessage);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, __FILE__);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8":");
    Arcadia_StringBuffer_insertBackString(thread, logMessage, Arcadia_String_createFromCxxInt(thread, __LINE__));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8": failed to set pixel format\n");

    Arcadia_Log_error(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(logMessage)));

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  int contextAttribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, Arcadia_String_toCxxInt(thread, desiredConfiguration->opengl.version.major),
    WGL_CONTEXT_MINOR_VERSION_ARB, Arcadia_String_toCxxInt(thread, desiredConfiguration->opengl.version.minor),
    WGL_CONTEXT_FLAGS_ARB, 0,
    0
  };
  self->glResourceContextHandle = wglFactoryContext->_wglCreateContextAttribs(self->deviceContextHandle, NULL, &contextAttribs[0]);
  if (!self->glResourceContextHandle) {
    Arcadia_StringBuffer_clear(thread, logMessage);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, __FILE__);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8":");
    Arcadia_StringBuffer_insertBackString(thread, logMessage, Arcadia_String_createFromCxxInt(thread, __LINE__));
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8": failed to create OpenGL/WGL context for OpenGL version ");
    Arcadia_StringBuffer_insertBackString(thread, logMessage, desiredConfiguration->opengl.version.major);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8".");
    Arcadia_StringBuffer_insertBackString(thread, logMessage, desiredConfiguration->opengl.version.minor);
    Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

    Arcadia_Log_error(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(logMessage)));

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_StringBuffer_clear(thread, logMessage);
  Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, __FILE__);
  Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8":");
  Arcadia_StringBuffer_insertBackString(thread, logMessage, Arcadia_String_createFromCxxInt(thread, __LINE__));
  Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8": created OpenGL/WGL context for OpenGL version \n");
  Arcadia_StringBuffer_insertBackString(thread, logMessage, desiredConfiguration->opengl.version.major);
  Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8".");
  Arcadia_StringBuffer_insertBackString(thread, logMessage, desiredConfiguration->opengl.version.minor);
  Arcadia_StringBuffer_insertBackCxxString(thread, logMessage, u8"\n");

  Arcadia_Log_info(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(logMessage)));
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

static void
getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  )
{
  *left = ((Arcadia_Visuals_Window*)self)->bounds.top;
  *top = ((Arcadia_Visuals_Window*)self)->bounds.left;
}

static void
setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  )
{
  ((Arcadia_Visuals_Window*)self)->bounds.left = left;
  ((Arcadia_Visuals_Window*)self)->bounds.top = top;
  if (self->windowHandle) {
    MoveWindow(self->windowHandle, ((Arcadia_Visuals_Window*)self)->bounds.left,
                                   ((Arcadia_Visuals_Window*)self)->bounds.top,
                                   ((Arcadia_Visuals_Window*)self)->bounds.width,
                                   ((Arcadia_Visuals_Window*)self)->bounds.height,
                                   FALSE);
  }
}

static void
getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = ((Arcadia_Visuals_Window*)self)->bounds.width;
  *height = ((Arcadia_Visuals_Window*)self)->bounds.height;
}

static void
setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  ((Arcadia_Visuals_Window*)self)->bounds.width = width;
  ((Arcadia_Visuals_Window*)self)->bounds.height = height;
  if (self->windowHandle) {
    MoveWindow(self->windowHandle, ((Arcadia_Visuals_Window*)self)->bounds.left,
                                    ((Arcadia_Visuals_Window*)self)->bounds.top,
                                    ((Arcadia_Visuals_Window*)self)->bounds.width,
                                    ((Arcadia_Visuals_Window*)self)->bounds.height,
                                    FALSE);
  }
}

Arcadia_Visuals_Windows_Window*
Arcadia_Visuals_Windows_Window_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_System* system,
    Arcadia_Visuals_Windows_DisplayDevice* displayDevice
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (system) { Arcadia_ValueStack_pushObjectReferenceValue(thread, system); } else { Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);  }
  if (displayDevice) { Arcadia_ValueStack_pushObjectReferenceValue(thread, displayDevice); } else { Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void); }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Windows_Window);
}
