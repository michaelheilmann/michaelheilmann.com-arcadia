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

#include "Arcadia/Visuals/Implementation/Linux/ErrorHandler.h"
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

static void
openContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
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
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
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

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_constructImpl,
  .destruct = &Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_destruct,
  .visit = &Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.GLX.WindowBackend", Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend,
                         u8"Arcadia.Visuals.WindowBackend", Arcadia_Visuals_WindowBackend,
                         &_typeOperations);

static void
openContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  glXMakeCurrent(self->backendContext->display, self->window, self->backendContext->context);
  XSync(self->backendContext->display, False);
  if (Arcadia_Visuals_Implementation_Linux_hasX11Error(thread)) {
    Arcadia_Visuals_Implementation_Linux_clearX11Error(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
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
    XDeleteProperty(self->backendContext->display, self->window, self->backendContext->_NET_WM_ICON);
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
    XChangeProperty(self->backendContext->display,
                    self->window,
                    self->backendContext->_NET_WM_ICON,
                    XA_CARDINAL,
                    32,
                    PropModeReplace,
                    Arcadia_ByteBuffer_getBytes(thread, byteBuffer),
                    numberOfElements);
  }
  XSync(self->backendContext->display, False);
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
  Arcadia_logf(Arcadia_LogFlags_Info, "%s:%d: Enter: Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_destruct\n", __FILE__, __LINE__);
  if (self->window) {
    XDestroyWindow(self->backendContext->display, self->window);
    self->window = None;
  }

  if (self->screen) {
  #if 0
    // Do NOT call XFree on self->screen (unlike some examples suggest).
    XFree(self->screen);
  #endif
    self->screen = NULL;
  }
  Arcadia_List_filter(thread, ((Arcadia_Visuals_BackendContext*)self->backendContext)->windows, Arcadia_Value_makeObjectReferenceValue(self), &filter);
  if (self->backendContext) {
    Arcadia_Object_unlock(thread, self->backendContext);
    self->backendContext = NULL;
  }
  Arcadia_logf(Arcadia_LogFlags_Info, "%s:%d: Leave: Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_destruct\n", __FILE__, __LINE__);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (self->backendContext) {
    Arcadia_Object_visit(thread, self->backendContext);
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
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext_getType(thread));
  Arcadia_Object_lock(thread, self->backendContext);
  self->smallIcon = NULL;
  self->bigIcon = NULL;
  self->screen = NULL;
  self->window = None;

  ((Arcadia_Visuals_WindowBackend*)self)->open = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*)) & openImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->close = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*)) & closeImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->getRequiredBigIconSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredBigIconSizeImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->getRequiredSmallIconSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredSmallIconSizeImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->getBigIcon = (Arcadia_Visuals_Icon*(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*)) & getBigIconImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->setBigIcon = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Visuals_Icon*)) & setBigIconImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->getSmallIcon = (Arcadia_Visuals_Icon*(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*)) & getSmallIconImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->setSmallIcon = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Visuals_Icon*)) & setSmallIconImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->getTitle = (Arcadia_String*(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*)) & getTitleImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->setTitle = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_String*)) & setTitleImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->getCanvasSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getCanvasSizeImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->beginRender = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*))&beginRenderImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->endRender = (void(*)(Arcadia_Thread*,Arcadia_Visuals_WindowBackend*))&endRenderImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->getPosition = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getPositionImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->setPosition = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & setPositionImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->getSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getSizeImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->setSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & setSizeImpl;

  ((Arcadia_Visuals_WindowBackend*)self)->getFullscreen = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*)) & getFullscreenImpl;
  ((Arcadia_Visuals_WindowBackend*)self)->setFullscreen = (void(*)(Arcadia_Thread*, Arcadia_Visuals_WindowBackend*, Arcadia_BooleanValue)) & setFullscreenImpl;

  Arcadia_Object_setType(thread, self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (!self->screen) {
    self->screen = DefaultScreenOfDisplay(self->backendContext->display);
    if (!self->screen) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  Arcadia_JumpTarget jumpTarget;

  if (!self->window) {
    int screenId = DefaultScreen(self->backendContext->display);

    Window rootWindow = RootWindowOfScreen(self->screen);
    int windowX = ((Arcadia_Visuals_WindowBackend*)self)->bounds.left;
    int windowY = ((Arcadia_Visuals_WindowBackend*)self)->bounds.top;
    int windowW = ((Arcadia_Visuals_WindowBackend*)self)->bounds.width;
    int windowH = ((Arcadia_Visuals_WindowBackend*)self)->bounds.height;
    // Does not seem to have an effect when using GNOME.
    int windowBorderWidth = 0;
    int windowClass = InputOutput;
    int windowDepth = DefaultDepth(self->backendContext->display, screenId);

    int attributeValueMask = 0;
    XSetWindowAttributes windowAttributes = {};

  #if 0
    // Not really useful for us.
    windowAttributes.background_pixel = 0xffafe9af;
    attributeValueMask |= CWBackPixel;
  #endif

  #if 1
    // Does not seem to have an effect when using GNOME.
    windowAttributes.border_pixel = WhitePixel(self->backendContext->display, screenId);
    attributeValueMask |= CWBorderPixel;
  #endif

    windowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask;
    attributeValueMask |= CWEventMask;

    windowAttributes.colormap = self->backendContext->colormap;
    attributeValueMask |= CWColormap;

    self->window = XCreateWindow(self->backendContext->display,
                                 rootWindow,
                                 windowX, windowY, windowW, windowH,
                                 windowBorderWidth,
                                 windowDepth,
                                 windowClass,
                                 self->backendContext->visualInfo->visual,
                                 attributeValueMask, &windowAttributes);
    if (!self->window) {

      XDestroyWindow(self->backendContext->display, self->window);
      self->window = None;

    #if 0
      // Do NOT call XFree on self->screen (unlike some examples suggest).
      XFree(self->screen);
    #endif
      self->screen = NULL;

      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
  XMapWindow(self->backendContext->display, self->window);

  XSetWMProtocols(self->backendContext->display, self->window, &self->backendContext->WM_DELETE_WINDOW, 1);

  XSync(self->backendContext->display, False);
  if (Arcadia_Visuals_Implementation_Linux_hasX11Error(thread)) {
    Arcadia_Visuals_Implementation_Linux_clearX11Error(thread);

    XDestroyWindow(self->backendContext->display, self->window);
    self->window = None;

  #if 0
    // Do NOT call XFree on self->screen (unlike some examples suggest).
    XFree(self->screen);
  #endif
    self->screen = NULL;

    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    openContext(thread, self);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);

    XDestroyWindow(self->backendContext->display, self->window);
    self->window = None;

  #if 0
    // Do NOT call XFree on self->screen (unlike some examples suggest).
    XFree(self->screen);
  #endif
    self->screen = NULL;

    Arcadia_Thread_jump(thread);
  }

  XSync(self->backendContext->display, False);
}

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (self->window) {
    XDestroyWindow(self->backendContext->display, self->window);
    self->window = None;
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
    if (((Arcadia_Visuals_WindowBackend*)self)->fullscreen != fullscreen) {

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
      XSync(self->backendContext->display, False);
      XSync(self->backendContext->display, False);
      XChangeProperty(self->backendContext->display, self->window, self->backendContext->_MOTIF_WM_HINTS,
                                                   self->backendContext->_MOTIF_WM_HINTS,
                                                   32, PropModeReplace, (unsigned char *)&hints,
                                                   5);
      XSync(self->backendContext->display, False);
      ((Arcadia_Visuals_WindowBackend*)self)->fullscreen = fullscreen;
      if (Arcadia_Visuals_Implementation_Linux_hasX11Error(thread)) {
        Arcadia_Visuals_Implementation_Linux_clearX11Error(thread);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    }
  } else {
    ((Arcadia_Visuals_WindowBackend*)self)->fullscreen = fullscreen;
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
    XStoreName(self->backendContext->display, self->window,
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
  if(!XGetWindowAttributes(self->backendContext->display, self->window, &attr)) {
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
  if (!glXMakeCurrent(self->backendContext->display, self->window, self->backendContext->context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
}

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* self
  )
{
  if (self->backendContext->context == glXGetCurrentContext()) {
    glXSwapBuffers(self->backendContext->display, self->window);
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
  status = XGetWindowProperty(self->backendContext->display, self->window, self->backendContext->_NET_FRAME_EXTENTS,
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
  XGetWindowAttributes(self->backendContext->display, self->window, &attributes);
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
  XSync(self->backendContext->display, False);
  Arcadia_Integer32Value borderLeft, borderTop, borderRight, borderBottom;
  getBorderInfo(thread, self, &borderLeft, &borderTop, &borderRight, &borderBottom);
  XMoveWindow(self->backendContext->display, self->window, left + borderLeft, top + borderTop);
  XSync(self->backendContext->display, False);
  if (Arcadia_Visuals_Implementation_Linux_hasX11Error(thread)) {
    Arcadia_Visuals_Implementation_Linux_clearX11Error(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
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
  XGetWindowAttributes(self->backendContext->display, self->window, &attributes);
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
  XResizeWindow(self->backendContext->display, self->window, width, height);
  XSync(self->backendContext->display, False);
}

Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend*
Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend);
}
