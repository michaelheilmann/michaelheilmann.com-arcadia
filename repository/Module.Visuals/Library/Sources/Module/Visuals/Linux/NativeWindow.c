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

// Last modified: 2025-04-28

#include "Module/Visuals/Linux/NativeWindow.h"

#include <X11/keysymdef.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h> 

static const char g_title[] = "Liminality";

static void
Linux_NativeWindow_destruct
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static void
Linux_NativeWindow_visit
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static void
Linux_NativeWindow_constructImpl
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
    Linux_NativeWindow* self
  );

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Arcadia_BooleanValue quitRequested
  );

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static Linux_NativeIcon*
getBigIconImpl 
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Linux_NativeIcon* icon
  );

static Linux_NativeIcon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Linux_NativeIcon* icon
  );

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Arcadia_String* title
  );

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  );

static Arcadia_BooleanValue g_quitRequested = Arcadia_BooleanValue_False;

static Atom NET_WM_ICON = None;

static Atom WM_DELETE_WINDOW = None;

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Linux_NativeWindow_constructImpl,
  .destruct = &Linux_NativeWindow_destruct,
  .visit = &Linux_NativeWindow_visit,
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

Arcadia_defineObjectType(u8"Linux.NativeWindow", Linux_NativeWindow, u8"NativeWindow", NativeWindow, &_typeOperations);

static void
Linux_NativeWindow_destruct
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{
  if (self->window) {
    XDestroyWindow(self->display, self->window);
    self->window = None;
  }
  if (self->colormap) {
    XFreeColormap(self->display, self->colormap);
    self->colormap = None;
  }
#if 0
  // Do NOT call XFree on self->screen (unlike some examples suggest).
  if (self->screen) {
    XFree(self->screen);
    self->screen = NULL;
  }
#endif
  if (self->display) {
    XCloseDisplay(self->display);
    self->display = NULL;
  }
}

static void
Linux_NativeWindow_visit
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{
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
Linux_NativeWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Linux_NativeWindow* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Linux_NativeWindow_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->smallIcon = NULL;
  _self->bigIcon = NULL;
  _self->display = NULL;
  _self->screen = NULL;
  _self->window = 0;
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
    Linux_NativeWindow* self
  )
{ 
  if (!self->display) {
    self->display = XOpenDisplay(NULL);
    if (!self->display) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
  if (!self->screen) {
    self->screen = DefaultScreenOfDisplay(self->display);
    if (!self->screen) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }  
  }
  
  if (!self->window) {
    int screenId = DefaultScreen(self->display);
   
    Window rootWindow = RootWindowOfScreen(self->screen);
    int windowX = 0;
    int windowY = 0;
    int windowW = 640;
    int windowH = 480;
    // Does not seem to have an effect when using GNOME.
    int windowBorderWidth = 0;
    int windowClass = InputOutput;
    Visual* windowVisual = DefaultVisual(self->display, screenId);
    int windowDepth = DefaultDepth(self->display, screenId);
    
    int attributeValueMask = 0;
    XSetWindowAttributes windowAttributes = {};

  #if 0
    // Not really useful for us.
    windowAttributes.background_pixel = 0xffafe9af;
    attributeValueMask |= CWBackPixel;
  #endif
    
  #if 1
    // Does not seem to have an effect when using GNOME.
    windowAttributes.border_pixel = WhitePixel(self->display, screenId);
    attributeValueMask |= CWBorderPixel;
  #endif
    
    windowAttributes.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ExposureMask;
    attributeValueMask |= CWEventMask;
    
    self->colormap = XCreateColormap(self->display,
                                     rootWindow,
                                     windowVisual,
                                     AllocNone);
    windowAttributes.colormap = self->colormap;
    attributeValueMask |= CWColormap;

    self->window = XCreateWindow(self->display,
                                 rootWindow, 
                                 windowX, windowY, windowW, windowH,
                                 windowBorderWidth,
                                 windowDepth,
                                 windowClass,
                                 windowVisual,
                                 attributeValueMask, &windowAttributes);
    if (!self->window) {
      
      XDestroyWindow(self->display, self->window);
      self->window = None;
      
      XFree(self->screen);
      self->screen = NULL;
      
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);     
    }
  }
  
  XMapWindow(self->display, self->window);
  
  if (WM_DELETE_WINDOW == None) {
    WM_DELETE_WINDOW = XInternAtom(self->display, "WM_DELETE_WINDOW", False);
    if (WM_DELETE_WINDOW == None) {
      
      XDestroyWindow(self->display, self->window);
      self->window = None;
      
      XFree(self->screen);
      self->screen = NULL;
      
      XCloseDisplay(self->display);
      self->display = NULL;
      
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);        
    }
  }
  XSetWMProtocols(self->display, self->window, &WM_DELETE_WINDOW, 1);
  
  XFlush(self->display);
}

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{
  if (self->window) {
    XDestroyWindow(self->display, self->window);
    self->window = None;
  }
  if (self->colormap) {
    XFreeColormap(self->display, self->colormap);
    self->colormap = None;
  }
#if 0
  // Do NOT call XFree on self->screen (unlike some examples suggest).
  if (self->screen) {
    XFree(self->screen);
    self->screen = NULL;
  }
#endif
  if (self->display) {
    XCloseDisplay(self->display);
    self->display = NULL;
  }
}

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{ return g_quitRequested; }

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Arcadia_BooleanValue quitRequested
  )
{ g_quitRequested = quitRequested; }

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{ 
  XEvent event;
  while (XPending(self->display)) {
    XNextEvent(self->display, &event);
    switch (event.type) {
      case KeyPress: {
        if (XLookupKeysym(&event.xkey, 0) == XK_Escape) {
          g_quitRequested = Arcadia_BooleanValue_True;
        } 
      } break;
      case ClientMessage: {
        if ((Atom)event.xclient.data.l[0] == WM_DELETE_WINDOW) {
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
    Linux_NativeWindow* self,
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
    Linux_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = 64;
  *height = 64;
}

/*
 * Pack the small icon and the big icon as required by _NET_WM_ICON.
 */
static void
applyIcons
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{
  if (!self->display || !self->window) {
    return;
  }
  if (NET_WM_ICON == None) {
    NET_WM_ICON = XInternAtom(self->display, "_NET_WM_ICON", False);
    if (NET_WM_ICON == None) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
  if (!self->smallIcon && !self->bigIcon) {
    XDeleteProperty(self->display, self->window, NET_WM_ICON);
  } else { 
    size_t numberOfElements = 0;
    Linux_NativeIcon* icons[] = {
      self->smallIcon,
      self->bigIcon,
    };
    Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
    for (size_t i = 0; i < 2; ++i) {
      Linux_NativeIcon* icon = icons[i];
      if (icon) {
        numberOfElements += icon->width * icon->height + 2;
        Arcadia_ByteBuffer_append_pn(thread, byteBuffer, icon->bytes, icon->numberOfBytes);
      }
    }
    void const* p = Arcadia_ByteBuffer_getBytes(thread, byteBuffer);
    int n = Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer);
    XChangeProperty(self->display,
                    self->window,
                    NET_WM_ICON,
                    XA_CARDINAL,
                    32,
                    PropModeReplace,
                    Arcadia_ByteBuffer_getBytes(thread, byteBuffer),
                    numberOfElements);
  }
  XFlush(self->display);
}

static Linux_NativeIcon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{ return self->bigIcon; }

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Linux_NativeIcon* icon
  )
{
  self->bigIcon = icon;
  applyIcons(thread, self);
}

static Linux_NativeIcon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{ return self->smallIcon; }

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Linux_NativeIcon* icon
  )
{
  self->smallIcon = icon;
  applyIcons(thread, self);
}

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{ return self->title; }

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
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
  Arcadia_StringBuffer_append(thread, stringBuffer, value);
  Arcadia_Value_setObjectReferenceValue(&value, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"", 1)));
  Arcadia_StringBuffer_append(thread, stringBuffer, value);
  
  if (self->display && self->window) {
    XStoreName(self->display, self->window,
               Arcadia_StringBuffer_getBytes(thread, stringBuffer));
  }
}

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  if (!self->display || !self->window) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);  
  }
  XWindowAttributes attr;
  if(!XGetWindowAttributes(self->display, self->window, &attr)) {
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
    Linux_NativeWindow* self
  )
{ }

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Linux_NativeWindow* self
  )
{ }


Linux_NativeWindow*
Linux_NativeWindow_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Linux_NativeWindow* self = Arcadia_allocateObject(thread, _Linux_NativeWindow_getType(thread), 0, &argumentValues[0]);
  return self;
}
