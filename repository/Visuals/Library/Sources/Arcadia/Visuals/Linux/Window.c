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

#include "Arcadia/Visuals/Linux/Window.h"

#include "Arcadia/Visuals/Linux/GlxDeviceInfo.h"
#include "Arcadia/Visuals/Events/WindowPositionChangedEvent.h"
#include "Arcadia/Visuals/Events/WindowSizeChangedEvent.h"

#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <limits.h>

static const char g_title[] = "Liminality";

static int
stringToInteger
  (
    Arcadia_Thread* thread,
    Arcadia_String* source
  );

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
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Visuals_Linux_GlxDeviceInfo* deviceInfo
  );

static void
openContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Visuals_Linux_GlxDeviceInfo* deviceInfo
  );

static void
applyIcons
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
Arcadia_Visuals_Linux_Window_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
Arcadia_Visuals_Linux_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
Arcadia_Visuals_Linux_Window_constructImpl
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
    Arcadia_Visuals_Linux_Window* self
  );

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static Arcadia_BooleanValue
getFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
setFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_BooleanValue fullscreen
  );

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_BooleanValue quitRequested
  );

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static Arcadia_Visuals_Linux_Icon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Visuals_Linux_Icon* icon
  );

static Arcadia_Visuals_Linux_Icon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Visuals_Linux_Icon* icon
  );

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_String* title
  );

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  );
  
static void
getBorderInfo
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  );

static void
getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  );

static void
setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  );

static void
getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

/// @todo Remove this.
static Arcadia_BooleanValue g_quitRequested = Arcadia_BooleanValue_False;

static bool g_error = false;

static int (*g_oldErrorHandler)(Display*, XErrorEvent*) = NULL;

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_Window_constructImpl,
  .destruct = &Arcadia_Visuals_Linux_Window_destruct,
  .visit = &Arcadia_Visuals_Linux_Window_visit,
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

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.Window", Arcadia_Visuals_Linux_Window,
                         u8"Arcadia.Visuals.Window", Arcadia_Visuals_Window,
                         &_typeOperations);

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
    Arcadia_Visuals_Linux_Window* self,
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
    GLX_RED_SIZE         , stringToInteger(thread, desiredConfiguration->colorBuffer.redBits),
    GLX_GREEN_SIZE       , stringToInteger(thread, desiredConfiguration->colorBuffer.greenBits),
    GLX_BLUE_SIZE        , stringToInteger(thread, desiredConfiguration->colorBuffer.blueBits),
    GLX_ALPHA_SIZE       , stringToInteger(thread, desiredConfiguration->colorBuffer.alphaBits),
    GLX_DEPTH_SIZE       , stringToInteger(thread, desiredConfiguration->depthBuffer.depthBits),
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
        self->application->display,
        DefaultScreen(self->application->display),
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
          self->application->display,
          frameBufferConfigurations[i]
        );
    if (visualInfo) {
      int sampleBuffers, samples;
      glXGetFBConfigAttrib(self->application->display, frameBufferConfigurations[i], GLX_SAMPLE_BUFFERS, &sampleBuffers );
      glXGetFBConfigAttrib(self->application->display, frameBufferConfigurations[i], GLX_SAMPLES       , &samples  );

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
    self->visualInfo = glXGetVisualFromFBConfig(self->application->display, *self->frameBufferConfiguration );
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
    Arcadia_Visuals_Linux_Window* self,
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
  self->context = glXCreateContextAttribsARB(self->application->display,
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
  if (!glXIsDirect(self->application->display, self->context)) {
    glXDestroyContext(self->application->display, self->context);
    self->context = NULL;

    // Restore the original error handler.
    XSetErrorHandler(g_oldErrorHandler);
    g_oldErrorHandler = NULL;

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  glXMakeCurrent(self->application->display, self->window, self->context);

  XSync(self->application->display, False);
  if (g_error) {
    glXDestroyContext(self->application->display, self->context);
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
    Arcadia_Visuals_Linux_Window* self
  )
{
  if (!self->window) {
    return;
  }
  if (!self->smallIcon && !self->bigIcon) {
    XDeleteProperty(self->application->display, self->window, self->application->_NET_WM_ICON);
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
    XChangeProperty(self->application->display,
                    self->window,
                    self->application->_NET_WM_ICON,
                    XA_CARDINAL,
                    32,
                    PropModeReplace,
                    Arcadia_ByteBuffer_getBytes(thread, byteBuffer),
                    numberOfElements);
  }
  // @todo Call XSync instead.
  XFlush(self->application->display);
}

static void
Arcadia_Visuals_Linux_Window_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  )
{
  if (self->context) {
    glXDestroyContext(self->application->display, self->context);
    self->context = NULL;
  }

  if (self->window) {
    XDestroyWindow(self->application->display, self->window);
    self->window = None;
  }

  if (self->colormap) {
    XFreeColormap(self->application->display, self->colormap);
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
  if (self->application->display) {
    XCloseDisplay(self->application->display);
    self->application->display = NULL;
  }
  if (self->application) {
    Arcadia_Object_unlock(thread, self->application);
    self->application = NULL;
  }
  fprintf(stdout, "%s:%d: GLX window destroyed\n", __FILE__, __LINE__);
}

static void
Arcadia_Visuals_Linux_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  )
{
  if (self->application) {
    Arcadia_Object_visit(thread, self->application);
  }
  if (self->title) {
    Arcadia_Object_visit(thread, self->title);
  }
  if (self->bigIcon) {
    Arcadia_Object_visit(thread, self->bigIcon);
  }
  if (self->smallIcon) {
    Arcadia_Object_visit(thread, self->smallIcon);
  }
}

static void
Arcadia_Visuals_Linux_Window_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Linux_Window* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_Window_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->title = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, g_title, sizeof(g_title) - 1));
  _self->application = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_Visuals_Linux_Application_getType(thread));
  Arcadia_Object_lock(thread, _self->application);
  _self->smallIcon = NULL;
  _self->bigIcon = NULL;
  _self->screen = NULL;
  _self->frameBufferConfiguration = NULL;
  _self->visualInfo = NULL;
  _self->colormap = None;
  _self->window = None;
  _self->title = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, g_title, sizeof(g_title) - 1));

  ((Arcadia_Visuals_Window*)_self)->open = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & openImpl;
  ((Arcadia_Visuals_Window*)_self)->close = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & closeImpl;

  ((Arcadia_Visuals_Window*)_self)->getQuitRequested = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getQuitRequestedImpl;
  ((Arcadia_Visuals_Window*)_self)->setQuitRequested = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*,Arcadia_BooleanValue)) & setQuitRequestedImpl;

  ((Arcadia_Visuals_Window*)_self)->update = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) &updateImpl;

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
}

static void
openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  )
{
  Arcadia_Visuals_Linux_GlxDeviceInfo* deviceInfo = Arcadia_Visuals_Linux_GlxDeviceInfo_create(thread);

  if (!self->screen) {
    self->screen = DefaultScreenOfDisplay(self->application->display);
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
    int screenId = DefaultScreen(self->application->display);

    Window rootWindow = RootWindowOfScreen(self->screen);
    int windowX = ((Arcadia_Visuals_Window*)self)->bounds.left;
    int windowY = ((Arcadia_Visuals_Window*)self)->bounds.top;
    int windowW = ((Arcadia_Visuals_Window*)self)->bounds.width;
    int windowH = ((Arcadia_Visuals_Window*)self)->bounds.height;
    // Does not seem to have an effect when using GNOME.
    int windowBorderWidth = 0;
    int windowClass = InputOutput;
    int windowDepth = DefaultDepth(self->application->display, screenId);

    int attributeValueMask = 0;
    XSetWindowAttributes windowAttributes = {};

  #if 0
    // Not really useful for us.
    windowAttributes.background_pixel = 0xffafe9af;
    attributeValueMask |= CWBackPixel;
  #endif

  #if 1
    // Does not seem to have an effect when using GNOME.
    windowAttributes.border_pixel = WhitePixel(self->application->display, screenId);
    attributeValueMask |= CWBorderPixel;
  #endif

    windowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask;
    attributeValueMask |= CWEventMask;

    self->colormap = XCreateColormap(self->application->display,
                                     rootWindow,
                                     self->visualInfo->visual,
                                     AllocNone);
    windowAttributes.colormap = self->colormap;
    attributeValueMask |= CWColormap;

    self->window = XCreateWindow(self->application->display,
                                 rootWindow,
                                 windowX, windowY, windowW, windowH,
                                 windowBorderWidth,
                                 windowDepth,
                                 windowClass,
                                 self->visualInfo->visual,
                                 attributeValueMask, &windowAttributes);
    if (!self->window) {

      XDestroyWindow(self->application->display, self->window);
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

  XMapWindow(self->application->display, self->window);

  XSetWMProtocols(self->application->display, self->window, &self->application->WM_DELETE_WINDOW, 1);

  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    openContext(thread, self, deviceInfo);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);

    XDestroyWindow(self->application->display, self->window);
    self->window = None;

    XFreeColormap(self->application->display, self->colormap);
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
  XFlush(self->application->display);
}

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  )
{
  if (self->context) {
    glXDestroyContext(self->application->display, self->context);
    self->context = NULL;
  }

  if (self->window) {
    XDestroyWindow(self->application->display, self->window);
    self->window = None;
  }

  if (self->colormap) {
    XFreeColormap(self->application->display, self->colormap);
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
    Arcadia_Visuals_Linux_Window* self
  )
{ return Arcadia_BooleanValue_False; }

static void
setFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_BooleanValue fullscreen
  )
{}

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  )
{ return g_quitRequested; }

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_BooleanValue quitRequested
  )
{ g_quitRequested = quitRequested; }

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self
  )
{
  XEvent event;
  while (XPending(self->application->display)) {
    XNextEvent(self->application->display, &event);
    switch (event.type) {
      case ConfigureNotify: {
        Arcadia_JumpTarget jumpTarget;
        Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
        if (Arcadia_JumpTarget_save(&jumpTarget)) {
          XConfigureEvent* configureEvent = (XConfigureEvent*)&event;
          int left = configureEvent->x;
          int top = configureEvent->y;
          int width = configureEvent->width + configureEvent->border_width * 2;
          int height = configureEvent->height + configureEvent->border_width * 2;
          bool positionChanged = false, sizeChanged = false;
          if (((Arcadia_Visuals_Window*)self)->bounds.left != left ||
              ((Arcadia_Visuals_Window*)self)->bounds.top != top) {
            ((Arcadia_Visuals_Window*)self)->bounds.left = left;
            ((Arcadia_Visuals_Window*)self)->bounds.top = top;
            positionChanged = true;
          }
          if (((Arcadia_Visuals_Window*)self)->bounds.width != width ||
              ((Arcadia_Visuals_Window*)self)->bounds.height != height) {
            ((Arcadia_Visuals_Window*)self)->bounds.width = width;
            ((Arcadia_Visuals_Window*)self)->bounds.height = height;
            sizeChanged = true;
          }
          if (positionChanged) {
            Arcadia_Visuals_WindowPositionChangedEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                (Arcadia_Visuals_Window*)self,
                left,
                top
              );
          }
          if (sizeChanged) {
            Arcadia_Visuals_WindowSizeChangedEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                (Arcadia_Visuals_Window*)self,
                width,
                height
              );            
          }
          Arcadia_Thread_popJumpTarget(thread);
        } else {
          Arcadia_Thread_popJumpTarget(thread);
        }
      } break;
      case KeyPress: {
        if (XLookupKeysym(&event.xkey, 0) == XK_Escape) {
          g_quitRequested = Arcadia_BooleanValue_True;
        }
      } break;
      case ClientMessage: {
        if ((Atom)event.xclient.data.l[0] == self->application->WM_DELETE_WINDOW) {
          g_quitRequested = Arcadia_BooleanValue_True;
        }
      } break;
    };
  }
}

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
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
    Arcadia_Visuals_Linux_Window* self,
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
    Arcadia_Visuals_Linux_Window* self
  )
{ return self->bigIcon; }

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
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
    Arcadia_Visuals_Linux_Window* self
  )
{ return self->smallIcon; }

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
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
    Arcadia_Visuals_Linux_Window* self
  )
{ return self->title; }

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
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
    XStoreName(self->application->display, self->window,
               Arcadia_StringBuffer_getBytes(thread, stringBuffer));
  }
}

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  if (!self->window) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  XWindowAttributes attr;
  if(!XGetWindowAttributes(self->application->display, self->window, &attr)) {
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
    Arcadia_Visuals_Linux_Window* self
  )
{
  if (!glXMakeCurrent(self->application->display, self->window, self->context)) {
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
    Arcadia_Visuals_Linux_Window* self
  )
{
  if (self->context == glXGetCurrentContext()) {
    glXSwapBuffers(self->application->display, self->window);
  }
}

static void
getBorderInfo
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
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
  status = XGetWindowProperty(self->application->display, self->window, self->application->_NET_FRAME_EXTENTS,
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
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  )
{
  XWindowAttributes attributes;
  XGetWindowAttributes(self->application->display, self->window, &attributes);
  *left = attributes.x;
  *top = attributes.y;
}

static void
setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  )
{
  Arcadia_Integer32Value borderLeft, borderTop, borderRight, borderBottom;
  getBorderInfo(thread, self, &borderLeft, &borderTop, &borderRight, &borderBottom);
  XMoveWindow(self->application->display, self->window, left + borderLeft, top + borderTop);
  XSync(self->application->display, False);
}

static void
getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  XWindowAttributes attributes;
  XGetWindowAttributes(self->application->display, self->window, &attributes); 
  *width = attributes.width;
  *height = attributes.height;
}

static void
setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  //Arcadia_Integer32Value borderLeft, borderTop, borderRight, borderBottom;
  //getBorderInfo(thread, self, &borderLeft, &borderTop, &borderRight, &borderBottom);
  XResizeWindow(self->application->display, self->window, width, height);
  XSync(self->application->display, False);
}

Arcadia_Visuals_Linux_Window*
Arcadia_Visuals_Linux_Window_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* application
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  if (application) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[0], application);
  }
  Arcadia_Visuals_Linux_Window* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Linux_Window_getType(thread), 1, &argumentValues[0]);
  return self;
}
