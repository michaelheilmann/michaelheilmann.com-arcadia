#include "Module/Visuals/Linux/GlxDeviceInfo.h"

#include <string.h>

// Utility variable.
static int (*g_oldErrorHandler)(Display*, XErrorEvent*) = NULL;

// Utility function.
static int
errorHandler
  (
    Display *display,
    XErrorEvent *event
  );

// Helper to check for extension string presence.  Adapted from:
// http://www.opengl.org/resources/features/OGLextensions/
static bool
isExtensionSupported
  (
    const char *extList,
    const char *extension
  );

static Arcadia_String*
integerToString
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  );

static void
addIfNotExisting
  (
    Arcadia_Thread* thread,
    Arcadia_List* configurations,
    Arcadia_Visuals_Configuration* configuration
  );

static void
Arcadia_Visuals_Linux_GlxDeviceInfo_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_GlxDeviceInfo* self
  );

static void
Arcadia_Visuals_Linux_GlxDeviceInfo_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_GlxDeviceInfo* self
  );

static void
Arcadia_Visuals_Linux_GlxDeviceInfo_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_GlxDeviceInfo_constructImpl,
  .destruct = &Arcadia_Visuals_Linux_GlxDeviceInfo_destruct,
  .visit = NULL,
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

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.GlxDeviceInfo", Arcadia_Visuals_Linux_GlxDeviceInfo, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static int
errorHandler
  (
    Display *display,
    XErrorEvent *event
  )
{ return 0; }

static bool
isExtensionSupported
  (
    const char *extList,
    const char *extension
  )
{
  const char *start;
  const char *where, *terminator;

  /* Extension names should not have spaces. */
  where = strchr(extension, ' ');
  if (where || *extension == '\0')
    return false;

  /* It takes a bit of care to be fool-proof about parsing the
     OpenGL extensions string. Don't be fooled by sub-strings,
     etc. */
  for (start=extList;;) {
    where = strstr(start, extension);

    if (!where)
      break;

    terminator = where + strlen(extension);

    if ( where == start || *(where - 1) == ' ' )
      if ( *terminator == ' ' || *terminator == '\0' )
        return true;

    start = terminator;
  }

  return false;
}

static Arcadia_String*
integerToString
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  )
{
  Arcadia_ImmutableUtf8String* immutableUtf8StringValue = Arcadia_ImmutableUtf8String_createFromInteger32(thread, integer32Value);
  Arcadia_Value value = { .tag = Arcadia_ValueTag_ImmutableUtf8String, .immutableUtf8StringValue = immutableUtf8StringValue };
  return Arcadia_String_create(thread, value);
}

static void
addIfNotExisting
  (
    Arcadia_Thread* thread,
    Arcadia_List* configurations,
    Arcadia_Visuals_Configuration* configuration
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, configurations); i < n; ++i) {
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

static void
Arcadia_Visuals_Linux_GlxDeviceInfo_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_GlxDeviceInfo* self
  )
{
  if (self->xDisplay) {
    XCloseDisplay(self->xDisplay);
    self->xDisplay = NULL;
  }
}

static void
Arcadia_Visuals_Linux_GlxDeviceInfo_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_GlxDeviceInfo* self
  )
{ }

static void
Arcadia_Visuals_Linux_GlxDeviceInfo_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Linux_GlxDeviceInfo* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_GlxDeviceInfo_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->xDisplay = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

Arcadia_Visuals_Linux_GlxDeviceInfo*
Arcadia_Visuals_Linux_GlxDeviceInfo_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Visuals_Linux_GlxDeviceInfo* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Linux_GlxDeviceInfo_getType(thread), 0, &argumentValues[0]);
  return self;
}

Arcadia_List*
Arcadia_Visuals_Linux_GlxDeviceInfo_getGlxConfigurations
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_GlxDeviceInfo* self
  )
{
  Arcadia_List* configurations = Arcadia_List_create(thread);

  if (!self->xDisplay) {
    self->xDisplay = XOpenDisplay(NULL);
    if (!self->xDisplay) {
      fprintf(stderr, "%s:%d: unable to open X display\n", __FILE__, __LINE__);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  int glXMajorVersion, glXMinorVersion;

  // FBConfigs were added in GLX version 1.3.
  if (!glXQueryVersion(self->xDisplay, &glXMajorVersion, &glXMinorVersion)) {
    fprintf(stderr, "%s:%d: unable to determine GLX version\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if ((glXMajorVersion == 1 && glXMinorVersion < 3) || glXMajorVersion < 1) {
    fprintf(stderr, "%s:%d: unsupported GLX version\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  int glXNumberOfConfigurations;
  GLXFBConfig* glXConfigurations = glXChooseFBConfig(self->xDisplay, DefaultScreen(self->xDisplay),
                                                     NULL, &glXNumberOfConfigurations);
  if (!glXConfigurations) {
    fprintf(stderr, "%s:%d: unable to obtain GLX frame buffer configuration\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    for (int majorVersion = 0; majorVersion < 5; majorVersion++) {
      for (int minorVersion = 0; minorVersion < 9; minorVersion++) {
        for (int i = 0, n = glXNumberOfConfigurations; i < n; ++i) {
          GLXFBConfig* glXConfiguration = glXConfigurations[i];
          int key, value;

          key = GLX_DRAWABLE_TYPE;
          if (glXGetFBConfigAttrib(self->xDisplay, glXConfiguration, key, &value)) {
            continue;
          }
          if (GLX_WINDOW_BIT != (value & GLX_WINDOW_BIT)) {
            continue;
          }

          key = GLX_RENDER_TYPE;
          if (glXGetFBConfigAttrib(self->xDisplay, glXConfiguration, key, &value)) {
            continue;
          }
          if (GLX_RGBA_BIT != (value & GLX_RGBA_BIT)) {
            continue;
          }

          key = GLX_X_VISUAL_TYPE;
          if (glXGetFBConfigAttrib(self->xDisplay, glXConfiguration, key, &value)) {
            continue;
          }
          if (value != GLX_TRUE_COLOR) {
            continue;
          }

          key = GLX_RED_SIZE;
          int redBits;
          if (glXGetFBConfigAttrib(self->xDisplay, glXConfiguration, key, &redBits)) {
            continue;
          }
          if (redBits < 8) {
            continue;
          }
          key = GLX_GREEN_SIZE;
          int greenBits;
          if (glXGetFBConfigAttrib(self->xDisplay, glXConfiguration, key, &greenBits)) {
            continue;
          }
          if (greenBits < 8) {
            continue;
          }
          key = GLX_BLUE_SIZE;
          int blueBits;
          if (glXGetFBConfigAttrib(self->xDisplay, glXConfiguration, key, &blueBits)) {
            continue;
          }
          if (blueBits < 8) {
            continue;
          }
          key = GLX_ALPHA_SIZE;
          int alphaBits;
          if (glXGetFBConfigAttrib(self->xDisplay, glXConfiguration, key, &alphaBits)) {
            continue;
          }
          if (alphaBits < 8) {
            continue;
          }

          key = GLX_DEPTH_SIZE;
          int depthBits;
          if (glXGetFBConfigAttrib(self->xDisplay, glXConfiguration, key, &depthBits)) {
            continue;
          }
          if (depthBits < 24) {
            continue;
          }

          // Get the default screen's GLX extension list.
          const char *glXExtensions = glXQueryExtensionsString(self->xDisplay, DefaultScreen(self->xDisplay));
          // Check for the GLX_ARB_create_context extension string.
          if (!isExtensionSupported(glXExtensions, "GLX_ARB_create_context")) {
            continue;
          }
          // Check for glCReateContextAttribsARB function.
          // NOTE: It is not necessary to create or make current to a context before calling glXGetProcAddressARB.
          PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB =
            (PFNGLXCREATECONTEXTATTRIBSARBPROC)
            glXGetProcAddressARB
              (
                (const GLubyte *)"glXCreateContextAttribsARB"
              );

          int contextAttributes[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
            GLX_CONTEXT_MINOR_VERSION_ARB, minorVersion,
            //GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            None
          };

          // Replace the original error handler with our error handler.
          g_oldErrorHandler = XSetErrorHandler(&errorHandler);

          GLXContext glXContext = glXCreateContextAttribsARB(self->xDisplay, glXConfiguration, 0, True,
                                                             contextAttributes);
          if (NULL == glXContext) {
            continue;
          }

          // Restore the original error handler.
          XSetErrorHandler(g_oldErrorHandler);
          g_oldErrorHandler = NULL;


          glXDestroyContext(self->xDisplay, glXContext);
          glXContext = NULL;

          Arcadia_Visuals_Configuration* configuration = Arcadia_Visuals_Configuration_create(thread);
          configuration->opengl.version.major = integerToString(thread, majorVersion);
          configuration->opengl.version.minor = integerToString(thread, minorVersion);
          configuration->colorBuffer.redBits = integerToString(thread, redBits);
          configuration->colorBuffer.greenBits = integerToString(thread, greenBits);
          configuration->colorBuffer.blueBits = integerToString(thread, blueBits);
          configuration->colorBuffer.alphaBits = integerToString(thread, alphaBits);
          configuration->depthBuffer.depthBits = integerToString(thread, depthBits);
          addIfNotExisting(thread, configurations, configuration);
        }
      }
    }

    Arcadia_Thread_popJumpTarget(thread);

    XFree(glXConfigurations);
    glXConfigurations = NULL;

    XCloseDisplay(self->xDisplay);
    self->xDisplay = NULL;

    return configurations;
  } else {
    Arcadia_Thread_popJumpTarget(thread);

    if (glXConfigurations) {
      XFree(glXConfigurations);
      glXConfigurations = NULL;
    }

    if (self->xDisplay) {
      XCloseDisplay(self->xDisplay);
      self->xDisplay = NULL;
    }

    Arcadia_Thread_jump(thread);
  }
}

Arcadia_BooleanValue
Arcadia_Visuals_Linux_GlxDeviceInfo_isGlxExtensionSupported
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_GlxDeviceInfo* self,
    const char *glXExtension
  )
{
  if (!self->xDisplay) {
    self->xDisplay = XOpenDisplay(NULL);
    if (!self->xDisplay) {
      fprintf(stderr, "%s:%d: unable to open X display\n", __FILE__, __LINE__);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
  // Get the default screen's GLX extension list.
  const char *glXExtensions = glXQueryExtensionsString(self->xDisplay, DefaultScreen(self->xDisplay));
  return isExtensionSupported(glXExtensions, glXExtension);
}
