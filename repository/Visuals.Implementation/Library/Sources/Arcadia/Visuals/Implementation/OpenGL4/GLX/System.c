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

#include "Arcadia/Visuals/Implementation/OpenGL4/GLX/System.h"

#include "Arcadia/Visuals/Implementation/Linux/DisplayDevice.h"
#include "Arcadia/Visuals/Implementation/Linux/Icon.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/GLX/GlxDeviceInfo.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/GLX/WindowBackend.h"

#include <string.h>

#include "Arcadia/Visuals/Implementation/Linux/_edid.h"

// https://www.x.org/releases/current/doc/index.html
// https://www.x.org/releases/current/doc/randrproto/randrproto.txt
#include <X11/extensions/Xrandr.h>

#if defined(Arcadia_Visuals_Implementation_Configuration_Direct3D12_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_Direct3D12_Backend_Enabled
  #include "Arcadia/Visuals/Direct3D12/Backend.h"
#endif

#if defined(Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled
  #include "Arcadia/Visuals/OpenGL4/Backend.h"
#endif

#if defined(Arcadia_Visuals_Implementation_Configuration_Vulkan_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_Vulkan_Backend_Enabled
  #include "Arcadia/Visuals/Vulkan/Backend.h"
#endif

static Arcadia_Visuals_Implementation_OpenGL4_GLX_System* g_instance = NULL;

static int
errorHandler
  (
    Display *display,
    XErrorEvent *event
  );

static Arcadia_Visuals_Linux_Icon*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    Arcadia_Imaging_PixelBuffer* pixelBuffer
  );

static Arcadia_Visuals_Window*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  );

static Arcadia_Visuals_Linux_DisplayDevice*
getDisplayDevice
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    RROutput outputId,
    RRMode modeId
  );

static Arcadia_List*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_getDisplayDevicesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_mapKeyboardKey
  (
    Arcadia_Thread* thread,
    XKeyEvent* source,
    Arcadia_Visuals_KeyboardKey* target
  );

static Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_findWindow
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    Window x11window
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onKeyPressEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    XKeyEvent* x11event
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onKeyReleaseEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    XKeyEvent* event
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onConfigureNotifyEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    XConfigureEvent* event
  );
  
static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onDeleteWindowEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    XClientMessageEvent* event
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Implementation_OpenGL4_GLX_System_constructImpl,
  .destruct = &Arcadia_Visuals_Implementation_OpenGL4_GLX_System_destruct,
  .visit = &Arcadia_Visuals_Implementation_OpenGL4_GLX_System_visit,
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

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.GLX.System", Arcadia_Visuals_Implementation_OpenGL4_GLX_System,
                         u8"Arcadia.Visuals.System", Arcadia_Visuals_System,
                         &_typeOperations);

static Arcadia_Visuals_Linux_Icon*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    Arcadia_Imaging_PixelBuffer* pixelBuffer
  )
{
  Arcadia_Visuals_Linux_Icon* icon = Arcadia_Visuals_Linux_Icon_create(thread, pixelBuffer);
  return icon;
}

static Arcadia_Visuals_Window*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* windowBackend = Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend_create(thread, self);
  Arcadia_Visuals_Window* window = Arcadia_Visuals_Window_create(thread);
  Arcadia_WeakReference* windowWeakReference =
    Arcadia_WeakReference_create
      (
        thread,
        Arcadia_Value_makeObjectReferenceValue(windowBackend)
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, ((Arcadia_Visuals_System*)self)->windows, (Arcadia_Object*)windowWeakReference);
  window->backend = windowBackend;
  windowBackend->window = window;
  return window;
}

static Arcadia_Visuals_Linux_DisplayDevice*
getDisplayDevice
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
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
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_getDisplayDevicesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  )
{
  Arcadia_List* displayDevices = (Arcadia_List*)Arcadia_ArrayList_create(thread);

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

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_mapKeyboardKey
  (
    Arcadia_Thread* thread,
    XKeyEvent* source,
    Arcadia_Visuals_KeyboardKey* target
  )
{
#define Define(Source, Target) \
  case Source: { \
    *target = Target; \
  } break;


  switch (XLookupKeysym(source, 0)) {
    Define(XK_Escape, Arcadia_Visuals_KeyboardKey_Escape)

    Define(XK_0, Arcadia_Visuals_KeyboardKey_Zero)
    Define(XK_1, Arcadia_Visuals_KeyboardKey_One)
    Define(XK_2, Arcadia_Visuals_KeyboardKey_Two)
    Define(XK_3, Arcadia_Visuals_KeyboardKey_Three)
    Define(XK_4, Arcadia_Visuals_KeyboardKey_Four)
    Define(XK_5, Arcadia_Visuals_KeyboardKey_Five)
    Define(XK_6, Arcadia_Visuals_KeyboardKey_Six)
    Define(XK_7, Arcadia_Visuals_KeyboardKey_Seven)
    Define(XK_8, Arcadia_Visuals_KeyboardKey_Eight)
    Define(XK_9, Arcadia_Visuals_KeyboardKey_Nine)
    
    Define(XK_Left, Arcadia_Visuals_KeyboardKey_Left)
    Define(XK_Up, Arcadia_Visuals_KeyboardKey_Up)
    Define(XK_Right, Arcadia_Visuals_KeyboardKey_Right)
    Define(XK_Down, Arcadia_Visuals_KeyboardKey_Down)
    
    Define(XK_Shift_L, Arcadia_Visuals_KeyboardKey_LeftShift)
    Define(XK_Shift_R, Arcadia_Visuals_KeyboardKey_RightShift)
    Define(XK_Control_L, Arcadia_Visuals_KeyboardKey_LeftControl)
    Define(XK_Control_R, Arcadia_Visuals_KeyboardKey_RightControl)
    Define(XK_Alt_L, Arcadia_Visuals_KeyboardKey_LeftMenu)   
    Define(XK_Alt_R, Arcadia_Visuals_KeyboardKey_RightMenu)     
  
    Define(XK_Page_Down, Arcadia_Visuals_KeyboardKey_PageDown)
    Define(XK_Page_Up, Arcadia_Visuals_KeyboardKey_PageUp)
    
    Define(XK_BackSpace, Arcadia_Visuals_KeyboardKey_Backspace)
    Define(XK_space, Arcadia_Visuals_KeyboardKey_Space)
    Define(XK_Tab, Arcadia_Visuals_KeyboardKey_Tabulator)
    Define(XK_Return, Arcadia_Visuals_KeyboardKey_Return)
    Define(XK_Delete, Arcadia_Visuals_KeyboardKey_Delete)
    Define(XK_Scroll_Lock, Arcadia_Visuals_KeyboardKey_ScrollLock)
    Define(XK_Clear, Arcadia_Visuals_KeyboardKey_Clear)
    Define(XK_Pause, Arcadia_Visuals_KeyboardKey_Pause)
    
    Define(XK_KP_Enter, Arcadia_Visuals_KeyboardKey_NumPadEnter)
    Define(XK_KP_0, Arcadia_Visuals_KeyboardKey_NumPadZero)
    Define(XK_KP_1, Arcadia_Visuals_KeyboardKey_NumPadOne)
    Define(XK_KP_2, Arcadia_Visuals_KeyboardKey_NumPadTwo) 
    Define(XK_KP_3, Arcadia_Visuals_KeyboardKey_NumPadThree)
    Define(XK_KP_4, Arcadia_Visuals_KeyboardKey_NumPadFour)
    Define(XK_KP_5, Arcadia_Visuals_KeyboardKey_NumPadFive)
    Define(XK_KP_6, Arcadia_Visuals_KeyboardKey_NumPadSix)
    Define(XK_KP_7, Arcadia_Visuals_KeyboardKey_NumPadSeven)
    Define(XK_KP_8, Arcadia_Visuals_KeyboardKey_NumPadEight)
    Define(XK_KP_9, Arcadia_Visuals_KeyboardKey_NumPadNine)
    Define(XK_KP_Multiply, Arcadia_Visuals_KeyboardKey_Multiply)   
    Define(XK_KP_Divide, Arcadia_Visuals_KeyboardKey_Divide)
    Define(XK_KP_Add, Arcadia_Visuals_KeyboardKey_Add)
    Define(XK_KP_Subtract, Arcadia_Visuals_KeyboardKey_Subtract)       

    Define(XK_a, Arcadia_Visuals_KeyboardKey_A)
    Define(XK_b, Arcadia_Visuals_KeyboardKey_B)
    Define(XK_c, Arcadia_Visuals_KeyboardKey_C)
    Define(XK_d, Arcadia_Visuals_KeyboardKey_D)
    Define(XK_e, Arcadia_Visuals_KeyboardKey_E)
    Define(XK_f, Arcadia_Visuals_KeyboardKey_F)
    Define(XK_g, Arcadia_Visuals_KeyboardKey_G)
    Define(XK_h, Arcadia_Visuals_KeyboardKey_H)
    Define(XK_i, Arcadia_Visuals_KeyboardKey_I)
    Define(XK_j, Arcadia_Visuals_KeyboardKey_J)
    Define(XK_k, Arcadia_Visuals_KeyboardKey_K)
    Define(XK_l, Arcadia_Visuals_KeyboardKey_L)
    Define(XK_m, Arcadia_Visuals_KeyboardKey_M)
    Define(XK_n, Arcadia_Visuals_KeyboardKey_N)
    Define(XK_o, Arcadia_Visuals_KeyboardKey_O)
    Define(XK_p, Arcadia_Visuals_KeyboardKey_P)
    Define(XK_q, Arcadia_Visuals_KeyboardKey_Q)
    Define(XK_r, Arcadia_Visuals_KeyboardKey_R)
    Define(XK_s, Arcadia_Visuals_KeyboardKey_S)
    Define(XK_t, Arcadia_Visuals_KeyboardKey_T)
    Define(XK_u, Arcadia_Visuals_KeyboardKey_U)
    Define(XK_v, Arcadia_Visuals_KeyboardKey_V)
    Define(XK_w, Arcadia_Visuals_KeyboardKey_W)
    Define(XK_x, Arcadia_Visuals_KeyboardKey_X)
    Define(XK_y, Arcadia_Visuals_KeyboardKey_Y)
    Define(XK_z, Arcadia_Visuals_KeyboardKey_Z)

    Define(XK_A, Arcadia_Visuals_KeyboardKey_A)
    Define(XK_B, Arcadia_Visuals_KeyboardKey_B)
    Define(XK_C, Arcadia_Visuals_KeyboardKey_C)
    Define(XK_D, Arcadia_Visuals_KeyboardKey_D)
    Define(XK_E, Arcadia_Visuals_KeyboardKey_E)
    Define(XK_F, Arcadia_Visuals_KeyboardKey_F)
    Define(XK_G, Arcadia_Visuals_KeyboardKey_G)
    Define(XK_H, Arcadia_Visuals_KeyboardKey_H)
    Define(XK_I, Arcadia_Visuals_KeyboardKey_I)
    Define(XK_J, Arcadia_Visuals_KeyboardKey_J)
    Define(XK_K, Arcadia_Visuals_KeyboardKey_K)
    Define(XK_L, Arcadia_Visuals_KeyboardKey_L)
    Define(XK_M, Arcadia_Visuals_KeyboardKey_M)
    Define(XK_N, Arcadia_Visuals_KeyboardKey_N)
    Define(XK_O, Arcadia_Visuals_KeyboardKey_O)
    Define(XK_P, Arcadia_Visuals_KeyboardKey_P)
    Define(XK_Q, Arcadia_Visuals_KeyboardKey_Q)
    Define(XK_R, Arcadia_Visuals_KeyboardKey_R)
    Define(XK_S, Arcadia_Visuals_KeyboardKey_S)
    Define(XK_T, Arcadia_Visuals_KeyboardKey_T)
    Define(XK_U, Arcadia_Visuals_KeyboardKey_U)
    Define(XK_V, Arcadia_Visuals_KeyboardKey_V)
    Define(XK_W, Arcadia_Visuals_KeyboardKey_W)
    Define(XK_X, Arcadia_Visuals_KeyboardKey_X)
    Define(XK_Y, Arcadia_Visuals_KeyboardKey_Y)
    Define(XK_Z, Arcadia_Visuals_KeyboardKey_Z)
    
    Define(XK_F1, Arcadia_Visuals_KeyboardKey_F1)
    Define(XK_F10, Arcadia_Visuals_KeyboardKey_F10)
    Define(XK_F11, Arcadia_Visuals_KeyboardKey_F11)
    Define(XK_F12, Arcadia_Visuals_KeyboardKey_F12)
    Define(XK_F13, Arcadia_Visuals_KeyboardKey_F13)
    Define(XK_F14, Arcadia_Visuals_KeyboardKey_F14)
    Define(XK_F15, Arcadia_Visuals_KeyboardKey_F15)
    Define(XK_F16, Arcadia_Visuals_KeyboardKey_F16)
    Define(XK_F17, Arcadia_Visuals_KeyboardKey_F17)
    Define(XK_F18, Arcadia_Visuals_KeyboardKey_F18)
    Define(XK_F19, Arcadia_Visuals_KeyboardKey_F19)
    Define(XK_F2, Arcadia_Visuals_KeyboardKey_F2)
    Define(XK_F20, Arcadia_Visuals_KeyboardKey_F20)
    Define(XK_F21, Arcadia_Visuals_KeyboardKey_F21)
    Define(XK_F22, Arcadia_Visuals_KeyboardKey_F22)
    Define(XK_F23, Arcadia_Visuals_KeyboardKey_F23)
    Define(XK_F24, Arcadia_Visuals_KeyboardKey_F24)

    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NotImplemented);
      Arcadia_Thread_popJumpTarget(thread);
    } break;
  };
  #undef Define
}

static Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_findWindow
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    Window x11window
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)((Arcadia_Visuals_System*)self)->windows); i < n; ++i) {
    Arcadia_WeakReference* weakReference = (Arcadia_WeakReference*)Arcadia_List_getObjectReferenceValueAt(thread, ((Arcadia_Visuals_System*)self)->windows, i);
    Arcadia_Value value = Arcadia_WeakReference_getValue(thread, weakReference);
    if (Arcadia_Value_isObjectReferenceValue(&value)) {
      Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* window = (Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend*)Arcadia_Value_getObjectReferenceValue(&value);
      if (window->window == x11window) {
        return window;
      }
    }
  }
  return NULL;  
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onKeyPressEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    XKeyEvent* x11event
  )
{  
  Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* windowBackend = Arcadia_Visuals_Implementation_OpenGL4_GLX_System_findWindow(thread, self, x11event->window);
  if (!windowBackend) {
    return;
  }
  Arcadia_Visuals_KeyboardKey keyboardKey; 
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System_mapKeyboardKey(thread, x11event, &keyboardKey);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Engine_Event* event =
    (Arcadia_Engine_Event*)
    Arcadia_Visuals_KeyboardKeyEvent_create
      (
        thread,
        Arcadia_getTickCount(thread),
        Arcadia_Visuals_KeyboardKeyAction_Pressed,
        keyboardKey
      );
  Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onKeyReleaseEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    XKeyEvent* x11event
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* windowBackend = Arcadia_Visuals_Implementation_OpenGL4_GLX_System_findWindow(thread, self, x11event->window);
  if (!windowBackend) {
    return;
  }
  Arcadia_Visuals_Window* window = windowBackend->window;
  if (!window) {
    return;
  }
  Arcadia_Visuals_KeyboardKey keyboardKey; 
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System_mapKeyboardKey(thread, x11event, &keyboardKey);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Engine_Event* event =
    (Arcadia_Engine_Event*)
    Arcadia_Visuals_KeyboardKeyEvent_create
      (
        thread,
        Arcadia_getTickCount(thread),
        Arcadia_Visuals_KeyboardKeyAction_Released,
        keyboardKey
      );
  Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onConfigureNotifyEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    XConfigureEvent* x11event
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* windowBackend = Arcadia_Visuals_Implementation_OpenGL4_GLX_System_findWindow(thread, self, x11event->window);
  if (!windowBackend) {
    return;
  }
  Arcadia_Visuals_Window* window = windowBackend->window;
  if (!window) {
    return;
  }
  int left = x11event->x;
  int top = x11event->y;
  int width = x11event->width + x11event->border_width * 2;
  int height = x11event->height + x11event->border_width * 2;
  bool positionChanged = false,
       sizeChanged = false;
  if (((Arcadia_Visuals_WindowBackend*)windowBackend)->bounds.left != left ||
      ((Arcadia_Visuals_WindowBackend*)windowBackend)->bounds.top != top) {
    ((Arcadia_Visuals_WindowBackend*)windowBackend)->bounds.left = left;
    ((Arcadia_Visuals_WindowBackend*)windowBackend)->bounds.top = top;
    positionChanged = true;
  }
  if (((Arcadia_Visuals_WindowBackend*)windowBackend)->bounds.width != width ||
      ((Arcadia_Visuals_WindowBackend*)windowBackend)->bounds.height != height) {
    ((Arcadia_Visuals_WindowBackend*)windowBackend)->bounds.width = width;
    ((Arcadia_Visuals_WindowBackend*)windowBackend)->bounds.height = height;
    sizeChanged = true;
  }
  if (positionChanged) {
    Arcadia_Engine_Event* event =
      (Arcadia_Engine_Event*)
      Arcadia_Visuals_WindowPositionChangedEvent_create
        (
          thread,
          Arcadia_getTickCount(thread),
          window,
          left,
          top
        );
    Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
  }
  if (sizeChanged) {
    Arcadia_Engine_Event* event =
      (Arcadia_Engine_Event*)
      Arcadia_Visuals_WindowSizeChangedEvent_create
        (
          thread,
          Arcadia_getTickCount(thread),
          window,
          width,
          height
        );
    Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onDeleteWindowEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self,
    XClientMessageEvent* x11event
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_GLX_WindowBackend* windowBackend = Arcadia_Visuals_Implementation_OpenGL4_GLX_System_findWindow(thread, self, x11event->window);
  if (!windowBackend) {
    return;
  }
  Arcadia_Visuals_Window* window = windowBackend->window;
  if (!window) {
    return;
  }
  Arcadia_Engine_Event* event =
    (Arcadia_Engine_Event*)
    Arcadia_Visuals_WindowClosedEvent_create
      (
        thread,
        Arcadia_getTickCount(thread),
        window
      );
  Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
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
          Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onConfigureNotifyEvent(thread, self, &event.xconfigure);
          Arcadia_Thread_popJumpTarget(thread);
        } else {
          Arcadia_Thread_popJumpTarget(thread);
        }
      } break;
      case KeyPress: {
        Arcadia_JumpTarget jumpTarget;
        Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
        if (Arcadia_JumpTarget_save(&jumpTarget)) {
          Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onKeyPressEvent(thread, self, &event.xkey);
          Arcadia_Thread_popJumpTarget(thread);
        } else {
          Arcadia_Thread_popJumpTarget(thread);
        }
      } break;
      case KeyRelease: {
        Arcadia_JumpTarget jumpTarget;
        Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
        if (Arcadia_JumpTarget_save(&jumpTarget)) {
          Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onKeyReleaseEvent(thread, self, &event.xkey);
          Arcadia_Thread_popJumpTarget(thread);
        } else {
          Arcadia_Thread_popJumpTarget(thread);
        }
      } break;
      case ClientMessage: {
        if ((Atom)event.xclient.data.l[0] == self->WM_DELETE_WINDOW) {
          Arcadia_Visuals_Implementation_OpenGL4_GLX_System_onDeleteWindowEvent(thread, self, &event.xclient);
        }
      } break;
    };
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_GLX_System* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_GLX_System_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  // (1) Open the default display.
  _self->display = XOpenDisplay(NULL);
  if (!_self->display) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // (2) Ensure the XRANDR extension is present. Determine its event base and its error base.
  int dummy;
  if (!XQueryExtension(_self->display, "RANDR", &dummy, &dummy, &dummy)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!XRRQueryExtension(_self->display, &_self->xrandr.eventBase, &_self->xrandr.errorBase)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // (3) Create WM_DELETE_WINDOW atom.
  _self->WM_DELETE_WINDOW = XInternAtom(_self->display, "WM_DELETE_WINDOW", False);
  if (_self->WM_DELETE_WINDOW == None) {
    _self->xrandr.errorBase = 0;
    _self->xrandr.eventBase = 0;
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // (4) Create _NET_WM_ICON atom.
  _self->_NET_WM_ICON = XInternAtom(_self->display, "_NET_WM_ICON", False);
  if (_self->_NET_WM_ICON == None) {
    _self->WM_DELETE_WINDOW = 0;
    _self->xrandr.errorBase = 0;
    _self->xrandr.eventBase = 0;
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // (5) Create _NET_FRAME_EXTENTS atom.
  _self->_NET_FRAME_EXTENTS = XInternAtom(_self->display, "_NET_FRAME_EXTENTS", False);
  if (_self->_NET_FRAME_EXTENTS == None) {
    _self->_NET_WM_ICON = 0;
    _self->WM_DELETE_WINDOW = 0;
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  // (6) Create _MOTIF_WM_HINTS atom.
  _self->_MOTIF_WM_HINTS = XInternAtom(_self->display, "_MOTIF_WM_HINTS", False);
  if (_self->_MOTIF_WM_HINTS == None) {
    _self->_NET_FRAME_EXTENTS = 0;
    _self->_NET_WM_ICON = 0;
    _self->WM_DELETE_WINDOW = 0;
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  
  // (7) Register backends.
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {  
  #if defined(Arcadia_Visuals_Implementation_Configuration_Direct3D12_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_Direct3D12_Backend_Enabled
    Arcadia_List_insertBack(thread, ((Arcadia_Visuals_System*)_self)->backends, Arcadia_Value_makeObjectReferenceValue(Arcadia_Visuals_Direct3D12_Backend_create(thread)));
  #endif
  #if defined(Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled
    Arcadia_List_insertBack(thread, ((Arcadia_Visuals_System*)_self)->backends, Arcadia_Value_makeObjectReferenceValue(Arcadia_Visuals_OpenGL4_Backend_create(thread)));
  #endif
  #if defined(Arcadia_Visuals_Implementation_Configuration_Vulkan_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_Vulkan_Backend_Enabled
    Arcadia_List_insertBack(thread, ((Arcadia_Visuals_System*)_self)->backends, Arcadia_Value_makeObjectReferenceValue(Arcadia_Visuals_Vulkan_Backend_create(thread)));
  #endif
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    _self->_MOTIF_WM_HINTS = 0;
    _self->_NET_FRAME_EXTENTS = 0;
    _self->_NET_WM_ICON = 0;
    _self->WM_DELETE_WINDOW = 0;
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_jump(thread);
  }
  ((Arcadia_Visuals_System*)_self)->createIcon = (Arcadia_Visuals_Icon* (*)(Arcadia_Thread*, Arcadia_Visuals_System*, Arcadia_Imaging_PixelBuffer*))&Arcadia_Visuals_Implementation_OpenGL4_GLX_System_createIconImpl;
  ((Arcadia_Visuals_System*)_self)->createWindow = (Arcadia_Visuals_Window* (*)(Arcadia_Thread*, Arcadia_Visuals_System*))&Arcadia_Visuals_Implementation_OpenGL4_GLX_System_createWindowImpl;
  ((Arcadia_Visuals_System*)_self)->getDisplayDevices = (Arcadia_List* (*)(Arcadia_Thread*, Arcadia_Visuals_System*)) & Arcadia_Visuals_Implementation_OpenGL4_GLX_System_getDisplayDevicesImpl;
  ((Arcadia_Visuals_System*)_self)->update = (void(*)(Arcadia_Thread*, Arcadia_Visuals_System*)) &Arcadia_Visuals_Implementation_OpenGL4_GLX_System_updateImpl;
  Arcadia_Object_setType(thread, _self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  )
{
  self->_MOTIF_WM_HINTS = 0;
  self->_NET_FRAME_EXTENTS = 0;
  self->_NET_WM_ICON = 0;
  self->WM_DELETE_WINDOW = 0;
  if (self->display) {
    XCloseDisplay(self->display);
    self->display = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* self
  )
{ }

Arcadia_Visuals_Implementation_OpenGL4_GLX_System*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_GLX_System);
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

Arcadia_Visuals_Implementation_OpenGL4_GLX_System*
Arcadia_Visuals_Implementation_OpenGL4_GLX_System_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_Visuals_Implementation_OpenGL4_GLX_System* instance = Arcadia_Visuals_Implementation_OpenGL4_GLX_System_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}
