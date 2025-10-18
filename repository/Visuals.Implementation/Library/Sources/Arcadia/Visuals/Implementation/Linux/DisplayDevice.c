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

#include "Arcadia/Visuals/Implementation/Linux/DisplayDevice.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/GLX/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Linux/DisplayMode.h"

static void
Arcadia_Visuals_Linux_DisplayDevice_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );

static void
Arcadia_Visuals_Linux_DisplayDevice_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );

static void
makeDisplayModes
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self,
    XRRScreenResources* screenResources,
    XRROutputInfo* outputInfo,
    Arcadia_List* displayModes
  );

static Arcadia_List*
Arcadia_Visuals_Linux_DisplayDevice_getAvailableDisplayModesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );

static Arcadia_String*
Arcadia_Visuals_Linux_DisplayDevice_getIdImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );

static Arcadia_String*
Arcadia_Visuals_Linux_DisplayDevice_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );

static void
Arcadia_Visuals_Linux_DisplayDevice_getBoundsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_DisplayDevice_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Linux_DisplayDevice_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.DisplayDevice", Arcadia_Visuals_Linux_DisplayDevice,
                         u8"Arcadia.Visuals.DisplayDevice", Arcadia_Visuals_DisplayDevice,
                         &_typeOperations);

static void
Arcadia_Visuals_Linux_DisplayDevice_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_DisplayDevice_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 3 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext_getType(thread));
  self->id = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  self->output = 0;
  self->mode = 0;

  ((Arcadia_Visuals_DisplayDevice*)self)->getAvailableDisplayModes = (Arcadia_List* (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Linux_DisplayDevice_getAvailableDisplayModesImpl;
  ((Arcadia_Visuals_DisplayDevice*)self)->getId = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Linux_DisplayDevice_getIdImpl;
  ((Arcadia_Visuals_DisplayDevice*)self)->getName = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Linux_DisplayDevice_getNameImpl;
  ((Arcadia_Visuals_DisplayDevice*)self)->getBounds = (void (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*, Arcadia_Integer32Value*, Arcadia_Integer32Value*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & Arcadia_Visuals_Linux_DisplayDevice_getBoundsImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 3 + 1);
}

static void
Arcadia_Visuals_Linux_DisplayDevice_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{
  if (self->backendContext) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->backendContext);
  }
  if (self->id) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->id);
  }
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
}

static void
makeDisplayMode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self,
    XRRScreenResources* screenResources,
    RRCrtc crtc,
    RRMode modeId,
    Arcadia_List* displayModes
  )
{
  int defaultScreen = DefaultScreen(self->backendContext->display);
  int defaultColorDepth = DefaultDepth(self->backendContext->display, defaultScreen);

  const XRRModeInfo* modeInfo = NULL;
  for (int i = 0; i < screenResources->nmode; ++i) {
    const XRRModeInfo* currentModeInfo = &(screenResources->modes[i]);
    if (currentModeInfo->id == modeId) {
      modeInfo = currentModeInfo;
      break;
    }
  }
  if (!modeInfo) {
    return;
  }
  Rotation rotation = 0;
  XFixed scaleWidth = 0x10000, scaleHeight = 0x10000;
  int width = 0, height = 0;
  int refreshRateNumerator, refreshRateDenominator;
  {
    XRRCrtcInfo* crtcInfo = XRRGetCrtcInfo(self->backendContext->display, screenResources, crtc);
    if (crtcInfo) {
      rotation = crtcInfo->rotation;
      XRRFreeCrtcInfo(crtcInfo);
      crtcInfo = NULL;
    }
  }
  {
    XRRCrtcTransformAttributes *crtcTransformAttributes = NULL;
    if (XRRGetCrtcTransform(self->backendContext->display, crtc, &crtcTransformAttributes) && crtcTransformAttributes) {
      scaleWidth = crtcTransformAttributes->currentTransform.matrix[0][0];
      scaleHeight = crtcTransformAttributes->currentTransform.matrix[1][1];
      XFree(crtcTransformAttributes);
      crtcTransformAttributes = NULL;
    }
  }
  {
    static const int RR_RotationLeft = (1 << 1);
    static const int RR_RotationRight = (1 << 3);
    if (rotation & (RR_RotationLeft | RR_RotationRight)) {
      width = (modeInfo->height * scaleWidth + 0xffff) >> 16;
      height = (modeInfo->width * scaleHeight + 0xffff) >> 16;
    } else {
      width = (modeInfo->width * scaleWidth + 0xffff) >> 16;
      height = (modeInfo->height * scaleHeight + 0xffff) >> 16;
    }
  }
  {
    int vTotal = modeInfo->vTotal;
    if (modeInfo->modeFlags & RR_DoubleScan) {
      // "doublescan" doubles scan lines.
      vTotal *= 2;
    }
    if (modeInfo->modeFlags & RR_Interlace) {
      // "interlace" halfs scan lines.
      vTotal /= 2;
    }
    if (modeInfo->hTotal && vTotal) {
      refreshRateNumerator = modeInfo->dotClock;
      refreshRateDenominator = (modeInfo->hTotal * vTotal);
    } else {
      return; // Ignore that one.
    }
    Arcadia_Visuals_Linux_DisplayMode* displayMode =
      Arcadia_Visuals_Linux_DisplayMode_create
        (
          thread,
          self,
          width,
          height,
          defaultColorDepth,
          refreshRateNumerator / refreshRateDenominator
        );
    displayMode->modeId = modeInfo->id;
    Arcadia_List_insertBackObjectReferenceValue(thread, displayModes, displayMode);
  }
}

static Arcadia_List*
Arcadia_Visuals_Linux_DisplayDevice_getAvailableDisplayModesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{
  Arcadia_List* displayModes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Window rootWindow = XDefaultRootWindow(self->backendContext->display);
  XRRScreenResources* screenResources = XRRGetScreenResources(self->backendContext->display, rootWindow);
  XRROutputInfo *outputInfo = XRRGetOutputInfo(self->backendContext->display, screenResources, self->output);
  if (outputInfo && outputInfo->connection != RR_Disconnected) {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      for (int i = 0; i < outputInfo->nmode; ++i) {
        makeDisplayMode(thread, self, screenResources, outputInfo->crtc, outputInfo->modes[i], displayModes);
      }
      XRRFreeOutputInfo(outputInfo);
      XRRFreeScreenResources(screenResources);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      XRRFreeOutputInfo(outputInfo);
      XRRFreeScreenResources(screenResources);
      Arcadia_Thread_jump(thread);
    }
  }
  return displayModes;
}

static Arcadia_String*
Arcadia_Visuals_Linux_DisplayDevice_getIdImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{ return self->id; }

static Arcadia_String*
Arcadia_Visuals_Linux_DisplayDevice_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{ return self->name; }

static void
Arcadia_Visuals_Linux_DisplayDevice_getBoundsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  )
{
  *left = self->bounds.left;
  *top = self->bounds.top;
  *right = self->bounds.right;
  *bottom = self->bounds.bottom;
}

Arcadia_Visuals_Linux_DisplayDevice*
Arcadia_Visuals_Linux_DisplayDevice_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext* backendContext,
    Arcadia_String* id,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (id) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, id);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Linux_DisplayDevice);
}

/// @brief Update the device bounds from the backend.
/// @param thread A pointer to this thread.
/// @param self A pointer to this device.
void
Arcadia_Visuals_Linux_DisplayDevice_updateBounds
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{
  Window rootWindow = XDefaultRootWindow(self->backendContext->display);
  XRRScreenResources* screenResources = XRRGetScreenResources(self->backendContext->display, rootWindow);
  if (!screenResources) {
    Arcadia_StringBuffer* buffer = Arcadia_StringBuffer_create(thread);
    Arcadia_StringBuffer_insertBackCxxString(thread, buffer, __FILE__);
    Arcadia_StringBuffer_insertBackCxxString(thread, buffer, u8":");
    Arcadia_StringBuffer_insertBackCxxInt(thread, buffer, __LINE__);
    Arcadia_StringBuffer_insertBackCxxString(thread, buffer, u8": ");
    Arcadia_StringBuffer_insertBackCxxString(thread, buffer, u8"XRRGetScreenResources");
    Arcadia_StringBuffer_insertBackCxxString(thread, buffer, u8" failed\n");
    fwrite(Arcadia_StringBuffer_getBytes(thread, buffer), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, buffer), stdout);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  XRROutputInfo *outputInfo = XRRGetOutputInfo(self->backendContext->display, screenResources, self->output);
  if (!outputInfo) {
    XRRFreeScreenResources(screenResources);
    screenResources = NULL;
    fprintf(stderr, u8"%s:%d: %s failed\n", __FILE__, __LINE__, u8"XRRGetOutputInfo");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  XRRCrtcInfo *crtcInfo = XRRGetCrtcInfo(self->backendContext->display, screenResources, outputInfo->crtc);
  if (!crtcInfo) {
    XRRFreeOutputInfo(outputInfo);
    outputInfo = NULL;
    XRRFreeScreenResources(screenResources);
    screenResources = NULL;
    fprintf(stderr, u8"%s:%d: %s failed\n", __FILE__, __LINE__, u8"XRRGetCrtcInfo");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  self->bounds.left = crtcInfo->x;
  self->bounds.top = crtcInfo->y;
  self->bounds.right = crtcInfo->x + crtcInfo->width;
  self->bounds.bottom = crtcInfo->y + crtcInfo->height;

  XRRFreeCrtcInfo(crtcInfo);
  crtcInfo = NULL;
  XRRFreeOutputInfo(outputInfo);
  outputInfo = NULL;
  XRRFreeScreenResources(screenResources);
  screenResources = NULL;
}
