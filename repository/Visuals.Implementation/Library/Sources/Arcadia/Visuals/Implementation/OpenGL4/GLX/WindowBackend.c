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

#include "Arcadia/Visuals/Implementation/OpenGL4/GLX/WindowBackend.h"

#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <limits.h>

static Arcadia_BooleanValue
isConfigurationSupported
  (
    Arcadia_Thread* thread,
    Arcadia_List* configurations,
    Arcadia_Visuals_Configuration* configuration
  );

static int
errorHandler
  (
    Display *display,
    XErrorEvent *event
  );

static void
openVisual
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Visuals_Linux_GlxDeviceInfo* deviceInfo
  );

static void
openContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Visuals_Linux_GlxDeviceInfo* deviceInfo
  );

static void
applyIcons
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_constructImpl
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
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static Arcadia_BooleanValue
getFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
setFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_BooleanValue fullscreen
  );

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static Arcadia_Visuals_Linux_Icon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Visuals_Linux_Icon* icon
  );

static Arcadia_Visuals_Linux_Icon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Visuals_Linux_Icon* icon
  );

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_String* title
  );

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  );
  
static void
getBorderInfo
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  );

static void
getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  );

static void
setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  );

static void
getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static bool g_error = false;

static int (*g_oldErrorHandler)(Display*, XErrorEvent*) = NULL;

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_constructImpl,
  .destruct = &Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_destruct,
  .visit = &Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_visit,
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

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.GLX.WindowBackend", Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend,
                         u8"Arcadia.Visuals.WindowBackend", Arcadia_Visuals_WindowBackend,
                         &_typeOperations);

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

static int
errorHandler
  (
    Display *display,
    XErrorEvent *event
  )
{
  g_error = true;
  return 0;
}

static void
openVisual
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Visuals_Linux_GlxDeviceInfo* deviceInfo
  )
{
  if (!self) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (self->visualInfo) {
    return;
  }

  Arcadia_Visuals_Configuration* desiredConfiguration = Arcadia_Visuals_Configuration_create(thread);
  Arcadia_List* availableConfigurations = Arcadia_Visuals_Linux_GlxDeviceInfo_getGlxConfigurations(thread, deviceInfo);

  if (!isConfigurationSupported(thread, availableConfigurations, desiredConfiguration)) {
    fprintf(stderr, "%s:%d: unsupported configuration\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // Get a matching frame buffer configuration.
  int visualsAttributes[] = {
    GLX_X_RENDERABLE     , True,
    GLX_DRAWABLE_TYPE    , GLX_WINDOW_BIT,
    GLX_RENDER_TYPE      , GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE    , GLX_TRUE_COLOR,
    GLX_RED_SIZE         , Arcadia_String_toCxxInt(thread, desiredConfiguration->colorBuffer.redBits),
    GLX_GREEN_SIZE       , Arcadia_String_toCxxInt(thread, desiredConfiguration->colorBuffer.greenBits),
    GLX_BLUE_SIZE        , Arcadia_String_toCxxInt(thread, desiredConfiguration->colorBuffer.blueBits),
    GLX_ALPHA_SIZE       , Arcadia_String_toCxxInt(thread, desiredConfiguration->colorBuffer.alphaBits),
    GLX_DEPTH_SIZE       , Arcadia_String_toCxxInt(thread, desiredConfiguration->depthBuffer.depthBits),
    //GLX_STENCIL_SIZE     , 8,
    GLX_DOUBLEBUFFER     , True,
    //GLX_SAMPLE_BUFFERS , 1,
    //GLX_SAMPLES        , 4,
    None
  };

  int numberOfFrameBufferConfigurations;
  GLXFBConfig* frameBufferConfigurations =
    glXChooseFBConfig
      (
        self->system->display,
        DefaultScreen(self->system->display),
        visualsAttributes,
        &numberOfFrameBufferConfigurations
      );
  if (!frameBufferConfigurations) {
    fprintf(stderr, "%s:%d: unable to obtain matching framebuffer configuration\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // Usually, multiple frame buffer configurations fulfill the requirements imposed by an Arcadia configuration.
  // We use a heuristic to select a good fame buffer configuration.
  int bestFrameBufferConfiguration = -1,
      worstFrameBufferConfiguration = -1,
      bestNumberOfSamples = -1,
      worstNumberOfSamples = 999;

  int i;
  for (i = 0; i < numberOfFrameBufferConfigurations; ++i) {
    XVisualInfo *visualInfo =
      glXGetVisualFromFBConfig
        (
          self->system->display,
          frameBufferConfigurations[i]
        );
    if (visualInfo) {
      int sampleBuffers, samples;
      glXGetFBConfigAttrib(self->system->display, frameBufferConfigurations[i], GLX_SAMPLE_BUFFERS, &sampleBuffers );
      glXGetFBConfigAttrib(self->system->display, frameBufferConfigurations[i], GLX_SAMPLES       , &samples  );

      if (bestFrameBufferConfiguration < 0 || sampleBuffers && samples > bestNumberOfSamples )
        bestFrameBufferConfiguration = i, bestNumberOfSamples = samples;
      if (worstFrameBufferConfiguration < 0 || !sampleBuffers || samples < worstNumberOfSamples )
        worstFrameBufferConfiguration = i, worstNumberOfSamples = samples;
      XFree(visualInfo);
    }
  }
  self->frameBufferConfiguration = NULL;
  self->visualInfo = NULL;
  if (bestFrameBufferConfiguration >= 0) {
    self->frameBufferConfiguration = malloc(sizeof(GLXFBConfig));
    if (!self->frameBufferConfiguration) {
      XFree(frameBufferConfigurations);
      frameBufferConfigurations = NULL;

      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    *self->frameBufferConfiguration = frameBufferConfigurations[bestFrameBufferConfiguration];
    self->visualInfo = glXGetVisualFromFBConfig(self->system->display, *self->frameBufferConfiguration );
    if (!self->visualInfo) {
      free(self->frameBufferConfiguration);
      self->frameBufferConfiguration = NULL;
      XFree(frameBufferConfigurations);
      frameBufferConfigurations = NULL;
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    XFree(frameBufferConfigurations);
    frameBufferConfigurations = NULL;
  } else {
    XFree(frameBufferConfigurations);
    frameBufferConfigurations = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
openContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Visuals_Linux_GlxDeviceInfo* deviceInfo
  )
{
  g_error = false;

  // NOTE: It is not necessary to create or make current to a context before calling glXGetProcAddressARB.
  PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB =
    (PFNGLXCREATECONTEXTATTRIBSARBPROC)
    glXGetProcAddressARB
      (
        (const GLubyte *)"glXCreateContextAttribsARB"
      );

  // Check for the GLX_ARB_create_context extension string and the function.
  // If either is not present, raise an error.
  if (!Arcadia_Visuals_Linux_GlxDeviceInfo_isGlxExtensionSupported(thread, deviceInfo, "GLX_ARB_create_context") || !glXCreateContextAttribsARB) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  int contextAttributes[] = {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
    GLX_CONTEXT_MINOR_VERSION_ARB, 0,
    //GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    None
  };
  // Replace the original error handler with our error handler.
  g_oldErrorHandler = XSetErrorHandler(&errorHandler);
  self->context = glXCreateContextAttribsARB(self->system->display,
                                             *self->frameBufferConfiguration,
                                             0,
                                             True,
                                             contextAttributes);
  if (NULL == self->context) {
    // Restore the original error handler.
    XSetErrorHandler(g_oldErrorHandler);
    g_oldErrorHandler = NULL;

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  // Verifying that context is a direct context
  if (!glXIsDirect(self->system->display, self->context)) {
    glXDestroyContext(self->system->display, self->context);
    self->context = NULL;

    // Restore the original error handler.
    XSetErrorHandler(g_oldErrorHandler);
    g_oldErrorHandler = NULL;

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  glXMakeCurrent(self->system->display, self->window, self->context);

  XSync(self->system->display, False);
  if (g_error) {
    glXDestroyContext(self->system->display, self->context);
    self->context = NULL;

    // Restore the original error handler.
    XSetErrorHandler(g_oldErrorHandler);
    g_oldErrorHandler = NULL;

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // Restore the original error handler.
  XSetErrorHandler(g_oldErrorHandler);
  g_oldErrorHandler = NULL;
}

static void
applyIcons
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (!self->window) {
    return;
  }
  if (!self->smallIcon && !self->bigIcon) {
    XDeleteProperty(self->system->display, self->window, self->system->_NET_WM_ICON);
  } else {
    size_t numberOfElements = 0;
    Arcadia_Visuals_Linux_Icon* icons[] = {
      self->smallIcon,
      self->bigIcon,
    };
    Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
    for (size_t i = 0; i < 2; ++i) {
      Arcadia_Visuals_Linux_Icon* icon = icons[i];
      if (icon) {
        numberOfElements += icon->width * icon->height + 2;
        Arcadia_ByteBuffer_append_pn(thread, byteBuffer, icon->bytes, icon->numberOfBytes);
      }
    }
    void const* p = Arcadia_ByteBuffer_getBytes(thread, byteBuffer);
    int n = Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer);
    XChangeProperty(self->system->display,
                    self->window,
                    self->system->_NET_WM_ICON,
                    XA_CARDINAL,
                    32,
                    PropModeReplace,
                    Arcadia_ByteBuffer_getBytes(thread, byteBuffer),
                    numberOfElements);
  }
  // @todo Call XSync instead.
  XFlush(self->system->display);
}

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
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (self->context) {
    glXDestroyContext(self->system->display, self->context);
    self->context = NULL;
  }

  if (self->window) {
    XDestroyWindow(self->system->display, self->window);
    self->window = None;
  }

  if (self->colormap) {
    XFreeColormap(self->system->display, self->colormap);
    self->colormap = None;
  }
  if (self->visualInfo) {
    XFree(self->visualInfo);
    self->visualInfo = NULL;
  }
  if (self->frameBufferConfiguration) {
    free(self->frameBufferConfiguration);
    self->frameBufferConfiguration = NULL;
  }
  if (self->screen) {
  #if 0
    // Do NOT call XFree on self->screen (unlike some examples suggest).
    XFree(self->screen);
  #endif
    self->screen = NULL;
  }
  Arcadia_List_filter(thread, ((Arcadia_Visuals_System*)self->system)->windows, Arcadia_Value_makeObjectReferenceValue(self), &filter);
  if (self->system) {
    Arcadia_Object_unlock(thread, self->system);
    self->system = NULL;
  }
  fprintf(stdout, "%s:%d: GLX window destroyed\n", __FILE__, __LINE__);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (self->system) {
    Arcadia_Object_visit(thread, self->system);
  }
  if (self->bigIcon) {
    Arcadia_Object_visit(thread, self->bigIcon);
  }
  if (self->smallIcon) {
    Arcadia_Object_visit(thread, self->smallIcon);
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  _self->system = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_OpenGL4_GLX_System_getType(thread));
  Arcadia_Object_lock(thread, _self->system);
  _self->smallIcon = NULL;
  _self->bigIcon = NULL;
  _self->screen = NULL;
  _self->frameBufferConfiguration = NULL;
  _self->visualInfo = NULL;
  _self->colormap = None;
  _self->window = None;

  ((Arcadia_Visuals_Window*)_self)->open = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & openImpl;
  ((Arcadia_Visuals_Window*)_self)->close = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & closeImpl;

  ((Arcadia_Visuals_Window*)_self)->getRequiredBigIconSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredBigIconSizeImpl;
  ((Arcadia_Visuals_Window*)_self)->getRequiredSmallIconSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredSmallIconSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->getBigIcon = (Arcadia_Visuals_Icon*(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getBigIconImpl;
  ((Arcadia_Visuals_Window*)_self)->setBigIcon = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*)) & setBigIconImpl;

  ((Arcadia_Visuals_Window*)_self)->getSmallIcon = (Arcadia_Visuals_Icon*(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getSmallIconImpl;
  ((Arcadia_Visuals_Window*)_self)->setSmallIcon = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*)) & setSmallIconImpl;

  ((Arcadia_Visuals_Window*)_self)->getTitle = (Arcadia_String*(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getTitleImpl;
  ((Arcadia_Visuals_Window*)_self)->setTitle = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_String*)) & setTitleImpl;

  ((Arcadia_Visuals_Window*)_self)->getCanvasSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getCanvasSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->beginRender = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*))&beginRenderImpl;
  ((Arcadia_Visuals_Window*)_self)->endRender = (void(*)(Arcadia_Thread*,Arcadia_Visuals_Window*))&endRenderImpl;

  ((Arcadia_Visuals_Window*)_self)->getPosition = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getPositionImpl;
  ((Arcadia_Visuals_Window*)_self)->setPosition = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & setPositionImpl;

  ((Arcadia_Visuals_Window*)_self)->getSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getSizeImpl;
  ((Arcadia_Visuals_Window*)_self)->setSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & setSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->getFullscreen = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getFullscreenImpl;
  ((Arcadia_Visuals_Window*)_self)->setFullscreen = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_BooleanValue)) & setFullscreenImpl;

  Arcadia_Object_setType(thread, _self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  Arcadia_Visuals_Linux_GlxDeviceInfo* deviceInfo = Arcadia_Visuals_Linux_GlxDeviceInfo_create(thread);

  if (!self->screen) {
    self->screen = DefaultScreenOfDisplay(self->system->display);
    if (!self->screen) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    openVisual(thread, self, deviceInfo);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }

  if (!self->window) {
    int screenId = DefaultScreen(self->system->display);

    Window rootWindow = RootWindowOfScreen(self->screen);
    int windowX = ((Arcadia_Visuals_Window*)self)->bounds.left;
    int windowY = ((Arcadia_Visuals_Window*)self)->bounds.top;
    int windowW = ((Arcadia_Visuals_Window*)self)->bounds.width;
    int windowH = ((Arcadia_Visuals_Window*)self)->bounds.height;
    // Does not seem to have an effect when using GNOME.
    int windowBorderWidth = 0;
    int windowClass = InputOutput;
    int windowDepth = DefaultDepth(self->system->display, screenId);

    int attributeValueMask = 0;
    XSetWindowAttributes windowAttributes = {};

  #if 0
    // Not really useful for us.
    windowAttributes.background_pixel = 0xffafe9af;
    attributeValueMask |= CWBackPixel;
  #endif

  #if 1
    // Does not seem to have an effect when using GNOME.
    windowAttributes.border_pixel = WhitePixel(self->system->display, screenId);
    attributeValueMask |= CWBorderPixel;
  #endif

    windowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask;
    attributeValueMask |= CWEventMask;

    self->colormap = XCreateColormap(self->system->display,
                                     rootWindow,
                                     self->visualInfo->visual,
                                     AllocNone);
    windowAttributes.colormap = self->colormap;
    attributeValueMask |= CWColormap;

    self->window = XCreateWindow(self->system->display,
                                 rootWindow,
                                 windowX, windowY, windowW, windowH,
                                 windowBorderWidth,
                                 windowDepth,
                                 windowClass,
                                 self->visualInfo->visual,
                                 attributeValueMask, &windowAttributes);
    if (!self->window) {

      XDestroyWindow(self->system->display, self->window);
      self->window = None;

      XFree(self->visualInfo);
      self->visualInfo = NULL;

      free(self->frameBufferConfiguration);
      self->frameBufferConfiguration = NULL;

    #if 0
      // Do NOT call XFree on self->screen (unlike some examples suggest).
      XFree(self->screen);
    #endif
      self->screen = NULL;

      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  XMapWindow(self->system->display, self->window);

  XSetWMProtocols(self->system->display, self->window, &self->system->WM_DELETE_WINDOW, 1);

  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    openContext(thread, self, deviceInfo);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);

    XDestroyWindow(self->system->display, self->window);
    self->window = None;

    XFreeColormap(self->system->display, self->colormap);
    self->colormap = None;

    XFree(self->visualInfo);
    self->visualInfo = NULL;

    free(self->frameBufferConfiguration);
    self->frameBufferConfiguration = NULL;

  #if 0
    // Do NOT call XFree on self->screen (unlike some examples suggest).
    XFree(self->screen);
  #endif
    self->screen = NULL;

    Arcadia_Thread_jump(thread);
  }

  // TODO: Use XSync.
  XFlush(self->system->display);
}

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (self->context) {
    glXDestroyContext(self->system->display, self->context);
    self->context = NULL;
  }

  if (self->window) {
    XDestroyWindow(self->system->display, self->window);
    self->window = None;
  }

  if (self->colormap) {
    XFreeColormap(self->system->display, self->colormap);
    self->colormap = None;
  }

  if (self->visualInfo) {
    XFree(self->visualInfo);
    self->visualInfo = NULL;
  }
  if (self->frameBufferConfiguration) {
    free(self->frameBufferConfiguration);
    self->frameBufferConfiguration = NULL;
  }

  if (self->screen) {
  #if 0
    // Do NOT call XFree on self->screen (unlike some examples suggest).
    XFree(self->screen);
  #endif
    self->screen = NULL;
  }
}

static Arcadia_BooleanValue
getFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{ return ((Arcadia_Visuals_Window*)self)->fullscreen; }

static void
setFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_BooleanValue fullscreen
  )
{
  if (self->window) {
    if (((Arcadia_Visuals_Window*)self)->fullscreen != fullscreen) {

      struct {
        unsigned long   flags;
        unsigned long   functions;
        unsigned long   decorations;
        long            inputMode;
        unsigned long   status;
      } hints = {
        .flags = 2, // indicate that we change the decorations
        .functions = 0, // ignored
        .decorations = fullscreen ? 0 : 1, // 0 means disables decorations, 1 enables decorations
        .inputMode = 0, // ignored
        .status = 0, // ingored
      };
      XChangeProperty(self->system->display, self->window, self->system->_MOTIF_WM_HINTS,
                                                   self->system->_MOTIF_WM_HINTS,
                                                   32, PropModeReplace, (unsigned char *)&hints,
                                                   5);
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
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = 128;
  *height = 128;
}

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = 64;
  *height = 64;
}

static Arcadia_Visuals_Linux_Icon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{ return self->bigIcon; }

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Visuals_Linux_Icon* icon
  )
{
  self->bigIcon = icon;
  applyIcons(thread, self);
}

static Arcadia_Visuals_Linux_Icon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{ return self->smallIcon; }

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Visuals_Linux_Icon* icon
  )
{
  self->smallIcon = icon;
  applyIcons(thread, self);
}

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{ return ((Arcadia_Visuals_Window*)self)->title; }

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_String* title
  )
{
  if (!title) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_Value value;
  Arcadia_Value_setObjectReferenceValue(&value, (Arcadia_ObjectReferenceValue)title);
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, value);
  Arcadia_Value_setObjectReferenceValue(&value, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"", 1)));
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, value);

  if (self->window) {
    XStoreName(self->system->display, self->window,
               Arcadia_StringBuffer_getBytes(thread, stringBuffer));
  }
  ((Arcadia_Visuals_Window*)self)->title = title;
}

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  if (!self->window) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  XWindowAttributes attr;
  if(!XGetWindowAttributes(self->system->display, self->window, &attr)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  *width = attr.width;
  *height = attr.height;
}

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (!glXMakeCurrent(self->system->display, self->window, self->context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Integer32Value width, height;
  Arcadia_Visuals_WindowBackend_getCanvasSize(thread, (Arcadia_Visuals_WindowBackend*)self, &width, &height);
  glViewport(0, 0, width, height);
  glClearColor(193.0f/255.0f, 216.0f/255.0f, 195.0f/255.0f, 255.0f/255.0f);
  glClearDepth(1.f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (self->context == glXGetCurrentContext()) {
    glXSwapBuffers(self->system->display, self->window);
  }
}

static void
getBorderInfo
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  )
{
  Atom type;
  int format;
  unsigned long nitems, bytes_after;
  unsigned char *property;
  Status status;
  status = XGetWindowProperty(self->system->display, self->window, self->system->_NET_FRAME_EXTENTS,
                              0, 16, 0, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &property);
  if (status != Success) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (type == None || nitems != 4) {
    XFree(property);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  *left = (int)((long *)property)[0];
  *top = (int)((long *)property)[1];
  *right = (int)((long *)property)[2];
  *bottom = (int)((long *)property)[3];
  XFree(property);
}

static void
getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  )
{
  XWindowAttributes attributes;
  XGetWindowAttributes(self->system->display, self->window, &attributes);
  *left = attributes.x;
  *top = attributes.y;
}

static void
setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  )
{
  Arcadia_Integer32Value borderLeft, borderTop, borderRight, borderBottom;
  getBorderInfo(thread, self, &borderLeft, &borderTop, &borderRight, &borderBottom);
  XMoveWindow(self->system->display, self->window, left + borderLeft, top + borderTop);
  XSync(self->system->display, False);
}

static void
getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  XWindowAttributes attributes;
  XGetWindowAttributes(self->system->display, self->window, &attributes); 
  *width = attributes.width;
  *height = attributes.height;
}

static void
setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  XResizeWindow(self->system->display, self->window, width, height);
  XSync(self->system->display, False);
}

Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend*
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* system
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (system) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, system);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend);
}
