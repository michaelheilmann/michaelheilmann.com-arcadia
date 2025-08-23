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

#include "Arcadia/Visuals/Implementation/Linux/Application.h"

#include "Arcadia/Visuals/Implementation/Linux/DisplayDevice.h"
#include "Arcadia/Visuals/Implementation/Linux/GlxDeviceInfo.h"
#include "Arcadia/Visuals/Implementation/Linux/Icon.h"
#include "Arcadia/Visuals/Implementation/Linux/Window.h"

#include <string.h>

#include "Arcadia/Visuals/Implementation/Linux/_edid.h"

// https://www.x.org/releases/current/doc/index.html
// https://www.x.org/releases/current/doc/randrproto/randrproto.txt
#include <X11/extensions/Xrandr.h>

static Arcadia_Visuals_Linux_Application* g_instance = NULL;

static int
errorHandler
  (
    Display *display,
    XErrorEvent *event
  );

static Arcadia_Visuals_Linux_Icon*
Arcadia_Visuals_Linux_Application_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  );

static Arcadia_Visuals_Linux_Window*
Arcadia_Visuals_Linux_Application_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  );
  
static Arcadia_Visuals_Linux_DisplayDevice*
getDisplayDevice
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self,
    RROutput outputId,
    RRMode modeId
  );

static Arcadia_List*
Arcadia_Visuals_Linux_Application_getDisplayDevicesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  );

static Arcadia_BooleanValue
Arcadia_Visuals_Linux_Application_getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  );

static void
Arcadia_Visuals_Linux_Application_setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self,
    Arcadia_BooleanValue quitRequested
  );
  
static void
Arcadia_Visuals_Linux_Application_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  );

static void
Arcadia_Visuals_Linux_Application_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Linux_Application_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  );

static void
Arcadia_Visuals_Linux_Application_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_Application_construct,
  .destruct = &Arcadia_Visuals_Linux_Application_destruct,
  .visit = &Arcadia_Visuals_Linux_Application_visit,
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

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.Application", Arcadia_Visuals_Linux_Application,
                         u8"Arcadia.Visuals.Application", Arcadia_Visuals_Application,
                         &_typeOperations);

static Arcadia_Visuals_Linux_Icon*
Arcadia_Visuals_Linux_Application_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  )
{
  Arcadia_Visuals_Linux_Icon* icon = Arcadia_Visuals_Linux_Icon_create(thread, width, height, 47, 47, 47, 255);
  return icon;
}

static Arcadia_Visuals_Linux_Window*
Arcadia_Visuals_Linux_Application_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  )
{
  Arcadia_Visuals_Linux_Window* window = Arcadia_Visuals_Linux_Window_create(thread, self);
  Arcadia_WeakReference* windowWeakReference =
    Arcadia_WeakReference_create
      (
        thread,
        Arcadia_Value_makeObjectReferenceValue(window)
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, self->windows, (Arcadia_Object*)windowWeakReference);
  return window;
}

static Arcadia_Visuals_Linux_DisplayDevice*
getDisplayDevice
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self,
    RROutput outputId,
    RRMode modeId
  )
{
  Atom EDID = XInternAtom(self->display, "EDID", False);
  int numberOfProperties;
  Atom* properties = XRRListOutputProperties(self->display, outputId, &numberOfProperties);
  if (!properties) {
    return NULL;
  }
  MonitorInfo* monitorInfo = NULL;
  for (int i = 0, n = numberOfProperties; i < n; ++i) {
    if (properties[i] == EDID) {
      unsigned char *property;
      int actualFormat;
      unsigned long numberOfItems, bytesAfter;
      Atom actualType;
      if  (Success != XRRGetOutputProperty(self->display, outputId, properties[i], 0, 100, False, False, AnyPropertyType,
                                           &actualType, &actualFormat, &numberOfItems, &bytesAfter, &property)) {
        XFree(properties);
        properties = NULL;
        return NULL;
      }
      monitorInfo = decode_edid(property);
      XFree(property);
      property = NULL;
      if (!monitorInfo) {
        XFree(properties);
        properties = NULL;
        return NULL;
      }
      break;
    }
  }
  
  Arcadia_Visuals_Linux_DisplayDevice* displayDevice = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_String* id =
      Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(
        Arcadia_ImmutableUtf8String_create(thread, monitorInfo->dsc_product_name,
                                           strlen(monitorInfo->dsc_product_name))));
    Arcadia_String* name =
      Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(
        Arcadia_ImmutableUtf8String_create(thread, monitorInfo->dsc_product_name,
                                           strlen(monitorInfo->dsc_product_name))));
    displayDevice =
      Arcadia_Visuals_Linux_DisplayDevice_create(thread, self, id, name);
    displayDevice->output = outputId;
    displayDevice->mode = modeId;
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
  }
  free(monitorInfo);
  monitorInfo = NULL;
  XFree(properties);
  properties = NULL;
  return displayDevice;
}

static Arcadia_List*
Arcadia_Visuals_Linux_Application_getDisplayDevicesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  )
{
  Arcadia_List* displayDevices = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  int dummy;
  if (!XQueryExtension(self->display, "RANDR", &dummy, &dummy, &dummy)) {
    return displayDevices;
  }
  Window rootWindow = XDefaultRootWindow(self->display);
  XRRScreenResources* screenResources = XRRGetScreenResources(self->display, rootWindow);
  for (int i = 0, n = screenResources->noutput; i < n; ++i) {
    RROutput output = screenResources->outputs[i];

    XRROutputInfo* outputInfo = XRRGetOutputInfo(self->display, screenResources, output);
    if (!outputInfo || !outputInfo->crtc || outputInfo->connection == RR_Disconnected) {
      XRRFreeOutputInfo(outputInfo);
      outputInfo = NULL;

      continue;
    }  

    XRRCrtcInfo *crtcInfo = XRRGetCrtcInfo(self->display, screenResources, outputInfo->crtc);
    if (!crtcInfo) {
      XRRFreeOutputInfo(outputInfo);
      outputInfo = NULL;

      continue;
    }
    
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_Visuals_Linux_DisplayDevice* displayDevice = getDisplayDevice(thread, self, output, crtcInfo->mode);
      if (displayDevice) {
        Arcadia_List_insertBackObjectReferenceValue(thread, displayDevices, (Arcadia_ObjectReferenceValue)displayDevice);
      }
      Arcadia_Visuals_Linux_DisplayDevice_updateBounds(thread, displayDevice);
      #if 0
      displayDevice->bounds.left = crtcInfo->x;
      displayDevice->bounds.top = crtcInfo->y;
      displayDevice->bounds.right = crtcInfo->x + crtcInfo->width;
      displayDevice->bounds.bottom = crtcInfo->y + crtcInfo->height;
      #endif
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);

      XRRFreeCrtcInfo(crtcInfo);
      crtcInfo = NULL;

      XRRFreeOutputInfo(outputInfo);
      outputInfo = NULL;
    
      continue;
    }
    
    XRRFreeCrtcInfo(crtcInfo);
    crtcInfo = NULL;
    
    XRRFreeOutputInfo(outputInfo);
    outputInfo = NULL;
  }
  XRRFreeScreenResources(screenResources);
  screenResources = NULL;
  
  return displayDevices;
}

static Arcadia_BooleanValue
Arcadia_Visuals_Linux_Application_getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  )
{ return self->quitRequested; }

static void
Arcadia_Visuals_Linux_Application_setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self,
    Arcadia_BooleanValue quitRequested
  )
{ self->quitRequested = quitRequested; }

static void
Arcadia_Visuals_Linux_Application_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  )
{
  XEvent event;
  while (XPending(self->display)) {
    XNextEvent(self->display, &event);
    switch (event.type) {
      case ConfigureNotify: {
        Arcadia_JumpTarget jumpTarget;
        Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
        if (Arcadia_JumpTarget_save(&jumpTarget)) {
          XConfigureEvent* configureEvent = (XConfigureEvent*)&event;
          Arcadia_Visuals_Linux_Window* window = NULL;
          for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->windows); i < n; ++i) {
            Arcadia_Visuals_Linux_Window* e = (Arcadia_Visuals_Linux_Window*)Arcadia_List_getObjectReferenceValueAt(thread, self->windows, i);
            if (e->window == configureEvent->window) {
              window = e;
              break;
            }
          }
          if (!window) {
            return;
          }
          int left = configureEvent->x;
          int top = configureEvent->y;
          int width = configureEvent->width + configureEvent->border_width * 2;
          int height = configureEvent->height + configureEvent->border_width * 2;
          bool positionChanged = false, sizeChanged = false;
          if (((Arcadia_Visuals_Window*)window)->bounds.left != left ||
              ((Arcadia_Visuals_Window*)window)->bounds.top != top) {
            ((Arcadia_Visuals_Window*)window)->bounds.left = left;
            ((Arcadia_Visuals_Window*)window)->bounds.top = top;
            positionChanged = true;
          }
          if (((Arcadia_Visuals_Window*)window)->bounds.width != width ||
              ((Arcadia_Visuals_Window*)window)->bounds.height != height) {
            ((Arcadia_Visuals_Window*)window)->bounds.width = width;
            ((Arcadia_Visuals_Window*)window)->bounds.height = height;
            sizeChanged = true;
          }
          if (positionChanged) {
            Arcadia_Visuals_WindowPositionChangedEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                (Arcadia_Visuals_Window*)window,
                left,
                top
              );
          }
          if (sizeChanged) {
            Arcadia_Visuals_WindowSizeChangedEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                (Arcadia_Visuals_Window*)window,
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
          Arcadia_Visuals_Application_setQuitRequested(thread, (Arcadia_Visuals_Application*)self, Arcadia_BooleanValue_True);
        }
      } break;
      case ClientMessage: {
        if ((Atom)event.xclient.data.l[0] == self->WM_DELETE_WINDOW) {
          Arcadia_Visuals_Application_setQuitRequested(thread, (Arcadia_Visuals_Application*)self, Arcadia_BooleanValue_True);
        }
      } break;
    };
  }
}

static void
Arcadia_Visuals_Linux_Application_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Linux_Application* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_Application_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  
  _self->windows = Arcadia_ArrayList_create(thread);
  _self->quitRequested = Arcadia_BooleanValue_False;

  // (1) Open the default display.
  _self->display = XOpenDisplay(NULL);
  if (!_self->display) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // (2) Create WM_DELETE_WINDOW atom.
  _self->WM_DELETE_WINDOW = XInternAtom(_self->display, "WM_DELETE_WINDOW", False);
  if (_self->WM_DELETE_WINDOW == None) {
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // (3) Create _NET_WM_ICON atom.
  _self->_NET_WM_ICON = XInternAtom(_self->display, "_NET_WM_ICON", False);
  if (_self->_NET_WM_ICON == None) {
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  
  // (4) Create _NET_FRAME_EXTENTS atom.
  _self->_NET_FRAME_EXTENTS = XInternAtom(_self->display, "_NET_FRAME_EXTENTS", False);
  if (_self->_NET_FRAME_EXTENTS == None) {
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  
  // (5) Create _MOTIF_WM_HINTS atom.
  _self->_MOTIF_WM_HINTS = XInternAtom(_self->display, "_MOTIF_WM_HINTS", False);
  if (_self->_MOTIF_WM_HINTS == None) {
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  ((Arcadia_Visuals_Application*)_self)->createIcon = (Arcadia_Visuals_Icon* (*)(Arcadia_Thread*, Arcadia_Visuals_Application*, Arcadia_Integer32Value, Arcadia_Integer32Value, Arcadia_Natural8Value, Arcadia_Natural8Value, Arcadia_Natural8Value, Arcadia_Natural8Value))&Arcadia_Visuals_Linux_Application_createIconImpl;
  ((Arcadia_Visuals_Application*)_self)->createWindow = (Arcadia_Visuals_Window* (*)(Arcadia_Thread*, Arcadia_Visuals_Application*))&Arcadia_Visuals_Linux_Application_createWindowImpl;
  ((Arcadia_Visuals_Application*)_self)->getDisplayDevices = (Arcadia_List* (*)(Arcadia_Thread*, Arcadia_Visuals_Application*)) & Arcadia_Visuals_Linux_Application_getDisplayDevicesImpl;
  ((Arcadia_Visuals_Application*)_self)->getQuitRequested = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Visuals_Application*)) & Arcadia_Visuals_Linux_Application_getQuitRequestedImpl;
  ((Arcadia_Visuals_Application*)_self)->setQuitRequested = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Application*,Arcadia_BooleanValue)) & Arcadia_Visuals_Linux_Application_setQuitRequestedImpl;
  ((Arcadia_Visuals_Application*)_self)->update = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Application*)) &Arcadia_Visuals_Linux_Application_updateImpl;
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_Visuals_Linux_Application_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  )
{
  if (self->display) {
    XCloseDisplay(self->display);
    self->display = NULL;
  }
}

static void
Arcadia_Visuals_Linux_Application_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  )
{
  if (self->windows) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->windows);
  }
}

Arcadia_Visuals_Linux_Application*
Arcadia_Visuals_Linux_Application_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Visuals_Linux_Application* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Linux_Application_getType(thread), 0, &argumentValues[0]);
  return self;
}

static void
destroyCallback
  (
    void* argument1,
    void* argument2
  )
{
  g_instance = NULL;
}

Arcadia_Visuals_Linux_Application*
Arcadia_Visuals_Linux_Application_getOrCreate
  (
    Arcadia_Thread* thread
  )
{ 
  if (!g_instance) {
    Arcadia_Visuals_Linux_Application* instance = Arcadia_Visuals_Linux_Application_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}
