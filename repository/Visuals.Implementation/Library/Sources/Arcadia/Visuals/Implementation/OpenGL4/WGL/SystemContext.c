#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/SystemContext.h"

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
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_constructImpl,
  .destruct = &Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.WGL.SystemContext", Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext,
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
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext* self
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
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow_close(thread, self->window);
    self->window = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  self->window = NULL;
  self->glResourceContextHandle = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext*
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext);
}

void
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext* self
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);

  self->window = Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow_create(thread);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow_open(thread, self->window);
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
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (self->glResourceContextHandle) {
      if (self->glResourceContextHandle == wglGetCurrentContext()) {
        wglMakeCurrent(self->window->deviceContextHandle, NULL);
      }
      wglDeleteContext(self->glResourceContextHandle);
      self->glResourceContextHandle = NULL;
    }
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow_close(thread, self->window);
    self->window = NULL;
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext* self
  )
{
  if (self->glResourceContextHandle) {
    if (self->glResourceContextHandle == wglGetCurrentContext()) {
      wglMakeCurrent(self->window->deviceContextHandle, NULL);
    }
    wglDeleteContext(self->glResourceContextHandle);
    self->glResourceContextHandle = NULL;
  }
  Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow_close(thread, self->window);
  self->window = NULL;
}

static Arcadia_Integer32Value
getIntegerAttribute
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemContext* self,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_SystemWindow* targetWindow,
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

