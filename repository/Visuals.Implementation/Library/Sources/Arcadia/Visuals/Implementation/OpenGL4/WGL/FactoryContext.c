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

#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/FactoryContext.h"

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

static void
Arcadia_Visuals_OpenGL_WGL_FactoryContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_OpenGL_WGL_FactoryContext_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_OpenGL_WGL_FactoryContext_constructImpl,
  .destruct = &Arcadia_Visuals_OpenGL_WGL_FactoryContext_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.WGL.FactoryContext", Arcadia_Visuals_OpenGL_WGL_FactoryContext,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

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

static void
Arcadia_Visuals_OpenGL_WGL_FactoryContext_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* self
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
    Arcadia_Visuals_OpenGL_WGL_FactoryWindow_close(thread, self->window);
    self->window = NULL;
  }
}

static void
Arcadia_Visuals_OpenGL_WGL_FactoryContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_OpenGL_WGL_FactoryContext* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_OpenGL_WGL_FactoryContext_getType(thread);
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
  _self->window = NULL;
  _self->glResourceContextHandle = NULL;
  _self->_wglChoosePixelFormat = NULL;
  _self->_wglCreateContextAttribs = NULL;
  _self->_wglGetExtensionsString = NULL;
  _self->_wglGetPixelFormatAttribfv = NULL;
  _self->_wglGetPixelFormatAttribiv = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

Arcadia_Visuals_OpenGL_WGL_FactoryContext*
Arcadia_Visuals_OpenGL_WGL_FactoryContext_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_OpenGL_WGL_FactoryContext);
}

void
Arcadia_Visuals_OpenGL_WGL_FactoryContext_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* self
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);

  self->window = Arcadia_Visuals_OpenGL_WGL_FactoryWindow_create(thread);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Visuals_OpenGL_WGL_FactoryWindow_open(thread, self->window);
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
    Arcadia_Visuals_OpenGL_WGL_FactoryWindow_close(thread, self->window);
    self->window = NULL;
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Visuals_OpenGL_WGL_FactoryContext_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* self
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
  Arcadia_Visuals_OpenGL_WGL_FactoryWindow_close(thread, self->window);
  self->window = NULL;
}

static Arcadia_Integer32Value
getIntegerAttribute
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* self,
    Arcadia_Visuals_OpenGL_WGL_FactoryWindow* targetWindow,
    int pixelFormatIndex,
    int attributeKey
  )
{
  int attributeValue;
  if (!self->_wglGetPixelFormatAttribiv(targetWindow->deviceContextHandle, pixelFormatIndex, 0, 1, &attributeKey, &attributeValue)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (attributeValue < Arcadia_Integer32Value_Minimum || attributeValue > Arcadia_Integer32Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  return attributeValue;
}

static void add(Arcadia_Thread* thread, Arcadia_List* configurations, Arcadia_Visuals_Configuration* configuration) {
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
    // Already in the list.
    return;
  }
  // Not in the list yet. Add.
  Arcadia_List_insertBackObjectReferenceValue(thread, configurations, (Arcadia_ObjectReferenceValue)configuration);
}

Arcadia_List*
Arcadia_Visuals_OpenGL_WGL_FactoryContext_getConfigurations
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_OpenGL_WGL_FactoryContext* self
  )
{
  Arcadia_List* configurations = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Visuals_OpenGL_WGL_FactoryWindow* window = Arcadia_Visuals_OpenGL_WGL_FactoryWindow_create(thread);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    // (1) iterate over the versions.
    for (Arcadia_Integer32Value majorVersion = 1; majorVersion < 5; majorVersion++) {
      for (Arcadia_Integer32Value minorVersion = 0; minorVersion < 9; minorVersion++) {
        Arcadia_Visuals_OpenGL_WGL_FactoryWindow_close(thread, window);
        Arcadia_Visuals_OpenGL_WGL_FactoryWindow_open(thread, window);
        // (1.1) Get the number of pixel formats.
        Arcadia_Integer32Value numberOfFormats = getIntegerAttribute(thread, self, window, 1, WGL_NUMBER_PIXEL_FORMATS_ARB);
        // (1.2) Iterate over the formats.
        for (Arcadia_Integer32Value i = 1, n = numberOfFormats; i < n; ++i) {
          Arcadia_Integer32Value supportOpenGl = getIntegerAttribute(thread, self, window, i, WGL_SUPPORT_OPENGL_ARB);
          if (supportOpenGl != 1) {
            continue;
          }
          Arcadia_Integer32Value pixelType = getIntegerAttribute(thread, self, window, i, WGL_PIXEL_TYPE_ARB);
          if (pixelType != WGL_TYPE_RGBA_ARB) {
            continue;
          }
          Arcadia_Integer32Value redBits = getIntegerAttribute(thread, self, window, i, WGL_RED_BITS_ARB);
          if (redBits < 8) {
            continue;
          }
          Arcadia_Integer32Value greenBits = getIntegerAttribute(thread, self, window, i, WGL_GREEN_BITS_ARB);
          if (greenBits < 8) {
            continue;
          }
          Arcadia_Integer32Value blueBits = getIntegerAttribute(thread, self, window, i, WGL_BLUE_BITS_ARB);
          if (blueBits < 8) {
            continue;
          }
          Arcadia_Integer32Value alphaBits = getIntegerAttribute(thread, self, window, i, WGL_ALPHA_BITS_ARB);
          if (alphaBits < 8) {
            continue;
          }
          Arcadia_Integer32Value depthBits = getIntegerAttribute(thread, self, window, i, WGL_DEPTH_BITS_ARB);
          if (depthBits < 8 || depthBits > Arcadia_Integer32Value_Maximum) {
            continue;
          }
          PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
          if (!DescribePixelFormat(window->deviceContextHandle, i, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor)) {
            continue;
          }
          if (!SetPixelFormat(window->deviceContextHandle, i, &pixelFormatDescriptor)) {
            continue;
          }
          int contextAttributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
            WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
            WGL_CONTEXT_FLAGS_ARB, 0,
            0
          };
          HGLRC glrc = self->_wglCreateContextAttribs(window->deviceContextHandle, NULL, &contextAttributes[0]);
          if (!glrc) {
            continue;
          }
          wglDeleteContext(glrc);
          glrc = NULL;

          Arcadia_Visuals_Configuration* configuration = Arcadia_Visuals_Configuration_create(thread);
          configuration->opengl.version.major = Arcadia_String_createFromInteger32(thread, majorVersion);
          configuration->opengl.version.minor = Arcadia_String_createFromInteger32(thread, minorVersion);
          configuration->colorBuffer.redBits = Arcadia_String_createFromInteger32(thread, redBits);
          configuration->colorBuffer.greenBits = Arcadia_String_createFromInteger32(thread, greenBits);
          configuration->colorBuffer.blueBits = Arcadia_String_createFromInteger32(thread, blueBits);
          configuration->colorBuffer.alphaBits = Arcadia_String_createFromInteger32(thread, alphaBits);
          configuration->depthBuffer.depthBits = Arcadia_String_createFromInteger32(thread, depthBits);
          add(thread, configurations, configuration);
        }
      }
    }
    Arcadia_Visuals_OpenGL_WGL_FactoryWindow_close(thread, window);
    Arcadia_Thread_popJumpTarget(thread);
    return configurations;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Visuals_OpenGL_WGL_FactoryWindow_open(thread, window);
    Arcadia_Thread_jump(thread);
  }
}
